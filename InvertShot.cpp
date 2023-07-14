#include "InvertShot.h"
#include "Player.h"
#include "Setting.h"

namespace
{
	// ショットスピード
	constexpr float kShotSpeed = 0.5f;

	// ショット開始位置
	constexpr float kShotBegin = 0.0f;

	// ショットモデルのスケール
	constexpr float kModeleScale = 1.5f;

	// ショットを消す位置
	constexpr float kShotDedetePosZ = 0.0f;

	// 半球サイズ
	constexpr float kShotSize = InvertShot::kShotSize;
}


InvertShot::InvertShot() :
	m_isExist(false),
	m_modeleHandle(-1),
	m_pos(),
	m_color()
{
}

InvertShot::~InvertShot()
{
	// グラフィックの削除
	MV1DeleteModel(m_modeleHandle);
}

void InvertShot::start(VECTOR pos)
{
	// 撃ち初めは弾を存在していることにする
	m_isExist = true;

	// m_posにプレイヤーから受け取った位置情報を代入する
	m_pos = pos;

	// ショットを撃ち始めの位置を変更する
	m_pos.z += kShotBegin;

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos);
}

void InvertShot::init()
{
	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(kModeleScale, kModeleScale, kModeleScale));
}

void InvertShot::update()
{
	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	// 弾幕の軌道
	BulletTrajectory();

	// 2Dの当たり判定
	Collision2D();

	// 移動制限
	LimitMove();
}

void InvertShot::draw()
{
	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	// ３Ｄモデルに含まれる０番目のマテリアルのディフューズカラーを変更します
	MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));

	// ショットの描画
	MV1DrawModel(m_modeleHandle);



	// 当たり判定
#if false
	DrawSphere3D(m_pos, kShotSize, 32, GetColor(0, 255, 0), GetColor(0, 0, 0), true);
#endif
}

void InvertShot::BulletTrajectory()
{
	// 弾が手前方向に飛んでいく
	m_pos.z -= kShotSpeed;

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos);
}

void InvertShot::Collision2D()
{
	// 円形の当たり判定
	{
		//当たり判定
		float dx = m_pPlayer->getPos().x - m_pos.x;
		float dy = m_pPlayer->getPos().y - m_pos.y;

		float dr = dx * dx + dy * dy;// A²＝B²＋C²

		float ar = kShotSize + PlayerSet::kCircleSize;// 当たり判定の大きさ
		float dl = ar * ar;

		// プレイヤーのショットにエネミーが当たったとき(X,Y)
		if (dr < dl)
		{

			// 円形の当たり判定(Z,Y)
			dx = m_pPlayer->getPos().z - m_pos.z;
			dr = dx * dx + dy * dy;// A²＝B²＋C²

			dl = ar * ar;

			// プレイヤーとエネミーが接触したとき
			if (dr < dl)
			{
				// ターゲットクラスに弾が当たった情報を送る
				m_pPlayer->getIsHit(true);

				// 弾の存在を消す
				m_isExist = false;
			}
		}
	}
}

void InvertShot::LimitMove()
{
	// 一定の位置まで進んだら弾を消す
	if (m_pos.z <= kShotDedetePosZ)
	{
		// 弾の存在を消す
		m_isExist = false;
	}
}
