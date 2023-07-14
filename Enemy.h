#pragma once
#include "game.h"
#include "Setting.h"


class SceneMain;
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX, int savePosZ, int enemyNum);

	void update();
	
	void draw();

	// 位置情報を返す
	VECTOR getPos() const { return m_pos; }


	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// エネミーの番号を返す
	int enemyNum() const { return m_enemyNum; }
public:


	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	// カラー取得
	void setColor(VECTOR color) { m_color = color; }

	// 移動までにかかる時間を減らす値を取得
	void getDecrementTime(int decrementTime) { m_decrementTime = decrementTime; }

	// レベルによる移動にかかる時間
	void getLvMoveTime(int lvMove) { m_LvMove = lvMove; }

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
	int m_handle[EnemySet::kEnemyGraphicNum];

	// アニメーションナンバー
	int m_animationNum;

	// エネミーナンバー
	int m_enemyNum;

	// レベルによる移動スピード
	int m_LvMove;

	// 表示位置
	VECTOR m_pos;

	// 色
	VECTOR m_color;

	// クラスポインタ
	SceneMain* m_pSceneMain;

	// 立体表示
	VERTEX3D Vertex[6];

	// 回転
	VECTOR Angle;
};

