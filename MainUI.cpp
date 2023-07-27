#include "MainUI.h"
#include "game.h"
#include "SceneMain.h"
#include <math.h>

namespace
{
	// ��n�[�g�̃O���t�B�b�N�̃t�@�C����
	const char* const kEmptyHeartGraphicFileName = "data/emptyHeart.png";
	// �n�[�g�̃O���t�B�b�N�̃t�@�C����
	const char* const kHeartGraphicFileName = "data/heart.png";
	// �����t�H���g
	const char* const kTextFontName = "�x�X�g�e��-CRT";




	// �����t�H���g�T�C�Y
	constexpr int kTextFontSize = 30;

	// �X�R�A�e�L�X�g�ʒu
	constexpr int kScoreTextPosX = 10;
	constexpr int kScoreTextPosY = 10;

	// �X�R�A�ʒu�i�e�L�X�g����̋����j
	constexpr int kTextDistance = 120;
	
	// �X�R�A�̕�������
	constexpr int kScoreDistance = 30;

	// �O���t�B�b�N�̃T�C�Y
	constexpr float kGraphicSize = 0.6;





	// ���C�t�e�L�X�g�ʒu
	constexpr int kLifeTextPosX = 10;
	constexpr int kLifeTextPosY = 50;

	// ���C�t�ʒu
	constexpr int kGraphicPosX = 140;
	constexpr int kGraphicPosY = 70;


	// �O���t�B�b�N���m�̋���
	constexpr int kGraphicDistance = 50;






	// �G�l�~�[���x���e�L�X�g�ʒu
	constexpr int kLevelTextPosX = 10;
	constexpr int kLevelTextPosY = 90;

	// �G�l�~�[���x���ʒu�i�e�L�X�g����̋����j
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
	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// �O���t�B�b�N�̍폜
	for (auto& handle : m_graphicHandle)
	{
		DeleteGraph(handle);
	}

	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(m_fontHandle);
}

void MainUI::init()
{

	// �O���t�B�b�N�̑}��
	m_graphicHandle[0] = LoadGraph(kEmptyHeartGraphicFileName);
	m_graphicHandle[1] = LoadGraph(kHeartGraphicFileName);


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
		// �e�L�X�g�����炷�l
		int slide = 2;

		// ���C�t�e�L�X�g(�e)
		DrawStringToHandle(kLifeTextPosX + slide, kLifeTextPosY + slide, "LIFE :",
			0x696969, m_fontHandle);

		// ���C�t�e�L�X�g
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




	// �X�R�A
	{
		// �e�L�X�g�����炷�l
		int slide = 2;

		// �X�R�A�e�L�X�g(�e)
		DrawStringToHandle(kScoreTextPosX+ slide, kScoreTextPosY+ slide, "SCORE:",
			0x696969, m_fontHandle);

		// �X�R�A�e�L�X�g
		DrawStringToHandle(kScoreTextPosX, kScoreTextPosY, "SCORE:",
			0xffffff, m_fontHandle);


		for (int i = 0; i < kScoreMaxNum; i++)
		{
			// �X�R�A�\���i�e�j
			DrawFormatStringToHandle((kScoreTextPosX + kTextDistance) + (kScoreDistance * i) + slide, kScoreTextPosY + slide,
				0x696969, m_fontHandle, "%d", m_scoreNum[i]);

			// �X�R�A�\��
			DrawFormatStringToHandle((kScoreTextPosX + kTextDistance) + (kScoreDistance * i), kScoreTextPosY,
				0xffffff, m_fontHandle, "%d", m_scoreNum[i]);
		}
	}



	// �G�l�~�[���x��
	{
		// �e�L�X�g�����炷�l
		int slide = 2;

		// ���x���̕\���i�e�j
		DrawFormatStringToHandle(kLevelTextPosX + slide, kLevelTextPosY + slide,
			0x696969, m_fontHandle, "LEVEL: %d", m_enemyLv);


		// ���x���̕\��
		DrawFormatStringToHandle(kLevelTextPosX, kLevelTextPosY,
			0xffffff, m_fontHandle, "LEVEL: %d", m_enemyLv);
	}





#if false

	// �v���C���[��Hp�̕`��
	DrawFormatString(0, 15 * 2, 0xffffff, "playerHp : %d", m_playerHp);
	// �X�R�A
	DrawFormatString(0, 15 * 4, 0xffffff, "score : %d", m_score);
	// �G�l�~�[�̃��x���̕`��
	DrawFormatString(0, 15 * 3, 0xffffff, "enemyLv : %d", m_enemyLv);


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

