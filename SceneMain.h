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
class GameStart;
class BonusEnemy;
class SceneMain : public SceneBase
{
public:
	// ショットの最大数
	static constexpr int kPlayerShotMaxNumber = 10;

	// エネミーのショット最大数
	static constexpr int kEnemyShotMaxNumber = 2;

	// エネミー最大数(kEnemyMaxLineの値で割った数が偶数)
	static constexpr int kEnemyMaxNum = 8;

	// エネミーの最大行
	static constexpr int kEnemyMaxLine = 2;

	// トーチカの最大数(奇数)
	static constexpr int kBunkerMaxNum = 9;

	// 移動するframeの減少値
	static constexpr int kdecrementFrame = 10;

	// プレイヤーの残機
	static constexpr int kPlayerRemaining = 3;



	// パーティクルの最大数
	static constexpr int kParticleMaxNum = 128;

	// ヒットストップ時に止める時間（フレーム）
	static constexpr int kFreezeFrameMaxCount = 60;

public:
	SceneMain();

	virtual ~SceneMain();


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

public:
	// ゲームオーバーフラグの取得
	void setIsGameOverFlag(bool isGameOver) { m_isGameOver = isGameOver; }

	// リセットフラグ
	void setIsResetFlag(bool isReset) { m_isReset = isReset; }

	// ポーズするかどうかを取得する
	void setIsPause(bool isPause) { m_isPause = isPause; }

	// タイトルに戻るかどうかのフラグを取得する
	void setIsTurnTitle(bool isTurnTitle) { m_isTurnTitle = isTurnTitle; }

	// ゲームスタートフラグの取得
	void setIsGameStartFlag(bool isGameStart) { m_isGameStart = isGameStart; }

public:

	// ヒットストップ処理
	void FreezeFrame();

	// リセット処理
	void RsetProcess();

	// 得点処理
	void ScoreProcess(int score);

	// エネミーの生成
	void CreateEnemy();

	// トーチカの生成
	void CreateBunker();

	// プレイヤーがダメージを受けたときの処理
	void PlayerDamageProcess();

	// エネミーの存在処理
	void EnemyExistProcess();

	// パーティクル生成
	void CreateParticle(VECTOR pos, VECTOR color, int particleValue,int alphaValue);

	// パーティクル生成3D
	void CreateParticle3D(VECTOR pos, VECTOR color, int particleValue, float alphaValue, float scale, bool isDualColor = false, VECTOR color2 = VGet(0, 0, 0), float alphaValue2 = 0.0f, float scale2 = 0.0f);

	// ゲームオーバーになるまでのカウント処理
	void GameOverCount();

	// プレイヤーがショットを撃つ
	bool CreateShotPlayer(VECTOR pos, bool isPowerUp, int powerUpNum);

	// エネミーがショットを撃つ
	bool CreateShotEnemy(VECTOR pos, int enemyLineNum);

	// エネミーショットフラグ
	void IsShotEnemy(VECTOR pos, int enemyNum, int enemyLineNum);


	// エネミーとショットのあたり判定
	void EnemyToShotCollision(int num, VECTOR pos, bool isPenetration, float shotSize);

	// トーチカとショットのあたり判定
	void BunkerToShotCollision();

	// トーチカとエネミーショットのあたり判定
	void BunkerToInvertShotCollision();

	// プレイヤーショットとエネミーショットの当たり判定
	void ShotToInvertShotCollision(bool isPenetration, float shotSize);

private:

	// ヒットストップカウント
	int m_freezeFrameCount;

	// ヒットストップ中かのフラグ
	bool m_isFreezeFrame;


	// エネミーレベル
	int m_enemyLv;


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
	int m_enemyLineNow;

	// プレイヤー残機
	int m_playerRemaining;

	// エネミーのグラフィック
	int m_enemyGraphic[EnemySet::kEnemyGraphicNum];

	// ショットのグラフィック
	int m_shotGraphic[kPlayerShotMaxNumber];

	// エネミーショットのグラフィック
	int m_invertShotGraphic[kEnemyShotMaxNumber];


	// Particleのグラフィック
	int m_particleGraphic;

	// トーチカのグラフィック
	int m_bunkerGraphic[kBunkerMaxNum];

	// エネミー列番号
	int m_enemyLineNum;

	// ゲームオーバーになるまでのカウント
	int m_gameOverCount;

	// プレイヤーが生きているかどうか
	int m_isAlivePlayer;

	// ポーズするかどうかのフラグ
	bool m_isPause;

	// タイトルに戻るかどうかのフラグ
	bool m_isTurnTitle;

	// ゲームを始めるかどうかのフラグ
	bool m_isGameStart;

	

	// クラスポインタ
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
	std::shared_ptr<GameStart>m_pGameStart;
	std::shared_ptr<BonusEnemy>m_pBonusEnemy;
};