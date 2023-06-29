#pragma once
#include "SceneBase.h"
#include <memory>
#include "game.h"


class Player;
class Camera;
class Shot;
class InvertShot;
class Enemy;
class SceneMain : public SceneBase
{
public:
	// オブジェクトの最大数
	static constexpr int kObjectMaxNumber = 10;
public:
	SceneMain();

	virtual ~SceneMain();


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

public:
	// プレイヤーがショットを撃つ
	bool createShotPlayer(VECTOR pos);

	// エネミーがショットを撃つ
	bool createShotEnemy(VECTOR pos);


private:

	// クラスポインタ
	std::shared_ptr<Player>m_pPlayer;
	std::shared_ptr<Camera>m_pCamera;
	std::shared_ptr<Shot>m_pShot[kObjectMaxNumber];
	std::shared_ptr<InvertShot>m_pInvertShot[kObjectMaxNumber];
	std::shared_ptr<Enemy>m_pEnemy;


};