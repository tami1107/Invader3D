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
	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;
}

void MainUI::init()
{
	// �v���C���[��HP
	m_playerHp = SceneMain::kPlayerRemaining;
	// �G�l�~�[�̃��x��
	m_enemyLv = 0;
	// �X�R�A
	m_score = 0;
}

void MainUI::update()
{
}

void MainUI::draw()
{
	// �v���C���[��Hp�̕`��
	DrawFormatString(0, 15 * 2, 0xffffff, "playerHp : %d", m_playerHp);
	// �G�l�~�[�̃��x���̕`��
	DrawFormatString(0, 15 * 3, 0xffffff, "enemyLv : %d", m_enemyLv);
	// �X�R�A
	DrawFormatString(0, 15 * 4, 0xffffff, "score : %d", m_score);
}
