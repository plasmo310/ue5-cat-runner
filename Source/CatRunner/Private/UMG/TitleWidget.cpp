// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "UMG/TitleWidget.h"
#include "GameInstance/CatRunnerGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// フェードイン
	FadeWidget->SetVisibility(ESlateVisibility::Visible);
	FadeWidget->FadeIn([this]()
	{
		FadeWidget->SetVisibility(ESlateVisibility::Hidden);
	});
}

void UTitleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// ボタンイベントのBind
	StartButton->OnClicked.AddDynamic(this, &UTitleWidget::OnPushStartButton);
}

void UTitleWidget::InitializeUi(const TObjectPtr<UTitleLevelUiData> UiData)
{
	OnPushStartButtonEvent = UiData->GetOnPushStartButtonEvent();
}

void UTitleWidget::OnPushStartButton()
{
	if (SePushedStartButton != nullptr)
	{
		UCatRunnerGameInstance::GetAudioService()->PlaySe2d(SePushedStartButton);
	}

	FadeWidget->SetVisibility(ESlateVisibility::Visible);
	FadeWidget->FadeOut([this]()
	{
		UGameplayStatics::OpenLevel(GetWorld(), "RunGame");
	});
}
