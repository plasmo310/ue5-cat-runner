// Copyright (c) 2024, CatRunner All Rights Reserved.

#include "Cat/CatCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACatRunnerCharacter

ACatCharacter::ACatCharacter()
	:CurrentMoveForwardSpeed(0.0f)
	,StartTurnCornerPoint(FVector::ZeroVector)
	,ChangeTurnCornerRotator(FRotator::ZeroRotator)
	,bIsReadyMove(false)
	,bIsPushSquat(false)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(50.f, 50.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACatCharacter::OnOverlapBegin); // setup overlap event.
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 200.0f);

	// Create FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
}

void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// カメラ位置を保持
	InitCameraBoomSocketOffset = CameraBoom->SocketOffset;

	// 前方への移動速度を設定
	CurrentMoveForwardSpeed = InitMoveForwardSpeed;

	// 最初のポイントを設定
	StartTurnCornerPoint = GetActorLocation();

	// ステート初期化
	StateMachine = MakeUnique<ZStateMachine<ACatCharacter>>(this);
	StateMachine->Add<StateWait>(static_cast<int>(ECatState::Wait));
	StateMachine->Add<StateRun>(static_cast<int>(ECatState::Run));
	StateMachine->Add<StateJump>(static_cast<int>(ECatState::Jump));
	StateMachine->Add<StateRotate>(static_cast<int>(ECatState::RotateL));
	StateMachine->Add<StateRotate>(static_cast<int>(ECatState::RotateR));
	StateMachine->Add<StateSquat>(static_cast<int>(ECatState::Squat));
	StateMachine->Add<StateTurnCorner>(static_cast<int>(ECatState::TurnCorner));
	StateMachine->Add<StateDead>(static_cast<int>(ECatState::Dead));
	StateMachine->OnBegin(static_cast<int>(ECatState::Wait));
}

void ACatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 常に前に進む
	if (GetCurrentState() != ECatState::Wait
		&& GetCurrentState() != ECatState::Dead)
	{
		const FVector MoveLocation = GetActorLocation() + GetActorForwardVector() * CurrentMoveForwardSpeed * DeltaTime;
		SetActorLocation(MoveLocation);
	}

	// ステート更新
	StateMachine->OnTick(DeltaTime);
}

void ACatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent == nullptr)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		return;
	}

	// Jumping
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACatCharacter::InputJump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	// Rotate
	EnhancedInputComponent->BindAction(RotateLAction, ETriggerEvent::Started, this, &ACatCharacter::InputRotateL);
	EnhancedInputComponent->BindAction(RotateRAction, ETriggerEvent::Started, this, &ACatCharacter::InputRotateR);

	// Squat
	EnhancedInputComponent->BindAction(SquatAction, ETriggerEvent::Started, this, &ACatCharacter::InputSquat);
	EnhancedInputComponent->BindAction(SquatAction, ETriggerEvent::Completed, this, &ACatCharacter::InputSquatCanceled);
}

void ACatCharacter::InputJump()
{
	// Runステート時のみが対象
	if (GetCurrentState() != ECatState::Run)
	{
		return;
	}

	// ステート変更
	ChangeState(ECatState::Jump);
	Super::Jump();
}

void ACatCharacter::InputRotateL()
{
	InputRotate(ECatState::RotateL);
}

void ACatCharacter::InputRotateR()
{
	InputRotate(ECatState::RotateR);
}

void ACatCharacter::InputRotate(const ECatState InputState) const
{
	if (InputState != ECatState::RotateL && InputState != ECatState::RotateR)
	{
		return;
	}

	// Run、Squatステートのみが対象
	const ECatState CurrentState = GetCurrentState();
	if (CurrentState != ECatState::Run && CurrentState != ECatState::Squat)
	{
		return;
	}

	// 最大移動距離を超えていないか？
	const float MoveDistance = InputState == ECatState::RotateL ? -MoveRotateDistance : MoveRotateDistance;
	const FVector MaxRotateLocation = StartTurnCornerPoint + GetActorRightVector() * MoveDistance;
	const FVector DiffRightLocation = (MaxRotateLocation - GetActorLocation()) * GetActorRightVector();
	if (DiffRightLocation.Length() <= MoveRotateDistance * 0.5f)
	{
		return;
	}

	// ステート変更
	ChangeState(InputState);
}

void ACatCharacter::InputSquat()
{
	bIsPushSquat = true;
}

void ACatCharacter::InputSquatCanceled()
{
	bIsPushSquat = false;
}

void ACatCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// イベント発行
	if (OnHitActorDelegate.IsBound())
	{
		OnHitActorDelegate.Execute(this, OtherActor);
	}
}

void ACatCharacter::OnTurnCorner(const FRotator& ChangeRotator, const FVector& StartPoint)
{
	// TurnCornerステートに変更
	ChangeTurnCornerRotator = ChangeRotator;
	StartTurnCornerPoint = StartPoint;
	ChangeState(ECatState::TurnCorner);
}

void ACatCharacter::OnDie() const
{
	ChangeState(ECatState::Dead);
}

ECatState ACatCharacter::GetCurrentState() const
{
	if (StateMachine == nullptr)
	{
		return ECatState::None;
	}
	return static_cast<ECatState>(StateMachine->GetCurrentStateId());
}

void ACatCharacter::ChangeState(ECatState State) const
{
	StateMachine->ChangeState(static_cast<int>(State));

	// イベント発行
	if (OnChangeCatStateDelegate.IsBound())
	{
		OnChangeCatStateDelegate.Execute(State);
	}
}
