// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "GameInstance/CatRunnerGameInstance.h"
#include "Level/RunGameLevelScript.h"

void ARunGameLevelScript::StateEnd::OnBegin(ARunGameLevelScript* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	// BGM停止してホイッスルを鳴らす
	UCatRunnerGameInstance::GetAudioService()->StopBgm();
	UCatRunnerGameInstance::GetAudioService()->PlaySe2d(StateOwner->SeWhistle);
}

void ARunGameLevelScript::StateEnd::OnTick(ARunGameLevelScript* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	// 数秒待機したら進める
	TotalStateTime += DeltaTime;
	if (TotalStateTime >= WaitDuration)
	{
		StateOwner->ChangeState(ERunGameState::Result);
	}
}

void ARunGameLevelScript::StateEnd::OnEnd(ARunGameLevelScript* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
