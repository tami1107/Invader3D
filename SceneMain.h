#pragma once
#include "SceneBase.h"
#include <memory>
#include "game.h"
#include "Setting.h"

class Player;
class Camera;
class Shot;
class InvertShot;
class Enemy;
class Bunker;
class GameOver;
class MainUI;
class BackGround;
class Particle;
class Particle3D;
class Pause;
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



	// �p�[�e�B�N���̍ő吔
	static constexpr int kParticleMaxNum = 128;

	// �q�b�g�X�g�b�v���Ɏ~�߂鎞�ԁi�t���[���j
	static constexpr int kFreezeFrameMaxCount = 60;
public:
	SceneMain();

	virtual ~SceneMain();


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

public:
	// �Q�[���I�[�o�[�t���O�̎擾
	void setIsGameOverFlag(bool isGameOver) { m_isGameOver = isGameOver; }

	// ���Z�b�g�t���O
	void setIsResetFlag(bool isReset) { m_isReset = isReset; }

	// �|�[�Y���邩�ǂ������擾����
	void setIsPause(bool isPause) { m_isPause = isPause; }

	// �^�C�g���ɖ߂邩�ǂ����̃t���O���擾����
	void setIsTurnTitle(bool isTurnTitle) { m_isTurnTitle = isTurnTitle; }

public:

	// �q�b�g�X�g�b�v����
	void FreezeFrame();

	// ���Z�b�g����
	void RsetProcess();

	// �G�l�~�[�̐���
	void CreateEnemy();

	// �g�[�`�J�̐���
	void CreateBunker();

	// �v���C���[���_���[�W���󂯂��Ƃ��̏���
	void PlayerDamageProcess();

	// �G�l�~�[�̑��ݏ���
	void EnemyExistProcess();

	// �p�[�e�B�N������
	void CreateParticle(VECTOR pos, int colorNum);

	// �p�[�e�B�N������3D
	void CreateParticle3D(VECTOR pos, int num);

	// �Q�[���I�[�o�[�ɂȂ�܂ł̃J�E���g����
	void GameOverCount();

	// �v���C���[���V���b�g������
	bool CreateShotPlayer(VECTOR pos);

	// �G�l�~�[���V���b�g������
	bool CreateShotEnemy(VECTOR pos, int enemyNum);

	// �G�l�~�[�ƃV���b�g�̂����蔻��
	void EnemyToShotCollision();

	// �g�[�`�J�ƃV���b�g�̂����蔻��
	void BunkerToShotCollision();

	// �g�[�`�J�ƃG�l�~�[�V���b�g�̂����蔻��
	void BunkerToInvertShotCollision();

	// �v���C���[�V���b�g�ƃG�l�~�[�V���b�g�̓����蔻��
	void ShotToInvertShotCollision();

private:

	// �q�b�g�X�g�b�v�J�E���g
	int m_freezeFrameCount;

	// �q�b�g�X�g�b�v�����̃t���O
	bool m_isFreezeFrame;


	// �G�l�~�[���x��
	int m_enemyLv;


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
	int m_enemyLineNow;

	// �v���C���[�c�@
	int m_playerRemaining;

	// �X�R�A
	int m_score;

	// �G�l�~�[�̃O���t�B�b�N
	int m_enemyGraphic[EnemySet::kEnemyGraphicNum];

	// �V���b�g�̃O���t�B�b�N
	int m_shotGraphic;

	// �G�l�~�[�V���b�g�̃O���t�B�b�N
	int m_invertShotGraphic[kEnemyShotMaxNumber];


	// Particle�̃O���t�B�b�N
	int m_particleGraphic;

	// �g�[�`�J�̃O���t�B�b�N
	int m_bunkerGraphic[kBunkerMaxNum];

	// �G�l�~�[�ԍ�
	int m_enemyNum[kEnemyMaxNum];

	// �Q�[���I�[�o�[�ɂȂ�܂ł̃J�E���g
	int m_gameOverCount;

	// �v���C���[�������Ă��邩�ǂ���
	int m_isAlivePlayer;

	// �|�[�Y���邩�ǂ����̃t���O
	bool m_isPause;

	// �^�C�g���ɖ߂邩�ǂ����̃t���O
	bool m_isTurnTitle;



	// �N���X�|�C���^
	std::shared_ptr<Player>m_pPlayer;
	std::shared_ptr<Camera>m_pCamera;
	std::shared_ptr<Shot>m_pShot[kPlayerShotMaxNumber];
	std::shared_ptr<InvertShot>m_pInvertShot[kEnemyShotMaxNumber];
	std::shared_ptr<Enemy>m_pEnemy[kEnemyMaxNum];
	std::shared_ptr<Bunker>m_pBunker[kBunkerMaxNum];
	std::shared_ptr<GameOver>m_pGameOver;
	std::shared_ptr<MainUI>m_pMainUI;
	std::shared_ptr<BackGround>m_pBackGround;
	std::shared_ptr<Particle>m_pParticle[kParticleMaxNum];
	std::shared_ptr<Particle3D>m_pParticle3D[kParticleMaxNum];
	std::shared_ptr<Pause>m_pPause;
};