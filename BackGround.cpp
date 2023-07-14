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
	//XYZ軸、デバッグ描写
	float lineHeightSize = 1000.0f;
	//DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineHeightSize, 0), VGet(0, lineHeightSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineHeightSize), VGet(0, 0, lineHeightSize), GetColor(0, 0, 255));

	// ラインの縦幅
	float lineWidthPos = EnemySet::kMovePosZ;
	// ラインの横幅
	lineHeightSize = (EnemySet::kLimitMove * EnemySet::kMovePosX) * 2.5;
	// ラインの列（0も含むので+１する）
	float lineArray = (EnemySet::kInitPosZ / lineWidthPos) + 1;



	for (int i = 0; i < lineArray; i++)
	{
		DrawLine3D(VGet(-lineHeightSize, 0, lineWidthPos * i), VGet(lineHeightSize, 0, lineWidthPos * i), GetColor(255, 0, 0));
	}

	// ライティング関連
#if true

	VECTOR Direction = VGet(0, 30, 50);
	ChangeLightTypeDir(Direction);

	// 球の表示
	DrawSphere3D(Direction, 1.0, 32, 0xffffff, GetColor(0, 0, 0), true);
#endif
}
