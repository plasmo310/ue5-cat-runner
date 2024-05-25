// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RunGameLevelUiData.h"
#include "RunGameLevelState.h"
#include "Engine/LevelScriptActor.h"
#include "Hit/HitDetectManager.h"
#include "Stage/StageGenerator.h"
#include "RunGameLevelScript.generated.h"

/**
 * RunGameレベルクラス
 */
UCLASS()
class ARunGameLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ARunGameLevelScript();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	/** スコアの加算処理 */
	void AddPickupScore(int Score) const;

	/** 現在のステート取得 */
	ERunGameState GetCurrentState() const;

protected:
	/** ヒット管理クラス */
	UPROPERTY()
	TObjectPtr<UHitDetectManager> HitDetectManager;

	/** ステージレベルテーブル */
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> StageLevelTable;

	/** StageGeneratorクラス */
	UPROPERTY(EditAnywhere)
	TObjectPtr<AStageGenerator> StageGenerator;

	/** RunGameUI */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> RunGameWidget;

	/** BGM: プレイ中 */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> BgmPlayGame;

	/** BGM: リザルト */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> BgmResult;

	/** SE: 開始 */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> SeStart;

	/** SE: 終了ホイッスル */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> SeWhistle;

private:
	/** RunGameレベルUIデータ */
	UPROPERTY()
	TObjectPtr<URunGameLevelUiData> RunGameLevelUiData;

	/** 最初に生成するステージの道の数 */
	const int InitGenerateStageRoad = 3;

	/** 現在のステージレベル情報 */
	const FStageLevelTableRow* CurrentStageLevelInfo;

	/** 現在のステージレベル */
	int CurrentStageLevel;

	/** ステージレベルアップ処理 */
	void LevelUpStage();

	/** プレイヤーが角を曲がった時のイベント */
	void OnPlayerTurnCorner();

	/** ステージレベル情報の取得 */
	FStageLevelTableRow* GetStageLevelInfo(int StageLevel) const;

	/** ステートマシン */
	TUniquePtr<ZStateMachine<ARunGameLevelScript>> StateMachine;

	/** ステート開始 */
	void BeginState(ERunGameState State) const;

	/** 現在のステート変更処理 */
	void ChangeState(ERunGameState State) const;

	/**
	 * State: 開始前
	 */
	class StateReady : public ZStateBase<ARunGameLevelScript>
	{
	public:
		virtual void OnBegin(ARunGameLevelScript* StateOwner) override;
		virtual void OnTick(ARunGameLevelScript* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ARunGameLevelScript* StateOwner) override;

	private:
		/** 待機時間 */
		const float WaitDuration = 2.0f;

		/** ステート経過時間 */
		float TotalStateTime = 0.0f;
	};

	/**
	 * State: プレイ中
	 */
	class StatePlay : public ZStateBase<ARunGameLevelScript>
	{
	public:
		virtual void OnBegin(ARunGameLevelScript* StateOwner) override;
		virtual void OnTick(ARunGameLevelScript* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ARunGameLevelScript* StateOwner) override;
	};

	/**
	 * State: 終了
	 */
	class StateEnd : public ZStateBase<ARunGameLevelScript>
	{
	public:
		virtual void OnBegin(ARunGameLevelScript* StateOwner) override;
		virtual void OnTick(ARunGameLevelScript* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ARunGameLevelScript* StateOwner) override;

	private:
		/** 待機時間 */
		const float WaitDuration = 2.0f;

		/** ステート経過時間 */
		float TotalStateTime = 0.0f;
	};

	/**
	 * State: リザルト
	 */
	class StateResult : public ZStateBase<ARunGameLevelScript>
	{
	public:
		virtual void OnBegin(ARunGameLevelScript* StateOwner) override;
		virtual void OnTick(ARunGameLevelScript* StateOwner, float DeltaTime) override;
		virtual void OnEnd(ARunGameLevelScript* StateOwner) override;
	};
};
