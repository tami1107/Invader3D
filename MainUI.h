#pragma once

class SceneMain;
class MainUI
{
public:
	
	static constexpr int kScoreMaxNum = 4;

public:
	MainUI();
	virtual~MainUI();

	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init();

	void update();

	void draw();
public:

	void getPlayerHp(int playerHp) { m_playerHp = playerHp; }
	void getEnemyLv(int enemyLv) { m_enemyLv = enemyLv; }

public:
	// �X�R�A��z��ɕϊ�
	void ScoreArray(int score);

private:
	// �t�H���g�n���h��
	int m_fontHandle;


	// �v���C���[��HP
	int m_playerHp;
	// �G�l�~�[�̃��x��
	int m_enemyLv;
	// �X�R�A
	int m_score;


	// �X�R�A�̔z��
	int m_scoreNum[kScoreMaxNum];

	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

