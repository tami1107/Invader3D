#pragma once
#include "Vec2.h"
#include <memory>

class MainUI
{
public:
	// スコアの最大桁数
	static constexpr int kScoreMaxNum = 6;
	

	// グラフィック分割数
	static constexpr int kGraphicDivX = 2;
	static constexpr int kGraphicDivY = 1;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;
public:
	MainUI();
	virtual~MainUI();


	void init();

	void update();

	void draw();
public:

	void getPlayerHp(int playerHp) { m_playerHp = playerHp; }
	void getEnemyLv(int enemyLv) { m_enemyLv = enemyLv; }
	void getIsTextMove(bool textMove) { m_isTextMove = textMove; }

public:
	// スコアを配列に変換
	void ScoreArray(int score);

	// テキスト処理
	void TextProcess();

	// タイマー処理
	void TimerProcess(int timer);

	// ダメージ処理
	void DamageProcess();

private:
	// グラフィックハンドル
	int m_graphicHandle[2];

	// フォントハンドル
	int m_fontHandle;

	// タイマーハンドル
	int m_timerHandle[kGraphicDivNum];


	// プレイヤーのHP
	int m_playerHp;
	// エネミーのレベル
	int m_enemyLv;
	// スコア
	int m_score;


	// スコアの配列
	int m_scoreNum[kScoreMaxNum];

	// テキストハンドル
	int m_textHandle;

	// テキストを移動させるか
	bool m_isTextMove;

	// テキストストップカウント
	int m_textStopCount;


	// タイマー
	int m_timer;

	// パーセント
	float m_percentage;

	// ダメージハンドル
	int m_damageHandle;

	// サイン
	float m_sin;

	// フェード値
	float m_fadeValue;

	// テキスト表示位置
	Vec2 m_textPos;

};