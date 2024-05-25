// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Level/RunGameLevelScript.h"

void ARunGameLevelScript::StateReady::OnBegin(ARunGameLevelScript* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);
}

void ARunGameLevelScript::StateReady::OnTick(ARunGameLevelScript* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	// 数秒待機したら進める
	TotalStateTime += DeltaTime;
	if (TotalStateTime >= WaitDuration)
	{
		StateOwner->ChangeState(ERunGameState::Play);
	}
}

void ARunGameLevelScript::StateReady::OnEnd(ARunGameLevelScript* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
