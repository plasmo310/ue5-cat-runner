// Copyright (c) 2024, CatRunner All Rights Reserved.

#pragma once

/**
 * ねこステート定義
 */
UENUM(BlueprintType)
enum class ECatState : uint8
{
	None,
	Wait,       // 待機
	Run,        // 走る
	Jump,       // ジャンプ
	RotateL,    // 左回転
	RotateR,    // 右回転
	Squat,      // しゃがむ
	TurnCorner, // 角を曲がる
	Dead,       // 死亡
};
