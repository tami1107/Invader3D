#pragma once
#include "game.h"
#include "Setting.h"
#include "Vec2.h"

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
	int getEnemyLineNum() const { return m_enemyLineNum; }

	// カラーの値を返す
	VECTOR getColor() const { return m_color; }

	// 現在のインターバルを返す
	int getMoveInterval() const { return m_moveMaxInterval; }

public:

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	// カラー取得
	void setColor(VECTOR color) { m_color = color; }

	// 移動までにかかる時間を減らす値を取得
	void setDecrementTime(int decrementTime) { m_decrementTime = decrementTime; }

	// エネミーの番号を受け取る
	void setEnemyNum(int enemyNum) { m_enemyNum = enemyNum; }


public:
	// ポリゴン初期設定
	void InitPolygon();

	// ポリゴンのアップデート
	void UpdatePolygon();

	// 移動処理
	void Move();

	// ショット処理
	void Shot();

	// レベルアップ設定
	void LevelUp(float IntervalDecrement);

	// エネミー数インターバル
	void EnemyNumInterval(int interval);

	// リセット処理
	void Reset();

	// 移動設定
	void MoveSetting(float enemyEdgePosX);

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
	int m_enemyLineNum;


	// エネミー番号
	int m_enemyNum;

	// 移動最大インターバル
	int m_moveMaxInterval;

	// 移動インターバル
	int m_moveInterval;

	// 移動量
	float m_movingDistance;

	// 最大移動量
	float m_movingMaxDistance;

	// エネミー端の座標
	float m_enemyEdgePosX;

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

