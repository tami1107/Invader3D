#pragma once
#include "game.h"


class Particle3D
{
public:
	Particle3D();
	virtual ~Particle3D();


	void update();
	void draw();

	void start(VECTOR pos, VECTOR color, float modeleScale, float alphaValue);

	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }


	// グラフィックデータ設定
	void setHandle(int handle) { m_modeleHandle = handle; }

public:

	// 移動処理
	void Move();

	// 移動制限
	void MoveLimit();

private:
	// 表示位置
	VECTOR	m_pos;
	// 移動量
	VECTOR	m_vec;


	// グラフィックハンドル
	int		m_modeleHandle;

	// 存在するか
	bool m_isExist;
};
