// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Stage/StageGenerator.h"

AStageGenerator::AStageGenerator()
	:StageFloor(nullptr)
	,StageFloorL(nullptr)
	,StageFloorR(nullptr)
	,PickupGenerateTable({})
	,Gimmick(nullptr)
	,FloorSize(600.0f)
	,GenerateDirection(FVector::ZeroVector)
	,GenerateStartPoint(FVector::ZeroVector)
	,NextFloorRotator(FRotator::ZeroRotator)
	,GenerateNextRoadCallCount(0)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AStageGenerator::InitializeStage(TArray<FStageLevelTableRow> InitStageLevelTableRows)
{
	// 道の最大生成数を設定
	MaxGenerateRoadCount = InitStageLevelTableRows.Num();

	// 生成情報を初期化
	GenerateStartPoint = GetActorLocation();
	GenerateDirection = FVector(1, 0, 0);

	// 初期情報から道を生成する
	for (auto i = 0; i < MaxGenerateRoadCount; i++)
	{
		auto FloorArray = GenerateRoad(InitStageLevelTableRows[i]);
		GeneratedRoadArray.Emplace(FloorArray);

		// 最初の道のアクタ郡を生成しておく
		if (i == 0)
		{
			GenerateActorsOnFloor(FloorArray, InitStageLevelTableRows[i]);
		}
	}
}

TSubclassOf<APickup> AStageGenerator::GetRandomGeneratePickup() const
{
	// PickupのWeightから抽選用の配列を生成
	TArray<int> LotteryIndexArray = {};
	for (auto Index = 0; Index < PickupGenerateTable.Num(); Index++)
	{
		const int Weight = PickupGenerateTable[Index].GenerateWeight;
		for (auto i = 0; i < Weight; i++)
		{
			LotteryIndexArray.Emplace(Index);
		}
	}

	if (LotteryIndexArray.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("please set PickupGenerateTable property."));
		return nullptr;
	}

	// ランダムに選んで返却する
	const int LotteryIndex = LotteryIndexArray[FMath::RandRange(0, LotteryIndexArray.Num() - 1)];
	return PickupGenerateTable[LotteryIndex].Pickup;
}

void AStageGenerator::GenerateNextRoad(const FStageLevelTableRow& GenerateStageLevelTableRow, const FStageLevelTableRow& PlayerStageLevelTableRow)
{
	GenerateNextRoadCallCount++;

	// 生成処理にバッファを持たせるため初回は待つ
	constexpr int WaitCount = 1;
	if (GenerateNextRoadCallCount == WaitCount)
	{
		// 次の道のアクタ郡は表示しておく
		GenerateActorsOnFloor(GeneratedRoadArray[WaitCount], PlayerStageLevelTableRow);
		return;
	}

	// 次の道を生成
	const auto FloorArray = GenerateRoad(GenerateStageLevelTableRow);
	GeneratedRoadArray.Emplace(FloorArray);

	// 最大数からあふれた古い道は削除する
	for (const auto OldStageFloor : GeneratedRoadArray[0])
	{
		OldStageFloor->DestroyGeneratedActors();
		OldStageFloor->Destroy();
	}
	GeneratedRoadArray.RemoveAt(0);

	// プレイヤーの次の道のアクタ郡を生成する
	GenerateActorsOnFloor(GeneratedRoadArray[WaitCount], PlayerStageLevelTableRow);
}

TArray<TObjectPtr<AStageFloor>> AStageGenerator::GenerateRoad(const FStageLevelTableRow& StageLevelTableRow)
{
	// 床の数だけループ
	const int FloorCount = StageLevelTableRow.RoadFloorCount;
	TArray<TObjectPtr<AStageFloor>> FloorArray;
	for (auto i = 0; i < FloorCount; i++)
	{
		const bool bIsLastFloor = i == FloorCount - 1;

		// 終端まで来たらランダムで左右どちらかに曲がる床を選択する
		auto SpawnFloorType = EStageFloorType::Normal;
		if (bIsLastFloor)
		{
			SpawnFloorType = FMath::RandRange(0, 1) == 0 ? EStageFloorType::Left : EStageFloorType::Right;
		}

		// 床の生成
		const auto SpawnLocation = GenerateStartPoint + GenerateDirection * FloorSize * i;
		AStageFloor* SpawnStageFloor = GenerateFloor(SpawnLocation, NextFloorRotator, SpawnFloorType);
		FloorArray.Emplace(SpawnStageFloor);

		// 次に生成する向きを再設定する
		if (bIsLastFloor)
		{
			auto ChangeFloorRotator = SpawnStageFloor->GetChangeFloorRotator();
			NextFloorRotator += ChangeFloorRotator;
			GenerateDirection = (GenerateDirection.Rotation() + ChangeFloorRotator).Vector();
			GenerateStartPoint = SpawnStageFloor->GetActorLocation() + GenerateDirection * FloorSize;
		}
	}
	return FloorArray;
}

TObjectPtr<AStageFloor> AStageGenerator::GenerateFloor(const FVector& SpawnLocation,  const FRotator& SpawnRotator, const EStageFloorType StageFloorType)
{
	// 床の種類からアクタを取得
	TSubclassOf<AStageFloor> StageFloorActor = nullptr;
	switch (StageFloorType)
	{
	case EStageFloorType::Normal:
		StageFloorActor = StageFloor;
		break;
	case EStageFloorType::Left:
		StageFloorActor = StageFloorL;
		break;
	case EStageFloorType::Right:
		StageFloorActor = StageFloorR;
		break;
	default:
		break;
	}
	if (StageFloorActor == nullptr)
	{
		return nullptr;
	}

	// アクタを生成
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	UWorld* const World = GetWorld();
	return World->SpawnActor<AStageFloor>(StageFloorActor, SpawnLocation, SpawnRotator, SpawnParams);
}

void AStageGenerator::GenerateActorsOnFloor(const TArray<TObjectPtr<AStageFloor>>& StageFloorArray, const FStageLevelTableRow& StageLevelTableRow) const
{
	for (auto i = 0; i < StageFloorArray.Num(); i++)
	{
		// 曲がった直後に対応できるよう手前側はスキップする
		constexpr int SkipGenerateFloorCount = 2;
		if (i < SkipGenerateFloorCount)
		{
			continue;
		}

		const TObjectPtr<AStageFloor> StageFloorActor = StageFloorArray[i];

		// 終端にはボーナスアイテムを置く
		const bool bIsLastFloor = i == StageFloorArray.Num() - 1;
		if (bIsLastFloor)
		{
			StageFloorActor->GenerateActorOnRandomPoints(*TurnCornerBonusPickup.GetDefaultObject());
			continue;
		}

		// ギミック生成
		if (Gimmick != nullptr)
		{
			const int GimmickGenerateCount = FMath::RandRange(StageLevelTableRow.MinGenerateGimmickCount, StageLevelTableRow.MaxGenerateGimmickCount);
			for (auto GimmickCount = 0; GimmickCount < GimmickGenerateCount; GimmickCount++)
			{
				StageFloorActor->GenerateActorOnRandomPoints(*Cast<AActor>(Gimmick.GetDefaultObject()));
			}
		}

		// ピックアップ生成
		const int PickupGenerateCount = StageLevelTableRow.MaxGeneratePickupCount;
		for (auto PickupCount = 0; PickupCount < PickupGenerateCount; PickupCount++)
		{
			if (FMath::RandRange(0, 100) > StageLevelTableRow.GeneratePickupPercent)
			{
				continue;
			}
			const AActor* PickupActor = Cast<AActor>(GetRandomGeneratePickup().GetDefaultObject());
			if (PickupActor != nullptr)
			{
				StageFloorActor->GenerateActorOnRandomPoints(*PickupActor);
			}
		}
	}
}
