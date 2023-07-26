#include "game.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"
#include "BackGround.h"

namespace
{
	// �����t�H���g
	const char* const kTextFontName = "NULL";

	// �����t�H���g�T�C�Y
	constexpr int kTextFontSize = 60;

	// �����ʒu
	constexpr int kTextInitPosX = 650;
	constexpr int kTextInitPosY = 650;

	// ����
	const char* const kText = "- P u s h ' A ' -";

	// �����̐U�ꕝ
	constexpr float kTextSinValue = 255.0f;

	// �����̃T�C���J�[�u�̃X�s�[�h
	constexpr float kTextSinSpeedValue = 0.03f;



	// ���f���̃O���t�B�b�N�t�@�C����
	const char* const kModelGraphicFileName = "data/model/text.mv1";

	// ���f���̏����ʒu
	constexpr int kModelInitPosX = 0;
	constexpr int kModelInitPosY = 15;
	constexpr int kModelInitPosZ = 0;

	// ���f���̃X�P�[��
	constexpr float kModelScale = 1.5f;

	// ���C�g�̏����ʒu
	constexpr int kLightInitPosX = 0;
	constexpr int kLightInitPosY = 30;
	constexpr int kLightInitPosZ = 40;

	// �U�ꕝ
	constexpr float kSinValue = 2.0f;

	// �T�C���J�[�u�̃X�s�[�h
	constexpr float kSinSpeedValue = 0.01f;
}


SceneTitle::SceneTitle() :
	m_isEnd(false),
	m_fontHandle(-1),
	m_textSin(2.0f),
	m_fadeValue(0.0f),
	m_modelHandle(-1),
	m_lightPos(),
	m_titlePos(),
	m_sinRate(0.0f),
	m_pBackGround(std::make_shared<BackGround>())
{

}

SceneTitle::~SceneTitle()
{
	// ���f���̍폜
	MV1DeleteModel(m_modelHandle);

	// �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle(m_fontHandle);
}

void SceneTitle::init()
{

	// �t�H���g�̑}���E�ݒ�
	m_fontHandle = CreateFontToHandle(kTextFontName, kTextFontSize, 3);


	{
		// �J������ ��O�N���b�v������ ���N���b�v������ݒ肷��
		SetCameraNearFar(0.1f, 1000.0f);
		// �J�����̉�]�p�x
		SetCameraPositionAndAngle(VGet(0,0,-100), 0.0f, 0.0f, 0.0f);
	}

	{
		// ���f��������
		m_modelHandle = MV1LoadModel(kModelGraphicFileName);

		m_titlePos = VGet(kModelInitPosX, kModelInitPosY, kModelInitPosZ);

		// ���f���̈ʒu
		MV1SetPosition(m_modelHandle, m_titlePos);

		// �R�c���f���̃X�P�[���ݒ�
		MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));
	}

	// ���C�g�̏����ʒu
	m_lightPos = VGet(kLightInitPosX, kLightInitPosY, kLightInitPosZ);

	// �N���X�̏���������
	m_pBackGround->init(0);

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	

	m_textSin += kTextSinSpeedValue;

	m_fadeValue = (((sinf(m_textSin) * kTextSinValue)+ kTextSinValue)/2);



	// ���f���̈ړ�����
	ModelMove();



	


	// �N���X�̃A�b�v�f�[�g����
	m_pBackGround->update();

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// Main�ɐ؂�ւ�
		return(new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{

	// �e�L�X�g
	{

		// �����ɂ��ĕ\������
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_fadeValue));

		int slide = 4;

		// �e�݂����ȕ\��
		DrawFormatStringToHandle(kTextInitPosX + slide, kTextInitPosY + slide,
			0x000000, m_fontHandle, kText);

		DrawFormatStringToHandle(kTextInitPosX, kTextInitPosY,
			0xff0000, m_fontHandle, kText);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	{
		VECTOR Direction = m_lightPos;
		ChangeLightTypeDir(Direction);

		// ���̕\��
		DrawSphere3D(Direction, 2.0, 32, 0xffffff, GetColor(0, 0, 0), true);
	}

	// ���f���`��
	MV1DrawModel(m_modelHandle);


	// �N���X�̕`�揈��
	m_pBackGround->draw();



	//XYZ���A�f�o�b�O�`��
	float lineHeightSize = 1000.0f;
	DrawLine3D(VGet(-lineHeightSize, 0, 0), VGet(lineHeightSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineHeightSize, 0), VGet(0, lineHeightSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineHeightSize), VGet(0, 0, lineHeightSize), GetColor(0, 0, 255));


#if true
	
	DrawString(0, 0, "�^�C�g�����", GetColor(255, 255, 255));

	DrawFormatString(0, 15 * 1, 0xffffff, "m_fadeValue=%f", m_fadeValue);

#endif


}

void SceneTitle::ModelMove()
{
	m_sinRate += kSinSpeedValue;

	float moveY = sinf(m_sinRate) * kSinValue;

	m_titlePos = VGet(kModelInitPosX, kModelInitPosY + moveY, kModelInitPosY);

	// ���f���̈ʒu
	MV1SetPosition(m_modelHandle, m_titlePos);
}
