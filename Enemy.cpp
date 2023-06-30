#include "Enemy.h"
#include "SceneMain.h"

namespace
{
	// 初期位置
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = 100.0f;



	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 60;


	// 移動間隔(フレーム数)
	//constexpr int kMoveInterval = 120;

	// 移動間隔(フレーム数)
	constexpr int kMoveInterval = 60;

	// 移動量X
	constexpr float kMovePosX = 5.0f;
	// 移動量Y
	constexpr float kMovePosZ = 10.0f;

	// どこまで移動するのか
	constexpr int kLimitMove = kMovePosX * 6;


	// ゲームオーバー座標
	constexpr float kGameOverPosY = kMovePosZ;

	// ダメージを受けた時のアニメーション最大フレーム
	constexpr int kDamageAnimationMaxFrame = 30;

	// グラフィックサイズ
	constexpr float kGraphicSize = 10.0;

}


Enemy::Enemy() :
	m_isExist(true),
	m_savePosX(0),
	m_savePosZ(0),
	m_frameCount(0),
	m_isRightMove(true),
	m_isUnderMove(false),
	m_isHit(false),
	m_shotInterval(0),
	m_decrementTime(0),
	m_animationNum(0),
	m_damageAnimationFrame(0),
	m_pos(),
	m_pSceneMain(nullptr)
{
	for (auto handle : m_handle)
	{
		handle = -1;
	}
}

Enemy::~Enemy()
{
	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// グラフィックの削除
	for (auto handle : m_handle)
	{
		DeleteGraph(handle);
	}
	
}

void Enemy::init(int savePosX, int savePosZ, int decrementTime)
{
	
	// スピードを代入
	m_decrementTime = decrementTime;

	// 存在している
	m_isExist = true;


	// 位置の保存
	m_savePosX = savePosX;
	m_savePosZ = savePosZ;



	// 位置の初期化
	m_pos = VGet(kInitPosX + m_savePosX, kInitPosY, kInitPosZ + savePosZ);

	// 移動の間隔
	m_frameCount = kMoveInterval - m_decrementTime;

	// 最初は右に進む
	m_isRightMove = true;

	// 最初は下に進まない
	m_isUnderMove = false;

	// ショットの発生間隔
	m_shotInterval = 0;

	// アニメーションナンバーの初期化
	m_animationNum = 0;

	// ダメージアニメーションフレームの初期化
	m_damageAnimationFrame = kDamageAnimationMaxFrame;


	// 最初はダメージを受けていない
	m_isHit = false;
}

void Enemy::update()
{
		

	// エネミーが存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	// ダメージを受けていたら処理を行う
	if (m_isHit)
	{
		// ダメージを受けたときのアニメーション
		DamageAnimation();
		return;
	}


	// 移動処理
	Move();

	// ショット処理
	Shot();


}

void Enemy::draw()
{
	// エネミーが存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	// ダメージを受けた場合、ここで処理を終了する
	if (m_isHit)return;
	

	
	// 球の表示
	//DrawSphere3D(m_pos, kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);


	// 画像描画
	DrawBillboard3D(m_pos, 0.5, 0.5, kGraphicSize, 0.0, m_handle[m_animationNum], true);
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
		// アニメーションを動かす
		m_animationNum++;
		// 移動アニメーションは0・1しか使わない為、2以上になったとき0にする
		if (m_animationNum == 2)
		{
			m_animationNum = 0;
		}
		




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

		// 一段手前にいくかどうか
		if (m_isUnderMove)
		{
			// 一段手前に行く
			m_pos.z -= kMovePosZ;

			m_isUnderMove = false;


			m_frameCount = moveFrame;

			// ゲームオーバーするかどうか
			if (m_pos.z <= kGameOverPosY)
			{
				//m_pSceneMain->getIsGameOverFlag(true);
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

		// 移動フレームを戻す
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

void Enemy::DamageAnimation()
{
	// ダメージアニメーションフレームをへ明日
	m_damageAnimationFrame--;
	// 一定フレーム経つとエネミーの存在を消す
	if (m_damageAnimationFrame <= 0)
	{
		m_isExist = false;
	}


	// ダメージアニメーション
	m_animationNum = 2;


}


