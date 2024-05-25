// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CatCharacterState.h"
#include "GameFramework/Character.h"
#include "StateMachine/StateMachine.h"
#include "Logging/LogMacros.h"
#include "CatCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 * ねこクラス
 */
UCLASS(config=Game)
class ACatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACatCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** 角を曲げる */
	void OnTurnCorner(const FRotator& ChangeRotator, const FVector& StartPoint);

	/** 死亡させる */
	void OnDie() const;

	/** 現在のステート取得 */
	UFUNCTION(BlueprintPure, Category = "CatRunner: Cat")
	ECatState GetCurrentState() const;

	/** ステート変更時のイベント */
	DECLARE_DELEGATE_OneParam(FChangeCatStateDelegate, ECatState);
	FChangeCatStateDelegate OnChangeCatStateDelegate;

	/** アクタ衝突時のイベント */
	DECLARE_DELEGATE_TwoParams(FHitActorDelegate, ACatCharacter*, AActor*);
	FHitActorDelegate OnHitActorDelegate;

	/** 前進スピードの加算 */
	void AddForwardSpeed(const float AddSpeed) { CurrentMoveForwardSpeed += AddSpeed; }

	/** Getter */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Setter */
	FORCEINLINE void SetIsReadyMove(const bool IsReadyMove) { bIsReadyMove = IsReadyMove; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Input Trigger Events */
	void InputJump();
	void InputRotateL();
	void InputRotateR();
	void InputRotate(const ECatState InputState) const;
	void InputSquat();
	void InputSquatCanceled();

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Rotate L Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RotateLAction;

	/** Rotate R Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RotateRAction;

	/** Squat Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SquatAction;

	/** Sound RotateL */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> RotateLSound;

	/** Sound RotateR */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> RotateRSound;

	/** Sound Jump */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> JumpSound;

	/** CameraBoom - SocketOffsetの初期位置 */
	FVector InitCameraBoomSocketOffset;

	/** 前進する初期速度 */
	const float InitMoveForwardSpeed = 500.0f;

	/** 横回転する最大距離 */
	const float MoveRotateDistance = 200.0f;

	/** 横回転する速度 */
	const float MoveRotateSpeed = 1200.0f;

	/** 前進する速度 */
	float CurrentMoveForwardSpeed;

	/** コーナー開始地点 */
	FVector StartTurnCornerPoint;

	/** コーナーによる変更回転量 */
	FRotator ChangeTurnCornerRotator;

	/** 移動の準備ができたか？ */
	bool bIsReadyMove;

	/** しゃがむアクション入力が有効か？ */
	bool bIsPushSquat;

	/** 衝突開始イベント */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	/** ステートマシン */
	TUniquePtr<ZStateMachine<ACatCharacter>> StateMachine;

	/** 現在のステート変更処理 */
	void ChangeState(ECatState State) const;

	/**
	 * State: 待機
	 */
	class StateWait : public ZStateBase<ACatCharacter>
	{
	public:
		virtual void OnBegin(ACatCharacter* StateOwner) override;
		virtual void OnTick(ACatCharacter* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ACatCharacter* StateOwner) override;
	};

	/**
	 * State: 走る
	 */
	class StateRun : public ZStateBase<ACatCharacter>
	{
	public:
		virtual void OnBegin(ACatCharacter* StateOwner) override;
		virtual void OnTick(ACatCharacter* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ACatCharacter* StateOwner) override;

	private:
		/** SocketOffsetの初期位置 */
		FVector MoveFromCameraBoomSocketOffset;

		/** SocketOffsetの移動先 */
		FVector MoveToCameraBoomSocketOffset;

		/** 累計ステート時間 */
		float TotalStateTime = 0.0f;

		/** 移動が完了したか？ */
		bool bIsCompleteMoveCamera = false;

		/** 移動させる時間 */
		const float MoveCameraDuration = 0.1f;
	};

	/**
	 * State: ジャンプ
	 */
	class StateJump : public ZStateBase<ACatCharacter>
	{
	public:
		virtual void OnBegin(ACatCharacter* StateOwner) override;
		virtual void OnTick(ACatCharacter* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ACatCharacter* StateOwner) override;
	};

	/**
	 * State: 回転中
	 */
	class StateRotate : public ZStateBase<ACatCharacter>
	{
	public:
		virtual void OnBegin(ACatCharacter* StateOwner) override;
		virtual void OnTick(ACatCharacter* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ACatCharacter* StateOwner) override;

	private:
		/** ステート開始時の初期位置 */
		FVector InitStateLocation;

	};

	/**
	 * State: しゃがむ
	 */
	class StateSquat : public ZStateBase<ACatCharacter>
	{
	public:
		virtual void OnBegin(ACatCharacter* StateOwner) override;
		virtual void OnTick(ACatCharacter* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ACatCharacter* StateOwner) override;

	private:
		/** SocketOffsetを移動させる量 */
		const FVector OffsetMoveCameraSocketOffset = FVector(0.0f, 0.0f, -100.0f);

		/** SocketOffsetの初期位置 */
		FVector MoveFromCameraBoomSocketOffset;

		/** SocketOffsetの移動先 */
		FVector MoveToCameraBoomSocketOffset;

		/** 累計ステート時間 */
		float TotalStateTime = 0.0f;

		/** 移動が完了したか？ */
		bool bIsCompleteMoveCamera = false;

		/** 移動させる時間 */
		const float MoveCameraDuration = 0.2f;
	};

	/**
	 * State: まがる
	 */
	class StateTurnCorner : public ZStateBase<ACatCharacter>
	{
	public:
		virtual void OnBegin(ACatCharacter* StateOwner) override;
		virtual void OnTick(ACatCharacter* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ACatCharacter* StateOwner) override;

	private:
		/** コーナーに到着したか？ */
		bool bIsArriveTurnCorner = false;

		/** 視点カメラに加える回転量 */
		const FRotator LookCameraExtendRotator = FRotator(0.0f, 30.0f, 0.0f);

		/** 視点カメラの継続時間 */
		const float LookCameraDuration = 1.0f;

		/** 視点カメラの累計時間 */
		float TotalLookCameraDuration = 0.0f;
	};

	/**
	 * State: 死亡
	 */
	class StateDead : public ZStateBase<ACatCharacter>
	{
	public:
		virtual void OnBegin(ACatCharacter* StateOwner) override;
		virtual void OnTick(ACatCharacter* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ACatCharacter* StateOwner) override;
	};

};
