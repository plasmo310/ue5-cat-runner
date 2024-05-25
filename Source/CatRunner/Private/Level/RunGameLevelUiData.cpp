// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "Level/RunGameLevelUiData.h"

URunGameLevelUiData::URunGameLevelUiData()
{
	ClearAll();
}

void URunGameLevelUiData::ClearAll()
{
	TotalPickupScore = 0;
	CurrentRunGameState = ERunGameState::None;
	CurrentCatState = ECatState::None;
	OnPushResultButtonEvent = nullptr;
	OnChangeTotalScoreDelegate.Unbind();
	OnChangeRunGameStateDelegate.Unbind();
	OnChangeCatStateDelegate.Unbind();
}

void URunGameLevelUiData::SetTotalScore(int Score)
{
	TotalPickupScore = Score;
	OnChangeTotalScoreDelegate.ExecuteIfBound(Score);
}

void URunGameLevelUiData::SetCurrentRunGameState(ERunGameState State)
{
	CurrentRunGameState = State;
	OnChangeRunGameStateDelegate.ExecuteIfBound(State);
}

void URunGameLevelUiData::SetCurrentCatState(ECatState State)
{
	CurrentCatState = State;
	OnChangeCatStateDelegate.ExecuteIfBound(State);
}

void URunGameLevelUiData::SetOnPushResultButtonEvent(TFunction<void()> Func)
{
	OnPushResultButtonEvent = Func;
}
