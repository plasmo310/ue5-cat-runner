// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RunGameLevelUpWidget.generated.h"

/**
 * RunGameWidget: レベルアップUI
 */
UCLASS()
class URunGameLevelUpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void Show();
	void Hide();

protected:
	/** レベルアップ 出現アニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> LevelUpAppearAnimation;

};
