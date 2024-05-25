// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FadeWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Level/TitleLevelUiData.h"
#include "TitleWidget.generated.h"

/**
 * TitleWidget
 */
UCLASS()
class UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public:
	/** 初期化処理 */
	void InitializeUi(const TObjectPtr<UTitleLevelUiData> UiData);

private:
	/** スタートボタン */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	/** フェード用ウィジェット */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UFadeWidget> FadeWidget;

	/** スタートボタン押下時SE */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> SePushedStartButton;

	/** スタートボタン押下処理 */
	UFUNCTION()
	void OnPushStartButton();

	/** スタートボタン押下時のコールバック処理 */
	TFunction<void()> OnPushStartButtonEvent;

};
