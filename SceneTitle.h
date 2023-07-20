#pragma once
#include "SceneBase.h"
#include "game.h"
#include <memory>

class BackGround;
class SceneTitle : public SceneBase
{

public:
	SceneTitle();

	virtual ~SceneTitle();


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }

public:



private:

	bool m_isEnd;

	// モデルハンドル
	int m_modelHandle;

	// サイン
	float sinRate;

	// タイトルテキストの位置
	VECTOR m_titlePos;

	// ライトの位置
	VECTOR m_lightPos;

	// クラスポインタ
	std::shared_ptr<BackGround>m_pBackGround;
};