#include "Player.h"
#include "Pad.h"
#include "SceneMain.h"
#include "MainUI.h"

namespace
{
	// 残像のずらす値
	constexpr int kAfterimageDisplace = 1;

	// 残像の透明度
	constexpr float kAfterimageAlpha= 0.2;
}


Player::Player():
	m_modeleHandle(-1),
	m_isHit(false),
	m_shotInterval(0),
	m_isPowerUp(false),
	m_powerUpFrame(0),
	m_powerUpNum(0),
	m_moveSpeed(0.0),
	m_isChangeStatus(false),
	m_pos(),
	m_dir(),
	m_color(),
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

	// 色を入れる
	m_color = VGet(PlayerSet::kCollarR, PlayerSet::kCollarG, PlayerSet::kCollarB);

	// 色設定
	MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));

	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(PlayerSet::kModeleScale, PlayerSet::kModeleScale, PlayerSet::kModeleScale));

	// ３Ｄモデルの不透明度
	MV1SetOpacityRate(m_modeleHandle, PlayerSet::kAlphaValue);

	// 位置の初期化
	m_pos[0] = VGet(PlayerSet::kInitPosX, PlayerSet::kInitPosY, PlayerSet::kInitPosZ);

	// 方向の初期化
	m_dir = VGet(0.0f, 0.0f, 0.0f);

	// ショットの発生間隔
	m_shotInterval = 0;

	// ショットのスピードアップフレームの最大値を代入
	m_powerUpFrame = kPowerUpMaxFrame;

	// 移動スピードを代入
	m_moveSpeed = PlayerSet::kMoveSpeed;
}

void Player::update()
{
	// 移動処理
	Move();

	// 移動制限
	LimitMove();

	// パワーアップ処理
	PowerUpProcess();

	// ショット処理
	Shot();

	// ダメージ処理
	CollisionProcess();

}

void Player::draw()
{
	
	// モデルの描画
	MV1DrawModel(m_modeleHandle);


	Afterimage();


	//// プレイヤーの座標表示
	//DrawFormatString(0, 15 * 17, 0xff0000, "pos.x:%f pos.y:%f pos.z:%f", m_pos[0].x, m_pos[0].y, m_pos[0].z);


	// デバッグ
#if false

	// 当たり判定表示
	DrawSphere3D(m_pos, PlayerSet::kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);

	// プレイヤーの座標表示
	DrawFormatString(0, 1 * 15, 0xffffff, "pos.x:%f pos.y:%f pos.z:%f", m_pos.x, m_pos.y, m_pos.z);

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
	VECTOR velocity = VScale(m_dir, m_moveSpeed);
	// ベクトルの足し算
	m_pos[0] = VAdd(m_pos[0], velocity);

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos[0]);
}

void Player::LimitMove()
{
	// 左方向の移動制限
	if (m_pos[0].x <= -PlayerSet::kMoveLimit)
	{
		m_pos[0].x = -PlayerSet::kMoveLimit;
	}
	// 右方向の移動制限
	if (m_pos[0].x >= PlayerSet::kMoveLimit)
	{
		m_pos[0].x = PlayerSet::kMoveLimit;
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
		{/*
			m_pSceneMain->CreateShotPlayer(m_pos, m_isPowerUp, m_powerUpNum);
			m_shotInterval = PlayerSet::kShotInterval;*/
		}

		m_pSceneMain->CreateShotPlayer(m_pos[0], m_isPowerUp, m_powerUpNum);
		m_shotInterval = PlayerSet::kShotInterval;
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

void Player::PowerUpProcess()
{

	if (!m_isPowerUp)return;

	// ステータスを変えてなければ変える
	if (!m_isChangeStatus)
	{

		if (m_powerUpNum == 0)// ショットスピードとショットサイズ
		{
			// 色を入れる
			m_color = VGet(kQuickCollarR, kQuickCollarG, kQuickCollarB);
		}
		else if (m_powerUpNum == 1)// 連射
		{
			// 色を入れる
			m_color = VGet(kRapidCollarR, kRapidCollarG, kRapidCollarB);
		}
		else if (m_powerUpNum == 2)// 貫通、移動スピードUP
		{
			// 色を入れる
			m_color = VGet(kPenetrationCollarR, kPenetrationCollarG, kPenetrationCollarB);
			
			// 移動スピードを代入
			m_moveSpeed = PlayerSet::kMoveSpeed2;
		}

		// 色設定
		MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));


		m_isChangeStatus = true;

	}


	// フレームを減らす
	m_powerUpFrame--;
	

	// MainUIのタイマーを動かす
	m_pMainUI->TimerProcess(m_powerUpFrame);


	// m_shotSpeedUpFrameが0になった時、
	if (m_powerUpFrame < 0)
	{
		// 色を入れる
		m_color = VGet(PlayerSet::kCollarR, PlayerSet::kCollarG, PlayerSet::kCollarB);

		// 色設定
		MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));

		// パワーアップフレームの最大値を代入
		m_powerUpFrame = kPowerUpMaxFrame;

		// パワーアップ番号に意味のない数字を入れる
		m_powerUpNum = kPowerUpMaxNum;

		m_isPowerUp = false;

		m_isChangeStatus = false;

		// 移動スピードを代入
		m_moveSpeed = PlayerSet::kMoveSpeed;
	}
}

void Player::Reset()
{
	// 位置の初期化
	m_pos[0] = VGet(0.0f, PlayerSet::kInitPosY, 0.0f);

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos[0]);

	// パワーアップフレームの最大値を代入
	m_powerUpFrame = kPowerUpMaxFrame;

	// パワーアップ番号に意味のない数字を入れる
	m_powerUpNum = kPowerUpMaxNum;

	m_isPowerUp = false;

	// 移動スピードを代入
	m_moveSpeed = PlayerSet::kMoveSpeed;
}

void Player::Afterimage()
{

	if (!m_isPowerUp)return;

	// 残像データを一つづつずらす
	for (int i = kAfterimageNum - 1; i > 0; i--)
	{
		m_pos[i] = m_pos[i - 1];

	}
	// ３Ｄモデルの不透明度	
	MV1SetOpacityRate(m_modeleHandle, kAfterimageAlpha);

	for (int i = kAfterimageNum - 1; i >= 0; i -= kAfterimageDisplace)
	{
		// 位置情報をモデルに入れる
		MV1SetPosition(m_modeleHandle, m_pos[i]);
		
		// モデルの描画
		MV1DrawModel(m_modeleHandle);

		
	}
	// ３Ｄモデルの不透明度
	MV1SetOpacityRate(m_modeleHandle, PlayerSet::kAlphaValue);

}
