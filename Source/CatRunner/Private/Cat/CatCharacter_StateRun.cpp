// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void ACatCharacter::StateRun::OnBegin(ACatCharacter* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	TotalStateTime = 0.0f;
	bIsCompleteMoveCamera = false;

	// カメラの移動先を設定(元の視点に戻す)
	MoveFromCameraBoomSocketOffset = StateOwner->GetCameraBoom()->SocketOffset;
	MoveToCameraBoomSocketOffset = StateOwner->InitCameraBoomSocketOffset;
}

void ACatCharacter::StateRun::OnTick(ACatCharacter* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	TotalStateTime += DeltaTime;

	// しゃがみアクションが入力されているか？
	if (StateOwner->bIsPushSquat)
	{
		StateOwner->ChangeState(ECatState::Squat);
		return;
	}

	// カメラの移動
	if (!bIsCompleteMoveCamera)
	{
		float Ratio = TotalStateTime / MoveCameraDuration;
		if (Ratio >= 1.0f)
		{
			Ratio = 1.0f;
			bIsCompleteMoveCamera = true;
		}
		StateOwner->GetCameraBoom()->SocketOffset = FMath::Lerp(MoveFromCameraBoomSocketOffset, MoveToCameraBoomSocketOffset, Ratio);
	}
}

void ACatCharacter::StateRun::OnEnd(ACatCharacter* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
