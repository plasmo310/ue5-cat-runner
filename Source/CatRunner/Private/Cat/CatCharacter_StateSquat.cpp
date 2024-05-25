// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void ACatCharacter::StateSquat::OnBegin(ACatCharacter* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	TotalStateTime = 0.0f;
	bIsCompleteMoveCamera = false;

	// カメラの移動先を設定(しゃがみに合わせて少し下にする)
	MoveFromCameraBoomSocketOffset = StateOwner->GetCameraBoom()->SocketOffset;
	MoveToCameraBoomSocketOffset = StateOwner->InitCameraBoomSocketOffset + OffsetMoveCameraSocketOffset;
}

void ACatCharacter::StateSquat::OnTick(ACatCharacter* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	TotalStateTime += DeltaTime;

	// しゃがみアクションが無効になったか？
	if (!StateOwner->bIsPushSquat)
	{
		StateOwner->ChangeState(ECatState::Run);
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

void ACatCharacter::StateSquat::OnEnd(ACatCharacter* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
