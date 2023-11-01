#include "GameOver.h"
#include "Pad.h"
#include "SceneMain.h"


namespace
{
	// 文字フォント
	const char* const kTextFontName = "ベストテン-CRT";

	// 文字フォントサイズ
	constexpr int kTextFontSize = 200;

	// 文字位置
	constexpr int kTextInitPosX = 530;
	constexpr int kTextInitPosY = 300;

	// 振れ幅
	constexpr float kSinValue = 10.0f;

	// サインカーブのスピード
	constexpr float kSinSpeedValue = 0.05f;

}

GameOver::GameOver():
	m_fontHandle(-1),
	m_textSin(0.0f),
	m_posY(0),
	m_pSceneMain(nullptr)
{
}

GameOver::~GameOver()
{
	// 作成したフォントデータを削除する
	DeleteFontToHandle(m_fontHandle);

	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;
}

void GameOver::init()
{

	// フォントの挿入・設定
	m_fontHandle = CreateFontToHandle(kTextFontName, kTextFontSize, 3);

}

void GameOver::update()
{

	m_textSin += kSinSpeedValue;

	m_posY = sinf(m_textSin) * kSinValue;


	// ゲームオーバーフラグをfalseする
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_pSceneMain->setIsGameOverFlag(false);
		m_pSceneMain->setIsResetFlag(true);
	}
}

void GameOver::draw()
{

	// ポーズウィンドウセロファン(黒い)
	SetDrawBlendMode(DX_BLENDMODE_MULA, 50);

	// 全体的に暗くする
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight,
		0x000000, true);


	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	// テキストをずらす値
	int slide = 4;

	// テキスト(影)
	DrawStringToHandle(kTextInitPosX + slide, (kTextInitPosY + slide) + m_posY, "GameOver",
		0x696969, m_fontHandle);

	// テキスト
	DrawStringToHandle(kTextInitPosX, kTextInitPosY + m_posY, "GameOver",
		0xffffff, m_fontHandle);


}
