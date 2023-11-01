#pragma once
#include "game.h"
#include "Setting.h"
#include "Vec2.h"

class SceneMain;
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX, int savePosZ, int enemyNum);

	void update();
	
	void draw();

	// �ʒu����Ԃ�
	VECTOR getPos() const { return m_pos; }


	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// �G�l�~�[�̔ԍ���Ԃ�
	int getEnemyLineNum() const { return m_enemyLineNum; }

	// �J���[�̒l��Ԃ�
	VECTOR getColor() const { return m_color; }

	// ���݂̃C���^�[�o����Ԃ�
	int getMoveInterval() const { return m_moveMaxInterval; }

public:

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	// �J���[�擾
	void setColor(VECTOR color) { m_color = color; }

	// �ړ��܂łɂ����鎞�Ԃ����炷�l���擾
	void setDecrementTime(int decrementTime) { m_decrementTime = decrementTime; }

	// �G�l�~�[�̔ԍ����󂯎��
	void setEnemyNum(int enemyNum) { m_enemyNum = enemyNum; }


public:
	// �|���S�������ݒ�
	void InitPolygon();

	// �|���S���̃A�b�v�f�[�g
	void UpdatePolygon();

	// �ړ�����
	void Move();

	// �V���b�g����
	void Shot();

	// ���x���A�b�v�ݒ�
	void LevelUp(float IntervalDecrement);

	// �G�l�~�[���C���^�[�o��
	void EnemyNumInterval(int interval);

	// ���Z�b�g����
	void Reset();

	// �ړ��ݒ�
	void MoveSetting(float enemyEdgePosX);

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
	int m_handle[EnemySet::kEnemyGraphicNum];

	// �A�j���[�V�����i���o�[
	int m_animationNum;

	// �G�l�~�[�i���o�[
	int m_enemyLineNum;


	// �G�l�~�[�ԍ�
	int m_enemyNum;

	// �ړ��ő�C���^�[�o��
	int m_moveMaxInterval;

	// �ړ��C���^�[�o��
	int m_moveInterval;

	// �ړ���
	float m_movingDistance;

	// �ő�ړ���
	float m_movingMaxDistance;

	// �G�l�~�[�[�̍��W
	float m_enemyEdgePosX;

	// �\���ʒu
	VECTOR m_pos;

	// �F
	VECTOR m_color;

	// �N���X�|�C���^
	SceneMain* m_pSceneMain;

	// ���̕\��
	VERTEX3D Vertex[6];

	// ��]
	VECTOR Angle;
};

