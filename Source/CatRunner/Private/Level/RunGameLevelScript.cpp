// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Level/RunGameLevelScript.h"

#include "Audio/AudioService.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/CatRunnerGameInstance.h"
#include "UMG/RunGameWidget.h"

ARunGameLevelScript::ARunGameLevelScript()
	:StageLevelTable(nullptr)
	,StageGenerator(nullptr)
	,CurrentStageLevelInfo(nullptr)
	,CurrentStageLevel(0)
	,StateMachine(nullptr)
{
	// enabled tick function.
	PrimaryActorTick.bCanEverTick = true;
}

void ARunGameLevelScript::BeginPlay()
{
	Super::BeginPlay();

	// UIデータ生成
	RunGameLevelUiData = NewObject<URunGameLevelUiData>();
	RunGameLevelUiData->SetOnPushResultButtonEvent([this]()
	{
		// タイトルレベルへ遷移する
		UGameplayStatics::OpenLevel(GetWorld(), "Title");
		RunGameLevelUiData->ClearAll();
	});

	// 最初のレベル情報を取得
	const FString Context;
	CurrentStageLevelInfo = StageLevelTable->FindRow<FStageLevelTableRow>(FName(FString::FromInt(CurrentStageLevel)), Context);
	if (CurrentStageLevelInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("please set level[0] stage level info."));
	}

	// プレイヤー取得
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	const auto PlayerCharacter = Cast<ACatCharacter>(PlayerPawn);
	if (PlayerCharacter != nullptr)
	{
		// ステート変更イベント設定
		PlayerCharacter->OnChangeCatStateDelegate.BindLambda([this](ECatState State)
		{
			if (State == ECatState::TurnCorner)
			{
				OnPlayerTurnCorner();
			}
			RunGameLevelUiData->SetCurrentCatState(State);
		});

		// ヒット管理クラスの生成
		HitDetectManager = NewObject<UHitDetectManager>();
		HitDetectManager->Initialize(PlayerCharacter);
	}

	// ステージ初期化
	// 初期生成の数分、レベルアップさせておく
	TArray<FStageLevelTableRow> InitStageLevelInfoArray;
	for (auto i = 0; i < InitGenerateStageRoad; i++)
	{
		InitStageLevelInfoArray.Emplace(*CurrentStageLevelInfo);
		LevelUpStage();
	}
	StageGenerator->InitializeStage(InitStageLevelInfoArray);

	// UI初期化
	const auto UserWidget = CreateWidget<UUserWidget>(GetWorld(), RunGameWidget);
	UserWidget->AddToViewport();
	const auto RunGameUserWidget = Cast<URunGameWidget>(UserWidget);
	if (RunGameUserWidget != nullptr)
	{
		RunGameUserWidget->InitializeUi(RunGameLevelUiData);
	}

	// InputModeをGameOnlyに変更
	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	PlayerController->SetShowMouseCursor(false);

	// BGM再生
	UCatRunnerGameInstance::GetAudioService()->PlayBgm(BgmPlayGame);

	// ステート初期化
	StateMachine = MakeUnique<ZStateMachine<ARunGameLevelScript>>(this);
	StateMachine->Add<StateReady>(static_cast<int>(ERunGameState::Ready));
	StateMachine->Add<StatePlay>(static_cast<int>(ERunGameState::Play));
	StateMachine->Add<StateEnd>(static_cast<int>(ERunGameState::End));
	StateMachine->Add<StateResult>(static_cast<int>(ERunGameState::Result));
	BeginState(ERunGameState::Ready);
}

void ARunGameLevelScript::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ステート更新
	StateMachine->OnTick(DeltaSeconds);
}

void ARunGameLevelScript::AddPickupScore(const int Score) const
{
	const int TotalScore = RunGameLevelUiData->GetTotalScore() + Score;
	RunGameLevelUiData->SetTotalScore(TotalScore);
}

void ARunGameLevelScript::LevelUpStage()
{
	// ステージレベルを加算
	CurrentStageLevel++;

	// レベル情報がある場合には更新
	const FStageLevelTableRow* StageLevelInfo = GetStageLevelInfo(CurrentStageLevel);
	if (StageLevelInfo != nullptr)
	{
		CurrentStageLevelInfo = StageLevelInfo;
	}
}

void ARunGameLevelScript::OnPlayerTurnCorner()
{
	// プレイヤーの速度を上げる
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ACatCharacter* PlayerCharacter = Cast<ACatCharacter>(PlayerPawn);
	const int PlayerFloorLevel = CurrentStageLevel - InitGenerateStageRoad; // プレイヤーがいる位置のレベル
	const FStageLevelTableRow* PlayerStageLevelInfo = GetStageLevelInfo(PlayerFloorLevel);
	if (PlayerStageLevelInfo != nullptr)
	{
		PlayerCharacter->AddForwardSpeed(PlayerStageLevelInfo->AddPlayerForwardSpeed);
	}

	// レベルアップして次の道を生成する
	LevelUpStage();
	StageGenerator->GenerateNextRoad(*CurrentStageLevelInfo, *PlayerStageLevelInfo);
}

FStageLevelTableRow* ARunGameLevelScript::GetStageLevelInfo(int StageLevel) const
{
	const FString Context;
	return StageLevelTable->FindRow<FStageLevelTableRow>(FName(FString::FromInt(StageLevel)), Context);
}

ERunGameState ARunGameLevelScript::GetCurrentState() const
{
	if (StateMachine == nullptr)
	{
		return ERunGameState::None;
	}
	return static_cast<ERunGameState>(StateMachine->GetCurrentStateId());
}

void ARunGameLevelScript::BeginState(ERunGameState State) const
{
	StateMachine->OnBegin(static_cast<int>(State));
	RunGameLevelUiData->SetCurrentRunGameState(State);
}

void ARunGameLevelScript::ChangeState(ERunGameState State) const
{
	StateMachine->ChangeState(static_cast<int>(State));
	RunGameLevelUiData->SetCurrentRunGameState(State);
}
