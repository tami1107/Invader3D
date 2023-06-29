#include "MainUI.h"
#include "game.h"
#include "SceneMain.h"


MainUI::MainUI():
	m_playerHp(0),
	m_enemyLv(0),
	m_score(0),
	m_pSceneMain(nullptr)
{
}

MainUI::~MainUI()
{
	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;
}

void MainUI::init()
{
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
	// プレイヤーのHpの描画
	DrawFormatString(0, 15 * 2, 0xffffff, "playerHp : %d", m_playerHp);
	// エネミーのレベルの描画
	DrawFormatString(0, 15 * 3, 0xffffff, "enemyLv : %d", m_enemyLv);
	// スコア
	DrawFormatString(0, 15 * 4, 0xffffff, "score : %d", m_score);
}
