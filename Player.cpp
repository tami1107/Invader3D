#include "Player.h"
#include "Pad.h"
#include "SceneMain.h"


Player::Player():
	m_modeleHandle(-1),
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

	// ���f���̍폜
	MV1DeleteModel(m_modeleHandle);
}

void Player::init()
{
	// ���f����ǂݍ���
	m_modeleHandle = MV1LoadModel(PlayerSet::kPlayerGraphicFileName);

	// �F�ݒ�
	MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(PlayerSet::kCollarR, PlayerSet::kCollarG, PlayerSet::kCollarB, 1.0f));

	// �R�c���f���̃X�P�[���ύX
	MV1SetScale(m_modeleHandle, VGet(PlayerSet::kModeleScale, PlayerSet::kModeleScale, PlayerSet::kModeleScale));

	// �ʒu�̏�����
	m_pos = VGet(PlayerSet::kInitPosX, PlayerSet::kInitPosY, PlayerSet::kInitPosZ);

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
	// ���f���̕`��
	MV1DrawModel(m_modeleHandle);

	DrawFormatString(0, 1 * 15, 0xffffff, "pos.x:%f pos.y:%f pos.z:%f", m_pos.x, m_pos.y, m_pos.z);

	// �����蔻��̕\��
#if true
	DrawSphere3D(m_pos, PlayerSet::kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);
#endif
}

void Player::Move()
{

	// �����̏�����
	m_dir = VGet(0, 0, 0);

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

#if false
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
	VECTOR velocity = VScale(m_dir, PlayerSet::kMoveSpeed);
	// �x�N�g���̑����Z
	m_pos = VAdd(m_pos, velocity);

	// �ʒu�������f���ɓ����
	MV1SetPosition(m_modeleHandle, m_pos);
}

void Player::LimitMove()
{
	// �������̈ړ�����
	if (m_pos.x <= -PlayerSet::kMoveLimit)
	{
		m_pos.x = -PlayerSet::kMoveLimit;
	}
	// �E�����̈ړ�����
	if (m_pos.x >= PlayerSet::kMoveLimit)
	{
		m_pos.x = PlayerSet::kMoveLimit;
	}
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
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		if (m_shotInterval <= 0)
		{
			m_pSceneMain->CreateShotPlayer(m_pos);
			m_shotInterval = PlayerSet::kShotInterval;
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
	m_pos = VGet(0.0f, PlayerSet::kInitPosY, 0.0f);
}
