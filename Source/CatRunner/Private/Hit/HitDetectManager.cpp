// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Hit/HitDetectManager.h"

#include "Cat/CatCharacter.h"
#include "Hit/HitInfo.h"
#include "Hit/HitObjectInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Level/RunGameLevelScript.h"

void UHitDetectManager::Initialize(ACatCharacter* Player) const
{
	// プレイヤーに監視イベントを設定
	Player->OnHitActorDelegate.BindLambda([this](ACatCharacter* Player, AActor* HitActor)
	{
		OnDetectedHitPlayer(Player, HitActor);
	});
}

void UHitDetectManager::OnDetectedHitPlayer(ACatCharacter* Player, AActor* HitActor)
{
	IHitObjectInterface* HitObject = Cast<IHitObjectInterface>(HitActor);
	if (HitObject == nullptr)
	{
		return;
	}

	// ヒット情報によって処理を行う
	const FHitInfo HitInfo = HitObject->OnHit(Player);

	// スコアの加算
	if (HitInfo.AddScore != 0)
	{
		const auto LevelScriptActor = UGameplayStatics::GetActorOfClass(Player->GetWorld(), ARunGameLevelScript::StaticClass());
		const auto RunGameLevelScript = Cast<ARunGameLevelScript>(LevelScriptActor);
		if (RunGameLevelScript != nullptr)
		{
			RunGameLevelScript->AddPickupScore(HitInfo.AddScore);
		}
	}

	// 死亡させるか？
	if (HitInfo.bIsTargetDestroy)
	{
		Player->OnDie();
	}

	// 回転させるか？
	if (HitInfo.ChangeTurnCornerRotator != FRotator::ZeroRotator)
	{
		Player->OnTurnCorner(HitInfo.ChangeTurnCornerRotator, HitActor->GetActorLocation());
	}
}
