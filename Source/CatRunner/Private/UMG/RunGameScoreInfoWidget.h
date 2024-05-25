// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RunGameScoreInfoWidget.generated.h"

/**
 * RunGameWidget: スコア情報UI
 */
UCLASS()
class URunGameScoreInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void Show();
	void Hide();

	/** スコアテキストの設定 */
	void SetScoreText(int Score, bool bIsPlayAnimation = true);

protected:
	/** スコアテキスト */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	/** スコア情報 出現アニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ScoreInfoAppearAnimation;

	/** スコア情報 出現アニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ScoreInfoLoopAnimation;

	/** スコア情報 出現アニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ScoreInfoCountAnimation;

private:
	int PrevScore;

};
