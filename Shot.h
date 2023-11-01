#pragma once
#include "game.h"
#include <memory>
#include "SceneMain.h"


class SceneMain;
class BonusEnemy;
class Player;
class Shot
{
public:

	// �V���b�g�̃T�C�Y
	static constexpr float kShotSize = 1.2f;

	// �V���b�g�̃T�C�Y
	static constexpr float kShotBigSize = 4.0f;

	// �c���̗�
	static constexpr int kAfterimageNum = 4;

	// �p�[�e�B�N���̗�
	static constexpr int kParticleValue = 16;

	// �����x�i1���s�����j
	static constexpr float kAlphaValue = 1.0;

	// �p�[�e�B�N���̃X�P�[��
	static constexpr float kParticleScale = 1.0;

	// �p�[�e�B�N���̃X�P�[��(�T�C�Y�̂ł����V���b�g)
	static constexpr float kParticleScale2 = 2.6;


public:
	Shot();
	virtual ~Shot();


	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_SceneMain = sceneMain; }
	void getBonusEnemyPointer(std::shared_ptr<BonusEnemy>bonusEnemy) { m_pBonusEnemy = bonusEnemy; }
	void getPlayerPointer(std::shared_ptr<Player>player) { m_pPlayer = player; }

	// ����
	void start(VECTOR pos, bool isPowerUp, int powerUpNum);

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
	VECTOR getPos() const { return m_pos[0]; }
	// �F�̎擾
	VECTOR getColor() const { return m_color; }
	// �F�̎擾
	float getParticleScale() const { return m_particleScale; }

public:
	// �O���t�B�b�N���󂯎��
	void getShotGraphic(int handle) { m_modeleHandle = handle; }

	// �V���b�g�ԍ����󂯎��
	void setShotNum(int num) { m_shotNum = num; }

public:

	// �e���̋O��
	void BulletTrajectory();

	// �����蔻��
	void Collision();

	// �ړ���������
	void LimitMove();

	// �c������
	void Afterimage();

private:

	// 3D���f���n���h��
	int m_modeleHandle;

	// ���݃t���O
	bool m_isExist;

	// �V���b�g�X�s�[�h
	float m_shotSpeed;

	// �ђʂ��邩�ǂ���
	bool m_isPenetration;

	// �V���b�g�T�C�Y
	float m_shotSize;

	// �p���[�A�b�v�����ǂ���
	bool m_isPowerUp;

	// �V���b�g�̔ԍ�
	int m_shotNum;

	// �p�[�e�B�N���̑傫��
	float m_particleScale;

	// �\���ʒu
	VECTOR m_pos[kAfterimageNum];

	// �F
	VECTOR m_color;


	// �N���X�|�C���^
	SceneMain* m_SceneMain;
	std::shared_ptr<BonusEnemy>m_pBonusEnemy;
	std::shared_ptr<Player>m_pPlayer;
};


