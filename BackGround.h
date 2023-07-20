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

	// �X�J�C�h�[����]
	void RotSkyDome();


	// ���C���`��
	void DrawLine();
	// �X�J�C�h�[���`��
	void DrawSkyDome();


private:
	// ���f���n���h��
	int m_modelHandle;

	// �p�x
	float m_degree;

};

