// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HitInfo.generated.h"

/**
 * ヒット情報
 */
USTRUCT(BlueprintType)
struct FHitInfo
{
 GENERATED_BODY()

 /** ヒット対象を破棄するか？ */
 UPROPERTY()
 bool bIsTargetDestroy = false;

 /** 加算するスコア */
 UPROPERTY()
 int AddScore = 0;

 /** 変更する回転量 */
 UPROPERTY()
 FRotator ChangeTurnCornerRotator = FRotator::ZeroRotator;

};
