#pragma once
#include "game.h"
#include <memory>

class Player;
class InvertShot
{
public:

	// ショットのサイズ
	static constexpr float kShotSize = 1.1f;

	// 透明度（1が不透明）
	static constexpr float kAlphaValue = 1.0;

	// パーティクルのスケール
	static constexpr float kParticleScale = 1.0;

public:
	InvertShot();
	virtual ~InvertShot();

	// クラスポインタの取得
	void getPlayerPointer(std::shared_ptr<Player>player) { m_pPlayer = player; }

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
	void setShotGraphic(int handle) { m_modeleHandle = handle; }

	// カラー取得
	void setColor(VECTOR color) { m_color = color; }
	// 情報の取得
	VECTOR getColor() const { return m_color; }

public:

	// 弾幕の軌道
	void BulletTrajectory();

	// 当たり判定
	void Collision();

	// 移動制限処理
	void LimitMove();

private:

	// 存在フラグ
	bool m_isExist;

	// 3Dモデルハンドル
	int m_modeleHandle;

	// 表示位置
	VECTOR m_pos;

	// カラー
	VECTOR m_color;

	// クラスポインタ
	std::shared_ptr<Player>m_pPlayer;
};




