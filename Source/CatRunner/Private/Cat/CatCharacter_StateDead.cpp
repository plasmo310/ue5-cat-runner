// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatCharacter.h"

void ACatCharacter::StateDead::OnBegin(ACatCharacter* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	// プレイヤーを非表示にする
	StateOwner->SetActorHiddenInGame(true);
}

void ACatCharacter::StateDead::OnTick(ACatCharacter* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);
}

void ACatCharacter::StateDead::OnEnd(ACatCharacter* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
