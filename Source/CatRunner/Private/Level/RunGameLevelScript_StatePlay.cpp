// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Cat/CatCharacter.h"
#include "GameInstance/CatRunnerGameInstance.h"
#include "Level/RunGameLevelScript.h"
#include "Kismet/GameplayStatics.h"

void ARunGameLevelScript::StatePlay::OnBegin(ARunGameLevelScript* StateOwner)
{
	ZStateBase::OnBegin(StateOwner);

	// プレイヤーの移動を開始させる
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(StateOwner->GetWorld(), 0);
	ACatCharacter* PlayerCharacter = Cast<ACatCharacter>(PlayerPawn);
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->SetIsReadyMove(true);
	}

	// SE再生
	UCatRunnerGameInstance::GetAudioService()->PlaySe2d(StateOwner->SeStart);
}

void ARunGameLevelScript::StatePlay::OnTick(ARunGameLevelScript* StateOwner, float DeltaTime)
{
	ZStateBase::OnTick(StateOwner, DeltaTime);

	// プレイヤーが死亡したらリザルトに進む
	const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(StateOwner->GetWorld(), 0);
	const auto Player = Cast<ACatCharacter>(PlayerPawn);
	if (Player != nullptr && Player->GetCurrentState() == ECatState::Dead)
	{
		StateOwner->ChangeState(ERunGameState::End);
	}
}

void ARunGameLevelScript::StatePlay::OnEnd(ARunGameLevelScript* StateOwner)
{
	ZStateBase::OnEnd(StateOwner);
}
