#pragma once
#include "game.h"
#include <memory>

class Player;
class InvertShot
{
public:

	// �V���b�g�̃T�C�Y
	static constexpr float kShotSize = 1.1f;

	// �V���b�g1�J���[R
	static constexpr float kShot1CollarR = 0;
	// �V���b�g1�J���[G
	static constexpr float kShot1CollarG = 1.0;
	// �V���b�g1�J���[B
	static constexpr float kShot1CollarB = 0;

	// �V���b�g2�J���[R
	static constexpr float kShot2CollarR = 0;
	// �V���b�g2�J���[G
	static constexpr float kShot2CollarG = 0;
	// �V���b�g2�J���[B
	static constexpr float kShot2CollarB = 1.0;

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

	// �J���[�擾
	void setColor(VECTOR color) { m_color = color; }
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

	// �J���[
	VECTOR m_color;

	// �N���X�|�C���^
	std::shared_ptr<Player>m_pPlayer;
};




