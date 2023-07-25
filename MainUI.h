#pragma once

class SceneMain;
class MainUI
{
public:
	
	static constexpr int kScoreMaxNum = 4;

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

public:
	// スコアを配列に変換
	void ScoreArray(int score);

private:
	// フォントハンドル
	int m_fontHandle;


	// プレイヤーのHP
	int m_playerHp;
	// エネミーのレベル
	int m_enemyLv;
	// スコア
	int m_score;


	// スコアの配列
	int m_scoreNum[kScoreMaxNum];

	// クラスポインタ
	SceneMain* m_pSceneMain;
};

