#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"

namespace
{
	// ���f���̃O���t�B�b�N�t�@�C����
	const char* const kModelGraphicFileName = "data/model/text.mv1";

	//// ���f���̃O���t�B�b�N�t�@�C����
	//const char* const kModelGraphicFileName = "data/model/text.mv1";

	//// ���f���̃O���t�B�b�N�t�@�C����
	//const char* const kModelGraphicFileName = "data/model/text.mv1";


	// ���f���̏����ʒu
	constexpr int kInitPosX = 0;
	constexpr int kInitPosY = 20;
	constexpr int kInitPosZ = 0;
}


SceneTitle::SceneTitle() :
	m_isEnd(false)
{
	//// �ʒu���̏�����
	//for (auto& textMove : m_textMove)
	//{
	//	textMove = VGet(0, 0, 0);
	//}
}

SceneTitle::~SceneTitle()
{
	// ���f���̍폜
	MV1DeleteModel(m_modelHandle[0]);
}

void SceneTitle::init()
{
	// �J������ ��O�N���b�v������ ���N���b�v������ݒ肷��
	SetCameraNearFar(0.1f, 1000.0f);
	// �J�����̉�]�p�x
	SetCameraPositionAndAngle(VGet(0,0,-100), 0.0f, 0.0f, 0.0f);

	// ���f��������
	m_modelHandle[0] = MV1LoadModel(kModelGraphicFileName);

	// ���f���̈ʒu
	MV1SetPosition(m_modelHandle[0], VGet(kInitPosX, kInitPosY, kInitPosZ));

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	
	
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// Main�ɐ؂�ւ�
		return(new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{


	//VECTOR Direction = VGet(0, 30, 50);
	//ChangeLightTypeDir(Direction);

	//// ���̕\��
	//DrawSphere3D(Direction, 1.0, 32, 0xffffff, GetColor(0, 0, 0), true);


	// �X�J�C�h�[���`��
	MV1DrawModel(m_modelHandle[0]);

	//XYZ���A�f�o�b�O�`��
	float lineHeightSize = 1000.0f;
	DrawLine3D(VGet(-lineHeightSize, 0, 0), VGet(lineHeightSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineHeightSize, 0), VGet(0, lineHeightSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineHeightSize), VGet(0, 0, lineHeightSize), GetColor(0, 0, 255));


	DrawString(0, 0, "�^�C�g�����", GetColor(255, 255, 255));
}