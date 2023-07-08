#include "Player.h"
#include "Pad.h"
#include "SceneMain.h"

namespace
{
	// プレイヤーのグラフィックファイル名
	const char* const kPlayerGraphicFileName = "data/modele/player.mv1";

	// モデルのスケール
	constexpr float kModeleScale = 2.5f;

	// 初期位置
	constexpr float kInitPosY = 3.0f;

	// 移動スピード
	constexpr float kMoveSpeed = 0.5f;

	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 8;

	// プレイヤーの移動範囲
	constexpr int kMoveLimit = 50;

}


Player::Player():
	m_modeleHandle(-1),
	m_isHit(false),
	m_shotInterval(0),
	m_pos(),
	m_dir(),
	m_pSceneMain(nullptr)
{
}

Player::~Player()
{
	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// モデルの削除
	MV1DeleteModel(m_modeleHandle);
}

void Player::init()
{
	// モデルを読み込む
	m_modeleHandle = MV1LoadModel(kPlayerGraphicFileName);

	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(kModeleScale, kModeleScale, kModeleScale));

	// 位置の初期化
	m_pos = VGet(0.0f, kInitPosY, 0.0f);

	// 方向の初期化
	m_dir = VGet(0.0f, 0.0f, 0.0f);


	// ショットの発生間隔
	m_shotInterval = 0;
}

void Player::update()
{
	// 移動処理
	Move();

	// 移動制限
	LimitMove();

	// ショット処理
	Shot();

	// ダメージ処理
	CollisionProcess();

}

void Player::draw()
{
	// 色変更
	int color = 0xffffff;

	if (m_isHit)
	{
		color = 0xff0000;
	}


	// モデルの描画
	MV1DrawModel(m_modeleHandle);


	DrawFormatString(0, 1 * 15, 0xffffff, "pos.x:%f pos.y:%f pos.z:%f", m_pos.x, m_pos.y, m_pos.z);

	// 当たり判定の表示
#if true
	DrawSphere3D(m_pos, kCircleSize, 32, color, GetColor(0, 0, 0), true);
#endif
}

void Player::Move()
{

	// 方向の初期化
	m_dir = VGet(0, 0, 0);

	// 上に進む
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_dir = VAdd(m_dir, VGet(0, -1, 0));
	}
	// 下に進む
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_dir = VAdd(m_dir, VGet(0, 1, 0));
	}
	// 左に進む
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_dir = VAdd(m_dir, VGet(-1, 0, 0));
	}
	// 右に進む
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_dir = VAdd(m_dir, VGet(1, 0, 0));
	}

#if true

	// 手前に進む
	if (Pad::isPress(PAD_INPUT_4))
	{
		m_dir = VAdd(m_dir, VGet(0, 0, -1));
	}
	// 奥に進む
	if (Pad::isPress(PAD_INPUT_5))
	{
		m_dir = VAdd(m_dir, VGet(0, 0, 1));
	}
#endif


	// 斜めになったとき((1,1,0)等)にいったん長さ１に戻す(正規化)
	if (VSquareSize(m_dir) > 0)// 長さが0のベクトルは正規化できない(1にできないので)
	{
		// ↑VSizeは重いのでVSquareSizeを使う（0を何乗しても0なので）
		m_dir = VNorm(m_dir);
	}

	// ベクトルの掛け算
	VECTOR velocity = VScale(m_dir, kMoveSpeed);
	// ベクトルの足し算
	m_pos = VAdd(m_pos, velocity);

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos);
}

void Player::LimitMove()
{
	//// 左方向の移動制限
	//if (m_pos.x < -kMoveLimit)
	//{
	//	m_pos.x = -kMoveLimit;
	//}
	//// 右方向の移動制限
	//if (m_pos.x > kMoveLimit)
	//{
	//	m_pos.x = kMoveLimit;
	//}
}

void Player::Shot()
{
	// ショットインターバル
	m_shotInterval--;
	if (m_shotInterval <= 0)
	{
		m_shotInterval = 0;
	}

	// ショットを撃つ
	if (Pad::isPress(PAD_INPUT_10))
	{
		if (m_shotInterval <= 0)
		{
			m_pSceneMain->CreateShotPlayer(m_pos);
			m_shotInterval = kShotInterval;
		}
	}
}

void Player::CollisionProcess()
{
	if (m_isHit)
	{
		// ダメージ処理を行う
		m_pSceneMain->PlayerDamageProcess();
	}

	// 判定の初期化
	m_isHit = false;
}

void Player::ResetPos()
{
	// 位置の初期化
	m_pos = VGet(0.0f, kInitPosY, 0.0f);
}
