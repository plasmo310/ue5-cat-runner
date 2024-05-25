// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Pickup.h"
#include "Hit/HitObjectInterface.h"
#include "ChuruPickup.generated.h"

/**
 * ちゅ〜るクラス
 */
UCLASS()
class AChuruPickup : public APickup, public IHitObjectInterface
{
	GENERATED_BODY()

public:
	AChuruPickup();

protected:
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual FHitInfo OnHit(AActor* HitActor) override;

private:
	/** アイテム取得時のスコア */
	UPROPERTY(EditAnywhere)
	int CollectScore = 1;

	/** 回転スピード */
	UPROPERTY(EditAnywhere)
	float RotateSpeed = 200.0f;

	/** 取得時のエフェクト */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> PickupEffect;

	/** 取得時のサウンド */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> PickupSound;

};
