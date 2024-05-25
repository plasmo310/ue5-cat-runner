// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameInstance/CatRunnerGameInstance.h"

void ACatCharacter::StateJump::OnBegin(ACatCharacter* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	// SE再生
	UCatRunnerGameInstance::GetAudioService()->PlaySe3d(StateOwner->JumpSound, StateOwner->GetActorLocation());

}

void ACatCharacter::StateJump::OnTick(ACatCharacter* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	// 着地したらステートを戻す
	if (!StateOwner->GetMovementComponent()->IsFalling())
	{
		StateOwner->ChangeState(ECatState::Run);
	}
}

void ACatCharacter::StateJump::OnEnd(ACatCharacter* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
