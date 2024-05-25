// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Cat/CatCharacter.h"
#include "HitDetectManager.generated.h"

/**
 * ヒット処理管理クラス
 */
UCLASS()
class UHitDetectManager : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(ACatCharacter* Player) const;

private:
	/** ヒット検知処理 */
	UFUNCTION()
	static void OnDetectedHitPlayer(ACatCharacter* Player, AActor* HitActor);

};
