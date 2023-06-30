#pragma once
#include "game.h"

class Particle
{
public:
	Particle();
	virtual ~Particle();

	void init();
	void end();

	void update();
	void draw();

	void start(VECTOR pos, int color);

	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }


	// グラフィックデータ設定
	void setHandle(int handle) {m_handle= handle; }

private:
	// 表示位置
	VECTOR	m_pos;
	// 移動量
	VECTOR	m_vec;

	// 色
	int		m_color;

	// グラフィックハンドル
	int		m_handle;

	// 存在するか
	bool m_isExist;
};
