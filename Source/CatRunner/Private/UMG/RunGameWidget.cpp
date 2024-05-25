// Copyright (c) 2024, CatRunner All Rights Reserved.


#include "UMG/RunGameWidget.h"

void URunGameWidget::InitializeUi(TObjectPtr<URunGameLevelUiData> UiData) const
{
	// ゲームステート変更時
	UiData->OnChangeRunGameStateDelegate.BindLambda([this, UiData](ERunGameState State)
	{
		switch (State)
		{
		case ERunGameState::Ready:
			{
				ScoreInfoWidget->Show();
				MessageInfoWidget->SetMessageText("Ready");
				MessageInfoWidget->Show();
				break;
			}
		case ERunGameState::Play:
			{
				MessageInfoWidget->Hide();
				break;
			}
		case ERunGameState::End:
			{
				ScoreInfoWidget->Hide();
				MessageInfoWidget->SetMessageText("Finish!");
				MessageInfoWidget->Show();
				break;
			}
		case ERunGameState::Result:
			{
				const auto OnPushResultButtonFunc = UiData->GetOnPushResultButtonEvent();
				ResultWidget->SetResultScoreText(UiData->GetTotalScore());
				ResultWidget->Show([this, OnPushResultButtonFunc]()
				{
					// フェードアウトして次のレベルへ遷移
					FadeWidget->SetVisibility(ESlateVisibility::Visible);
					FadeWidget->FadeOut([this, OnPushResultButtonFunc]()
					{
						OnPushResultButtonFunc();
					});
				});
				break;
			}
		default:
			break;
		}
	});

	// 累計スコア変更時
	UiData->OnChangeTotalScoreDelegate.BindLambda([this](int Score)
	{
		ScoreInfoWidget->SetScoreText(Score);
	});

	// プレイヤーステート変更時
	UiData->OnChangeCatStateDelegate.BindLambda([this](ECatState State)
	{
		if (State == ECatState::TurnCorner)
		{
			LevelUpWidget->Show();
		}
		else
		{
			LevelUpWidget->Hide();
		}
	});

	// フェードイン
	FadeWidget->SetVisibility(ESlateVisibility::Visible);
	FadeWidget->FadeIn([this]()
	{
		FadeWidget->SetVisibility(ESlateVisibility::Hidden);
	});
}
