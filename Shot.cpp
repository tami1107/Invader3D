#include "Shot.h"
#include "Enemy.h"
#include "SceneMain.h"
#include "BonusEnemy.h"
#include "Player.h"

namespace
{
	// ショットスピード
	constexpr float kShotSpeed = 1.5f;

	constexpr float kShotSpeed2 = 5.0f;


	// ショット開始位置
	constexpr float kShotBegin = 0.0f;

	// ショットを消す位置
	constexpr float kShotDedetePosZ = 100.0f;

	// ショットモデルのスケール
	constexpr float kModeleScale = 1.5f;

	// ショットモデルのスケール
	constexpr float kModeleScale2 = 4.0f;

	// 残像の透明度
	constexpr float kAfterimageAlpha = 0.4;

	// 残像のずらす値
	constexpr int kAfterimageDisplace = 1;
}


Shot::Shot() :
	m_isExist(false),
	m_modeleHandle(-1),
	m_shotSpeed(0.0f),
	m_isPenetration(false),
	m_shotSize(0.0f),
	m_isPowerUp(false),
	m_shotNum(),
	m_particleScale(0.0f),
	m_pos(),
	m_color(),
	m_SceneMain(nullptr)
{
}

Shot::~Shot()
{
	m_SceneMain = nullptr;
	delete m_SceneMain;

	// グラフィックの削除
	DeleteGraph(m_modeleHandle);
}


void Shot::start(VECTOR pos, bool isPowerUp, int powerUpNum)
{
	// 撃ち初めは弾を存在していることにする
	m_isExist = true;

	// m_posにプレイヤーから受け取った位置情報を代入する
	m_pos[0] = pos;

	// ショットを撃ち始めの位置を変更する
	m_pos[0].z += kShotBegin;

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos[0]);

	// ショットスピード
	m_shotSpeed = kShotSpeed;

	// 貫通しない
	m_isPenetration = false;

	// ショットの大きさ
	m_shotSize = kShotSize;

	// パワーアップしているかどうかを代入する
	m_isPowerUp = isPowerUp;

	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(kModeleScale, kModeleScale, kModeleScale));

	// パーティクルの大きさ
	m_particleScale = kParticleScale;

	if (isPowerUp)
	{
		// ショットのスピード
		switch (powerUpNum)
		{
		case 0:
			
			// ショットスピード
			m_shotSpeed = kShotSpeed2;

			// ショットの大きさ
			m_shotSize = kShotBigSize;

			// パーティクルの大きさ
			m_particleScale = kParticleScale2;

			// ３Ｄモデルのスケール変更
			MV1SetScale(m_modeleHandle, VGet(kModeleScale2, kModeleScale2, kModeleScale2));


			break;

		case 1:
			
			break;
		case 2:
			
			// 貫通する
			m_isPenetration = true;

			break;
		}
	}

	// プレイヤーの色を入れる
	m_color = m_pPlayer->getColor();

	// 色設定
	MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));

}

void Shot::init()
{

}

void Shot::update()
{
	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;
	
	// 弾幕の軌道
	BulletTrajectory();

	// 当たり判定
	Collision();

	// 移動制限
	LimitMove();
}

void Shot::draw()
{
	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;


	// ショットの描画
	MV1DrawModel(m_modeleHandle);

	Afterimage();

	// あたり判定の表示
#if false
	// 弾の表示
	DrawSphere3D(m_pos, kShotSize, 32, GetColor(255, 0, 0), GetColor(0, 0, 0), true);
#endif
}

void Shot::BulletTrajectory()
{
	// 弾が上方向に飛んでいく
	m_pos[0].z += m_shotSpeed;

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos[0]);
}

void Shot::Collision()
{
	// エネミーとショットの当たり判定　(貫通するかしないかを送る,ショットサイズを送る)
	m_SceneMain->EnemyToShotCollision(m_shotNum, m_pos[0], m_isPenetration, m_shotSize);



	// プレイヤーショットとエネミーショットの当たり判定　(貫通するかしないかを送る,ショットサイズを送る)
	m_SceneMain->ShotToInvertShotCollision(m_isPenetration, m_shotSize);


	// ボーナスエネミーとショットの当たり判定
	{
		// 円形の当たり判定(X,Y,Z)
		float dx = m_pos[0].x - m_pBonusEnemy->getPos().x;
		float dy = m_pos[0].y - m_pBonusEnemy->getPos().y;
		float dz = m_pos[0].z - m_pBonusEnemy->getPos().z;


		float dr = (dx * dx) + (dy * dy) + (dz * dz);// A²＝B²＋C²＋D²

		float ar = kShotSize + BonusEnemy::kCircleSize;// 当たり判定の大きさ
		float dl = ar * ar;

		if (dr < dl)
		{
			// ボーナスエネミーの設定を行う
			m_pBonusEnemy->Setting();

			// パーティクルを出す
			m_SceneMain->CreateParticle(m_pos[0], m_pBonusEnemy->getColor(), BonusEnemy::kParticleValue, BonusEnemy::kAlphaValue);

			// スコアを送る
			m_SceneMain->ScoreProcess(BonusEnemy::kEnemyKillScore);


			// パワーアップする項目をランダムに決める
			int powerRand = GetRand(Player::kPowerUpMaxNum - 1);


			// プレイヤーのショットのパワーアップフラグをtrueにし、パワーアップする項目を送る
			m_pPlayer->getPowerUp(true, powerRand);

			// 貫通しないなら消す
			if (!m_isPenetration)
			{
				// 弾の存在を消す
				m_isExist = false;
			}
		}
	}
}

void Shot::LimitMove()
{
	// 一定の位置まで進んだら弾を消す
	if (m_pos[0].z >= kShotDedetePosZ)
	{
		// 弾の存在を消す
		m_isExist = false;
	}
}

void Shot::Afterimage()
{
	// もしパワーアップしていないならここで処理を終了する
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
