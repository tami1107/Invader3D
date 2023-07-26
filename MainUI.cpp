#include "MainUI.h"
#include "game.h"
#include "SceneMain.h"
#include <math.h>

namespace
{
	// �n�[�g�̃O���t�B�b�N�̃t�@�C����
	const char* const kGraphicFileName = "data/heart.png";

	// �O���t�B�b�N�̃T�C�Y
	constexpr float kGraphicSize = 0.5;

	// �O���t�B�b�N�̈ʒu
	constexpr int kGraphicPosX = 100;
	constexpr int kGraphicPosY = 100;

	// �O���t�B�b�N���m�̋���
	constexpr int kGraphicDistance = 30;



	// �����t�H���g
	const char* const kTextFontName = "NULL";

	// �����t�H���g�T�C�Y
	constexpr int kTextFontSize = 50;

	// �X�R�A�ʒu
	constexpr int kScorePosX = 10;
	constexpr int kScorePosY = 10;

	// �X�R�A�̕�������
	constexpr int kScoreDistance = 30;
}


MainUI::MainUI():
	m_graphicHandle(-1),
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
	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// �O���t�B�b�N�̍폜
	DeleteGraph(m_graphicHandle);

	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(m_fontHandle);
}

void MainUI::init()
{

	// �O���t�B�b�N�̑}��
	m_graphicHandle = LoadGraph(kGraphicFileName);

	// �t�H���g�̑}���E�ݒ�
	m_fontHandle = CreateFontToHandle(kTextFontName, kTextFontSize, 3);


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
	// ���C�t
	{
		for (int i = 0; i < m_playerHp; i++)
		{

			DrawRotaGraph(kGraphicPosX + (kGraphicDistance * i), kGraphicPosY,
				kGraphicSize, 0.0, m_graphicHandle, true);

		}
	}






	// �X�R�A
	{
		for (int i = 0; i < kScoreMaxNum; i++)
		{

			DrawFormatStringToHandle(kScorePosX + (kScoreDistance * i), kScorePosY,
				0xff0000, m_fontHandle, "%d", m_scoreNum[i]);

		}
	}

#if true

	// �v���C���[��Hp�̕`��
	DrawFormatString(0, 15 * 2, 0xffffff, "playerHp : %d", m_playerHp);
	// �G�l�~�[�̃��x���̕`��
	DrawFormatString(0, 15 * 3, 0xffffff, "enemyLv : %d", m_enemyLv);
	// �X�R�A
	DrawFormatString(0, 15 * 4, 0xffffff, "score : %d", m_score);


	DrawFormatString(0, 15 * 13, 0xffffff, "1�̈�:%d", m_scoreNum[3]);
	DrawFormatString(0, 15 * 14, 0xffffff, "10�̈�:%d", m_scoreNum[2]);
	DrawFormatString(0, 15 * 15, 0xffffff, "100�̈�:%d", m_scoreNum[1]);
	DrawFormatString(0, 15 * 16, 0xffffff, "1000�̈�:%d", m_scoreNum[0]);

#endif
}

void MainUI::ScoreArray(int score)
{
	// �X�R�A���
	m_score = score;


	//1�̈�
	m_scoreNum[kScoreMaxNum - 1] = (m_score % 10);				


	for (int i = 1; i < kScoreMaxNum; i++)
	{
		int num = pow(10, static_cast<float>((kScoreMaxNum - 1) - i));

		m_scoreNum[i] = ((m_score / (num) % 10));
	}
}

