// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Pickup/ChuruPickup.h"

#include "GameInstance/CatRunnerGameInstance.h"
#include "Level/RunGameLevelScript.h"

AChuruPickup::AChuruPickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AChuruPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// オブジェクトを常に回転させる
	AddActorLocalRotation(FRotator(0.0f, -RotateSpeed * DeltaSeconds, 0.0f));
}

FHitInfo AChuruPickup::OnHit(AActor* HitActor)
{
	// エフェクト、サウンド再生
	if (PickupEffect != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), PickupEffect, GetActorLocation());
	}
	if (PickupSound != nullptr)
	{
		UCatRunnerGameInstance::GetAudioService()->PlaySe3d(PickupSound, GetActorLocation());
	}

	// 自身を破棄
	Destroy();

	// スコアを加算する
	FHitInfo HitInfo;
	HitInfo.AddScore = CollectScore;
	return HitInfo;
}
