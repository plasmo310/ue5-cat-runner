// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatCharacter.h"

void ACatCharacter::StateWait::OnBegin(ACatCharacter* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);
}

void ACatCharacter::StateWait::OnTick(ACatCharacter* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	// 移動準備ができたか？
	if (StateOwner->bIsReadyMove)
	{
		StateOwner->ChangeState(ECatState::Run);
	}
}

void ACatCharacter::StateWait::OnEnd(ACatCharacter* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
