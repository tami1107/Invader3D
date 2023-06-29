#pragma once

#include<DxLib.h>

namespace Game
{
	// ウインドウモード設定
	constexpr bool kWindowMode = true;
	// ウインドウ名
	const char* const kTitleText = "ゲーム名";
	// ウインドウサイズ
	constexpr int kScreenWidth = 1800;
	constexpr int kScreenHeight = 900;
	// カラーモード
	constexpr int kColorDepth = 32;		// 32 or 16
};