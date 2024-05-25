// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatCharacter.h"
#include "GameInstance/CatRunnerGameInstance.h"

void ACatCharacter::StateRotate::OnBegin(ACatCharacter* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	// tmp init actor location.
	InitStateLocation = StateOwner->GetActorLocation();

	// SE再生
	const bool bIsRotateL = StateOwner->GetCurrentState() == ECatState::RotateL;
	const auto RotateSound = bIsRotateL ? StateOwner->RotateLSound : StateOwner->RotateRSound;
	UCatRunnerGameInstance::GetAudioService()->PlaySe3d(RotateSound, StateOwner->GetActorLocation());
}

void ACatCharacter::StateRotate::OnTick(ACatCharacter* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	// 回転が右左どちらの方向か？
	const bool bIsRotateL = StateOwner->GetCurrentState() == ECatState::RotateL;

	// 移動後の位置を計算
	FVector CurrentLocation = StateOwner->GetActorLocation();
	const float MoveVelocity = bIsRotateL ? -StateOwner->MoveRotateSpeed : StateOwner->MoveRotateSpeed;
	CurrentLocation += StateOwner->GetActorRightVector() * MoveVelocity * DeltaTime;

	// 目的位置
	const float MoveDistance = bIsRotateL ? -StateOwner->MoveRotateDistance : StateOwner->MoveRotateDistance;
	const FVector Destination = InitStateLocation + StateOwner->GetActorRightVector() * MoveDistance;

	// 到着したかのチェック
	constexpr float AllowDistance = 30.0f;
	const FVector DiffRightLocation = (Destination - CurrentLocation) * StateOwner->GetActorRightVector().GetAbs();
	if (DiffRightLocation.Length() <= AllowDistance)
	{
		CurrentLocation += DiffRightLocation;
		CurrentLocation.Z = InitStateLocation.Z; // 念のため...
		StateOwner->ChangeState(ECatState::Run);
	}

	// 計算した位置を設定
	StateOwner->SetActorLocation(CurrentLocation);
}

void ACatCharacter::StateRotate::OnEnd(ACatCharacter* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
