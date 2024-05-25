// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RunGameResultWidget.generated.h"

/**
 * RunGameWidget: リザルトUI
 */
UCLASS()
class URunGameResultWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public:
	void Show(const TFunction<void()>& PushOkButtonCallback);
	void Hide();

	/** リザルトスコアテキストの設定 */
	void SetResultScoreText(const int Score) const;

protected:
	/** リザルトスコアテキスト */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResultScoreText;

	/** リザルト 出現アニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ResultAppearAnimation;

	/** OKボタン */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OkButton;

	/** OKボタン押下時のコールバック処理 */
	TFunction<void()> OkButtonCallback;

	/** OKボタン押下時SE */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> SePushedOkButton;

private:
	/** OKボタン押下処理 */
	UFUNCTION()
	void PushOkButton();

};
