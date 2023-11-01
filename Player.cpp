#include "Player.h"
#include "Pad.h"
#include "SceneMain.h"
#include "MainUI.h"

namespace
{
	// �c���̂��炷�l
	constexpr int kAfterimageDisplace = 1;

	// �c���̓����x
	constexpr float kAfterimageAlpha= 0.2;
}


Player::Player():
	m_modeleHandle(-1),
	m_isHit(false),
	m_shotInterval(0),
	m_isPowerUp(false),
	m_powerUpFrame(0),
	m_powerUpNum(0),
	m_moveSpeed(0.0),
	m_isChangeStatus(false),
	m_pos(),
	m_dir(),
	m_color(),
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

	// �F������
	m_color = VGet(PlayerSet::kCollarR, PlayerSet::kCollarG, PlayerSet::kCollarB);

	// �F�ݒ�
	MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));

	// �R�c���f���̃X�P�[���ύX
	MV1SetScale(m_modeleHandle, VGet(PlayerSet::kModeleScale, PlayerSet::kModeleScale, PlayerSet::kModeleScale));

	// �R�c���f���̕s�����x
	MV1SetOpacityRate(m_modeleHandle, PlayerSet::kAlphaValue);

	// �ʒu�̏�����
	m_pos[0] = VGet(PlayerSet::kInitPosX, PlayerSet::kInitPosY, PlayerSet::kInitPosZ);

	// �����̏�����
	m_dir = VGet(0.0f, 0.0f, 0.0f);

	// �V���b�g�̔����Ԋu
	m_shotInterval = 0;

	// �V���b�g�̃X�s�[�h�A�b�v�t���[���̍ő�l����
	m_powerUpFrame = kPowerUpMaxFrame;

	// �ړ��X�s�[�h����
	m_moveSpeed = PlayerSet::kMoveSpeed;
}

void Player::update()
{
	// �ړ�����
	Move();

	// �ړ�����
	LimitMove();

	// �p���[�A�b�v����
	PowerUpProcess();

	// �V���b�g����
	Shot();

	// �_���[�W����
	CollisionProcess();

}

void Player::draw()
{
	
	// ���f���̕`��
	MV1DrawModel(m_modeleHandle);


	Afterimage();


	//// �v���C���[�̍��W�\��
	//DrawFormatString(0, 15 * 17, 0xff0000, "pos.x:%f pos.y:%f pos.z:%f", m_pos[0].x, m_pos[0].y, m_pos[0].z);


	// �f�o�b�O
#if false

	// �����蔻��\��
	DrawSphere3D(m_pos, PlayerSet::kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);

	// �v���C���[�̍��W�\��
	DrawFormatString(0, 1 * 15, 0xffffff, "pos.x:%f pos.y:%f pos.z:%f", m_pos.x, m_pos.y, m_pos.z);

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
	VECTOR velocity = VScale(m_dir, m_moveSpeed);
	// �x�N�g���̑����Z
	m_pos[0] = VAdd(m_pos[0], velocity);

	// �ʒu�������f���ɓ����
	MV1SetPosition(m_modeleHandle, m_pos[0]);
}

void Player::LimitMove()
{
	// �������̈ړ�����
	if (m_pos[0].x <= -PlayerSet::kMoveLimit)
	{
		m_pos[0].x = -PlayerSet::kMoveLimit;
	}
	// �E�����̈ړ�����
	if (m_pos[0].x >= PlayerSet::kMoveLimit)
	{
		m_pos[0].x = PlayerSet::kMoveLimit;
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
		{/*
			m_pSceneMain->CreateShotPlayer(m_pos, m_isPowerUp, m_powerUpNum);
			m_shotInterval = PlayerSet::kShotInterval;*/
		}

		m_pSceneMain->CreateShotPlayer(m_pos[0], m_isPowerUp, m_powerUpNum);
		m_shotInterval = PlayerSet::kShotInterval;
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

void Player::PowerUpProcess()
{

	if (!m_isPowerUp)return;

	// �X�e�[�^�X��ς��ĂȂ���Ες���
	if (!m_isChangeStatus)
	{

		if (m_powerUpNum == 0)// �V���b�g�X�s�[�h�ƃV���b�g�T�C�Y
		{
			// �F������
			m_color = VGet(kQuickCollarR, kQuickCollarG, kQuickCollarB);
		}
		else if (m_powerUpNum == 1)// �A��
		{
			// �F������
			m_color = VGet(kRapidCollarR, kRapidCollarG, kRapidCollarB);
		}
		else if (m_powerUpNum == 2)// �ђʁA�ړ��X�s�[�hUP
		{
			// �F������
			m_color = VGet(kPenetrationCollarR, kPenetrationCollarG, kPenetrationCollarB);
			
			// �ړ��X�s�[�h����
			m_moveSpeed = PlayerSet::kMoveSpeed2;
		}

		// �F�ݒ�
		MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));


		m_isChangeStatus = true;

	}


	// �t���[�������炷
	m_powerUpFrame--;
	

	// MainUI�̃^�C�}�[�𓮂���
	m_pMainUI->TimerProcess(m_powerUpFrame);


	// m_shotSpeedUpFrame��0�ɂȂ������A
	if (m_powerUpFrame < 0)
	{
		// �F������
		m_color = VGet(PlayerSet::kCollarR, PlayerSet::kCollarG, PlayerSet::kCollarB);

		// �F�ݒ�
		MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));

		// �p���[�A�b�v�t���[���̍ő�l����
		m_powerUpFrame = kPowerUpMaxFrame;

		// �p���[�A�b�v�ԍ��ɈӖ��̂Ȃ�����������
		m_powerUpNum = kPowerUpMaxNum;

		m_isPowerUp = false;

		m_isChangeStatus = false;

		// �ړ��X�s�[�h����
		m_moveSpeed = PlayerSet::kMoveSpeed;
	}
}

void Player::Reset()
{
	// �ʒu�̏�����
	m_pos[0] = VGet(0.0f, PlayerSet::kInitPosY, 0.0f);

	// �ʒu�������f���ɓ����
	MV1SetPosition(m_modeleHandle, m_pos[0]);

	// �p���[�A�b�v�t���[���̍ő�l����
	m_powerUpFrame = kPowerUpMaxFrame;

	// �p���[�A�b�v�ԍ��ɈӖ��̂Ȃ�����������
	m_powerUpNum = kPowerUpMaxNum;

	m_isPowerUp = false;

	// �ړ��X�s�[�h����
	m_moveSpeed = PlayerSet::kMoveSpeed;
}

void Player::Afterimage()
{

	if (!m_isPowerUp)return;

	// �c���f�[�^����Â��炷
	for (int i = kAfterimageNum - 1; i > 0; i--)
	{
		m_pos[i] = m_pos[i - 1];

	}
	// �R�c���f���̕s�����x	
	MV1SetOpacityRate(m_modeleHandle, kAfterimageAlpha);

	for (int i = kAfterimageNum - 1; i >= 0; i -= kAfterimageDisplace)
	{
		// �ʒu�������f���ɓ����
		MV1SetPosition(m_modeleHandle, m_pos[i]);
		
		// ���f���̕`��
		MV1DrawModel(m_modeleHandle);

		
	}
	// �R�c���f���̕s�����x
	MV1SetOpacityRate(m_modeleHandle, PlayerSet::kAlphaValue);

}
