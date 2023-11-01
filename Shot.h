#pragma once
#include "game.h"
#include <memory>
#include "SceneMain.h"


class SceneMain;
class BonusEnemy;
class Player;
class Shot
{
public:

	// ショットのサイズ
	static constexpr float kShotSize = 1.2f;

	// ショットのサイズ
	static constexpr float kShotBigSize = 4.0f;

	// 残像の量
	static constexpr int kAfterimageNum = 4;

	// パーティクルの量
	static constexpr int kParticleValue = 16;

	// 透明度（1が不透明）
	static constexpr float kAlphaValue = 1.0;

	// パーティクルのスケール
	static constexpr float kParticleScale = 1.0;

	// パーティクルのスケール(サイズのでかいショット)
	static constexpr float kParticleScale2 = 2.6;


public:
	Shot();
	virtual ~Shot();


	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_SceneMain = sceneMain; }
	void getBonusEnemyPointer(std::shared_ptr<BonusEnemy>bonusEnemy) { m_pBonusEnemy = bonusEnemy; }
	void getPlayerPointer(std::shared_ptr<Player>player) { m_pPlayer = player; }

	// 発射
	void start(VECTOR pos, bool isPowerUp, int powerUpNum);

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
	VECTOR getPos() const { return m_pos[0]; }
	// 色の取得
	VECTOR getColor() const { return m_color; }
	// 色の取得
	float getParticleScale() const { return m_particleScale; }

public:
	// グラフィックを受け取る
	void getShotGraphic(int handle) { m_modeleHandle = handle; }

	// ショット番号を受け取る
	void setShotNum(int num) { m_shotNum = num; }

public:

	// 弾幕の軌道
	void BulletTrajectory();

	// 当たり判定
	void Collision();

	// 移動制限処理
	void LimitMove();

	// 残像処理
	void Afterimage();

private:

	// 3Dモデルハンドル
	int m_modeleHandle;

	// 存在フラグ
	bool m_isExist;

	// ショットスピード
	float m_shotSpeed;

	// 貫通するかどうか
	bool m_isPenetration;

	// ショットサイズ
	float m_shotSize;

	// パワーアップ中かどうか
	bool m_isPowerUp;

	// ショットの番号
	int m_shotNum;

	// パーティクルの大きさ
	float m_particleScale;

	// 表示位置
	VECTOR m_pos[kAfterimageNum];

	// 色
	VECTOR m_color;


	// クラスポインタ
	SceneMain* m_SceneMain;
	std::shared_ptr<BonusEnemy>m_pBonusEnemy;
	std::shared_ptr<Player>m_pPlayer;
};


