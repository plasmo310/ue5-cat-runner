// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatAnimInstance.h"
#include "Cat/CatCharacter.h"

void UCatAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// プロパティ初期化
	bIsRunState = false;
	bIsJumpState = false;
	bIsRotateLState = false;
	bIsRotateRState = false;
	bIsSquatState = false;

	// プレイヤーのステートをチェック
	const auto player = Cast<ACatCharacter>(GetOwningActor());
	if (player == nullptr)
	{
		return;
	}
	const ECatState CurrentState = player->GetCurrentState();
	switch (CurrentState)
	{
	case ECatState::Run:
		bIsRunState = true;
		break;
	case ECatState::Jump:
		bIsJumpState = true;
		break;
	case ECatState::RotateL:
		bIsRotateLState = true;
		break;
	case ECatState::RotateR:
		bIsRotateRState = true;
		break;
	case ECatState::Squat:
		bIsSquatState = true;
		break;
	default:
		break;
	}
}
