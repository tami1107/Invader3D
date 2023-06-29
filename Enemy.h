#pragma once
#include "game.h"

class SceneMain;
class Enemy
{
public:
	// �����T�C�Y
	static constexpr float kCircleSize = 2.0f;

	// �G�l�~�[�O���t�B�b�N������
	static constexpr int kEnemyGraphicDivX = 3;
	static constexpr int kEnemyGraphicDivY = 1;
	static constexpr int kEnemyGraphicDivNum = kEnemyGraphicDivX * kEnemyGraphicDivY;
public:
	Enemy();
	virtual ~Enemy();

	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX, int savePosY, int decrementTime);

	void update();
	
	void draw();

	// �ʒu����Ԃ�
	VECTOR getPos() const { return m_pos; }

	// �����蔻����擾
	void getIsHit(bool isHit) { m_isHit = isHit; }

	// �ړ��܂łɂ����鎞�Ԃ����炷���l���擾
	void getDecrementTime(int decrementTime) { m_decrementTime = decrementTime; }


	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

public:


	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }



public:

	// �ړ�����
	void Move();

	// �V���b�g����
	void Shot();

	// �_���[�W���󂯂��Ƃ��̃A�j���[�V����
	void DamageAnimation();


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

	// ���ɍs�����ǂ���
	bool m_isUnderMove;


	// �����������ǂ���
	bool m_isHit;

	// �V���b�g�̔����Ԋu
	int m_shotInterval;

	// �ړ��܂łɂ����鎞�Ԃ����炷
	int m_decrementTime;

	// �G�l�~�[�̃O���t�B�b�N
	int m_handle[kEnemyGraphicDivNum];

	// �A�j���[�V�����i���o�[
	int m_animationNum;

	// �_���[�W�A�j���[�V�����t���[��
	int m_damageAnimationFrame;

	


	// �\���ʒu
	VECTOR m_pos;

	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

