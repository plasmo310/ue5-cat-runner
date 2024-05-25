// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeWidget.generated.h"

/**
 * フェード用UI
 */
UCLASS()
class UFadeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	/** フェードイン処理 */
	void FadeIn(const TFunction<void()>& Callback = nullptr);

	/** フェードアウト処理 */
	void FadeOut(const TFunction<void()>& Callback = nullptr);

protected:
	/** フェードインアニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeInAnimation;

	/** フェードアウトアニメーション */
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeOutAnimation;

private:
	/** フェードイン時のコールバック処理 */
	TFunction<void()> FadeInCallback;

	/** フェードアウト時のコールバック処理 */
	TFunction<void()> FadeOutCallback;

	UFUNCTION()
	void OnFinishedFadeIn();

	UFUNCTION()
	void OnFinishedFadeOut();

};
