#pragma once
#include "game.h"

class SceneMain;
class Enemy
{
public:
	// �����T�C�Y
	static constexpr float kCircleSize = 5.0f;

	// �G�l�~�[�O���t�B�b�N��
	static constexpr int kEnemyGraphicNum = 2;

	// �������W
	static constexpr float kInitPosZ = 100.0f;

	// �ړ���X
	static constexpr float kMovePosX = 5.0f;

	// �ړ���Z
	static constexpr float kMovePosZ = 10.0f;

	// �ǂ��܂ňړ�����̂� (kMovePosX * kLimitMove)
	static constexpr int kLimitMove = 6;

public:
	Enemy();
	virtual ~Enemy();

	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX, int savePosZ);

	void update();
	
	void draw();

	// �ʒu����Ԃ�
	VECTOR getPos() const { return m_pos; }


	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

public:


	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	// �ړ��܂łɂ����鎞�Ԃ����炷�l���擾
	void getDecrementTime(int decrementTime) { m_decrementTime = decrementTime; }

public:
	// �|���S�������ݒ�
	void InitPolygon();

	// �|���S���̃A�b�v�f�[�g
	void UpdatePolygon();

	// �ړ�����
	void Move();

	// �V���b�g����
	void Shot();

private:
	
	// ���݃t���O
	bool m_isExist;


	// �ۑ��ʒu
	int m_savePosX;
	int m_savePosZ;

	// �t���[���J�E���g
	int m_frameCount;


	// �E�ɍs�����ǂ���
	bool m_isRightMove;

	// ��O�ɍs�����ǂ���
	bool m_isUnderMove;


	// �V���b�g�̔����Ԋu
	int m_shotInterval;

	// �ړ��܂łɂ����鎞�Ԃ����炷
	int m_decrementTime;

	// �G�l�~�[�̃O���t�B�b�N
	int m_handle[kEnemyGraphicNum];

	// �A�j���[�V�����i���o�[
	int m_animationNum;


	// �\���ʒu
	VECTOR m_pos;

	// �N���X�|�C���^
	SceneMain* m_pSceneMain;

	// ���̕\��
	VERTEX3D Vertex[6];

	// ��]
	VECTOR Angle;
};

