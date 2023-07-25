#include "MainUI.h"
#include "game.h"
#include "SceneMain.h"
#include <math.h>

namespace
{
	// 文字フォント
	const char* const kTextFontName = "NULL";

	// 文字フォントサイズ
	constexpr int kTextFontSize = 50;

	// スコア位置
	constexpr int kScorePosX = 10;
	constexpr int kScorePosY = 10;

	// スコアの文字距離
	constexpr int kScoreDistance = 30;
}


MainUI::MainUI():
	m_fontHandle(-1),
	m_playerHp(0),
	m_enemyLv(0),
	m_score(0),
	m_pSceneMain(nullptr)
{
	for (auto& score : m_scoreNum)
	{
		score = 0;
	}
}

MainUI::~MainUI()
{
	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// 作成したフォントデータを削除する
	DeleteFontToHandle(m_fontHandle);
}

void MainUI::init()
{
	// フォントの挿入・設定
	m_fontHandle = CreateFontToHandle(kTextFontName, kTextFontSize, 3);


	// プレイヤーのHP
	m_playerHp = SceneMain::kPlayerRemaining;
	// エネミーのレベル
	m_enemyLv = 0;
	// スコア
	m_score = 0;
}

void MainUI::update()
{







}

void MainUI::draw()
{

	for (int i = 0; i < kScoreMaxNum; i++)
	{

		DrawFormatStringToHandle(kScorePosX + (kScoreDistance * i), kScorePosY,
			0xff0000, m_fontHandle, "%d", m_scoreNum[i]);

	}


#if true

	// プレイヤーのHpの描画
	DrawFormatString(0, 15 * 2, 0xffffff, "playerHp : %d", m_playerHp);
	// エネミーのレベルの描画
	DrawFormatString(0, 15 * 3, 0xffffff, "enemyLv : %d", m_enemyLv);
	// スコア
	DrawFormatString(0, 15 * 4, 0xffffff, "score : %d", m_score);


	DrawFormatString(0, 15 * 13, 0xffffff, "1の位:%d", m_scoreNum[3]);
	DrawFormatString(0, 15 * 14, 0xffffff, "10の位:%d", m_scoreNum[2]);
	DrawFormatString(0, 15 * 15, 0xffffff, "100の位:%d", m_scoreNum[1]);
	DrawFormatString(0, 15 * 16, 0xffffff, "1000の位:%d", m_scoreNum[0]);

#endif
}

void MainUI::ScoreArray(int score)
{
	// スコア代入
	m_score = score;


	//1の位
	m_scoreNum[kScoreMaxNum - 1] = (m_score % 10);				


	for (int i = 1; i < kScoreMaxNum; i++)
	{
		int num = pow(10, static_cast<float>((kScoreMaxNum - 1) - i));

		m_scoreNum[i] = ((m_score / (num) % 10));
	}
}

