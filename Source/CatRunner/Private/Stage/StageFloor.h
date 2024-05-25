// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hit/HitObjectInterface.h"
#include "StageFloor.generated.h"

/**
 * ステージ床クラス
 */
UCLASS()
class AStageFloor : public AActor, public IHitObjectInterface
{
	GENERATED_BODY()
	
public:	
	AStageFloor();

	/** GeneratePointsのいずれかにアクタを生成する */
	void GenerateActorOnRandomPoints(const AActor& SpawnActor);

	/** 生成済のアクタを破棄する */
	void DestroyGeneratedActors();

	/** ヒット処理 */
	virtual FHitInfo OnHit(AActor* HitActor) override;

	/** Getter */
	FRotator GetChangeFloorRotator() const { return ChangeNextFloorRotator; }

protected:
	virtual void BeginPlay() override;

private:
	/** Pickup,Gimmickアクタの生成可能な位置配列 */
	UPROPERTY(EditAnywhere)
	TArray<FVector> GeneratePoints;

	/** 次の床へ進む回転量 */
	UPROPERTY(EditAnywhere)
	FRotator ChangeNextFloorRotator = FRotator::ZeroRotator;

	/** 生成した回数 */
	int GenerateCount;

	/** 生成したアクタ */
	UPROPERTY()
	TArray<TObjectPtr<AActor>> GenerateActorArray;

};
