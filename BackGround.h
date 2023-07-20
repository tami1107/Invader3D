#pragma once
#include "game.h"

class BackGround
{
public:
	BackGround();
	virtual ~BackGround();

	void init(int num);
	void update();
	void draw();

public:

	// スカイドーム回転
	void RotSkyDome();


	// ライン描画
	void DrawLine();
	// スカイドーム描画
	void DrawSkyDome();


private:
	// モデルハンドル
	int m_modelHandle;

	// 角度
	float m_degree;

};

