#pragma once
#include "SceneBase.h"
#include "game.h"


class SceneTitle : public SceneBase
{


public:
	SceneTitle();

	virtual ~SceneTitle();


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }

public:



private:

	bool m_isEnd;

	// ���f���n���h��
	int m_modelHandle[3];

	// �e�L�X�g�̈ړ��ʒu
	//VECTOR m_textMove[2];



};