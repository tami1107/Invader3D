#include "Enemy.h"
#include "SceneMain.h"

namespace
{
	// 初期位置
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 100.0f;


	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 60;


	// 移動間隔(フレーム数)
	constexpr int kMoveInterval = 120;

	// 移動量X
	constexpr float kMovePosX = 5.0f;
	// 移動量Y
	constexpr float kMovePosY = 10.0f;

	// どこまで移動するのか
	constexpr int kLimitMove = kMovePosX * 6;


	// ゲームオーバー座標
	constexpr float kGameOverPosY = kMovePosY;

	// テストグラフィックの挿入
	const char* const kTestGraphic = "data/enemy.png";
}


Enemy::Enemy() :
	m_isExist(true),
	m_savePosX(0),
	m_savePosY(0),
	m_frameCount(0),
	m_isRightMove(true),
	m_isUnderMove(false),
	m_isHit(false),
	m_shotInterval(0),
	m_decrementTime(0),
	m_enemyGraphic(-1),
	m_pos(),
	m_pSceneMain(nullptr)
{

	// 画像のロード
	m_enemyGraphic = LoadGraph(kTestGraphic);
}

Enemy::~Enemy()
{
	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// グラフィックの削除
	DeleteGraph(m_enemyGraphic);
}

void Enemy::init(int savePosX, int savePosY, int decrementTime)
{
	
	// スピードを代入
	m_decrementTime = decrementTime;

	// 存在している
	m_isExist = true;


	// 位置の保存
	m_savePosX = savePosX;
	m_savePosY = savePosY;

	// 位置の初期化
	m_pos = VGet(kInitPosX + m_savePosX, kInitPosY + savePosY, 0.0f);

	// 移動の間隔
	m_frameCount = kMoveInterval - m_decrementTime;

	// 最初は右に進む
	m_isRightMove = true;

	// 最初は下に進まない
	m_isUnderMove = false;

	// ショットの発生間隔
	m_shotInterval = 0;



}

void Enemy::update()
{

	// エネミーが存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	// 移動処理
	Move();

	// ショット処理
	Shot();

	// 判定の初期化
	m_isHit = false;
}

void Enemy::draw()
{
	// エネミーが存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	// 色変更
	int color = 0x0000ff;

	if (m_isHit)
	{
		color = 0xff0000;
	}

	
	// 球の表示
	DrawSphere3D(m_pos, kCircleSize, 32, color, GetColor(0, 0, 0), true);


	// オブジェクト描画
	DrawBillboard3D(m_pos, 0.5, 0.5, 20.0, 0.0, m_enemyGraphic, true);
}

void Enemy::Move()
{
	// 移動インターバル


	// 移動するまでにかかるフレーム
	int moveFrame = kMoveInterval - m_decrementTime;


	// frameCountが0になったら移動
	m_frameCount--;
	if (m_frameCount <= 0)
	{

	
		// 右に進むかどうかのフラグ処理
		if (m_pos.x >= kLimitMove+ m_savePosX)
		{
			if (m_isRightMove)
			{
				m_isRightMove = false;

				m_isUnderMove = true;
			}
		}
		// 左に進むかどうかのフラグ処理
		if (m_pos.x <= -kLimitMove+ m_savePosX)
		{
			if (!m_isRightMove)
			{
				m_isRightMove = true;

				m_isUnderMove = true;
			}
		}

		// 一段下がるかどうか
		if (m_isUnderMove)
		{
			// 一段下がる
			m_pos.y -= kMovePosY;

			m_isUnderMove = false;


			m_frameCount = moveFrame;


			if (m_pos.y <= kGameOverPosY)
			{
				m_pSceneMain->getIsGameOverFlag(true);
			}


			return;
		}


		// フラグによって移動方向を変える
		if (m_isRightMove)
		{
			m_pos.x += kMovePosX;
		}
		else
		{
			m_pos.x -= kMovePosX;
		}

		m_frameCount = moveFrame;
	}
}

void Enemy::Shot()
{
	// ショットインターバル
	m_shotInterval--;
	if (m_shotInterval <= 0)
	{
		m_shotInterval = 0;
	}

	// ショットを撃つ
	if (m_shotInterval <= 0)
	{
		// ショットを撃つか撃たないかの変数
		int isShot = 0;

		// 乱数を取得
		isShot = GetRand(1);

		if (isShot == 1)
		{
			m_pSceneMain->CreateShotEnemy(m_pos);
		}
		m_shotInterval = kShotInterval;
	}
}


