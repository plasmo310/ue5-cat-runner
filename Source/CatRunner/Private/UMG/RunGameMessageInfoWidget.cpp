// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "UMG/RunGameMessageInfoWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

void URunGameMessageInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MessageText->SetText(FText::FromString(""));

	// コールバックを設定
	FWidgetAnimationDynamicEvent MessageTextFadeOutFinishedDelegate;
	MessageTextFadeOutFinishedDelegate.BindDynamic(this, &URunGameMessageInfoWidget::OnFadeOutFinished);
	BindToAnimationFinished(MessageTextFadeOutAnimation, MessageTextFadeOutFinishedDelegate);
}

void URunGameMessageInfoWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(MessageTextAppearAnimation);
}

void URunGameMessageInfoWidget::Hide()
{
	PlayAnimation(MessageTextFadeOutAnimation);
}

void URunGameMessageInfoWidget::SetMessageText(const FString& Message) const
{
	MessageText->SetText(FText::FromString(Message));
}

void URunGameMessageInfoWidget::OnFadeOutFinished()
{
	SetMessageText("");
	SetVisibility(ESlateVisibility::Hidden);
}
