#include "Shot.h"
#include "Enemy.h"
#include "SceneMain.h"

namespace
{
	// ショットスピード
	constexpr float kShotSpeed = 1.5f;

	// ショット開始位置
	constexpr float kShotBegin = 0.0f;

	// ショットを消す位置
	constexpr float kShotDedetePosZ = 100.0f;
}


Shot::Shot() :
	m_isExist(false),
	m_handle(-1),
	m_pos()
{
}

Shot::~Shot()
{
	m_SceneMain = nullptr;
	delete m_SceneMain;

	// グラフィックの削除
	DeleteGraph(m_handle);
}

void Shot::start(VECTOR pos)
{
	// 撃ち初めは弾を存在していることにする
	m_isExist = true;

	// m_posにプレイヤーから受け取った位置情報を代入する
	m_pos = pos;

	// ショットを撃ち始めの位置を変更する
	m_pos.z += kShotBegin;
}

void Shot::update()
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

void Shot::draw()
{
	// 弾が存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;

	// 弾の表示
	DrawSphere3D(m_pos, kShotSize, 32, GetColor(255, 0, 0), GetColor(0, 0, 0), true);

	// 画像描画
	//DrawBillboard3D(m_pos, 0.5, 0.5, 1.0, 0.0, m_handle, true);
}

void Shot::BulletTrajectory()
{
	// 弾が上方向に飛んでいく
	m_pos.z += kShotSpeed;
}

void Shot::Collision2D()
{
	m_SceneMain->EnemyToShotCollision();
}

void Shot::LimitMove()
{
	// 一定の位置まで進んだら弾を消す
	if (m_pos.z >= kShotDedetePosZ)
	{
		// 弾の存在を消す
		m_isExist = false;
	}
}
