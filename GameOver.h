#pragma once
#include "game.h"


class SceneMain;
class GameOver
{
public:
	GameOver();
	virtual~GameOver();

	// �N���X�|�C���^�̎擾
	void setSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init();

	void update();

	void draw();

private:
	
	// �O���t�B�b�N�̑}��
	int m_graphic;


	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

