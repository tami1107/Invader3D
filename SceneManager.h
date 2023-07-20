#pragma once

#include "SceneBase.h"
#include <memory>


class BackGround;
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void init();
	void end();

	void update();
	void draw();


private:
	SceneBase* m_pScene;
};