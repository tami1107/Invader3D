#include "MainUI.h"
#include "game.h"
#include "SceneMain.h"
#include <math.h>

namespace
{
	// 空ハートのグラフィックのファイル名
	const char* const kEmptyHeartGraphicFileName = "data/emptyHeart.png";
	// ハートのグラフィックのファイル名
	const char* const kHeartGraphicFileName = "data/heart.png";
	// 文字フォント
	const char* const kTextFontName = "ベストテン-CRT";




	// 文字フォントサイズ
	constexpr int kTextFontSize = 30;

	// スコアテキスト位置
	constexpr int kScoreTextPosX = 10;
	constexpr int kScoreTextPosY = 10;

	// スコア位置（テキストからの距離）
	constexpr int kTextDistance = 120;
	
	// スコアの文字距離
	constexpr int kScoreDistance = 30;

	// グラフィックのサイズ
	constexpr float kGraphicSize = 0.6;





	// ライフテキスト位置
	constexpr int kLifeTextPosX = 10;
	constexpr int kLifeTextPosY = 50;

	// ライフ位置
	constexpr int kGraphicPosX = 140;
	constexpr int kGraphicPosY = 70;


	// グラフィック同士の距離
	constexpr int kGraphicDistance = 50;






	// エネミーレベルテキスト位置
	constexpr int kLevelTextPosX = 10;
	constexpr int kLevelTextPosY = 90;

	// エネミーレベル位置（テキストからの距離）
	constexpr int kLevelDistance = 120;



}


MainUI::MainUI():
	m_fontHandle(-1),
	m_playerHp(0),
	m_enemyLv(0),
	m_score(0),
	m_pSceneMain(nullptr)
{

	for (auto& handle : m_graphicHandle)
	{
		handle = -1;
	}

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

	// グラフィックの削除
	for (auto& handle : m_graphicHandle)
	{
		DeleteGraph(handle);
	}

	// 作成したフォントデータを削除する
	DeleteFontToHandle(m_fontHandle);
}

void MainUI::init()
{

	// グラフィックの挿入
	m_graphicHandle[0] = LoadGraph(kEmptyHeartGraphicFileName);
	m_graphicHandle[1] = LoadGraph(kHeartGraphicFileName);


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
	// ライフ
	{
		// テキストをずらす値
		int slide = 2;

		// ライフテキスト(影)
		DrawStringToHandle(kLifeTextPosX + slide, kLifeTextPosY + slide, "LIFE :",
			0x696969, m_fontHandle);

		// ライフテキスト
		DrawStringToHandle(kLifeTextPosX, kLifeTextPosY, "LIFE :",
			0xffffff, m_fontHandle);


		for (int i = 0; i < SceneMain::kPlayerRemaining; i++)
		{
			DrawRotaGraph(kGraphicPosX + (kGraphicDistance * i), kGraphicPosY,
				kGraphicSize, 0.0, m_graphicHandle[0], true);
		}

		for (int i = 0; i < m_playerHp; i++)
		{
			DrawRotaGraph(kGraphicPosX + (kGraphicDistance * i), kGraphicPosY,
				kGraphicSize, 0.0, m_graphicHandle[1], true);
		}
	}




	// スコア
	{
		// テキストをずらす値
		int slide = 2;

		// スコアテキスト(影)
		DrawStringToHandle(kScoreTextPosX+ slide, kScoreTextPosY+ slide, "SCORE:",
			0x696969, m_fontHandle);

		// スコアテキスト
		DrawStringToHandle(kScoreTextPosX, kScoreTextPosY, "SCORE:",
			0xffffff, m_fontHandle);


		for (int i = 0; i < kScoreMaxNum; i++)
		{
			// スコア表示（影）
			DrawFormatStringToHandle((kScoreTextPosX + kTextDistance) + (kScoreDistance * i) + slide, kScoreTextPosY + slide,
				0x696969, m_fontHandle, "%d", m_scoreNum[i]);

			// スコア表示
			DrawFormatStringToHandle((kScoreTextPosX + kTextDistance) + (kScoreDistance * i), kScoreTextPosY,
				0xffffff, m_fontHandle, "%d", m_scoreNum[i]);
		}
	}



	// エネミーレベル
	{
		// テキストをずらす値
		int slide = 2;

		// レベルの表示（影）
		DrawFormatStringToHandle(kLevelTextPosX + slide, kLevelTextPosY + slide,
			0x696969, m_fontHandle, "LEVEL: %d", m_enemyLv);


		// レベルの表示
		DrawFormatStringToHandle(kLevelTextPosX, kLevelTextPosY,
			0xffffff, m_fontHandle, "LEVEL: %d", m_enemyLv);
	}





#if false

	// プレイヤーのHpの描画
	DrawFormatString(0, 15 * 2, 0xffffff, "playerHp : %d", m_playerHp);
	// スコア
	DrawFormatString(0, 15 * 4, 0xffffff, "score : %d", m_score);
	// エネミーのレベルの描画
	DrawFormatString(0, 15 * 3, 0xffffff, "enemyLv : %d", m_enemyLv);


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

