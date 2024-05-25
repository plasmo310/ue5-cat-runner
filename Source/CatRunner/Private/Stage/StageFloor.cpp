// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Stage/StageFloor.h"

AStageFloor::AStageFloor()
	:GenerateCount(0)
	,GenerateActorArray({})
{
	PrimaryActorTick.bCanEverTick = false;
}

void AStageFloor::BeginPlay()
{
	Super::BeginPlay();

	// 生成ポイントをランダムにシャッフルする
	GeneratePoints.Sort([this](const FVector&, const FVector&)
	{
		return FMath::FRand() < 0.5f;
	});
}

void AStageFloor::GenerateActorOnRandomPoints(const AActor& SpawnActor)
{
	if (GeneratePoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("please set GeneratePoints property."))
		return;
	}

	if (GeneratePoints.Num() <= GenerateCount)
	{
		UE_LOG(LogTemp, Error, TEXT("limit generate count."))
		return;
	}

	// 生成情報の設定
	// 生成位置はアクタの向きに合わせて回転させる
	const FRotator SpawnRotation = GetActorRotation();
	FVector GeneratePoint = GeneratePoints[GenerateCount];
	GeneratePoint = GeneratePoint.RotateAngleAxis(SpawnRotation.Euler().X, GetActorForwardVector());
	GeneratePoint = GeneratePoint.RotateAngleAxis(SpawnRotation.Euler().Y, GetActorRightVector());
	GeneratePoint = GeneratePoint.RotateAngleAxis(SpawnRotation.Euler().Z, GetActorUpVector());
	const FVector SpawnLocation = GetActorLocation() + GeneratePoint;

	// アクタを生成する
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	UWorld* const World = GetWorld();
	const auto Actor = World->SpawnActor<AActor>(SpawnActor.GetClass(), SpawnLocation, SpawnRotation, SpawnParams);
	GenerateActorArray.Emplace(Actor);

	// 生成数をインクリメント
	GenerateCount++;
}

void AStageFloor::DestroyGeneratedActors()
{
	for (const auto GeneratedActor : GenerateActorArray)
	{
		if (GeneratedActor == nullptr || !IsValid(GeneratedActor))
		{
			continue;
		}
		GeneratedActor->Destroy();
	}
}

FHitInfo AStageFloor::OnHit(AActor* HitActor)
{
	// 次のフロアの回転情報を返却する
	FHitInfo HitInfo;
	if (ChangeNextFloorRotator != FRotator::ZeroRotator)
	{
		HitInfo.ChangeTurnCornerRotator = ChangeNextFloorRotator;
	}
	return HitInfo;
}
