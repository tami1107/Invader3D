#pragma once
#include "game.h"

class SceneMain;
class Player
{
public:
	// 半球サイズ
	static constexpr float kCircleSize = 2.0f;

	
public:
	Player();
	virtual~Player();

	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init();
	void update();
	void draw();

	// 位置情報を返す
	VECTOR getPos() const { return m_pos; }

	// 当たり判定を取得
	void getIsHit(bool isHit) { m_isHit = isHit; }

public:
	// 移動処理
	void Move();

	// 移動制限
	void LimitMove();

	// ショット処理
	void Shot();

	// ダメージ処理
	void CollisionProcess();

	// 位置初期化
	void ResetPos();

private:

	// 当たったかどうか
	bool m_isHit;

	// ショットの発生間隔
	int m_shotInterval;



	// 表示位置
	VECTOR m_pos;

	// 方向
	VECTOR m_dir;



	// クラスポインタ
	SceneMain* m_pSceneMain;
};

