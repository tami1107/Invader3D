#pragma once
#include "game.h"
#include <memory>
#include "SceneMain.h"


class SceneMain;
class Shot
{
public:

	// ショットのサイズ
	static constexpr float kShotSize = 1.1f;

	// ショット1カラーR
	static constexpr float kShotCollarR = 1.0f;
	// ショット1カラーG
	static constexpr float kShotCollarG = 1.0f;
	// ショット1カラーB
	static constexpr float kShotCollarB = 1.0f;

public:
	Shot();
	virtual ~Shot();


	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_SceneMain = sceneMain; }
	

	// 発射
	void start(VECTOR pos);

	// 初期化処理
	void init();

	// 更新
	void update();
	// 表示
	void draw();

	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// 情報の取得
	VECTOR getPos() const { return m_pos; }
public:
	// グラフィックを受け取る
	void getShotGraphic(int handle) { m_modeleHandle = handle; }

public:

	// 弾幕の軌道
	void BulletTrajectory();

	// 2Dの当たり判定
	void Collision2D();

	// 移動制限処理
	void LimitMove();

private:

	// 3Dモデルハンドル
	int m_modeleHandle;

	// 存在フラグ
	bool m_isExist;


	// 表示位置
	VECTOR m_pos;

	// クラスポインタ
	SceneMain* m_SceneMain;

};


