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
	// ショットの最大数
	static constexpr int kPlayerShotMaxNumber = 1;

	// エネミーのショット最大数
	static constexpr int kEnemyShotMaxNumber = 2;

	// エネミー最大数(kEnemyMaxLineの値で割った数が偶数)
	static constexpr int kEnemyMaxNum = 10;

	// エネミーの最大行
	static constexpr int kEnemyMaxLine = 2;

	// トーチカの最大数(奇数)
	static constexpr int kBunkerMaxNum = 9;

	// 移動するframeの減少値
	static constexpr int kdecrementFrame = 10;

	// プレイヤーの残機
	static constexpr int kPlayerRemaining = 3;

	// スコア加点
	static constexpr int kAddedPoints = 10;


public:
	SceneMain();

	virtual ~SceneMain();


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

public:
	// ゲームオーバーフラグの取得
	void getIsGameOverFlag(bool isGameOver) { m_isGameOver = isGameOver; }

	// リセットフラグ
	void getIsResetFlag(bool isReset) { m_isReset = isReset; }



public:

	// リセット処理
	void RsetProcess();


	// エネミーの生成
	void CreateEnemy();

	// トーチカの生成
	void CreateBunker();

	// プレイヤーがダメージを受けたときの処理
	void PlayerDamageProcess();


	// プレイヤーがショットを撃つ
	bool CreateShotPlayer(VECTOR pos);

	// エネミーがショットを撃つ
	bool CreateShotEnemy(VECTOR pos);

	// エネミーとショットのあたり判定
	void EnemyToShotCollision();

	// トーチカとショットのあたり判定
	void BunkerToShotCollision();

	// トーチカとエネミーショットのあたり判定
	void BunkerToInvertShotCollision();

private:

	// エネミーのスライドカウント
	int m_enemySlideCount;

	// エネミーの列カウント
	int m_enemyLineCount;

	// エネミー行
	int m_enemyLine;

	// エネミー生成フラグ
	bool m_isEnemyCreate;

	// エネミーカウント
	int m_enemyCount;

	// トーチカのスライドカウント
	int m_bunkerSlideCount;

	// トーチカの列カウント
	int m_bunkerLineCount;

	// トーチカのカウント
	int m_bunkerCount;

	// ゲームオーバーフラグ
	int m_isGameOver;

	// リセットフラグ
	int m_isReset;

	// エネミーレベル
	int m_enemyLevel;

	// プレイヤー残機
	int m_playerRemaining;

	// スコア
	int m_score;

	// エネミーのグラフィック
	int m_enemyGraphic[Enemy::kEnemyGraphicDivNum];

	// ショットのグラフィック
	int m_shotGraphic;


	// クラスポインタ
	std::shared_ptr<Player>m_pPlayer;
	std::shared_ptr<Camera>m_pCamera;
	std::shared_ptr<Shot>m_pShot[kPlayerShotMaxNumber];
	std::shared_ptr<InvertShot>m_pInvertShot[kEnemyShotMaxNumber];
	std::shared_ptr<Enemy>m_pEnemy[kEnemyMaxNum];
	std::shared_ptr<Bunker>m_pBunker[kBunkerMaxNum];
	std::shared_ptr<GameOver>m_pGameOver;
	std::shared_ptr<MainUI>m_pMainUI;
};