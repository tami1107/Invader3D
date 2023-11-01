#include "GameOver.h"
#include "Pad.h"
#include "SceneMain.h"


namespace
{
	// �����t�H���g
	const char* const kTextFontName = "�x�X�g�e��-CRT";

	// �����t�H���g�T�C�Y
	constexpr int kTextFontSize = 200;

	// �����ʒu
	constexpr int kTextInitPosX = 530;
	constexpr int kTextInitPosY = 300;

	// �U�ꕝ
	constexpr float kSinValue = 10.0f;

	// �T�C���J�[�u�̃X�s�[�h
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
	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(m_fontHandle);

	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;
}

void GameOver::init()
{

	// �t�H���g�̑}���E�ݒ�
	m_fontHandle = CreateFontToHandle(kTextFontName, kTextFontSize, 3);

}

void GameOver::update()
{

	m_textSin += kSinSpeedValue;

	m_posY = sinf(m_textSin) * kSinValue;


	// �Q�[���I�[�o�[�t���O��false����
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_pSceneMain->setIsGameOverFlag(false);
		m_pSceneMain->setIsResetFlag(true);
	}
}

void GameOver::draw()
{

	// �|�[�Y�E�B���h�E�Z���t�@��(����)
	SetDrawBlendMode(DX_BLENDMODE_MULA, 50);

	// �S�̓I�ɈÂ�����
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight,
		0x000000, true);


	// �`��u�����h���[�h���m�[�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	// �e�L�X�g�����炷�l
	int slide = 4;

	// �e�L�X�g(�e)
	DrawStringToHandle(kTextInitPosX + slide, (kTextInitPosY + slide) + m_posY, "GameOver",
		0x696969, m_fontHandle);

	// �e�L�X�g
	DrawStringToHandle(kTextInitPosX, kTextInitPosY + m_posY, "GameOver",
		0xffffff, m_fontHandle);


}
