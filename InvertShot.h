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

	// �e���̋O��
	void BulletTrajectory();

	// 2D�̓����蔻��
	void Collision2D();

	// �ړ���������
	void LimitMove();

private:

	// ���݃t���O
	bool m_isExist;

	// �\���ʒu
	VECTOR m_pos;


	// �N���X�|�C���^
	std::shared_ptr<Player>m_pPlayer;
};



