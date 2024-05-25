// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Level/TitleLevelScript.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameInstance/CatRunnerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/TitleWidget.h"

ATitleLevelScript::ATitleLevelScript()
{
	// enabled tick function.
	PrimaryActorTick.bCanEverTick = true;
}

void ATitleLevelScript::BeginPlay()
{
	Super::BeginPlay();

	// UIデータ作成
	TitleLevelUiData = NewObject<UTitleLevelUiData>();
	TitleLevelUiData->SetOnPushStartButtonEvent([this]()
	{
		// RunGameレベルへ遷移する
		UGameplayStatics::OpenLevel(GetWorld(), "RunGame");
	});

	// UI初期化
	const auto UserWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidget);
	UserWidget->AddToViewport();
	const auto TitleUserWidget = Cast<UTitleWidget>(UserWidget);
	if (TitleUserWidget != nullptr)
	{
		TitleUserWidget->InitializeUi(TitleLevelUiData);
	}

	// InputModeをUIOnlyに変更
	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, UserWidget, EMouseLockMode::LockAlways);
	PlayerController->SetShowMouseCursor(true);

	// BGM再生
	if (BgmTitle != nullptr)
	{
		UCatRunnerGameInstance::GetAudioService()->PlayBgm(BgmTitle);
	}
}

void ATitleLevelScript::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
