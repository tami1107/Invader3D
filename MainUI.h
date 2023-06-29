#pragma once

class SceneMain;
class MainUI
{
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
	void getScore(int score) { m_score = score; }

private:
	// �v���C���[��HP
	int m_playerHp;
	// �G�l�~�[�̃��x��
	int m_enemyLv;
	// �X�R�A
	int m_score;


	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

