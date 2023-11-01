#include "MainUI.h"
#include "game.h"
#include "SceneMain.h"
#include "Player.h"
#include <math.h>

namespace
{
	// ��n�[�g�̃O���t�B�b�N�̃t�@�C����
	const char* const kEmptyHeartGraphicFileName = "data/emptyHeart.png";
	// �n�[�g�̃O���t�B�b�N�̃t�@�C����
	const char* const kHeartGraphicFileName = "data/heart.png";
	// �����t�H���g
	const char* const kTextFontName = "�x�X�g�e��-CRT";

	// �����O���t�B�b�N�n���h��
	const char* const kTextGraphicFileName = "data/levelUp.png";

	// �_���[�W�O���t�B�b�N�n���h��
	const char* const kDamageGraphicFileName = "data/damage.png";

	// �����t�H���g�T�C�Y
	constexpr int kTextFontSize = 30;

	// �����O���t�B�b�N�T�C�Y
	constexpr float kTextGraphicSize = 1.0;


	// �X�R�A�e�L�X�g�ʒu
	constexpr int kScoreTextPosX = 10;
	constexpr int kScoreTextPosY = 10;

	// �X�R�A�ʒu�i�e�L�X�g����̋����j
	constexpr int kTextDistance = 120;
	
	// �X�R�A�̕�������
	constexpr int kScoreDistance = 30;

	// �O���t�B�b�N�̃T�C�Y
	constexpr float kGraphicSize = 0.6;


	// �e�L�X�g�O���t�B�b�N�ʒu
	constexpr int kTextGraphicPosX = -400;
	constexpr int kTextGraphicPosY = Game::kScreenHeight * 0.5;

	// �e�L�X�g���~�߂鎞��
	constexpr int kTextStopCount = 50;

	// �e�L�X�g�̈ړ��X�s�[�h
	constexpr int kTextMoveSpeed = 30;

	// �e�L�X�g�̉�ʊO�ʒu
	constexpr int kTextGraphicOutPosX = Game::kScreenWidth + 50;


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


	// �O���t�B�b�N�t�@�C����
	const char* const kTimerGraphicFileName = "data/test.png";


	// �c���̐�
	constexpr int kAfterimageNum = 5;

	// �c���̒l
	constexpr float kAfterimageValue = 0.2;

	// �c���̓����x
	constexpr int kAfterimageAlpha = 100;

	// �^�C�}�[�O���t�B�b�N�T�C�Y
	constexpr float kTimerGraphicSize = 1.0;

	// HP�̓����x
	constexpr int kAlpha = 255;


	// �����̐U�ꕝ
	constexpr float kSinValue = 255.0f;

	// �����̃T�C���J�[�u�̃X�s�[�h
	constexpr float kSinSpeedValue = 0.03f;
}


MainUI::MainUI() :
	m_fontHandle(-1),
	m_playerHp(0),
	m_enemyLv(0),
	m_score(0),
	m_textHandle(-1),
	m_textPos(Vec2()),
	m_isTextMove(false),
	m_textStopCount(0),
	m_timer(0),
	m_percentage(0),
	m_damageHandle(-1),
	m_sin(0.0f)
{

	for (auto& handle : m_graphicHandle)
	{
		handle = -1;
	}
	for (auto& handle : m_timerHandle)
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

	// �O���t�B�b�N�̍폜
	for (auto& handle : m_graphicHandle)
	{
		DeleteGraph(handle);
	}
	for (auto& handle : m_timerHandle)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_textHandle);
	DeleteGraph(m_damageHandle);


	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(m_fontHandle);
}

void MainUI::init()
{

	// �O���t�B�b�N�̑}��
	m_graphicHandle[0] = LoadGraph(kEmptyHeartGraphicFileName);
	m_graphicHandle[1] = LoadGraph(kHeartGraphicFileName);
	m_textHandle = LoadGraph(kTextGraphicFileName);
	m_damageHandle = LoadGraph(kDamageGraphicFileName);

	int W = 0;// �O���t�B�b�N�̉���
	int H = 0;// �O���t�B�b�N�̏c��
	int G = 0;// �O���t�B�b�N�̑��


	// �O���t�B�b�N�T�C�Y���擾
	{
		G = LoadGraph(kTimerGraphicFileName);
		GetGraphSize(G, &W, &H);
	}

	LoadDivGraph(kTimerGraphicFileName, kGraphicDivNum,
		kGraphicDivX, kGraphicDivY,
		W / kGraphicDivX, H / kGraphicDivY, m_timerHandle);





	// �t�H���g�̑}���E�ݒ�
	m_fontHandle = CreateFontToHandle(kTextFontName, kTextFontSize, 3);

	// �e�L�X�g�̕\���ʒu
	m_textPos = Vec2(kTextGraphicPosX, kTextGraphicPosY);
	// �e�L�X�g�X�g�b�v�J�E���g
	m_textStopCount = kTextStopCount;


	// �v���C���[��HP
	m_playerHp = SceneMain::kPlayerRemaining;
	// �G�l�~�[�̃��x��
	m_enemyLv = 0;
	// �X�R�A
	m_score = 0;


	// �^�C�}�[�ɍő�b������
	m_timer = Player::kPowerUpMaxNum;
}

void MainUI::update()
{


	// �e�L�X�g����
	TextProcess();



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

	// �_���[�W����
	DamageProcess();





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
	m_score += score;

	// ����ꂽ���l��0�������ꍇ�Am_score��0�ɂ���
	if (score == 0)
	{
		m_score = 0;
	}


	//1�̈�
	m_scoreNum[kScoreMaxNum - 1] = (m_score % 10);				


	for (int i = 1; i < kScoreMaxNum; i++)
	{
		int num = pow(10, static_cast<float>((kScoreMaxNum - 1) - i));

		m_scoreNum[i] = ((m_score / (num) % 10));
	}
}

void MainUI::TextProcess()
{

	// m_isTextMove��false�Ȃ炱���ŏ������I������
	if (!m_isTextMove)return;

	// �e�L�X�g����ʊO�ɍs�����Ƃ�
	if (m_textPos.x >= kTextGraphicOutPosX)
	{
		m_isTextMove = false;

		// �e�L�X�g�̕\���ʒu
		m_textPos = Vec2(kTextGraphicPosX, kTextGraphicPosY);
		// �e�L�X�g�X�g�b�v�J�E���g
		m_textStopCount = kTextStopCount;
	}

	// �e�L�X�g�̈ʒu�����S�܂ŗ��ĂȂ����e�L�X�g�J�E���g�̒l��0�Ȃ�΃e�L�X�g�̓������~�߂�
	if (m_textPos.x >= Game::kScreenWidth * 0.5 && m_textStopCount != 0)
	{
		m_textStopCount--;
	}
	else
	{
		m_textPos.x += kTextMoveSpeed;
	}



	// �e�L�X�g�`�揈��
	DrawRotaGraph(m_textPos.x, m_textPos.y,
		kTextGraphicSize, 0.0, m_textHandle, true);


}

void MainUI::TimerProcess(int timer)
{

	// m_timer�����炵�A0�ɂȂ�ƍő�l�ɖ߂�
	{
		m_timer--;
	}

	// m_timer�̃p�[�Z���g�����߂�
	{
		// ����
		float ratio = 100.0 * timer;

		// �p�[�Z���g������
		m_percentage = ratio / Player::kPowerUpMaxFrame;
	}



	// �`�揈��
	{
		float H = timer * (512.0f / Player::kPowerUpMaxFrame) - 100;

		int R = min(max((384 - H), 0), 0xff);

		int G = min(max((H + 64), 0), 0xff);

		int B = max((H - 384), 0);

		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);

			// �~�`�ŕ\��
			DrawCircleGauge(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
				100, m_timerHandle[1], 0.0, kTimerGraphicSize, 0, 0);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);           //�u�����h���[�h���I�t
		}


		SetDrawBright(R, G, B);

		// �~�`�ŕ\��
		DrawCircleGauge(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
			m_percentage, m_timerHandle[0], 0.0, kTimerGraphicSize, 0, 0);



		// �c������
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAfterimageAlpha);             //�u�����h���[�h�����Z(255/255)�ɐݒ�

			// �c���̃p�[�Z���g
			float afterimagePercentage = 0.0;

			for (int i = 0; i < kAfterimageNum; i++)
			{

				// �c���̃p�[�Z���g�����߂�
				afterimagePercentage = m_percentage + (kAfterimageValue * i);

				// �~�`�ŕ\��
				DrawCircleGauge(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
					afterimagePercentage, m_timerHandle[0], 0.0, kTimerGraphicSize, 0, 0);

			}



			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);           //�u�����h���[�h���I�t
		}
		

		SetDrawBright(255, 255, 255);
	}

}

void MainUI::DamageProcess()
{
	if (m_playerHp != 1)return;

	m_sin += kSinSpeedValue;

	m_fadeValue = (((sinf(m_sin) * kSinValue) + kSinValue) / 2);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeValue);

	DrawModiGraph(0, 0, Game::kScreenWidth, 0,
		Game::kScreenWidth, Game::kScreenHeight, 0, Game::kScreenHeight,
		m_damageHandle, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);           //�u�����h���[�h���I�t

}
