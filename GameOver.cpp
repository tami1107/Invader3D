#include "GameOver.h"
#include "Pad.h"
#include "SceneMain.h"

namespace
{
	// ゲームオーバーグラフィックの挿入
	const char* const kGameOverGraphic = "data/gameOver.png";
}


GameOver::GameOver():
	m_graphic(-1),
	m_pSceneMain(nullptr)
{
}

GameOver::~GameOver()
{
	// グラフィックの削除
	DeleteGraph(m_graphic);

	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

}

void GameOver::init()
{
	// グラフィックを挿入する
	m_graphic = LoadGraph(kGameOverGraphic);


}

void GameOver::update()
{
	// ゲームオーバーフラグをfalseする
	if (Pad::isTrigger(PAD_INPUT_10))
	{
		m_pSceneMain->getIsGameOverFlag(false);
		m_pSceneMain->getIsResetFlag(true);
	}
}

void GameOver::draw()
{

	// 画面を薄暗くする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);

	int x1 = 0;
	int y1 = 0;
	int x2 = Game::kScreenWidth;
	int y2 = Game::kScreenHeight;


	//DrawBox(x1, y1, x2, y2, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	VECTOR pos = VGet(0, 50, 0);

	// ゲームオーバーのグラフィック描画
	DrawBillboard3D(pos, 0.5, 0.5, 100.0, 0.0, m_graphic, true);


}
