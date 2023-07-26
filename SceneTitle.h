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

	// ���f���̈ړ�����
	void ModelMove();


private:

	bool m_isEnd;

	// �t�H���g�n���h��
	int m_fontHandle;

	// �e�L�X�g�̃T�C��
	float m_textSin;

	// �t�F�[�h�l
	float m_fadeValue;

	// ���f���n���h��
	int m_modelHandle;

	// �T�C��
	float m_sinRate;

	// �^�C�g���e�L�X�g�̈ʒu
	VECTOR m_titlePos;

	// ���C�g�̈ʒu
	VECTOR m_lightPos;

	// �N���X�|�C���^
	std::shared_ptr<BackGround>m_pBackGround;
};