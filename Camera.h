#pragma once
#include "game.h"
#include <memory>


class Player;
class Camera
{
public:
	Camera();
	virtual~Camera();

	// クラスポインタの取得
	void getPlayerPointer(std::shared_ptr<Player>player) { m_pPlayer = player; }


	void init();
	void update();
	void draw();


private:
	// 表示位置
	VECTOR m_pos;


	// クラスポインタ
	std::shared_ptr<Player>m_pPlayer;

};

