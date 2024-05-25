// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "AudioService.generated.h"

/**
 * オーディオ管理クラス
 */
UCLASS()
class UAudioService : public UObject
{
	GENERATED_BODY()

public:
	UAudioService();

	/** BGM再生 */
	void PlayBgm(USoundBase* PlayBgm);

	/** BGM停止 */
	void StopBgm() const;

	/** SE2D再生 */
	void PlaySe2d(USoundBase* PlaySe);

	/** SE3D再生 */
	void PlaySe3d(USoundBase* PlaySe, const FVector& PlayLocation);

private:
	/** BGM再生用AudioComponent */
	UPROPERTY()
	TObjectPtr<UAudioComponent> BgmAudioComponent;

};
