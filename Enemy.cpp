#include "Enemy.h"
#include "SceneMain.h"

namespace
{
	// �����ʒu
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = Enemy::kInitPosZ;


	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 60;


	// �ړ��Ԋu(�t���[����)
	//constexpr int kMoveInterval = 120;

	// �ړ��Ԋu(�t���[����)�f�o�b�O
	constexpr int kMoveInterval = 60;

	// �ړ���X
	constexpr float kMovePosX = Enemy::kMovePosX;
	// �ړ���Y
	constexpr float kMovePosZ = Enemy::kMovePosZ;

	// �ǂ��܂ňړ�����̂�
	constexpr int kLimitMove = Enemy::kLimitMove;


	// �Q�[���I�[�o�[���W
	constexpr float kGameOverPosY = 0.0f;


	// �O���t�B�b�N�T�C�Y
	constexpr float kGraphicSize = 5.0f;

}


Enemy::Enemy() :
	m_isExist(true),
	m_savePosX(0),
	m_savePosZ(0),
	m_frameCount(0),
	m_isRightMove(true),
	m_isUnderMove(false),
	m_shotInterval(0),
	m_decrementTime(0),
	m_animationNum(0),
	m_pos(),
	m_pSceneMain(nullptr)
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}

	// �|���S���̏����ݒ�
	InitPolygon();
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



}

void Enemy::update()
{
	// �G�l�~�[�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist) return;


	// �ړ�����
	Move();

	// �|���S���̃A�b�v�f�[�g����
	UpdatePolygon();

	// �V���b�g����
	Shot();

}

void Enemy::draw()
{
	// �G�l�~�[�����݂��Ȃ������ꍇ�A�����ŏ������I������
	if (!m_isExist) return;


	// �Q�|���S���̕`��
	DrawPolygon3D(Vertex, 2, m_handle[m_animationNum], true);

	// �摜�`��
	//DrawBillboard3D(m_pos, 0.5, 0.5, kGraphicSize, 0.0, m_handle[m_animationNum], true);

	
	// �����蔻��̕\��
#if false
	// ���̕\��
	DrawSphere3D(m_pos, kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);
#endif
}


void Enemy::InitPolygon()
{

	// �Q�|���S�����̒��_�̍��W�Ɩ@���ȊO�̃f�[�^���Z�b�g
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4] = Vertex[2];
	Vertex[5] = Vertex[1];

	// ��]�p�����[�^��������
	Angle.x = 0.0f;
	Angle.y = 0.0f;
	Angle.z = 0.0f;

}

void Enemy::UpdatePolygon()
{
	MATRIX TransformMatrix;

	// ��]( x, y, z����]�̏� )�{���W�ړ��s��̍쐬
	TransformMatrix = MGetRotX(Angle.x);
	TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
	TransformMatrix = MMult(TransformMatrix, MGetRotZ(Angle.z));
	TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(0.0f, 0.0f, 0.0f)));

	// �s����g���ă��[���h���W���Z�o
	Vertex[0].pos = VTransform(VGet(m_pos.x + -kGraphicSize, m_pos.y + kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[1].pos = VTransform(VGet(m_pos.x + kGraphicSize, m_pos.y + kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[2].pos = VTransform(VGet(m_pos.x + -kGraphicSize, m_pos.y + -kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[3].pos = VTransform(VGet(m_pos.x + kGraphicSize, m_pos.y + -kGraphicSize, m_pos.z), TransformMatrix);

	Vertex[4].pos = Vertex[2].pos;
	Vertex[5].pos = Vertex[1].pos;

	// �s����g���Ė@�����Z�o
	Vertex[2].norm = Vertex[0].norm;
	Vertex[3].norm = Vertex[0].norm;
	Vertex[4].norm = Vertex[0].norm;
	Vertex[5].norm = Vertex[0].norm;

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
		if (m_pos.x >= (kMovePosX * kLimitMove) + m_savePosX)
		{
			if (m_isRightMove)
			{
				m_isRightMove = false;

				m_isUnderMove = true;
			}
		}
		// ���ɐi�ނ��ǂ����̃t���O����
		if (m_pos.x <= -(kMovePosX * kLimitMove)+ m_savePosX)
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




