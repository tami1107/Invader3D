#pragma once

class SceneMain;
class MainUI
{
public:
	// �X�R�A�̍ő包��
	static constexpr int kScoreMaxNum = 6;
	

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
	// �O���t�B�b�N�n���h��
	int m_graphicHandle[2];


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

