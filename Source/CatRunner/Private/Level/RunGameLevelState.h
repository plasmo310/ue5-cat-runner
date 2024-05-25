// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

/**
 * RunGameレベルステート定義
 */
UENUM(BlueprintType)
enum class ERunGameState : uint8
{
	None,
	Ready,  // 準備中
	Play,   // プレイ中
	End,    // 終了
	Result, // リザルト
};
