#include "Particle3D.h"


namespace
{
	// サイズ
	constexpr float kGraphicSize = 0.7;
	// 重力	
	constexpr float kGravity = 0.2f;

	// どこまで下に行ったら存在を消すのか
	constexpr float kDeletePosY = -100.0f;
}

Particle3D::Particle3D() :
	m_pos(),
	m_vec(),
	m_modeleHandle(-1),
	m_isExist(false)
{

}

Particle3D::~Particle3D()
{
	// モデルの削除
	MV1DeleteModel(m_modeleHandle);
}




void Particle3D::update()
{
	if (!m_isExist)	return;


	// 移動処理
	Move();

	// パーティクルの移動制限
	MoveLimit();

}

void Particle3D::draw()
{
	if (!m_isExist)	return;


	// モデルの描画
	MV1DrawModel(m_modeleHandle);


	// 球の表示
	//DrawSphere3D(m_pos, kSize, 32, 0xffffff, GetColor(0, 0, 0), true);


}

void Particle3D::start(VECTOR pos, VECTOR color, float modeleScale, float alphaValue)
{
	m_isExist = true;
	m_pos = pos;

	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(modeleScale, modeleScale, modeleScale));

	m_vec.x = static_cast<float>(GetRand(10) - 5);
	m_vec.y = static_cast<float>(-GetRand(6));
	m_vec.z = static_cast<float>(GetRand(6));

	// 色設定
	MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(color.x, color.y, color.z, 1.0f));

	// ３Ｄモデルの不透明度
	MV1SetOpacityRate(m_modeleHandle, alphaValue);
}




void Particle3D::Move()
{
	// 重力を与える
	m_vec.y -= kGravity;

	// ベクトルの加算
	m_pos = VAdd(m_pos, m_vec);

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos);
}

void Particle3D::MoveLimit()
{

	if (m_pos.y < kDeletePosY)
	{
		m_isExist = false;
	}
}
