// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StageFloor.h"
#include "Data/StageLevelTableRow.h"
#include "GameFramework/Actor.h"
#include "Gimmick/BlockGimmick.h"
#include "Pickup/Pickup.h"
#include "StageGenerator.generated.h"

/**
 * ステージ床タイプ
 */
UENUM(BlueprintType)
enum class EStageFloorType : uint8
{
	Normal,
	Left,
	Right,
};

/**
 * 取得アイテム生成情報
 */
USTRUCT()
struct FPickupGenerateInfo
{
	GENERATED_BODY()

	/** 取得アイテム */
	UPROPERTY(EditAnywhere)
	TSubclassOf<APickup> Pickup;

	/** 生成する重み */
	UPROPERTY(EditAnywhere)
	uint8 GenerateWeight;
};

/**
 * ステージ生成クラス
 */
UCLASS()
class AStageGenerator : public AActor
{
	GENERATED_BODY()
	
public:
	AStageGenerator();

	// ステージ初期化処理
	// InitStageLevelTableRows: ステージ初期生成情報
	void InitializeStage(TArray<FStageLevelTableRow> InitStageLevelTableRows);

	/** 次の道を生成する */
	void GenerateNextRoad(const FStageLevelTableRow& GenerateStageLevelTableRow, const FStageLevelTableRow& PlayerStageLevelTableRow);

private:
	/** ステージ床アクタ */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AStageFloor> StageFloor;

	/** ステージ床アクタ(左L字) */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AStageFloor> StageFloorL;

	/** ステージ床アクタ(右L字) */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AStageFloor> StageFloorR;

	/** 曲がるときに出すボーナスピックアップ */
	UPROPERTY(EditAnywhere)
	TSubclassOf<APickup> TurnCornerBonusPickup;

	/** 取得アイテム生成情報テーブル */
	UPROPERTY(EditAnywhere)
	TArray<FPickupGenerateInfo> PickupGenerateTable;

	/** ギミック(現状1種類) */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGimmick> Gimmick;

	/** 1つの床あたりのサイズ */
	UPROPERTY(EditAnywhere)
	float FloorSize;

	/** GeneratedRoadQueueに格納する最大数 */
	int MaxGenerateRoadCount;

	/** 生成した道を格納した配列 */
	TArray<TArray<TObjectPtr<AStageFloor>>> GeneratedRoadArray = {};

	/** ステージ生成情報: 回転 */
	FVector GenerateDirection;

	/** ステージ生成情報: 開始位置 */
	FVector GenerateStartPoint;

	/** 次に生成する床への回転情報 */
	FRotator NextFloorRotator;

	/** GenerateNextRoad()が呼ばれた数 */
	int GenerateNextRoadCallCount;

	/** 生成する取得アイテムをランダムに取得する */
	TSubclassOf<APickup> GetRandomGeneratePickup() const;

	/** 道の生成処理 */
	TArray<TObjectPtr<AStageFloor>> GenerateRoad(const FStageLevelTableRow& StageLevelTableRow);

	/** 床の生成処理 */
	TObjectPtr<AStageFloor> GenerateFloor(const FVector& SpawnLocation, const FRotator& SpawnRotator, const EStageFloorType StageFloorType);

	/** 床の上のアクタ生成処理 */
	void GenerateActorsOnFloor(const TArray<TObjectPtr<AStageFloor>>& StageFloorArray, const FStageLevelTableRow& StageLevelTableRow) const;

};
