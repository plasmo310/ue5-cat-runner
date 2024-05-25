// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "UMG/RunGameScoreInfoWidget.h"

#include "Components/TextBlock.h"

void URunGameScoreInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ScoreText->SetText(FText::FromString(""));

	// アニメーションの初期状態にするための対策
	PlayAnimation(ScoreInfoAppearAnimation);
	StopAnimation(ScoreInfoAppearAnimation);
}

void URunGameScoreInfoWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);

	PrevScore = -1;
	SetScoreText(0, false);
	PlayAnimation(ScoreInfoAppearAnimation);
	PlayAnimation(ScoreInfoLoopAnimation, 0, 0); // Loop
}

void URunGameScoreInfoWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
	StopAnimation(ScoreInfoLoopAnimation);
}

void URunGameScoreInfoWidget::SetScoreText(const int Score, bool bIsPlayAnimation)
{
	if (PrevScore == Score)
	{
		return;
	}
	PrevScore = Score;

	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
	if (bIsPlayAnimation)
	{
		PlayAnimation(ScoreInfoCountAnimation);
	}
}
