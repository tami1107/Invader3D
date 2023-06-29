#include "Enemy.h"
#include "SceneMain.h"

namespace
{
	// �����ʒu
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 100.0f;


	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 60;


	// �ړ��Ԋu(�t���[����)
	constexpr int kMoveInterval = 120;

	// �ړ���X
	constexpr float kMovePosX = 5.0f;
	// �ړ���Y
	constexpr float kMovePosY = 10.0f;

	// �ǂ��܂ňړ�����̂�
	constexpr int kLimitMove = kMovePosX * 6;


	// �Q�[���I�[�o�[���W
	constexpr float kGameOverPosY = kMovePosY;

	// �e�X�g�O���t�B�b�N�̑}��
	const char* const kTestGraphic = "data/enemy.png";
}


Enemy::Enemy() :
	m_isExist(true),
	m_savePosX(0),
	m_savePosY(0),
	m_frameCount(0),
	m_isRightMove(true),
	m_isUnderMove(false),
	m_isHit(false),
	m_shotInterval(0),
	m_decrementTime(0),
	m_enemyGraphic(-1),
	m_pos(),
	m_pSceneMain(nullptr)
{

	// �摜�̃��[�h
	m_enemyGraphic = LoadGraph(kTestGraphic);
}

Enemy::~Enemy()
{
	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// �O���t�B�b�N�̍폜
	DeleteGraph(m_enemyGraphic);
}

void Enemy::init(int savePosX, int savePosY, int decrementTime)
{
	
	// �X�s�[�h����
	m_decrementTime = decrementTime;

	// ���݂��Ă���
	m_isExist = true;


	// �ʒu�̕ۑ�
	m_savePosX = savePosX;
	m_savePosY = savePosY;

	// �ʒu�̏�����
	m_pos = VGet(kInitPosX + m_savePosX, kInitPosY + savePosY, 0.0f);

	// �ړ��̊Ԋu
	m_frameCount = kMoveInterval - m_decrementTime;

	// �ŏ��͉E�ɐi��
	m_isRightMove = true;

	// �ŏ��͉��ɐi�܂Ȃ�
	m_isUnderMove = false;

	// �V���b�g�̔����Ԋu
	m_shotInterval = 0;



}

void Enemy::update()
{

	// �G�l�~�[�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist) return;

	// �ړ�����
	Move();

	// �V���b�g����
	Shot();

	// ����̏�����
	m_isHit = false;
}

void Enemy::draw()
{
	// �G�l�~�[�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist) return;

	// �F�ύX
	int color = 0x0000ff;

	if (m_isHit)
	{
		color = 0xff0000;
	}

	
	// ���̕\��
	DrawSphere3D(m_pos, kCircleSize, 32, color, GetColor(0, 0, 0), true);


	// �I�u�W�F�N�g�`��
	DrawBillboard3D(m_pos, 0.5, 0.5, 20.0, 0.0, m_enemyGraphic, true);
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

		// ��i�����邩�ǂ���
		if (m_isUnderMove)
		{
			// ��i������
			m_pos.y -= kMovePosY;

			m_isUnderMove = false;


			m_frameCount = moveFrame;


			if (m_pos.y <= kGameOverPosY)
			{
				m_pSceneMain->getIsGameOverFlag(true);
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


