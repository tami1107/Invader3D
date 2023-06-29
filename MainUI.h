#pragma once

class SceneMain;
class MainUI
{
public:
	MainUI();
	virtual~MainUI();

	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init();

	void update();

	void draw();
public:

	void getPlayerHp(int playerHp) { m_playerHp = playerHp; }
	void getEnemyLv(int enemyLv) { m_enemyLv = enemyLv; }
	void getScore(int score) { m_score = score; }

private:
	// プレイヤーのHP
	int m_playerHp;
	// エネミーのレベル
	int m_enemyLv;
	// スコア
	int m_score;


	// クラスポインタ
	SceneMain* m_pSceneMain;
};

