#pragma once
#include "game.h"
#include <memory>

class Player;
class InvertShot
{
public:
	InvertShot();
	virtual ~InvertShot();

	// �N���X�|�C���^�̎擾
	void getPlayerPointer(std::shared_ptr<Player>player) { m_pPlayer = player; }


	// ����
	void start(VECTOR pos);

	// ����������
	void init();

	// �X�V
	void update();
	// �\��
	void draw();

	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// ���̎擾
	VECTOR getPos() const { return m_pos; }

public:
	// �O���t�B�b�N���󂯎��
	void getShotGraphic(int handle) { m_modeleHandle = handle; }

public:

	// �e���̋O��
	void BulletTrajectory();

	// 2D�̓����蔻��
	void Collision2D();

	// �ړ���������
	void LimitMove();

private:

	// ���݃t���O
	bool m_isExist;

	// 3D���f���n���h��
	int m_modeleHandle;

	// �\���ʒu
	VECTOR m_pos;

	// �N���X�|�C���^
	std::shared_ptr<Player>m_pPlayer;
};




