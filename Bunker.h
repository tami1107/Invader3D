#pragma once
#include "game.h"

class SceneMain;
class Bunker
{
public:
	// �����T�C�Y
	static constexpr float kCircleSize = 2.0f;

	// �J���[R
	static constexpr float kCollarR = 0.0f;
	// �J���[G
	static constexpr float kCollarG = 1.0f;
	// �J���[B
	static constexpr float kCollarB = 0.0f;

public:
	Bunker();
	virtual ~Bunker();

	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX);

	void update();

	void draw();

	// �ʒu����Ԃ�
	VECTOR getPos() const { return m_pos; }


	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }


public:
	// �O���t�B�b�N���󂯎��
	void getGraphic(int handle) { m_modeleHandle = handle; }
public:
	// �_���[�W����
	void DamegeProcess(int damages);

	// �����蔻��
	void Collision2D();

private:

	// 3D���f���n���h��
	int m_modeleHandle;


	// ���݃t���O
	bool m_isExist;


	// �q�b�g�|�C���g
	int m_hp;

	// �A���t�@�u�����h�̒l
	int m_alphaValue;

	// �A���t�@�u�����h�̌����l
	int m_alphaValueDecrement;


	// �\���ʒu
	VECTOR m_pos;
	
	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

