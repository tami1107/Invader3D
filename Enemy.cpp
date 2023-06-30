#include "Enemy.h"
#include "SceneMain.h"

namespace
{
	// �����ʒu
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = 100.0f;



	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 60;


	// �ړ��Ԋu(�t���[����)
	//constexpr int kMoveInterval = 120;

	// �ړ��Ԋu(�t���[����)
	constexpr int kMoveInterval = 60;

	// �ړ���X
	constexpr float kMovePosX = 5.0f;
	// �ړ���Y
	constexpr float kMovePosZ = 10.0f;

	// �ǂ��܂ňړ�����̂�
	constexpr int kLimitMove = kMovePosX * 6;


	// �Q�[���I�[�o�[���W
	constexpr float kGameOverPosY = kMovePosZ;

	// �_���[�W���󂯂����̃A�j���[�V�����ő�t���[��
	constexpr int kDamageAnimationMaxFrame = 30;

	// �O���t�B�b�N�T�C�Y
	constexpr float kGraphicSize = 10.0;

}


Enemy::Enemy() :
	m_isExist(true),
	m_savePosX(0),
	m_savePosZ(0),
	m_frameCount(0),
	m_isRightMove(true),
	m_isUnderMove(false),
	m_isHit(false),
	m_shotInterval(0),
	m_decrementTime(0),
	m_animationNum(0),
	m_damageAnimationFrame(0),
	m_pos(),
	m_pSceneMain(nullptr)
{
	for (auto handle : m_handle)
	{
		handle = -1;
	}
}

Enemy::~Enemy()
{
	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// �O���t�B�b�N�̍폜
	for (auto handle : m_handle)
	{
		DeleteGraph(handle);
	}
	
}

void Enemy::init(int savePosX, int savePosZ, int decrementTime)
{
	
	// �X�s�[�h����
	m_decrementTime = decrementTime;

	// ���݂��Ă���
	m_isExist = true;


	// �ʒu�̕ۑ�
	m_savePosX = savePosX;
	m_savePosZ = savePosZ;



	// �ʒu�̏�����
	m_pos = VGet(kInitPosX + m_savePosX, kInitPosY, kInitPosZ + savePosZ);

	// �ړ��̊Ԋu
	m_frameCount = kMoveInterval - m_decrementTime;

	// �ŏ��͉E�ɐi��
	m_isRightMove = true;

	// �ŏ��͉��ɐi�܂Ȃ�
	m_isUnderMove = false;

	// �V���b�g�̔����Ԋu
	m_shotInterval = 0;

	// �A�j���[�V�����i���o�[�̏�����
	m_animationNum = 0;

	// �_���[�W�A�j���[�V�����t���[���̏�����
	m_damageAnimationFrame = kDamageAnimationMaxFrame;


	// �ŏ��̓_���[�W���󂯂Ă��Ȃ�
	m_isHit = false;
}

void Enemy::update()
{
		

	// �G�l�~�[�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist) return;

	// �_���[�W���󂯂Ă����珈�����s��
	if (m_isHit)
	{
		// �_���[�W���󂯂��Ƃ��̃A�j���[�V����
		DamageAnimation();
		return;
	}


	// �ړ�����
	Move();

	// �V���b�g����
	Shot();


}

void Enemy::draw()
{
	// �G�l�~�[�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist) return;

	// �_���[�W���󂯂��ꍇ�A�����ŏ������I������
	if (m_isHit)return;
	

	
	// ���̕\��
	//DrawSphere3D(m_pos, kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);


	// �摜�`��
	DrawBillboard3D(m_pos, 0.5, 0.5, kGraphicSize, 0.0, m_handle[m_animationNum], true);
}


void Enemy::Move()
{
	// �ړ��C���^�[�o��


	// �ړ�����܂łɂ�����t���[��
	int moveFrame = kMoveInterval - m_decrementTime;


	// frameCount��0�ɂȂ�����ړ�
	m_frameCount--;
	if (m_frameCount <= 0)
	{
		// �A�j���[�V�����𓮂���
		m_animationNum++;
		// �ړ��A�j���[�V������0�E1�����g��Ȃ��ׁA2�ȏ�ɂȂ����Ƃ�0�ɂ���
		if (m_animationNum == 2)
		{
			m_animationNum = 0;
		}
		




		// �E�ɐi�ނ��ǂ����̃t���O����
		if (m_pos.x >= kLimitMove+ m_savePosX)
		{
			if (m_isRightMove)
			{
				m_isRightMove = false;

				m_isUnderMove = true;
			}
		}
		// ���ɐi�ނ��ǂ����̃t���O����
		if (m_pos.x <= -kLimitMove+ m_savePosX)
		{
			if (!m_isRightMove)
			{
				m_isRightMove = true;

				m_isUnderMove = true;
			}
		}

		// ��i��O�ɂ������ǂ���
		if (m_isUnderMove)
		{
			// ��i��O�ɍs��
			m_pos.z -= kMovePosZ;

			m_isUnderMove = false;


			m_frameCount = moveFrame;

			// �Q�[���I�[�o�[���邩�ǂ���
			if (m_pos.z <= kGameOverPosY)
			{
				//m_pSceneMain->getIsGameOverFlag(true);
			}

			return;
		}


		// �t���O�ɂ���Ĉړ�������ς���
		if (m_isRightMove)
		{
			m_pos.x += kMovePosX;
		}
		else
		{
			m_pos.x -= kMovePosX;
		}

		// �ړ��t���[����߂�
		m_frameCount = moveFrame;
	}
}

void Enemy::Shot()
{
	// �V���b�g�C���^�[�o��
	m_shotInterval--;
	if (m_shotInterval <= 0)
	{
		m_shotInterval = 0;
	}

	// �V���b�g������
	if (m_shotInterval <= 0)
	{
		// �V���b�g�����������Ȃ����̕ϐ�
		int isShot = 0;

		// �������擾
		isShot = GetRand(1);

		if (isShot == 1)
		{
			m_pSceneMain->CreateShotEnemy(m_pos);
		}
		m_shotInterval = kShotInterval;
	}
}

void Enemy::DamageAnimation()
{
	// �_���[�W�A�j���[�V�����t���[�����֖���
	m_damageAnimationFrame--;
	// ���t���[���o�ƃG�l�~�[�̑��݂�����
	if (m_damageAnimationFrame <= 0)
	{
		m_isExist = false;
	}


	// �_���[�W�A�j���[�V����
	m_animationNum = 2;


}


