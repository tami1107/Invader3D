#include "game.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"
#include "BackGround.h"

namespace
{
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
	m_modelHandle(-1),
	m_lightPos(),
	m_titlePos(),
	sinRate(0.0f),
	m_pBackGround(std::make_shared<BackGround>())
{

}

SceneTitle::~SceneTitle()
{
	// ���f���̍폜
	MV1DeleteModel(m_modelHandle);

}

void SceneTitle::init()
{
	// �J������ ��O�N���b�v������ ���N���b�v������ݒ肷��
	SetCameraNearFar(0.1f, 1000.0f);
	// �J�����̉�]�p�x
	SetCameraPositionAndAngle(VGet(0,0,-100), 0.0f, 0.0f, 0.0f);

	// ���f��������
	m_modelHandle = MV1LoadModel(kModelGraphicFileName);

	m_titlePos = VGet(kModelInitPosX, kModelInitPosY, kModelInitPosZ);

	// ���f���̈ʒu
	MV1SetPosition(m_modelHandle, m_titlePos);

	// �R�c���f���̃X�P�[���ݒ�
	MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));


	// ���C�g�̏����ʒu
	m_lightPos = VGet(kLightInitPosX, kLightInitPosY, kLightInitPosZ);

	// �N���X�̏���������
	m_pBackGround->init(0);

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	

	sinRate += kSinSpeedValue;

	float moveY = sinf(sinRate) * kSinValue;

	m_titlePos = VGet(kModelInitPosX, kModelInitPosY + moveY, kModelInitPosY);

	// ���f���̈ʒu
	MV1SetPosition(m_modelHandle, m_titlePos);
	


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


	DrawString(0, 0, "�^�C�g�����", GetColor(255, 255, 255));
}