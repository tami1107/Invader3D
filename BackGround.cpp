#include "BackGround.h"
#include "game.h"


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
	float lineSize = 1000.0f;
	DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

	float linePos = 10;
	lineSize = 100.0f;

	for (int i = 0; i < 10; i++)
	{
		DrawLine3D(VGet(-lineSize, 0, linePos * i), VGet(lineSize, 0, linePos * i), GetColor(255, 0, 0));

	}
}
