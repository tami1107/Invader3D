#include "bunker.h"
#include "SceneMain.h"

namespace
{
	// 初期位置
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = 10.0f;


	// 最大HP量
	constexpr int kMaxHp = 5;

	// モデルのスケール
	constexpr float kModeleScale = 5.5f;
}

Bunker::Bunker():
	m_isExist(true),
	m_modeleHandle(-1),
	m_hp(0),
	m_alphaValue(0),
	m_alphaValueDecrement(0),
	m_pos(),
	m_pSceneMain(nullptr)
{
}

Bunker::~Bunker()
{
	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// グラフィックの削除
	MV1DeleteModel(m_modeleHandle);
}

void Bunker::init(int savePosX)
{
	// 存在している
	m_isExist = true;


	// 位置の初期化
	m_pos = VGet(kInitPosX + savePosX, kInitPosY, kInitPosZ);

	// 最大HP量を代入
	m_hp = kMaxHp;

	// アルファブレンドの最大値を代入
	m_alphaValue = 255;

	// アルファブレンドの減少値を代入
	m_alphaValueDecrement = m_alphaValue / kMaxHp;

	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(kModeleScale, kModeleScale, kModeleScale));

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos);
}

void Bunker::update()
{
	if (!m_isExist)return;

	// あたり判定処理
	Collision2D();
}

void Bunker::draw()
{
	if (!m_isExist)return;

	// モデルの描画
	MV1DrawModel(m_modeleHandle);

#if true
	// ダメージを受けるたびに薄くする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaValue);
	// 球の表示
	DrawSphere3D(m_pos, kCircleSize, 32, 0x0000ff, GetColor(0, 0, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#endif

}

void Bunker::DamegeProcess(int damages)
{
	// HPからダメージを引く
	m_hp -= damages;

	// アルファブレンドを引く
	m_alphaValue -= m_alphaValueDecrement;

	// HPが0の場合、存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}

void Bunker::Collision2D()
{
	// トーチカとエネミーショットのあたり判定
	m_pSceneMain->BunkerToInvertShotCollision();
	// トーチカとプレイヤーショットのあたり判定
	m_pSceneMain->BunkerToShotCollision();
}
