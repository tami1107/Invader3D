#pragma once
#include "game.h"

class SceneMain;
class Enemy
{
public:
	// 半球サイズ
	static constexpr float kCircleSize = 5.0f;

	// エネミーグラフィック数
	static constexpr int kEnemyGraphicNum = 2;

	// 初期座標
	static constexpr float kInitPosZ = 100.0f;

	// 移動量X
	static constexpr float kMovePosX = 5.0f;

	// 移動量Z
	static constexpr float kMovePosZ = 10.0f;

	// どこまで移動するのか (kMovePosX * kLimitMove)
	static constexpr int kLimitMove = 6;

public:
	Enemy();
	virtual ~Enemy();

	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX, int savePosZ);

	void update();
	
	void draw();

	// 位置情報を返す
	VECTOR getPos() const { return m_pos; }


	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

public:


	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	// 移動までにかかる時間を減らす値を取得
	void getDecrementTime(int decrementTime) { m_decrementTime = decrementTime; }

public:
	// ポリゴン初期設定
	void InitPolygon();

	// ポリゴンのアップデート
	void UpdatePolygon();

	// 移動処理
	void Move();

	// ショット処理
	void Shot();

private:
	
	// 存在フラグ
	bool m_isExist;


	// 保存位置
	int m_savePosX;
	int m_savePosZ;

	// フレームカウント
	int m_frameCount;


	// 右に行くかどうか
	bool m_isRightMove;

	// 手前に行くかどうか
	bool m_isUnderMove;


	// ショットの発生間隔
	int m_shotInterval;

	// 移動までにかかる時間を減らす
	int m_decrementTime;

	// エネミーのグラフィック
	int m_handle[kEnemyGraphicNum];

	// アニメーションナンバー
	int m_animationNum;


	// 表示位置
	VECTOR m_pos;

	// クラスポインタ
	SceneMain* m_pSceneMain;

	// 立体表示
	VERTEX3D Vertex[6];

	// 回転
	VECTOR Angle;
};

