// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "UMG/FadeWidget.h"

void UFadeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// bind delegate.
	FWidgetAnimationDynamicEvent FadeInDelegate;
	FadeInDelegate.BindDynamic(this, &UFadeWidget::OnFinishedFadeIn);
	BindToAnimationFinished(FadeInAnimation, FadeInDelegate);
	FWidgetAnimationDynamicEvent FadeOutDelegate;
	FadeOutDelegate.BindDynamic(this, &UFadeWidget::OnFinishedFadeOut);
	BindToAnimationFinished(FadeOutAnimation, FadeOutDelegate);
}

void UFadeWidget::FadeIn(const TFunction<void()>& Callback)
{
	FadeInCallback = Callback;
	PlayAnimation(FadeInAnimation);
}

void UFadeWidget::FadeOut(const TFunction<void()>& Callback)
{
	FadeOutCallback = Callback;
	PlayAnimation(FadeOutAnimation);
}

void UFadeWidget::OnFinishedFadeIn()
{
	if (FadeInCallback != nullptr)
	{
		FadeInCallback();
	}
}

void UFadeWidget::OnFinishedFadeOut()
{
	if (FadeOutCallback != nullptr)
	{
		FadeOutCallback();
	}
}
