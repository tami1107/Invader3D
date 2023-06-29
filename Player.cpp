#include "Player.h"
#include "Pad.h"
#include "SceneMain.h"

namespace
{
	// �ړ��X�s�[�h
	constexpr float kMoveSpeed = 0.5f;

	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 8;

	// �v���C���[�̈ړ��͈�
	constexpr int kMoveLimit = 50;
}


Player::Player():
	m_isHit(false),
	m_shotInterval(0),
	m_pos(),
	m_dir(),
	m_pSceneMain(nullptr)
{
}

Player::~Player()
{
	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;
}

void Player::init()
{
	// �ʒu�̏�����
	m_pos = VGet(0.0f, 0.0f, 0.0f);

	// �����̏�����
	m_dir = VGet(0.0f, 0.0f, 0.0f);


	// �V���b�g�̔����Ԋu
	m_shotInterval = 0;
}

void Player::update()
{
	// �ړ�����
	Move();

	// �ړ�����
	LimitMove();

	// �V���b�g����
	Shot();

	// �_���[�W����
	CollisionProcess();

}

void Player::draw()
{
	// �F�ύX
	int color = 0xffffff;

	if (m_isHit)
	{
		color = 0xff0000;
	}

	DrawSphere3D(m_pos, 2, 32, color, GetColor(0, 0, 0), true);

	DrawFormatString(0, 1 * 15, 0xffffff, "pos.x:%f pos.y:%f", m_pos.x, m_pos.y);
}

void Player::Move()
{

	// �����̏�����
	m_dir = VGet(0, 0, 0);

	// ��ɐi��
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_dir = VAdd(m_dir, VGet(0, -1, 0));
	}
	// ���ɐi��
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_dir = VAdd(m_dir, VGet(0, 1, 0));
	}
	// ���ɐi��
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_dir = VAdd(m_dir, VGet(-1, 0, 0));
	}
	// �E�ɐi��
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_dir = VAdd(m_dir, VGet(1, 0, 0));
	}

#if true

	// ��O�ɐi��
	if (Pad::isPress(PAD_INPUT_4))
	{
		m_dir = VAdd(m_dir, VGet(0, 0, -1));
	}
	// ���ɐi��
	if (Pad::isPress(PAD_INPUT_5))
	{
		m_dir = VAdd(m_dir, VGet(0, 0, 1));
	}
#endif


	// �΂߂ɂȂ����Ƃ�((1,1,0)��)�ɂ������񒷂��P�ɖ߂�(���K��)
	if (VSquareSize(m_dir) > 0)// ������0�̃x�N�g���͐��K���ł��Ȃ�(1�ɂł��Ȃ��̂�)
	{
		// ��VSize�͏d���̂�VSquareSize���g���i0�����悵�Ă�0�Ȃ̂Łj
		m_dir = VNorm(m_dir);
	}

	// �x�N�g���̊|���Z
	VECTOR velocity = VScale(m_dir, kMoveSpeed);
	// �x�N�g���̑����Z
	m_pos = VAdd(m_pos, velocity);


}

void Player::LimitMove()
{
	//// �������̈ړ�����
	//if (m_pos.x < -kMoveLimit)
	//{
	//	m_pos.x = -kMoveLimit;
	//}
	//// �E�����̈ړ�����
	//if (m_pos.x > kMoveLimit)
	//{
	//	m_pos.x = kMoveLimit;
	//}
}

void Player::Shot()
{
	// �V���b�g�C���^�[�o��
	m_shotInterval--;
	if (m_shotInterval <= 0)
	{
		m_shotInterval = 0;
	}

	// �V���b�g������
	if (Pad::isPress(PAD_INPUT_10))
	{
		if (m_shotInterval <= 0)
		{
			m_pSceneMain->CreateShotPlayer(m_pos);
			m_shotInterval = kShotInterval;
		}
	}
}

void Player::CollisionProcess()
{
	if (m_isHit)
	{
		// �_���[�W�������s��
		m_pSceneMain->PlayerDamageProcess();
	}

	// ����̏�����
	m_isHit = false;
}

void Player::ResetPos()
{
	// �ʒu�̏�����
	m_pos = VGet(0.0f, 0.0f, 0.0f);
}