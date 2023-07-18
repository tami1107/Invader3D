#include "Particle.h"
#include "game.h"

namespace
{
	// サイズ
	constexpr float kGraphicSize = 0.7;
	// 重力	
	constexpr float kGravity = 0.2f;

	// どこまで下に行ったら存在を消すのか
	constexpr float kDeletePosY = -100.0f;
}

Particle::Particle() :
	m_pos(),
	m_vec(),
	m_color(),
	m_handle(-1),
	m_isExist(false)
{	
	// ポリゴンの初期設定
	InitPolygon();
}

Particle::~Particle()
{
	// グラフィックの削除
	DeleteGraph(m_handle);
}


void Particle::update()
{
	if (!m_isExist)	return;

	 
	// ポリゴンのアップデート処理
	UpdatePolygon();

	// 移動処理
	Move();

	// パーティクルの移動制限
	MoveLimit();

}

void Particle::draw()
{
	if (!m_isExist)	return;
	

	MATERIALPARAM Material;

	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(m_color.x, m_color.y, m_color.z, 0.0f);
	Material.Power = 20.0f;

	SetMaterialParam(Material);

	// ２ポリゴンの描画
	DrawPolygon3D(Vertex, 2, m_handle, true);


	// 球の表示
	//DrawSphere3D(m_pos, kSize, 32, 0xffffff, GetColor(0, 0, 0), true);

	// 画像描画
	//DrawBillboard3D(m_pos, 0.5, 0.5, kGraphicSize, 0.0, m_handle, true);

}

void Particle::start(VECTOR pos, VECTOR color)
{
	m_isExist = true;
	m_pos = pos;

	
	m_vec.x = static_cast<float>(GetRand(6) - 3);
	m_vec.y = static_cast<float>(GetRand(3)-1);
	m_vec.z = static_cast<float>(GetRand(6));

	m_color = color;
}

void Particle::InitPolygon()
{

	// ２ポリゴン分の頂点の座標と法線以外のデータをセット
	Vertex[0].dif = GetColorU8(0, 0, 0, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].dif = GetColorU8(0, 0, 0, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].dif = GetColorU8(0, 0, 0, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].dif = GetColorU8(0, 0, 0, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4] = Vertex[2];
	Vertex[5] = Vertex[1];

	// 回転パラメータを初期化
	Angle.x = 0.0f;
	Angle.y = 0.0f;
	Angle.z = 0.0f;

}

void Particle::UpdatePolygon()
{
	MATRIX TransformMatrix;

	// 回転( x, y, z軸回転の順 )＋座標移動行列の作成
	TransformMatrix = MGetRotX(Angle.x);
	TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
	TransformMatrix = MMult(TransformMatrix, MGetRotZ(Angle.z));
	TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(0.0f, 0.0f, 0.0f)));

	// 行列を使ってワールド座標を算出
	Vertex[0].pos = VTransform(VGet(m_pos.x + -kGraphicSize, m_pos.y + kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[1].pos = VTransform(VGet(m_pos.x + kGraphicSize, m_pos.y + kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[2].pos = VTransform(VGet(m_pos.x + -kGraphicSize, m_pos.y + -kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[3].pos = VTransform(VGet(m_pos.x + kGraphicSize, m_pos.y + -kGraphicSize, m_pos.z), TransformMatrix);

	Vertex[4].pos = Vertex[2].pos;
	Vertex[5].pos = Vertex[1].pos;

	// 行列を使って法線を算出
	Vertex[2].norm = Vertex[0].norm;
	Vertex[3].norm = Vertex[0].norm;
	Vertex[4].norm = Vertex[0].norm;
	Vertex[5].norm = Vertex[0].norm;

}

void Particle::Move()
{
	// 重力を与える
	m_vec.y -= kGravity;

	// ベクトルの加算
	m_pos = VAdd(m_pos, m_vec);

}

void Particle::MoveLimit()
{

	if (m_pos.y < kDeletePosY)
	{
		m_isExist = false;
	}
}
