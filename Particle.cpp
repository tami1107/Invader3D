#include "Particle.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	// サイズ
	constexpr float kGraphicSize = 1.4;
	// 重力	
	constexpr float kGravity = 0.2f;
}

Particle::Particle() :
	m_pos(),
	m_vec(),
	m_color(0),
	m_handle(-1),
	m_isExist(false)
{	
}

Particle::~Particle()
{
	// グラフィックの削除
	DeleteGraph(m_handle);
}

void Particle::init()
{
	
}

void Particle::end()
{

}

void Particle::update()
{
	if (!m_isExist)	return;

	 
	// ベクトルの加算
	m_pos = VAdd(m_pos, m_vec);

	m_vec.y -= kGravity;

	if (m_pos.y < -100)
	{
		m_isExist = false;
	}


}

void Particle::draw()
{
	if (!m_isExist)	return;
	//DrawBoxAA(m_pos.x, m_pos.y, m_pos.x + kSize, m_pos.y + kSize, m_color, true);

		// 球の表示
	//DrawSphere3D(m_pos, kSize, 32, 0xffffff, GetColor(0, 0, 0), true);

	// 画像描画
	DrawBillboard3D(m_pos, 0.5, 0.5, kGraphicSize, 0.0, m_handle, true);

}

void Particle::start(VECTOR pos, int color)
{
	m_isExist = true;
	m_pos = pos;

	//m_colSize.x = kSize;
	//m_colSize.y = kSize;

	m_vec.x = static_cast<float>(GetRand(10) - 5);
	m_vec.y = static_cast<float>(-GetRand(6));
	m_vec.z = static_cast<float>(GetRand(6));

	m_color = color;
}
