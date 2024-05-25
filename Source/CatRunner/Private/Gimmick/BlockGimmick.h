// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/Gimmick.h"
#include "NiagaraFunctionLibrary.h"
#include "Hit/HitObjectInterface.h"
#include "BlockGimmick.generated.h"


/**
 * ブロックギミッククラス
 */
UCLASS()
class ABlockGimmick : public AGimmick, public IHitObjectInterface
{
	GENERATED_BODY()

public:
	ABlockGimmick();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual FHitInfo OnHit(AActor* HitActor) override;

private:
	/** プレイヤー破棄時のエフェクト */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> PlayerDestroyEffect;

	/** プレイヤー破棄時のサウンド */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> PlayerDestroySound;

	/** 非表示にするカメラ距離 */
	const float HideCameraDistance = 350.0f;

};
