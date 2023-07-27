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
	// フォントハンドル
	int m_fontHandle;

	// テキストのサイン
	float m_textSin;

	// テキストのY座標
	int m_posY;


	// クラスポインタ
	SceneMain* m_pSceneMain;
};

