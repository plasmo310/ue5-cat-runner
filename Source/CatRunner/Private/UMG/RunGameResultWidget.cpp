// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "UMG/RunGameResultWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameInstance/CatRunnerGameInstance.h"
#include "Kismet/GameplayStatics.h"

void URunGameResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetResultScoreText(0);

	// アニメーションの初期状態にするための対策
	PlayAnimation(ResultAppearAnimation);
	StopAnimation(ResultAppearAnimation);
}

void URunGameResultWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// ボタンイベントのBind
	OkButton->OnClicked.AddDynamic(this, &URunGameResultWidget::PushOkButton);
}

void URunGameResultWidget::Show(const TFunction<void()>& PushOkButtonCallback)
{
	OkButtonCallback = PushOkButtonCallback;

	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(ResultAppearAnimation);

	// change input mode ui only.
	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, this, EMouseLockMode::LockAlways);
	PlayerController->SetShowMouseCursor(true);
}

void URunGameResultWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void URunGameResultWidget::SetResultScoreText(const int Score) const
{
	ResultScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}

void URunGameResultWidget::PushOkButton()
{
	if (SePushedOkButton != nullptr)
	{
		UCatRunnerGameInstance::GetAudioService()->PlaySe2d(SePushedOkButton);
	}

	if (OkButtonCallback != nullptr)
	{
		OkButtonCallback();
	}
}
