#pragma once
#include "game.h"

class SceneMain;
class Enemy
{
public:
	// 半球サイズ
	static constexpr float kCircleSize = 2.0f;

	// エネミーグラフィック分割数
	static constexpr int kEnemyGraphicDivX = 3;
	static constexpr int kEnemyGraphicDivY = 1;
	static constexpr int kEnemyGraphicDivNum = kEnemyGraphicDivX * kEnemyGraphicDivY;
public:
	Enemy();
	virtual ~Enemy();

	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX, int savePosY, int decrementTime);

	void update();
	
	void draw();

	// 位置情報を返す
	VECTOR getPos() const { return m_pos; }

	// 当たり判定を取得
	void getIsHit(bool isHit) { m_isHit = isHit; }

	// 移動までにかかる時間を減らす数値を取得
	void getDecrementTime(int decrementTime) { m_decrementTime = decrementTime; }


	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

public:


	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }



public:

	// 移動処理
	void Move();

	// ショット処理
	void Shot();

	// ダメージを受けたときのアニメーション
	void DamageAnimation();


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

	// 下に行くかどうか
	bool m_isUnderMove;


	// 当たったかどうか
	bool m_isHit;

	// ショットの発生間隔
	int m_shotInterval;

	// 移動までにかかる時間を減らす
	int m_decrementTime;

	// エネミーのグラフィック
	int m_handle[kEnemyGraphicDivNum];

	// アニメーションナンバー
	int m_animationNum;

	// ダメージアニメーションフレーム
	int m_damageAnimationFrame;

	


	// 表示位置
	VECTOR m_pos;

	// クラスポインタ
	SceneMain* m_pSceneMain;
};

