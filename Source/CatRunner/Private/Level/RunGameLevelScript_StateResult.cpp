// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "GameInstance/CatRunnerGameInstance.h"
#include "Level/RunGameLevelScript.h"

void ARunGameLevelScript::StateResult::OnBegin(ARunGameLevelScript* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	// BGM再生 不自然だったのでちょっと遅らせる
	auto ResultBgm = StateOwner->BgmResult;
	FTimerHandle Handle;
	StateOwner->GetWorldTimerManager().SetTimer(Handle, [ResultBgm]()
	{
		UCatRunnerGameInstance::GetAudioService()->PlayBgm(ResultBgm);
	}, 0.5f, false);
}

void ARunGameLevelScript::StateResult::OnTick(ARunGameLevelScript* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);
}

void ARunGameLevelScript::StateResult::OnEnd(ARunGameLevelScript* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
