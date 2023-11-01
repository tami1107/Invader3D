#pragma once
#include "game.h"
#include <memory>

class MainUI;
class SceneMain;
class Player
{
public:
	// �p���[�A�b�v�ԍ�
	static constexpr int kPowerUpMaxNum = 3;


	// �V���b�g�̃X�s�[�h�A�b�v�t���[���̍ő�l
	static constexpr int kPowerUpMaxFrame = 60*8;

	// �v���C���[�̐F�ύX
	// ���x
	static constexpr float kQuickCollarR = 1.0;
	static constexpr float kQuickCollarG = 0.0;
	static constexpr float kQuickCollarB = 0.0;

	// �A��
	static constexpr float kRapidCollarR = 0.0;
	static constexpr float kRapidCollarG = 0.0;
	static constexpr float kRapidCollarB = 1.0;

	// �ђ�
	static constexpr float kPenetrationCollarR = 0.0;
	static constexpr float kPenetrationCollarG = 1.0;
	static constexpr float kPenetrationCollarB = 0.0;

	// �c���̗�
	static constexpr int kAfterimageNum = 5;
public:
	Player();
	virtual~Player();

	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }
	void getMainUIPointer(std::shared_ptr<MainUI>mainUI) { m_pMainUI = mainUI; }

	void init();
	void update();
	void draw();

	// �ʒu����Ԃ�
	VECTOR getPos() const { return m_pos[0]; }

	// �F����Ԃ�
	VECTOR getColor() const { return m_color; }


	// �����蔻����擾
	void getIsHit(bool isHit) { m_isHit = isHit; }

	// �p���[�A�b�v���邩�ǂ������擾
	void getPowerUp(bool isPowerUp, int powerUpNum) { m_isPowerUp = isPowerUp, m_powerUpNum = powerUpNum; }

public:
	// �ړ�����
	void Move();

	// �ړ�����
	void LimitMove();

	// �V���b�g����
	void Shot();

	// �_���[�W����
	void CollisionProcess();

	// �p���[�A�b�v����
	void PowerUpProcess();

	// ��ԏ�����
	void Reset();

	// �c������
	void Afterimage();

private:


	// 3D���f���n���h��
	int m_modeleHandle;

	// �����������ǂ���
	bool m_isHit;

	// �V���b�g�̔����Ԋu
	int m_shotInterval;

	// �p���[�A�b�v�t���O
	bool m_isPowerUp;

	// �p���[�A�b�v�t���[��
	int m_powerUpFrame;

	// �p���[�A�b�v�ԍ�
	int m_powerUpNum;

	// �ړ��X�s�[�h
	float m_moveSpeed;

	// �X�e�[�^�X��ς������ǂ���
	bool m_isChangeStatus;

	// �\���ʒu
	VECTOR m_pos[kAfterimageNum];

	// ����
	VECTOR m_dir;

	// �F
	VECTOR m_color;

	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
	std::shared_ptr<MainUI>m_pMainUI;
};

