// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FadeWidget.h"
#include "RunGameLevelUpWidget.h"
#include "RunGameMessageInfoWidget.h"
#include "RunGameResultWidget.h"
#include "RunGameScoreInfoWidget.h"
#include "Blueprint/UserWidget.h"
#include "Level/RunGameLevelUiData.h"
#include "RunGameWidget.generated.h"

/**
 * RunGameWidget
 */
UCLASS()
class URunGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** UI初期化処理 */
	void InitializeUi(TObjectPtr<URunGameLevelUiData> UiData) const;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URunGameScoreInfoWidget> ScoreInfoWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URunGameMessageInfoWidget> MessageInfoWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URunGameLevelUpWidget> LevelUpWidget;

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<URunGameResultWidget> ResultWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UFadeWidget> FadeWidget;

};
