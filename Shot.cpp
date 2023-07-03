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

	// ショットモデルのスケール
	constexpr float kModeleScale = 1.5f;
}


Shot::Shot() :
	m_isExist(false),
	m_modeleHandle(-1),
	m_pos(),
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


void Shot::start(VECTOR pos)
{
	// 撃ち初めは弾を存在していることにする
	m_isExist = true;

	// m_posにプレイヤーから受け取った位置情報を代入する
	m_pos = pos;

	// ショットを撃ち始めの位置を変更する
	m_pos.z += kShotBegin;
}

void Shot::init()
{
	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(kModeleScale, kModeleScale, kModeleScale));
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

	// ショットの描画
	MV1DrawModel(m_modeleHandle);

	// あたり判定の表示
#if false
	// 弾の表示
	DrawSphere3D(m_pos, kShotSize, 32, GetColor(255, 0, 0), GetColor(0, 0, 0), true);
#endif
}

void Shot::BulletTrajectory()
{
	// 弾が上方向に飛んでいく
	m_pos.z += kShotSpeed;

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos);
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
