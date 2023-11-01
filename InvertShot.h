#pragma once
#include "game.h"
#include <memory>

class Player;
class InvertShot
{
public:

	// �V���b�g�̃T�C�Y
	static constexpr float kShotSize = 1.1f;

	// �����x�i1���s�����j
	static constexpr float kAlphaValue = 1.0;

	// �p�[�e�B�N���̃X�P�[��
	static constexpr float kParticleScale = 1.0;

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
	void setShotGraphic(int handle) { m_modeleHandle = handle; }

	// �J���[�擾
	void setColor(VECTOR color) { m_color = color; }
	// ���̎擾
	VECTOR getColor() const { return m_color; }

public:

	// �e���̋O��
	void BulletTrajectory();

	// �����蔻��
	void Collision();

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




