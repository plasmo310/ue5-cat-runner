// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StageLevelTableRow.generated.h"

/**
 * ステージレベル情報
 */
USTRUCT(BlueprintType)
struct FStageLevelTableRow : public FTableRowBase
{
	GENERATED_BODY()

	/** プレイヤーに加算する前進速度 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AddPlayerForwardSpeed;

	/** 1つの道に含まれる床の数 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 RoadFloorCount;

	/** 取得アイテム生成確率(%) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 GeneratePickupPercent;

	/** 取得アイテム最大生成数 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MaxGeneratePickupCount;

	/** ギミック最小生成数 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MinGenerateGimmickCount;

	/** ギミック最大生成数 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 MaxGenerateGimmickCount;
};
