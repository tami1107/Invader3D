#pragma once
#include <memory>
#include "Vec2.h"


class SceneMain;
class Pause
{
public:
	Pause();
	virtual ~Pause();

	// �|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }

	void init();
	void update();
	void draw();

public:
	// �|�[�Y����
	void PauseProcess();

	// �I������
	void SelectProcess();

	// �t���[���̕`��
	void DrawFrame();


	// ���ڃe�L�X�g�̕`��
	void DrawSelectText();

	// �^�C�g���ɖ߂�I�����̏���
	void TitleSelectProcess();

private:


	// �|�[�Y�����ǂ���
	bool m_isPause;

	// �I��ԍ�
	int m_selectNum;

	// ���ڑI�����̈ړ��C���^�[�o��
	int m_selectInterval;

	// �����t�H���g
	int m_textFont;

	// �T�C��
	float sinRate;

	// �^�C�g���ɖ߂邩�ǂ����̃t���O
	int m_titleFlag;

	// �I��ԍ�(�^�C�g���ɖ߂�Ƃ��̔ԍ�)
	int m_selectNum2;



	// ���W���
	Vec2 m_pos;




	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

