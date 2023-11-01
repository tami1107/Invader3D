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

	// �����x(1.0f���s�����A0.0f������)
	static constexpr float kAlphaValue = 0.5f;

	// �p�[�e�B�N���̗�
	static constexpr int kParticleValue = 32;

	// �p�[�e�B�N���̃X�P�[��
	static constexpr float kParticleScale = 5.0;

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

	// �F����Ԃ�
	VECTOR getColor() const { return m_color; }

	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// �ԍ��̎擾
	void setNumber(int number) { m_number = number; }

public:
	// �O���t�B�b�N���󂯎��
	void setGraphic(int handle) { m_modeleHandle = handle; }
public:
	// �_���[�W����
	void DamegeProcess(int damages);

private:

	// �����蔻��
	void Collision2D();

	// �J���[����
	void ColorProcess();

private:

	// 3D���f���n���h��
	int m_modeleHandle;


	// ���݃t���O
	bool m_isExist;


	// �q�b�g�|�C���g
	int m_hp;

	// �ԍ�
	int m_number;


	// �\���ʒu
	VECTOR m_pos;

	// �F�w��
	VECTOR m_color;

	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

