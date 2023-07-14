#pragma once
#include "game.h"


class SceneMain;
class GameOver
{
public:
	GameOver();
	virtual~GameOver();

	// クラスポインタの取得
	void setSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init();

	void update();

	void draw();

private:
	
	// グラフィックの挿入
	int m_graphic;


	// クラスポインタ
	SceneMain* m_pSceneMain;
};

