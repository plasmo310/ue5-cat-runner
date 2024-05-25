// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TitleLevelUiData.generated.h"

/**
 * TitleUIデータクラス
 */
UCLASS()
class UTitleLevelUiData : public UObject
{
	GENERATED_BODY()

public:
	UTitleLevelUiData() = default;

	FORCEINLINE TFunction<void()> GetOnPushStartButtonEvent() const { return OnPushStartButtonEvent; }
	FORCEINLINE void SetOnPushStartButtonEvent(const TFunction<void()>& Func) { OnPushStartButtonEvent = Func; };

private:
	/** スタートボタン押下処理 */
	TFunction<void()> OnPushStartButtonEvent;

};
