#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"


SceneTitle::SceneTitle() :
	m_isEnd(false)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::init()
{


	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	
	
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// Main‚ÉØ‚è‘Ö‚¦
		return(new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{
	DrawString(0, 0, "ƒ^ƒCƒgƒ‹‰æ–Ê", GetColor(255, 255, 255));
}