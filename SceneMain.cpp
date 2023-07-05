﻿#include "game.h"

#include "SceneMain.h"
#include "SceneTitle.h"
#include "Pad.h"
#include "Player.h"
#include "Camera.h"
#include "Shot.h"
#include "InvertShot.h"
#include "Bunker.h"
#include "GameOver.h"
#include "MainUI.h"
#include "BackGround.h"
#include "Particle.h"

namespace
{
	// エネミーグラフィックの挿入
	const char* const kEnemyGraphic1FileName = "data/enemy1.png";

	// エネミーグラフィックの挿入
	const char* const kEnemyGraphic2FileName = "data/enemy2.png";

	// ショットグラフィック
	const char* const kShotGraphicFileName = "data/modele/cube.mv1";

	// エネミーショットグラフィック
	const char* const kEnemyShotGraphicFileName = "data/modele/cube.mv1";

	// パーティクルのグラフィックファイル名
	const char* const kParticleGraphicFileName = "data/particle.png";

	// トーチカのグラフィックファイル名
	const char* const kBunkerGraphicFileName = "data/modele/bunker.mv1";


	// エネミーの横距離
	constexpr float kEnemyWidthDistance = 20.0;

	// エネミーの移動レベル1（何割以下で速度を上げるのか）
	constexpr float kEnemyMoveLevel1 = 0.5;

	// エネミーの移動レベル2（何割以下で速度を上げるのか）
	constexpr float kEnemyMoveLevel2 = 0.2;

	// エネミーの移動インターバル減少値レベル1
	constexpr int kEnemyMoveInterval1 = 10;

	// エネミーの移動インターバル減少値レベル2
	constexpr int kEnemyMoveInterva2 = 30;

	// エネミーに下から何列目まで進ませるか
	constexpr int kEnemyEndCol = 2;


	// トーチカの横距離
	constexpr float kBunkerWidthDistance = 15.0f;

	// パーティクルの分散量
	constexpr int kParticleDistributedValue = 32;
}




SceneMain::SceneMain():
	m_enemySlideCount(0),
	m_enemyLineCount(0),
	m_enemyLine(0),
	m_isEnemyCreate(false),
	m_enemyCount(0),
	m_isGameOver(false),
	m_isReset(false),
	m_enemyLevel(0),
	m_playerRemaining(0),
	m_shotGraphic(-1),
	m_particleGraphic(-1),
	m_pPlayer(std::make_shared<Player>()),
	m_pCamera(std::make_shared<Camera>()),
	m_pGameOver(std::make_shared<GameOver>()),
	m_pMainUI(std::make_shared<MainUI>()),
	m_pBackGround(std::make_shared<BackGround>())
{

	for (auto& enemy : m_pEnemy)
	{
		enemy = std::make_shared<Enemy>();
	}

	for (auto& shot : m_pShot)
	{
		shot = std::make_shared<Shot>();
	}

	for (auto& invertShot : m_pInvertShot)
	{
		invertShot = std::make_shared<InvertShot>();
	}

	for (auto& bunker : m_pBunker)
	{
		bunker = std::make_shared<Bunker>();
	}

	for (auto& particle : m_pParticle)
	{
		particle = std::make_shared<Particle>();
	}

	// グラフィックハンドルの初期化
	for (auto& handle : m_enemyGraphic)
	{
		handle = -1;
	}

	for (auto& invertShot : m_invertShotGraphic)
	{
		invertShot = -1;
	}

	for (auto& bunker : m_bunkerGraphic)
	{
		bunker = -1;
	}

}

SceneMain::~SceneMain()
{
	// グラフィックの削除
	for (auto& handle : m_enemyGraphic)
	{
		DeleteGraph(handle);
	}
	for (auto& invertShot : m_invertShotGraphic)
	{
		MV1DeleteModel(invertShot);
	}
	for (auto& bunker : m_bunkerGraphic)
	{
		MV1DeleteModel(bunker);
	}


	DeleteGraph(m_particleGraphic);
	MV1DeleteModel(m_shotGraphic);

}

void SceneMain::init()
{
	// クラスポインタを送る
	m_pCamera->getPlayerPointer(m_pPlayer);
	m_pPlayer->getSceneMainPointer(this);
	m_pGameOver->setSceneMain(this);
	for (auto& enemy : m_pEnemy)
	{
		enemy->getSceneMainPointer(this);
	}
	for (auto& shot : m_pShot)
	{
		shot->getSceneMainPointer(this);
	}
	for (auto& invertShot : m_pInvertShot)
	{
		invertShot->getPlayerPointer(m_pPlayer);
	}
	for (auto& bunker : m_pBunker)
	{
		bunker->getSceneMainPointer(this);
	}

	// エネミーのグラフィックをロード
	m_enemyGraphic[0] = LoadGraph(kEnemyGraphic1FileName);
	m_enemyGraphic[1] = LoadGraph(kEnemyGraphic2FileName);

	// 分割したグラフィックを送る
	for (int i = 0; i < Enemy::kEnemyGraphicNum; i++)
	{
		for (auto& enemy : m_pEnemy)
		{
			enemy->setHandle(i, m_enemyGraphic[i]);
		}
	}



	// ショットのモデルを読み込む
	m_shotGraphic = MV1LoadModel(kShotGraphicFileName);

	// ショットにグラフィックを送る
	for (int i = 0; i < kPlayerShotMaxNumber; i++)
	{
		m_pShot[i]->getShotGraphic(m_shotGraphic);
	}


	// エネミーショットのモデルを読み込む
	int invertShotGraphic = MV1LoadModel(kEnemyShotGraphicFileName);



	// ショットにグラフィックを送る
	for (int i = 0; i < kEnemyShotMaxNumber; i++)
	{
		// モデルを配列にコピーする
		m_invertShotGraphic[i] = MV1DuplicateModel(invertShotGraphic);

		// ショットにグラフィックを送る
		m_pInvertShot[i]->getShotGraphic(m_invertShotGraphic[i]);
	}


	// グラフィックの挿入
	m_particleGraphic = LoadGraph(kParticleGraphicFileName);
	// パーティクルにグラフィックを送る
	for (auto& particle : m_pParticle)
	{
		particle->setHandle(m_particleGraphic);
	}

	// トーチカのグラフィック挿入
	int bunkerGraphic= MV1LoadModel(kBunkerGraphicFileName);

	// トーチカグラフィックを送る
	for (int i = 0; i < kBunkerMaxNum; i++)
	{
		// モデルを配列にコピーする
		m_bunkerGraphic[i] = MV1DuplicateModel(bunkerGraphic);

		m_pBunker[i]->getGraphic(m_bunkerGraphic[i]);
	}



	// クラスの初期化処理
	m_pPlayer->init();
	m_pCamera->init();
	m_pGameOver->init();
	m_pMainUI->init();
	m_pBackGround->init();

	// ショットにグラフィックを送る
	for (int i = 0; i < kPlayerShotMaxNumber; i++)
	{
		m_pShot[i]->init();
	}
	// エネミーショットにグラフィックを送る
	for (int i = 0; i < kEnemyShotMaxNumber; i++)
	{
		m_pInvertShot[i]->init();
	}



	// エネミーの生成
	CreateEnemy();

	// トーチカの生成
	CreateBunker();

	// 変数の初期化
	m_isGameOver = false;
	m_isReset = false;
	m_enemyLevel = 0;

	// プレイヤー残機の代入
	m_playerRemaining = kPlayerRemaining;
}

SceneBase* SceneMain::update()
{

	if (m_isGameOver)
	{
		m_pGameOver->update();
		return this;
	}

	if (m_isReset)
	{
		// リセット処理
		RsetProcess();

		m_isReset = false;
	}


	// クラスのアップデート処理
	m_pPlayer->update();
	m_pCamera->update();
	m_pMainUI->update();
	m_pBackGround->update();


	for (auto& enemy : m_pEnemy)
	{
		enemy->update();
	}
	for (auto shot : m_pShot)
	{
		shot->update();
	}
	for (auto& invertShot : m_pInvertShot)
	{
		invertShot->update();
	}
	for (auto& bunker : m_pBunker)
	{
		bunker->update();
	}
	for (auto& particle : m_pParticle)
	{
		particle->update();
	}


	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return (new SceneTitle);
	}



	// プレイヤーショットとエネミーショットの当たり判定
	ShotToInvertShotCollision();



	// エネミーをすべて消す
#if true

	DrawString(0, 15*8, "Dキーでエネミー全削除", GetColor(255, 255, 255));

	if (Pad::isTrigger(PAD_INPUT_6))
	{
		for (auto& enemy : m_pEnemy)
		{
			enemy->setExist(false);
			EnemyExistProcess();
		}
	}

#endif



	return this;
}

void SceneMain::draw()
{

	
	if (m_isGameOver)
	{
		m_pGameOver->draw();
	}

	
	// クラスの描画処理
	m_pPlayer->draw();
	m_pCamera->draw();
	m_pMainUI->draw();
	m_pBackGround->draw();

	for (auto& enemy : m_pEnemy)
	{
		enemy->draw();
	}
	for (auto shot : m_pShot)
	{
		shot->draw();
	}
	for (auto& invertShot : m_pInvertShot)
	{
		invertShot->draw();
	}
	for (auto& bunker : m_pBunker)
	{
		bunker->draw();
	}
	for (auto& particle : m_pParticle)
	{
		particle->draw();
	}


	DrawString(0, 0, "メイン画面", GetColor(255, 255, 255));

	// エネミーの数を表示
	DrawFormatString(0, 6 * 15, 0xffffff, "Maim enemyCount : %d", m_enemyCount);
}

void SceneMain::RsetProcess()
{
	// エネミーのレベルを1に戻す
	m_enemyLevel = 0;

	// プレイヤーの残機を最初の値に戻す
	m_playerRemaining = kPlayerRemaining;

	// プレイヤーを初期位置に戻す
	m_pPlayer->ResetPos();


	for (auto& enemy : m_pEnemy)
	{
		enemy->setExist(false);
	}
	for (auto shot : m_pShot)
	{
		shot->setExist(false);
	}
	for (auto& invertShot : m_pInvertShot)
	{
		invertShot->setExist(false);
	}
	for (auto& bunker : m_pBunker)
	{
		bunker->setExist(false);
	}

	// エネミーを作る
	CreateEnemy();

	// トーチカを作る
	CreateBunker();
}

void SceneMain::CreateEnemy()
{

	// 何列で次の行に移るのか
	int nextLine = kEnemyMaxNum / kEnemyMaxLine;


	// 変数の初期化
	m_enemyLineCount = 0;
	m_enemySlideCount = 0;
	m_enemyLine = 0;

	// レベルの値によって初期Ｚ座標をずらす
	float initSlaidPosZ = (Enemy::kMovePosZ * m_enemyLevel);

	// 初期Ｚ座標の最大値値
	float initMinPosZ = Enemy::kInitPosZ - ((Enemy::kMovePosZ * kEnemyEndCol) + (Enemy::kMovePosZ));

	// 初期Z座標が最大値を上回ったらレベルを0に戻す
	if (initSlaidPosZ > initMinPosZ)
	{
		// レベルを0にする
		m_enemyLevel = 0;

		// レベルの値によって初期Ｚ座標をずらす
		initSlaidPosZ = (Enemy::kMovePosZ * m_enemyLevel);
	}



	for (int i = 0; i < kEnemyMaxNum; i++)
	{
		// 位置をずらす
		float slidePosX = kEnemyWidthDistance;
		float slidePosZ = -Enemy::kMovePosZ;

		// エネミーを改行する
		if (m_enemyLineCount == nextLine)
		{
			// 変数の初期化
			m_enemyLineCount = 0;
			m_enemySlideCount = 0;

			// 列の変更
			m_enemyLine++;
		}

		// 奇数か偶数かで処理を分ける
		if (m_enemyLineCount % 2 == 0)
		{
			slidePosX *= -(m_enemyLineCount - m_enemySlideCount);

			// エネミーの列カウントを増やす
			m_enemyLineCount++;
		}
		else
		{
			slidePosX *= (m_enemyLineCount - m_enemySlideCount);

			// スライドカウントを増やすo
			m_enemySlideCount++;
			// エネミーの列カウントを増やす
			m_enemyLineCount++;
		}

		// 存在を与える
		m_pEnemy[i]->setExist(true);

		// 現在のY座標の値
		int nowPosZ = (slidePosZ * m_enemyLine) + (-initSlaidPosZ);

		// 位置を送る
		m_pEnemy[i]->init(slidePosX, nowPosZ);

		// 生成したエネミーの数を数える
		m_enemyCount++;
	}


}

void SceneMain::CreateBunker()
{
	// 変数の初期化
	m_bunkerLineCount = 0;
	m_bunkerSlideCount = 0;
	

	for (int i = 0; i < kBunkerMaxNum; i++)
	{
		// 位置をずらす
		float slidePosX = kBunkerWidthDistance;

		// 奇数か偶数かで処理を分ける
		if (m_bunkerLineCount % 2 == 0)
		{
			slidePosX *= -(m_bunkerLineCount - m_bunkerSlideCount);

			// エネミーの列カウントを増やす
			m_bunkerLineCount++;
		}
		else
		{
			slidePosX *= (m_bunkerLineCount - m_bunkerSlideCount);

			// スライドカウントを増やす
			m_bunkerSlideCount++;
			// エネミーの列カウントを増やす
			m_bunkerLineCount++;
		}

		// 存在を与える
		m_pBunker[i]->setExist(true);

		// 位置を送る
		m_pBunker[i]->init(slidePosX);
	}
}

void SceneMain::PlayerDamageProcess()
{
	// プレイヤーのHPを減らす（1ダメージ）
	m_playerRemaining -= 1;

	// プレイヤーのHP値（残機）を送る
	m_pMainUI->getPlayerHp(m_playerRemaining);


	// エネミーのレベルを下げる
	if (m_enemyLevel > 0)
	{
		m_enemyLevel -= 1;
	}


	// プレイヤーのHPが0だった場合はゲームオーバーフラグをtrueにする
	if (m_playerRemaining == 0)
	{
		m_isGameOver = true;
	}

}

/// <summary>
/// エネミーの存在処理
/// </summary>
void SceneMain::EnemyExistProcess()
{

	// エネミーの移動レベル1
	int enemyMoveLevel1 = kEnemyMaxNum * kEnemyMoveLevel1;

	// エネミーの移動レベル2
	int enemyMoveLevel2 = kEnemyMaxNum * kEnemyMoveLevel2;


	// エネミーの数を減らす
	m_enemyCount--;

	// すべてのエネミーを見る
	for (auto& enemy : m_pEnemy)
	{

		// エネミーの数がenemyMoveLevel1以下の時、エネミーの移動速度を上げる
		if (m_enemyCount <= enemyMoveLevel1)
		{
			enemy->getDecrementTime(kEnemyMoveInterval1);
		}
		// エネミーの数がenemyMoveLevel2以下の時、エネミーの移動速度を上げる
		if (m_enemyCount <= enemyMoveLevel2)
		{
			enemy->getDecrementTime(kEnemyMoveInterva2);
		}
	}


	// エネミーの数が0以下の時、エネミーを生成する
	if (m_enemyCount <= 0)
	{
		// エネミーのレベルを上げる
		m_enemyLevel++;

		// エネミーのレベル値を送る
		m_pMainUI->getEnemyLv(m_enemyLevel);

		// エネミーの生成
		CreateEnemy();
	}
}

/// <summary>
/// パーティクルの生成
/// </summary>
/// <param name="pos">エネミーの位置</param>
/// <param name="color">色</param>
/// <returns></returns>
void SceneMain::createParticle(VECTOR pos, int color)
{
	int particleCount = 0;
	
	
	// すべてのパーティクルをみる
	for (auto& particle : m_pParticle)
	{
		// 存在していないパーティクルを探す
		if (!particle->isExist())
		{
			// ショットを打つたびにカウントを増やす
			particleCount++;

			// ショットを打つ
			particle->start(VECTOR(pos), color);

		}

		//パーティクルの数が32個を超えたら処理を終える
		if (particleCount >= kParticleDistributedValue)
		{
			break;
		}
	}
	
}

bool SceneMain::CreateShotPlayer(VECTOR pos)
{
	// すべてのショットをみる
	for (auto& shot : m_pShot)
	{
		// 存在していないショットを探す
		if (!shot->isExist())
		{
			// ショットを打つ
			shot->start(VECTOR(pos));

			return true;
		}
	}

	return false;
}

bool SceneMain::CreateShotEnemy(VECTOR pos)
{
	// すべてのショットをみる
	for (auto& invertShot : m_pInvertShot)
	{
		// 存在していないショットを探す
		if (!invertShot->isExist())
		{
			// ショットを打つ
			invertShot->start(VECTOR(pos));

			return true;
		}
	}
	return false;
}


void SceneMain::EnemyToShotCollision()
{
	// エネミーを見る
	for (auto& enemy : m_pEnemy)
	{
		// プレイヤーのショットが存在するとき
		if (enemy->isExist())
		{
			// すべてのプレイヤーの弾をみる
			for (auto& shot : m_pShot)
			{
				// プレイヤーのショットが存在するとき
				if (shot->isExist())
				{
					// FIXME

					// 円形の当たり判定(X,Y)
					float dx = shot->getPos().x - enemy->getPos().x;
					float dy = shot->getPos().y - enemy->getPos().y;
					float dr = dx * dx + dy * dy;// A²＝B²＋C²

					float ar = Shot::kShotSize + Enemy::kCircleSize;// 当たり判定の大きさ
					float dl = ar * ar;


		
					// プレイヤーのショットにエネミーが当たったとき(X,Y)
					if (dr < dl)
					{

						// 円形の当たり判定(Z,Y)
						dx = shot->getPos().z - enemy->getPos().z;
						dr = dx * dx + dy * dy;// A²＝B²＋C²

						dl = ar * ar;


						// プレイヤーのショットにエネミーが当たったとき処理を終わらせる(Z,Y)
						if (dr < dl)
						{

							// エネミーに当たったプレイヤーの弾を消す
							shot->setExist(false);

							// プレイヤーのショットに当たったエネミーを消す
							enemy->setExist(false);

							// エネミーの存在処理
							EnemyExistProcess();

							// パーティクル処理を呼び出す
							createParticle(enemy->getPos(),0);

							// スコアを増やす
							m_score += kAddedPoints;

							m_pMainUI->getScore(m_score);


						}
					}
				}
			}
		}
	}
}

/// <summary>
/// トーチカとショットの当たり判定
/// </summary>
void SceneMain::BunkerToShotCollision()
{
	// トーチカを見る
	for (auto& bunker : m_pBunker)
	{
		// トーチカが存在するとき
		if (bunker->isExist())
		{
			// すべてのプレイヤーの弾をみる
			for (auto& shot : m_pShot)
			{
				// プレイヤーのショットが存在するとき
				if (shot->isExist())
				{
					// 円形の当たり判定
					float dx = shot->getPos().x - bunker->getPos().x;
					float dy = shot->getPos().y - bunker->getPos().y;
					float dr = dx * dx + dy * dy;// A²＝B²＋C²

					float ar = Shot::kShotSize + Bunker::kCircleSize;// 当たり判定の大きさ
					float dl = ar * ar;

					// プレイヤーのショットにトーチカが当たったとき(X,Y)
					if (dr < dl)
					{
						// 円形の当たり判定(Z,Y)
						dx = shot->getPos().z - bunker->getPos().z;
						dr = dx * dx + dy * dy;// A²＝B²＋C²

						dl = ar * ar;
						
						// プレイヤーのショットにトーチカが当たったとき(Z,Y)
						if (dr < dl)
						{

							// トーチカ当たったプレイヤーの弾を消す
							shot->setExist(false);

							// プレイヤーのショットに当たったトーチカにダメージを与える
							bunker->DamegeProcess(1);
						}
					}
				}
			}
		}
	}
}

/// <summary>
/// トーチカとエネミーショットの判定
/// </summary>
void SceneMain::BunkerToInvertShotCollision()
{
	// トーチカを見る
	for (auto& bunker : m_pBunker)
	{
		// トーチカが存在するとき
		if (bunker->isExist())
		{
			// すべてのエネミーの弾をみる
			for (auto& invertShot : m_pInvertShot)
			{
				// エネミーのショットが存在するとき
				if (invertShot->isExist())
				{
					// 円形の当たり判定
					float dx = invertShot->getPos().x - bunker->getPos().x;
					float dy = invertShot->getPos().y - bunker->getPos().y;
					float dr = dx * dx + dy * dy;// A²＝B²＋C²

					float ar = InvertShot::kShotSize + Bunker::kCircleSize;// 当たり判定の大きさ
					float dl = ar * ar;

					// エネミーのショットにトーチカが当たったとき(X,Y)
					if (dr < dl)
					{
						// 円形の当たり判定(Z,Y)
						dx = invertShot->getPos().z - bunker->getPos().z;
						dr = dx * dx + dy * dy;// A²＝B²＋C²

						dl = ar * ar;

						// エネミーのショットにトーチカが当たったとき(Z,Y)
						if (dr < dl)
						{

							// トーチカに当たったエネミーの弾を消す
							invertShot->setExist(false);

							// エネミーのショットに当たったトーチカにダメージを与える
							bunker->DamegeProcess(1);

						}
					}
				}
			}
		}
	}
}


/// <summary>
/// プレイヤーのショットとエネミーのショットの当たり判定
/// </summary>
void SceneMain::ShotToInvertShotCollision()
{

	// すべてのプレイヤーの弾をみる
	for (auto& shot : m_pShot)
	{
		// プレイヤーのショットが存在するとき
		if (shot->isExist())
		{

			// すべてのエネミーの弾をみる
			for (auto& invertShot : m_pInvertShot)
			{
				// エネミーのショットが存在するとき
				if (invertShot->isExist())
				{
					// 円形の当たり判定
					float dx = shot->getPos().x - invertShot->getPos().x;
					float dy = shot->getPos().y - invertShot->getPos().y;
					float dr = dx * dx + dy * dy;// A²＝B²＋C²

					float ar = Shot::kShotSize + InvertShot::kShotSize;// 当たり判定の大きさ

					float dl = ar * ar;

					// プレイヤーのショットとエネミーのショットが当たったとき(X,Y)
					if (dr < dl)
					{
						// 円形の当たり判定(Z,Y)
						dx = shot->getPos().z - invertShot->getPos().z;
						dr = dx * dx + dy * dy;// A²＝B²＋C²

						dl = ar * ar;

						// プレイヤーのショットとエネミーのショットが当たったとき(Z,Y)
						if (dr < dl)
						{

							// プレイヤーの弾を消す
							shot->setExist(false);


							// エネミーの弾を消す
							invertShot->setExist(false);
						}
					}

				}
			}
		}
	}
}


