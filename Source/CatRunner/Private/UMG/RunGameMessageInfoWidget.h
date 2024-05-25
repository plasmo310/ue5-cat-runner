// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RunGameMessageInfoWidget.generated.h"

/**
 * RunGameWidget: メッセージ情報UI
 */
UCLASS()
class URunGameMessageInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void Show();
	void Hide();

	/** メッセージテキストの設定 */
	void SetMessageText(const FString& Message) const;

protected:
	/** メッセージテキスト */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageText;

	/** メッセージテキスト 出現アニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> MessageTextAppearAnimation;

	/** メッセージテキスト フェードアウトアニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> MessageTextFadeOutAnimation;

private:
	/** フェードアウト終了時のコールバック */
	UFUNCTION()
	void OnFadeOutFinished();
};
