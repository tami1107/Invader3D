#include "Enemy.h"
#include "SceneMain.h"
#include "Setting.h"


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
	m_enemyLineNum(0),
	m_enemyNum(0),
	m_moveMaxInterval(EnemySet::kMoveInterval),
	m_moveInterval(EnemySet::kMoveInterval),
	m_movingDistance(0.0f),
	m_movingMaxDistance(0.0f),
	m_enemyEdgePosX(0.0f),
	m_pos(),
	m_color(),
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

void Enemy::init(int savePosX, int savePosZ, int enemyLineNum)
{
	
	// ���݂��Ă���
	m_isExist = true;

	// �ʒu�̑��
	m_savePosX = savePosX;
	m_savePosZ = savePosZ;

	// �G�l�~�[�̗�ԍ�����
	m_enemyLineNum = enemyLineNum;

	
	// �ړ��C���^�[�o�������l�̏�����
	m_decrementTime = 0;

	// �ʒu�̏�����
	m_pos = VGet(EnemySet::kInitPosX + m_savePosX, EnemySet::kInitPosY, EnemySet::kInitPosZ + savePosZ);

	// �ړ��̊Ԋu
	m_frameCount = EnemySet::kMoveInterval;

	// �ŏ��͉E�ɐi��
	m_isRightMove = true;

	// �ŏ��͉��ɐi�܂Ȃ�
	m_isUnderMove = false;

	// �V���b�g�̔����Ԋu
	m_shotInterval = 0;

	// �A�j���[�V�����i���o�[�̏�����
	m_animationNum = 0;

	// �C���^�[�o���̑��
	m_moveInterval = m_moveMaxInterval;

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

	MATERIALPARAM Material;

	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(m_color.x, m_color.y, m_color.z, 0.0f);
	Material.Power = 20.0f;

	SetMaterialParam(Material);



	// �����ɂ��ĕ\������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, EnemySet::kAlphaValue);

	// �Q�|���S���̕`��
	DrawPolygon3D(Vertex, 2, m_handle[m_animationNum], true);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//DrawFormatString(0, 15 * 10, 0xffffff, "�C���^�[�o��max%d", m_moveMaxInterval);
	//DrawFormatString(0, 15 * 11, 0xffffff, "�C���^�[�o��%d", m_moveInterval);

	//DrawFormatString(300, 15 * m_enemyNum, 0xffffff, "[%d]�ړ���:%f �ő�ړ���:%f",
	//	m_enemyNum, m_movingDistance, m_movingMaxDistance);
	

		//DrawFormatString(300, 15 * 12+ m_enemyNum, 0xffffff, "�ړ���:%f", m_movingDistance);
		//DrawFormatString(300, 15 * 13+i, 0xffffff, "�ő�ړ���:%f", m_movingMaxDistance);
	



	// Debug
	{
		if (!EnemySet::kDebug)return;
		// �����蔻��̕\���i���́j
		DrawSphere3D(m_pos, EnemySet::kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);
	}
}


void Enemy::InitPolygon()
{

	// �Q�|���S�����̒��_�̍��W�Ɩ@���ȊO�̃f�[�^���Z�b�g
	Vertex[0].dif = GetColorU8(0, 0, 0, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].dif = GetColorU8(0, 0, 0, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].dif = GetColorU8(0, 0, 0, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].dif = GetColorU8(0, 0, 0, 255);
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
	Vertex[0].pos = VTransform(VGet(m_pos.x + -EnemySet::kGraphicSize, m_pos.y + EnemySet::kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[1].pos = VTransform(VGet(m_pos.x + EnemySet::kGraphicSize, m_pos.y + EnemySet::kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[2].pos = VTransform(VGet(m_pos.x + -EnemySet::kGraphicSize, m_pos.y + -EnemySet::kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[3].pos = VTransform(VGet(m_pos.x + EnemySet::kGraphicSize, m_pos.y + -EnemySet::kGraphicSize, m_pos.z), TransformMatrix);

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


	
	// frameCount��0�ɂȂ�����ړ�
	m_frameCount--;
	if (m_frameCount <= 0)
	{
		// �A�j���[�V�����𓮂���
		m_animationNum++;
		// �ړ��A�j���[�V������0�E1�����g��Ȃ��ׁA2�ȏ�ɂȂ����Ƃ�0�ɂ���
		m_animationNum %= 2;


	
		// �E�ɐi�ނ��ǂ����̃t���O����
		if (m_movingDistance >= m_movingMaxDistance)
		{
			if (m_isRightMove)
			{
				m_isRightMove = false;

				m_isUnderMove = true;

				m_movingDistance = 0.0f;

				m_movingMaxDistance = (EnemySet::kLimitMove + m_enemyEdgePosX) * -2;
			}
		}
		// ���ɐi�ނ��ǂ����̃t���O����
		if (m_movingDistance <= m_movingMaxDistance)
		{
			if (!m_isRightMove)
			{
				m_isRightMove = true;

				m_isUnderMove = true;

				m_movingDistance = 0.0f;

				m_movingMaxDistance = (EnemySet::kLimitMove + m_enemyEdgePosX) * 2;
			}
		}

		//// �E�ɐi�ނ��ǂ����̃t���O����
		//if (m_pos.x >= (EnemySet::kMovePosX * EnemySet::kLimitMove) + m_savePosX)
		//{
		//	if (m_isRightMove)
		//	{
		//		m_isRightMove = false;

		//		m_isUnderMove = true;
		//	}
		//}
		//// ���ɐi�ނ��ǂ����̃t���O����
		//if (m_pos.x <= -(EnemySet::kMovePosX * EnemySet::kLimitMove) + m_savePosX)
		//{
		//	if (!m_isRightMove)
		//	{
		//		m_isRightMove = true;

		//		m_isUnderMove = true;
		//	}
		//}

		// ��i��O�ɂ������ǂ���
		if (m_isUnderMove)
		{
			// ��i��O�ɍs��
			m_pos.z -= EnemySet::kMovePosZ;

			m_isUnderMove = false;


			m_frameCount = m_moveInterval;

			// �Q�[���I�[�o�[���邩�ǂ���
			if (m_pos.z <= EnemySet::kGameOverLine * EnemySet::kMovePosZ)
			{
				m_pSceneMain->setIsGameOverFlag(true);
			}

			return;
		}


		// �t���O�ɂ���Ĉړ�������ς���
		if (m_isRightMove)
		{
			m_pos.x += EnemySet::kMovePosX;

			m_movingDistance += EnemySet::kMovePosX;
		}
		else
		{
			m_pos.x -= EnemySet::kMovePosX;

			m_movingDistance -= EnemySet::kMovePosX;
		}

		// �ړ��t���[����߂�
		m_frameCount = m_moveInterval;
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
		// �V���b�g��ł��ǂ���
		m_pSceneMain->IsShotEnemy(m_pos, m_enemyNum, m_enemyLineNum);

	
		m_shotInterval = EnemySet::kShotInterval;
	}
}

void Enemy::LevelUp(float IntervalDecrement)
{
	// �ړ��C���^�[�o�������炷
	m_moveMaxInterval *= IntervalDecrement;

	// �C���^�[�o���ɑ��
	m_moveInterval = m_moveMaxInterval;
}

void Enemy::EnemyNumInterval(int interval)
{

	// �C���^�[�o���ɑ��
	m_moveInterval = interval;
}



void Enemy::Reset()
{
	// �ړ��C���^�[�o���̏�����
	m_moveMaxInterval = EnemySet::kMoveInterval;

	// �C���^�[�o���ɑ��
	m_moveInterval = m_moveMaxInterval;
}

void Enemy::MoveSetting(float enemyEdgePosX)
{
	

	m_enemyEdgePosX = enemyEdgePosX;

	// �ő�ړ���
	m_movingMaxDistance = EnemySet::kLimitMove + enemyEdgePosX;

	m_movingDistance = 0.0f;
}

