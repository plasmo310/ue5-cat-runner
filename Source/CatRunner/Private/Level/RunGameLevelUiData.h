// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RunGameLevelState.h"
#include "Cat/CatCharacterState.h"
#include "RunGameLevelUiData.generated.h"

/**
 * RunGameレベルUIデータクラス
 */
UCLASS()
class URunGameLevelUiData : public UObject
{
	GENERATED_BODY()

public:
	URunGameLevelUiData();

	/** データクリア処理 */
	void ClearAll();

	/** Getter */
	FORCEINLINE int GetTotalScore() const { return TotalPickupScore; }
	FORCEINLINE ERunGameState GetCurrentRunGameState() const { return CurrentRunGameState; }
	FORCEINLINE ECatState GetCurrentCatState() const { return CurrentCatState; }
	FORCEINLINE TFunction<void()> GetOnPushResultButtonEvent() const { return OnPushResultButtonEvent; }

	/** Setter */
	void SetTotalScore(int Score);
	void SetCurrentRunGameState(ERunGameState State);
	void SetCurrentCatState(ECatState State);
	void SetOnPushResultButtonEvent(TFunction<void()> Func);

	/** データ変更時のイベント */
	DECLARE_DELEGATE_OneParam(FChangeScoreDelegate, int)
	FChangeScoreDelegate OnChangeTotalScoreDelegate;
	DECLARE_DELEGATE_OneParam(FChangeRunGameStateDelegate, ERunGameState)
	FChangeRunGameStateDelegate OnChangeRunGameStateDelegate;
	DECLARE_DELEGATE_OneParam(FChangeCatStateDelegate, ECatState)
	FChangeCatStateDelegate OnChangeCatStateDelegate;

private:
	/** 累計スコア */
	int TotalPickupScore;

	/** 現在のゲームステート */
	ERunGameState CurrentRunGameState;

	/** 現在のプレイヤーステート */
	ECatState CurrentCatState;

	/** リザルトボタン押下処理 */
	TFunction<void()> OnPushResultButtonEvent;

};
