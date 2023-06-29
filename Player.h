#pragma once
#include "game.h"

class SceneMain;
class Player
{
public:
	// �����T�C�Y
	static constexpr float kCircleSize = 2.0f;

	
public:
	Player();
	virtual~Player();

	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init();
	void update();
	void draw();

	// �ʒu����Ԃ�
	VECTOR getPos() const { return m_pos; }

	// �����蔻����擾
	void getIsHit(bool isHit) { m_isHit = isHit; }

public:
	// �ړ�����
	void Move();

	// �ړ�����
	void LimitMove();

	// �V���b�g����
	void Shot();

	// �_���[�W����
	void CollisionProcess();

	// �ʒu������
	void ResetPos();

private:

	// �����������ǂ���
	bool m_isHit;

	// �V���b�g�̔����Ԋu
	int m_shotInterval;



	// �\���ʒu
	VECTOR m_pos;

	// ����
	VECTOR m_dir;



	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

