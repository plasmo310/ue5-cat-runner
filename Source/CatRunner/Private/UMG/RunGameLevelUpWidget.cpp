// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "UMG/RunGameLevelUpWidget.h"

void URunGameLevelUpWidget::NativeConstruct()
{
	// アニメーションの初期状態にするための対策
	PlayAnimation(LevelUpAppearAnimation);
	StopAnimation(LevelUpAppearAnimation);
}

void URunGameLevelUpWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(LevelUpAppearAnimation);
}

void URunGameLevelUpWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}
