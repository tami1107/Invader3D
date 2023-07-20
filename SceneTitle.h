#pragma once
#include "SceneBase.h"
#include "game.h"
#include <memory>

class BackGround;
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
	int m_modelHandle;

	// �T�C��
	float sinRate;

	// �^�C�g���e�L�X�g�̈ʒu
	VECTOR m_titlePos;

	// ���C�g�̈ʒu
	VECTOR m_lightPos;

	// �N���X�|�C���^
	std::shared_ptr<BackGround>m_pBackGround;
};