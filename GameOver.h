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
	// �t�H���g�n���h��
	int m_fontHandle;

	// �e�L�X�g�̃T�C��
	float m_textSin;

	// �e�L�X�g��Y���W
	int m_posY;


	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

