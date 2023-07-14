#include "BackGround.h"
#include "Enemy.h"


BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::init()
{
	
}

void BackGround::update()
{
}

void BackGround::draw()
{
	//XYZ���A�f�o�b�O�`��
	float lineHeightSize = 1000.0f;
	//DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineHeightSize, 0), VGet(0, lineHeightSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineHeightSize), VGet(0, 0, lineHeightSize), GetColor(0, 0, 255));

	// ���C���̏c��
	float lineWidthPos = EnemySet::kMovePosZ;
	// ���C���̉���
	lineHeightSize = (EnemySet::kLimitMove * EnemySet::kMovePosX) * 2.5;
	// ���C���̗�i0���܂ނ̂�+�P����j
	float lineArray = (EnemySet::kInitPosZ / lineWidthPos) + 1;



	for (int i = 0; i < lineArray; i++)
	{
		DrawLine3D(VGet(-lineHeightSize, 0, lineWidthPos * i), VGet(lineHeightSize, 0, lineWidthPos * i), GetColor(255, 0, 0));
	}

	// ���C�e�B���O�֘A
#if true

	VECTOR Direction = VGet(0, 30, 50);
	ChangeLightTypeDir(Direction);

	// ���̕\��
	DrawSphere3D(Direction, 1.0, 32, 0xffffff, GetColor(0, 0, 0), true);
#endif
}
