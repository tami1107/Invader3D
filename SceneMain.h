#pragma once
#include "SceneBase.h"
#include <memory>
#include "game.h"
#include "Enemy.h"


class Player;
class Camera;
class Shot;
class InvertShot;
class Enemy;
class Bunker;
class GameOver;
class MainUI;
class SceneMain : public SceneBase
{
public:
	// �V���b�g�̍ő吔
	static constexpr int kPlayerShotMaxNumber = 1;

	// �G�l�~�[�̃V���b�g�ő吔
	static constexpr int kEnemyShotMaxNumber = 2;

	// �G�l�~�[�ő吔(kEnemyMaxLine�̒l�Ŋ�������������)
	static constexpr int kEnemyMaxNum = 10;

	// �G�l�~�[�̍ő�s
	static constexpr int kEnemyMaxLine = 2;

	// �g�[�`�J�̍ő吔(�)
	static constexpr int kBunkerMaxNum = 9;

	// �ړ�����frame�̌����l
	static constexpr int kdecrementFrame = 10;

	// �v���C���[�̎c�@
	static constexpr int kPlayerRemaining = 3;

	// �X�R�A���_
	static constexpr int kAddedPoints = 10;


public:
	SceneMain();

	virtual ~SceneMain();


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

public:
	// �Q�[���I�[�o�[�t���O�̎擾
	void getIsGameOverFlag(bool isGameOver) { m_isGameOver = isGameOver; }

	// ���Z�b�g�t���O
	void getIsResetFlag(bool isReset) { m_isReset = isReset; }



public:

	// ���Z�b�g����
	void RsetProcess();


	// �G�l�~�[�̐���
	void CreateEnemy();

	// �g�[�`�J�̐���
	void CreateBunker();

	// �v���C���[���_���[�W���󂯂��Ƃ��̏���
	void PlayerDamageProcess();


	// �v���C���[���V���b�g������
	bool CreateShotPlayer(VECTOR pos);

	// �G�l�~�[���V���b�g������
	bool CreateShotEnemy(VECTOR pos);

	// �G�l�~�[�ƃV���b�g�̂����蔻��
	void EnemyToShotCollision();

	// �g�[�`�J�ƃV���b�g�̂����蔻��
	void BunkerToShotCollision();

	// �g�[�`�J�ƃG�l�~�[�V���b�g�̂����蔻��
	void BunkerToInvertShotCollision();

private:

	// �G�l�~�[�̃X���C�h�J�E���g
	int m_enemySlideCount;

	// �G�l�~�[�̗�J�E���g
	int m_enemyLineCount;

	// �G�l�~�[�s
	int m_enemyLine;

	// �G�l�~�[�����t���O
	bool m_isEnemyCreate;

	// �G�l�~�[�J�E���g
	int m_enemyCount;

	// �g�[�`�J�̃X���C�h�J�E���g
	int m_bunkerSlideCount;

	// �g�[�`�J�̗�J�E���g
	int m_bunkerLineCount;

	// �g�[�`�J�̃J�E���g
	int m_bunkerCount;

	// �Q�[���I�[�o�[�t���O
	int m_isGameOver;

	// ���Z�b�g�t���O
	int m_isReset;

	// �G�l�~�[���x��
	int m_enemyLevel;

	// �v���C���[�c�@
	int m_playerRemaining;

	// �X�R�A
	int m_score;

	// �G�l�~�[�̃O���t�B�b�N
	int m_enemyGraphic[Enemy::kEnemyGraphicDivNum];

	// �V���b�g�̃O���t�B�b�N
	int m_shotGraphic;


	// �N���X�|�C���^
	std::shared_ptr<Player>m_pPlayer;
	std::shared_ptr<Camera>m_pCamera;
	std::shared_ptr<Shot>m_pShot[kPlayerShotMaxNumber];
	std::shared_ptr<InvertShot>m_pInvertShot[kEnemyShotMaxNumber];
	std::shared_ptr<Enemy>m_pEnemy[kEnemyMaxNum];
	std::shared_ptr<Bunker>m_pBunker[kBunkerMaxNum];
	std::shared_ptr<GameOver>m_pGameOver;
	std::shared_ptr<MainUI>m_pMainUI;
};