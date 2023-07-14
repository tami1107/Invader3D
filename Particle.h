#pragma once
#include "game.h"

class Particle
{
public:
	Particle();
	virtual ~Particle();

	void update();
	void draw();

	void start(VECTOR pos, VECTOR color);

	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }


	// グラフィックデータ設定
	void setHandle(int handle) {m_handle= handle; }

public:
	// ポリゴン初期設定
	void InitPolygon();

	// ポリゴンのアップデート
	void UpdatePolygon();

	// 移動処理
	void Move();

	// 移動制限
	void MoveLimit();

private:
	// 表示位置
	VECTOR	m_pos;
	// 移動量
	VECTOR	m_vec;

	// 色
	VECTOR	m_color;

	// グラフィックハンドル
	int		m_handle;

	// 存在するか
	bool m_isExist;

	// 立体表示
	VERTEX3D Vertex[6];

	// 回転
	VECTOR Angle;
};
