#include "game.h"

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
#include "Particle3D.h"
#include "Enemy.h"
#include "Pause.h"
#include "GameStart.h"
#include "BonusEnemy.h"

namespace
{
	
	// ショットモデルグラフィック
	const char* const kShotGraphicFileName = "data/model/cube.mv1";

	// エネミーショットモデルグラフィック
	const char* const kEnemyShotGraphicFileName = "data/model/cube.mv1";

	// パーティクルのグラフィックファイル名
	const char* const kParticleGraphicFileName = "data/particle.png";

	// トーチカのモデルグラフィックファイル名
	const char* const kBunkerGraphicFileName = "data/model/cube.mv1";

	// 3Dパーティクルのモデルグラフィックファイル名
	const char* const kParticleModelFileName = "data/model/cube.mv1";


	// レベルが上がるごとにスピードを上げる
	constexpr int kEnemyLvMoveSpeed = 5;



	// トーチカの横距離
	constexpr float kBunkerWidthDistance = 15.0f;

	// パーティクルの分散量
	constexpr int kParticleDistributedValue = 32;

	// ショットが衝突したときのパーティクルのスケール
	constexpr float kShotParticleScale = 1.0f;

	// ショットが衝突したときのパーティクルの分散量
	constexpr int kShotParticleDistributedValue = 16;




	// ゲームオーバー時のフレームカウント(プレイヤーがやられてからなんフレーム後にゲームオーバーに移行させるか)
	constexpr int kGameOverMaxFrame = 40;

}






SceneMain::SceneMain():
	m_freezeFrameCount(0),
	m_isFreezeFrame(false),
	m_isEnemyCreate(false),
	m_enemyLv(0),
	m_enemyCount(0),
	m_isGameOver(false),
	m_isReset(false),
	m_enemyLineNow(0),
	m_playerRemaining(0),
	m_particleGraphic(-1),
	m_gameOverCount(0),
	m_isAlivePlayer(true),
	m_isPause(false),
	m_isTurnTitle(false),
	m_isGameStart(false),
	m_enemyLineNum(0),
	m_pPlayer(std::make_shared<Player>()),
	m_pCamera(std::make_shared<Camera>()),
	m_pGameOver(std::make_shared<GameOver>()),
	m_pMainUI(std::make_shared<MainUI>()),
	m_pBackGround(std::make_shared<BackGround>()),
	m_pPause(std::make_shared<Pause>()),
	m_pGameStart(std::make_shared<GameStart>()),
	m_pBonusEnemy(std::make_shared<BonusEnemy>())
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

	for (auto& particle3D : m_pParticle3D)
	{
		particle3D = std::make_shared<Particle3D>();
	}


	// グラフィックハンドルの初期化
	for (auto& handle : m_enemyGraphic)
	{
		handle = -1;
	}

	for (auto& Shot : m_shotGraphic)
	{
		Shot = -1;
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
	for (auto& Shot : m_shotGraphic)
	{
		MV1DeleteModel(Shot);
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

}

void SceneMain::init()
{
	// クラスポインタを送る
	m_pCamera->getPlayerPointer(m_pPlayer);
	m_pPlayer->getSceneMainPointer(this);
	m_pPlayer->getMainUIPointer(m_pMainUI);
	m_pGameOver->setSceneMainPointer(this);
	m_pPause->getSceneMainPointer(this);
	m_pGameStart->getSceneMainPointer(this);
	m_pBonusEnemy->getSceneMainPointer(this);


	for (auto& enemy : m_pEnemy)
	{
		enemy->getSceneMainPointer(this);
	}
	for (auto& shot : m_pShot)
	{
		shot->getSceneMainPointer(this);
		shot->getBonusEnemyPointer(m_pBonusEnemy);
		shot->getPlayerPointer(m_pPlayer);
		
	}
	for (auto& invertShot : m_pInvertShot)
	{
		invertShot->getPlayerPointer(m_pPlayer);
	}
	for (auto& bunker : m_pBunker)
	{
		bunker->getSceneMainPointer(this);
	}


	// ショットのモデルを読み込む
	int shotGraphic = MV1LoadModel(kShotGraphicFileName);

	// ショットにグラフィックを送る
	for (int i = 0; i < kPlayerShotMaxNumber; i++)
	{
		// モデルを配列にコピーする
		m_shotGraphic[i] = MV1DuplicateModel(shotGraphic);

		m_pShot[i]->getShotGraphic(m_shotGraphic[i]);

		m_pShot[i]->setShotNum(i);
	}


	// エネミーショットのモデルを読み込む
	int invertShotGraphic = MV1LoadModel(kEnemyShotGraphicFileName);

	// ショットにグラフィックを送る
	for (int i = 0; i < kEnemyShotMaxNumber; i++)
	{
		// モデルを配列にコピーする
		m_invertShotGraphic[i] = MV1DuplicateModel(invertShotGraphic);

		// ショットにグラフィックを送る
		m_pInvertShot[i]->setShotGraphic(m_invertShotGraphic[i]);
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

		m_pBunker[i]->setGraphic(m_bunkerGraphic[i]);
		m_pBunker[i]->setNumber(i);
	}


	// グラフィックの挿入
	int particleModel = MV1LoadModel(kParticleModelFileName);

	// グラフィックの格納配列
	int particleModelGnar[kParticleMaxNum];

	// 3Dパーティクルにグラフィックを送る
	for (int i=0;i<kParticleMaxNum;i++)
	{
		// モデルを配列にコピーする
		particleModelGnar[i]= MV1DuplicateModel(particleModel);

		m_pParticle3D[i]->setHandle(particleModelGnar[i]);
	}



	// クラスの初期化処理
	m_pPlayer->init();
	m_pCamera->init();
	m_pGameOver->init();
	m_pMainUI->init();
	m_pBackGround->init(1);
	m_pPause->init();
	m_pGameStart->init();
	m_pBonusEnemy->init();


	// ショットの初期化処理
	for (int i = 0; i < kPlayerShotMaxNumber; i++)
	{
		m_pShot[i]->init();
	}
	// エネミーショットの初期化処理
	for (int i = 0; i < kEnemyShotMaxNumber; i++)
	{
		m_pInvertShot[i]->init();
	}



	// エネミーの生成
	CreateEnemy();

	// トーチカの生成
	CreateBunker();

	// 変数の初期化
	m_freezeFrameCount = kFreezeFrameMaxCount;
	m_isFreezeFrame = false;
	m_isGameOver = false;
	m_isReset = false;
	m_enemyLv = 0;
	m_enemyLineNow = 0;

	// プレイヤー残機の代入
	m_playerRemaining = kPlayerRemaining;


	// ゲームオーバーに移行するためのフレーム初期化
	m_gameOverCount = kGameOverMaxFrame;

	// プレイヤーは生きているのでtrue
	m_isAlivePlayer = true;

	// ポーズしていないのでfalse
	m_isPause = false;

	// タイトルフラグが立っていないのでfalse
	m_isTurnTitle = false;

	// グラフィック削除
	MV1DeleteModel(particleModel);
	


	// test
	//m_isGameOver = true;
}

SceneBase* SceneMain::update()
{
	// ゲームスタートしてなかったら処理を行う
	if (!m_isGameStart)
	{
		m_pGameStart->update();

		return this;
	}

	if (m_isGameOver)
	{
		m_pGameOver->update();

		m_isFreezeFrame = false;

		return this;
	}

	if (m_isReset)
	{
		// リセット処理
		RsetProcess();

		m_isReset = false;
	}


	m_pPause->update();

	// タイトルに戻る
	if (m_isTurnTitle)
	{
		return (new SceneTitle);
	}

	// ポーズしていたらこの下の処理を行わない
	if (m_isPause)return this;

	// クラスのアップデート処理
	m_pCamera->update();
	m_pMainUI->update();
	m_pBackGround->update();


	for (auto& bunker : m_pBunker)
	{
		bunker->update();
	}
	for (auto& particle : m_pParticle)
	{
		particle->update();
	}
	for (auto& particle3D : m_pParticle3D)
	{
		particle3D->update();
	}

	// ヒットストップ中は処理を行わない
	if (!m_isFreezeFrame)
	{

		// プレイヤーのHPが0以外なら処理を行う
		if (m_playerRemaining != 0)m_pPlayer->update();

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

		m_pBonusEnemy->update();
	}


	// ヒットストップ処理
	FreezeFrame();

	// ゲームオーバーになるまでのカウント処理
	GameOverCount();



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
	
	// クラスの描画処理
	
	//ゲームスタートしてなかったら処理を行う
	if (!m_isGameStart)
	{
		m_pGameStart->draw();
	}

	m_pCamera->draw();
	m_pBackGround->draw();
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
	for (auto& particle3D : m_pParticle3D)
	{
		particle3D->draw();
	}

	
	m_pBonusEnemy->draw();

	for (auto& enemy : m_pEnemy)
	{
		enemy->draw();
	}

	for (auto& particle : m_pParticle)
	{
		particle->draw();
	}



	// プレイヤーが生きていたら表示する
	if (m_isAlivePlayer)
	{
		m_pPlayer->draw();
	}

	m_pMainUI->draw();

#if false

	DrawString(0, 0, "メイン画面", GetColor(255, 255, 255));

	// エネミーの数を表示
	DrawFormatString(0, 6 * 15, 0xffffff, "Maim enemyCount : %d", m_enemyCount);

	DrawFormatString(0, 5 * 15, 0xffffff, "Maim playerHP : %d", m_playerRemaining);

#endif

	m_pPause->draw();

	if (m_isGameOver)
	{
		m_pGameOver->draw();
	}

}

void SceneMain::FreezeFrame()
{
	// フラグがfalseならここで処理を終わる
	if (!m_isFreezeFrame)return;

	// パッドを振動させる
	StartJoypadVibration(DX_INPUT_PAD1, 500, -1, -1);

	// フレームカウントを減らす
	m_freezeFrameCount--;

	// カメラクラス
	m_pCamera->ShakeScreen(m_freezeFrameCount);



	// フレームカウントが0になったらフレームカウントを初期値に戻しフラグをfalseにする
	if (m_freezeFrameCount < 0)
	{
		// パッドの振動を止める
		StopJoypadVibration(DX_INPUT_PAD1, -1);

		// すべてのショットをみる
		for (auto& shot : m_pShot)
		{
			// ショットを消す
			shot->setExist(false);
		}
		// すべてのショットをみる
		for (auto& shot : m_pInvertShot)
		{
			// ショットを消す
			shot->setExist(false);
		}

		// フレームカウントの初期化
		m_freezeFrameCount = kFreezeFrameMaxCount;

		// フラグをfalseにする
		m_isFreezeFrame = false;

		// プレイヤーのHPが0だった場合はパーティクルを出す
		if (m_playerRemaining == 0)
		{
			CreateParticle3D(m_pPlayer->getPos(), m_pPlayer->getColor(),PlayerSet::kParticleValue, PlayerSet::kAlphaValue, PlayerSet::kParticleScale);

			m_isAlivePlayer = false;
		}
	}

}

void SceneMain::RsetProcess()
{
	// エネミーの列を0に戻す
	m_enemyLineNow = 0;

	// エネミーのレベルを0にする
	m_enemyLv = 0;

	// プレイヤーの残機を最初の値に戻す
	m_playerRemaining = kPlayerRemaining;

	// UIに送る
	m_pMainUI->getEnemyLv(m_enemyLv);
	m_pMainUI->getPlayerHp(m_playerRemaining);
	m_pMainUI->ScoreArray(0);// スコアを0にする

	// プレイヤーを初期状態に戻す
	m_pPlayer->Reset();

	// エネミーの数を０にする
	m_enemyCount = 0;

	// ゲームオーバーに移行するためのフレーム初期化
	m_gameOverCount = kGameOverMaxFrame;

	// プレイヤーを生きていることにする
	m_isAlivePlayer = true;


	for (auto& enemy : m_pEnemy)
	{
		enemy->setExist(false);
		enemy->Reset();
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

void SceneMain::ScoreProcess(int score)
{

	// スコアを送る
	m_pMainUI->ScoreArray(score);
}

void SceneMain::CreateEnemy()
{

	// 色指定
	VECTOR color = VGet(0,0,0);


	// 何列で次の行に移るのか
	int nextColumn = kEnemyMaxNum / kEnemyMaxLine;

	// 変数の初期化
	int enemyLineCount = 0;
	int enemySlideCount = 0;
	int enemyLine = 0;

	// 現在のエネミーの列の値によって初期Ｚ座標をずらす
	float initSlaidPosZ = (EnemySet::kMovePosZ * m_enemyLineNow);

	// 初期Ｚ座標の最大値
	float initMinPosZ = EnemySet::kInitPosZ - ((EnemySet::kMovePosZ * EnemySet::kEnemyEndCol) + (EnemySet::kMovePosZ * (kEnemyMaxLine - 1)));


	// エネミーの列が奇数かどうか（奇数ならtrue、偶数ならfalse）
	bool isOddNumber = true;

	if (nextColumn % 2 == 0)
	{
		isOddNumber = false;
	}


	// 初期Z座標が最大値を上回ったら列を初期値に戻す
	if (initSlaidPosZ > initMinPosZ)
	{
		// レベルを上げる
		m_enemyLv++;

		// エネミーのレベル値を送る
		m_pMainUI->getEnemyLv(m_enemyLv);
		m_pMainUI->getIsTextMove(true);

		// エネミーのインターバルを減らす
		for (auto& enemy : m_pEnemy)
		{
			enemy->LevelUp(EnemySet::kLevelMoveInterval);
		}
	

		// 列の初期化
		m_enemyLineNow = 0;

		// 列の値によって初期Ｚ座標をずらす
		initSlaidPosZ = (EnemySet::kMovePosZ * m_enemyLineNow);
	}

	// 位置をずらす
	float slidePosX = 0.0f;
	float slidePosZ = 0.0f;

	float savePosX = 0.0f;

	for (int i = 0; i < kEnemyMaxNum; i++)
	{


		// 位置をずらす
		slidePosX = EnemySet::kEnemyWidthDistance;
		slidePosZ = -EnemySet::kMovePosZ;

		// エネミーを改行する
		if (enemyLineCount == nextColumn || enemyLineCount == 0)
		{


			if (enemyLineCount != 0)
			{
				// 列の変更
				enemyLine++;
			}

			// 変数の初期化
			enemyLineCount = 0;
			enemySlideCount = 0;

			// 列によって処理を分ける
			switch (enemyLine % kEnemyMaxLine)
			{
			case 0:
				// エネミーのグラフィックをロード
				m_enemyGraphic[0] = LoadGraph(EnemySet::kEnemy1_1GraphicFileName);
				m_enemyGraphic[1] = LoadGraph(EnemySet::kEnemy1_2GraphicFileName);

				// 色指定
				color = VGet(EnemySet::kEnemy1CollarR, EnemySet::kEnemy1CollarG, EnemySet::kEnemy1CollarB);

				break;
			case 1:
				// エネミーのグラフィックをロード
				m_enemyGraphic[0] = LoadGraph(EnemySet::kEnemy2_1GraphicFileName);
				m_enemyGraphic[1] = LoadGraph(EnemySet::kEnemy2_2GraphicFileName);

				// 色指定
				color = VGet(EnemySet::kEnemy2CollarR, EnemySet::kEnemy2CollarG, EnemySet::kEnemy2CollarB);
				break;
			case 2:
				// エネミーのグラフィックをロード
				m_enemyGraphic[0] = LoadGraph(EnemySet::kEnemy3_1GraphicFileName);
				m_enemyGraphic[1] = LoadGraph(EnemySet::kEnemy3_2GraphicFileName);

				// 色指定
				color = VGet(EnemySet::kEnemy3CollarR, EnemySet::kEnemy3CollarG, EnemySet::kEnemy3CollarB);
				break;
			}
		}

		// エネミーの番号を代入
		m_enemyLineNum = enemyLine;

		if (isOddNumber)
		{
			// 奇数か偶数かで処理を分ける
			if (enemyLineCount % 2 == 0)
			{
				slidePosX *= -(enemyLineCount - enemySlideCount);

				// エネミーの列カウントを増やす
				enemyLineCount++;
			}
			else
			{
				slidePosX *= (enemyLineCount - enemySlideCount);

				// スライドカウントを増やすo
				enemySlideCount++;
				// エネミーの列カウントを増やす
				enemyLineCount++;
			}
		}
		else
		{
			
			// 位置をずらす
			slidePosX = EnemySet::kEnemyWidthDistance / 2;
			

			float pos = 0.0f;

			if (enemyLineCount >= 2)
			{
				// 位置をずらす
				pos = EnemySet::kEnemyWidthDistance / 2;
			}


			// 奇数か偶数かで処理を分ける
			if (enemyLineCount % 2 == 0)
			{
				// エネミーの列カウントを増やす
				enemyLineCount++;
				slidePosX *= -(enemyLineCount - enemySlideCount);

				slidePosX -= pos;
			}
			else
			{
				// スライドカウントを増やすo
				enemySlideCount++;
				// エネミーの列カウントを増やす
				enemyLineCount++;

				slidePosX *= (enemyLineCount - enemySlideCount);

				slidePosX += pos;
			}

		}

		// 存在を与える
		m_pEnemy[i]->setExist(true);

		// 現在のY座標の値
		int nowPosZ = (slidePosZ * enemyLine) + (-initSlaidPosZ);

		// 位置を送る
		m_pEnemy[i]->init(slidePosX, nowPosZ, m_enemyLineNum);

		// 色を送る
		m_pEnemy[i]->setColor(color);

		// エネミーの番号を送る
		m_pEnemy[i]->setEnemyNum(i);


		// 分割したグラフィックを送る
		for (int j = 0; j < EnemySet::kEnemyGraphicNum; j++)
		{
			m_pEnemy[i]->setHandle(j, m_enemyGraphic[j]);
		}


		// 一番端のエネミーの座標を入れる
		if (nextColumn == enemyLineCount)
		{
			if (isOddNumber)
			{
				savePosX = slidePosX;
			}
			else
			{
				savePosX = -slidePosX;
			}
		}


		// 生成したエネミーの数を数える
		m_enemyCount++;
	}

	for (auto& enemy : m_pEnemy)
	{
		enemy->MoveSetting(savePosX);
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
	if (m_enemyLineNow > 0)
	{
		m_enemyLineNow -= 1;
	}

	// ヒットストップをする
	m_isFreezeFrame = true;
}

/// <summary>
/// エネミーの存在処理
/// </summary>
void SceneMain::EnemyExistProcess()
{
	// パーセントを入れる
	int percentage=0;

	// インターバル減少値
	float intervalDecrement = 1.0;

	// エネミーの数を減らす
	m_enemyCount--;

	// 生き残っているエネミーのパーセントを求める
	{
		// 割合
		float ratio = 100.0 * m_enemyCount;

		// パーセントを入れる
		percentage = ratio / kEnemyMaxNum;

		if (percentage < EnemySet::kEnemyMoveLevel1)
		{
			intervalDecrement = EnemySet::kEnemyMoveInterval1;

			if (percentage < EnemySet::kEnemyMoveLevel2)
			{
				intervalDecrement = EnemySet::kEnemyMoveInterval2;
			}
		}

	}


	// すべてのエネミーを見る
	for (auto& enemy : m_pEnemy)
	{
		// エネミーが存在するとき
		if (enemy->isExist())
		{
			/*int interval = (enemy->getMoveInterval() * intervalDecrement);


			enemy->EnemyNumInterval(interval);*/
		}

		int interval = (enemy->getMoveInterval() * intervalDecrement);


		enemy->EnemyNumInterval(interval);
	}


	// エネミーの数が0以下の時、エネミーを生成する
	if (m_enemyCount <= 0)
	{
		// エネミーの列の値をあげる
		m_enemyLineNow++;

		// ショットを消す
		{
			for (auto shot : m_pShot)
			{
				shot->setExist(false);
			}
			for (auto& invertShot : m_pInvertShot)
			{
				invertShot->setExist(false);
			}
		}

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
void SceneMain::CreateParticle(VECTOR pos, VECTOR color, int particleValue, int alphaValue)
{
	// パーティクルを出した数を数える
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
			particle->start(VECTOR(pos), color, alphaValue);
		}

		//パーティクルの数がparticleValueを超えたら処理を終える
		if (particleCount >= particleValue)
		{
			return;
		}
	}

	return;
}



/// <summary>
/// 3Dパーティクル
/// </summary>
/// <param name="pos">位置</param>
/// <param name="color">色</param>
/// <param name="particleValue">パーティクル量</param>
/// <param name="alphaValue">透明度</param>
/// <param name="scale">大きさ</param>
/// <param name="isDualColor">色が二つかどうか</param>
/// <param name="color2">色</param>
/// <param name="alphaValue2">透明度</param>
/// <param name="scale">大きさ</param>
void SceneMain::CreateParticle3D(VECTOR pos, VECTOR color, int particleValue, float alphaValue, float scale, bool isDualColor, VECTOR color2,float alphaValue2, float scale2)
{

	VECTOR Color = color;
	float AlphaValue = alphaValue;
	float Scale = scale;


	// パーティクルの数を数える
	int particleCount = 0;

	// すべてのパーティクルをみる
	for (auto& particle3D : m_pParticle3D)
	{
		// 存在していないパーティクルを探す
		if (!particle3D->isExist())
		{
			// ショットを打つたびにカウントを増やす
			particleCount++;

			if (isDualColor)
			{
				// 色を変えるか変えないかの変数
				int isChange = 0;

				// 乱数を取得
				isChange = GetRand(1);

				if (isChange == 0)
				{
					Color = color;
					AlphaValue = alphaValue;
					Scale = scale;
				}
				else
				{
					Color = color2;
					AlphaValue = alphaValue2;
					Scale = scale2;
				}

			}



			// ショットを打つ
			particle3D->start(VECTOR(pos), Color, Scale, AlphaValue);
		}

		//パーティクルの数が32個を超えたら処理を終える
		if (particleCount >= particleValue)
		{
			break;
		}
	}
}

void SceneMain::GameOverCount()
{
	// プレイヤーのHPが0以外ならここで処理を終了する
	if (m_playerRemaining != 0)return;

	// プレイヤーがやられたときm_gameOverCountを減らし、0になったらゲームオーバー処理へ移行する
	if (!m_isAlivePlayer)
	{
		m_gameOverCount--;

		if (m_gameOverCount <= 0)
		{
			m_isGameOver = true;
		}
	}

}

bool SceneMain::CreateShotPlayer(VECTOR pos, bool isPowerUp, int powerUpNum)
{

	// すべてのショットをみる
	for (int i = 0; i < kPlayerShotMaxNumber; i++)
	{
		// 存在していないショットを探す
		if (!m_pShot[i]->isExist())
		{

		
			switch (powerUpNum)
			{
			case 1:
				break;

			case 2:
				if (i >= 2)
				{
					return false;
				}
				break;

			default:
				if (i >= 1)
				{
					return false;
				}
				break;
			}

			// ショットを打つ
			m_pShot[i]->start(VECTOR(pos), isPowerUp, powerUpNum);

			return true;
		}
	}

	return false;
}

bool SceneMain::CreateShotEnemy(VECTOR pos,int enemyNum)
{
	// ショットカラー
	VECTOR shotColor = VGet(0, 0, 0);

	// すべてのショットをみる
	for (int i = 0; i < kEnemyShotMaxNumber; i++)
	{
		// 存在していないショットを探す
		if (!m_pInvertShot[i]->isExist())
		{

			// 色を与える
			shotColor = m_pEnemy[enemyNum]->getColor();

			// 色を送る
			m_pInvertShot[i]->setColor(shotColor);

			// ショットを打つ
			m_pInvertShot[i]->start(VECTOR(pos));

			return true;
		}
	}
	return false;
}

void SceneMain::IsShotEnemy(VECTOR pos, int enemyNum, int enemyLineNum)
{
	// エネミーの列数
	int enemyArray = kEnemyMaxNum / kEnemyMaxLine;

	// 自分の前のエネミー番号
	int forwardEnemyNum = enemyNum + enemyArray;
	
	// エネミーの列が違うとき
	if (kEnemyMaxLine - 1 != enemyLineNum)
	{
		// エネミーが存在するとき
		if (m_pEnemy[forwardEnemyNum]->isExist())
		{
			return;
		}
	}


	
	// ショットを撃つか撃たないかの変数
	int isShot = 0;

	// 乱数を取得
	isShot = GetRand(1);

	if (isShot == 1)
	{
		CreateShotEnemy(pos, enemyNum);
	}

	return;
}





/// <summary>
/// エネミーとショットの当たり判定処理
/// </summary>
/// <param name="num"><ショットの番号/param>
/// <param name="pos"><ショットの位置/param>
/// <param name="isPenetration"><貫通するかどうか/param>
/// <param name="shotSize"><ショットのサイズ/param>
void SceneMain::EnemyToShotCollision(int num, VECTOR pos, bool isPenetration, float shotSize)
{
	// エネミーを見る
	for (auto& enemy : m_pEnemy)
	{
		// プレイヤーのショットが存在するとき
		if (enemy->isExist())
		{
		
			// FIXME

			// 円形の当たり判定(X,Y)
			float dx = pos.x - enemy->getPos().x;
			float dy = pos.y - enemy->getPos().y;
			float dz = pos.z - enemy->getPos().z;


			float dr = (dx * dx) + (dy * dy) + (dz * dz);// A²＝B²＋C²＋D²

			float ar = shotSize + EnemySet::kCircleSize;// 当たり判定の大きさ
			float dl = ar * ar;


		
			// プレイヤーのショットにエネミーが当たったとき(X,Y)
			if (dr < dl)
			{

				// 貫通しないなら消す
				if (!isPenetration)
				{
					// エネミーに当たったプレイヤーの弾を消す
					m_pShot[num]->setExist(false);
				}

				// プレイヤーのショットに当たったエネミーを消す
				enemy->setExist(false);

				// エネミーの存在処理
				EnemyExistProcess();

				// パーティクル処理を呼び出す
				CreateParticle(enemy->getPos(),enemy->getColor(), 
					EnemySet::kParticleValue, EnemySet::kAlphaValue);

				// スコア
				int score = 0;

		

				// エネミーの列番号を割ったあまり
				int enemyDivideLineNum = enemy->getEnemyLineNum() % kEnemyMaxLine;


				// スコアを増やす
				switch (enemy->getEnemyLineNum())
				{
				case 0:
					score += EnemySet::kEnemy1KillScore;
					break;
				case 1:
					score += EnemySet::kEnemy2KillScore;
					break;
				case 2:
					score += EnemySet::kEnemy3KillScore;
					break;
				}



				// 得点処理に移行
				ScoreProcess(score);
							
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
					float dz = shot->getPos().z - bunker->getPos().z;
					float dr = (dx * dx) + (dy * dy) + (dz * dz);// A²＝B²＋C²＋D²

					float ar = Shot::kShotSize + Bunker::kCircleSize;// 当たり判定の大きさ
					float dl = ar * ar;

					// プレイヤーのショットにトーチカが当たったとき(X,Y)
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
					float dz = invertShot->getPos().z - bunker->getPos().z;
					float dr = (dx * dx) + (dy * dy) + (dz * dz);// A²＝B²＋C²＋D²

					float ar = InvertShot::kShotSize + Bunker::kCircleSize;// 当たり判定の大きさ
					float dl = ar * ar;

					// エネミーのショットにトーチカが当たったとき(X,Y)
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


/// <summary>
/// プレイヤーのショットとエネミーのショットの当たり判定
/// </summary>
void SceneMain::ShotToInvertShotCollision(bool isPenetration, float shotSize)
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
					float dz = shot->getPos().z - invertShot->getPos().z;
					float dr = (dx * dx) + (dy * dy) + (dz * dz);// A²＝B²＋C²＋D²

					float ar = shotSize + InvertShot::kShotSize;// 当たり判定の大きさ

					float dl = ar * ar;

					// プレイヤーのショットとエネミーのショットが当たったとき(X,Y)
					if (dr < dl)
					{
						// 貫通しないなら消す
						if (!isPenetration)
						{
							// プレイヤーの弾を消す
							shot->setExist(false);
						}

						// エネミーの弾を消す
						invertShot->setExist(false);


						// パーティクルを発生させる
						CreateParticle3D(shot->getPos(),shot->getColor(),Shot::kParticleValue, Shot::kAlphaValue, shot->getParticleScale(),
						true, invertShot->getColor(),InvertShot::kAlphaValue, InvertShot::kParticleScale);

					}
				}
			}
		}
	}
}