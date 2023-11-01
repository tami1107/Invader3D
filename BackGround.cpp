#include "BackGround.h"
#include "Enemy.h"

namespace
{
	// ���f���̃O���t�B�b�N�t�@�C����
	const char* const kModelGraphicFileName = "data/model/Dome_Y301.mv1";

	// �����Ă����p�x�̒l
	constexpr float kDegreeAdd = 0.02;
}


BackGround::BackGround():
	m_modelHandle(-1),
	m_degree(0)
{
}

BackGround::~BackGround()
{
	// ���f���̍폜
	MV1DeleteModel(m_modelHandle);
}

void BackGround::init(int num)
{
	// �X�J�C�h�[���̃��f��������
	m_modelHandle = MV1LoadModel(kModelGraphicFileName);

	switch (num)
	{
	case 0:
		// �X�J�C�h�[���̒��S�ʒu
		MV1SetPosition(m_modelHandle, VGet(0, 0, -200));
		break;
	case 1:
		// �X�J�C�h�[���̒��S�ʒu
		MV1SetPosition(m_modelHandle, VGet(0, 200, 0));
		break;
	}

}

void BackGround::update()
{
	// �X�J�C�h�[���̉�]����
	RotSkyDome();
}

void BackGround::draw()
{
	// ���C���̕`��
	DrawLine();

	// �X�J�C�h�[���`��
	DrawSkyDome();


	// ���C�e�B���O�֘A
#if true
	VECTOR Direction = VGet(0, 30, 50);
	ChangeLightTypeDir(Direction);

	// ���̕\��
	DrawSphere3D(Direction, 1.0, 32, 0xffffff, GetColor(0, 0, 0), true);
#endif
}

void BackGround::RotSkyDome()
{
	// �p�x�̒l�𑝂₷
	m_degree += kDegreeAdd;

	// �p�x�̒l��360���𒴂����ꍇ�A0�ɂ���
	if (m_degree >= 360.0f)
	{
		m_degree = 0.0f;
	}

	// ���W�A���ϊ�
	float rot = m_degree * (DX_PI / 180);


	MV1SetRotationXYZ(m_modelHandle, VGet(0,rot,0));
}

void BackGround::DrawLine()
{
	//XYZ���A�f�o�b�O�`��
	float lineHeightSize = 1000.0f;
	//DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineHeightSize, 0), VGet(0, lineHeightSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineHeightSize), VGet(0, 0, lineHeightSize), GetColor(0, 0, 255));

	// ���C���̏c��
	float lineWidthPos = EnemySet::kMovePosZ;
	

	lineHeightSize = EnemySet::kLimitMove * 1.1;
	// ���C���̗�i0���܂ނ̂�+�P����j
	float lineArray = (EnemySet::kInitPosZ / lineWidthPos) + 1;



	for (int i = 0; i < lineArray; i++)
	{
		DrawLine3D(VGet(-lineHeightSize, 0, lineWidthPos * i), VGet(lineHeightSize, 0, lineWidthPos * i), GetColor(255, 0, 0));
	}
}

void BackGround::DrawSkyDome()
{
	// �X�J�C�h�[���`��
	MV1DrawModel(m_modelHandle);
}
