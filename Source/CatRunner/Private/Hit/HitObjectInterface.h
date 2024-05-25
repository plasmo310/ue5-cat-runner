// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HitInfo.h"
#include "HitObjectInterface.generated.h"

/**
 * 衝突を行うオブジェクト
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UHitObjectInterface : public UInterface
{
	GENERATED_BODY()
};

class IHitObjectInterface
{
	GENERATED_BODY()

public:
	/** 衝突処理 */
	virtual FHitInfo OnHit(AActor* HitActor) = 0;

};
