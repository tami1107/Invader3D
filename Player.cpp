#include "Player.h"
#include "Pad.h"
#include "SceneMain.h"


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
	m_modeleHandle = MV1LoadModel(PlayerSet::kPlayerGraphicFileName);

	// 色設定
	MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(PlayerSet::kCollarR, PlayerSet::kCollarG, PlayerSet::kCollarB, 1.0f));

	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(PlayerSet::kModeleScale, PlayerSet::kModeleScale, PlayerSet::kModeleScale));

	// 位置の初期化
	m_pos = VGet(PlayerSet::kInitPosX, PlayerSet::kInitPosY, PlayerSet::kInitPosZ);

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
	// モデルの描画
	MV1DrawModel(m_modeleHandle);

	DrawFormatString(0, 1 * 15, 0xffffff, "pos.x:%f pos.y:%f pos.z:%f", m_pos.x, m_pos.y, m_pos.z);

	// 当たり判定の表示
#if true
	DrawSphere3D(m_pos, PlayerSet::kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);
#endif
}

void Player::Move()
{

	// 方向の初期化
	m_dir = VGet(0, 0, 0);

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

#if false
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
	VECTOR velocity = VScale(m_dir, PlayerSet::kMoveSpeed);
	// ベクトルの足し算
	m_pos = VAdd(m_pos, velocity);

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos);
}

void Player::LimitMove()
{
	// 左方向の移動制限
	if (m_pos.x <= -PlayerSet::kMoveLimit)
	{
		m_pos.x = -PlayerSet::kMoveLimit;
	}
	// 右方向の移動制限
	if (m_pos.x >= PlayerSet::kMoveLimit)
	{
		m_pos.x = PlayerSet::kMoveLimit;
	}
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
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		if (m_shotInterval <= 0)
		{
			m_pSceneMain->CreateShotPlayer(m_pos);
			m_shotInterval = PlayerSet::kShotInterval;
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
	m_pos = VGet(0.0f, PlayerSet::kInitPosY, 0.0f);
}
