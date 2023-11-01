#pragma once
#include "game.h"
#include <memory>

class MainUI;
class SceneMain;
class Player
{
public:
	// パワーアップ番号
	static constexpr int kPowerUpMaxNum = 3;


	// ショットのスピードアップフレームの最大値
	static constexpr int kPowerUpMaxFrame = 60*8;

	// プレイヤーの色変更
	// 速度
	static constexpr float kQuickCollarR = 1.0;
	static constexpr float kQuickCollarG = 0.0;
	static constexpr float kQuickCollarB = 0.0;

	// 連射
	static constexpr float kRapidCollarR = 0.0;
	static constexpr float kRapidCollarG = 0.0;
	static constexpr float kRapidCollarB = 1.0;

	// 貫通
	static constexpr float kPenetrationCollarR = 0.0;
	static constexpr float kPenetrationCollarG = 1.0;
	static constexpr float kPenetrationCollarB = 0.0;

	// 残像の量
	static constexpr int kAfterimageNum = 5;
public:
	Player();
	virtual~Player();

	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }
	void getMainUIPointer(std::shared_ptr<MainUI>mainUI) { m_pMainUI = mainUI; }

	void init();
	void update();
	void draw();

	// 位置情報を返す
	VECTOR getPos() const { return m_pos[0]; }

	// 色情報を返す
	VECTOR getColor() const { return m_color; }


	// 当たり判定を取得
	void getIsHit(bool isHit) { m_isHit = isHit; }

	// パワーアップするかどうかを取得
	void getPowerUp(bool isPowerUp, int powerUpNum) { m_isPowerUp = isPowerUp, m_powerUpNum = powerUpNum; }

public:
	// 移動処理
	void Move();

	// 移動制限
	void LimitMove();

	// ショット処理
	void Shot();

	// ダメージ処理
	void CollisionProcess();

	// パワーアップ処理
	void PowerUpProcess();

	// 状態初期化
	void Reset();

	// 残像処理
	void Afterimage();

private:


	// 3Dモデルハンドル
	int m_modeleHandle;

	// 当たったかどうか
	bool m_isHit;

	// ショットの発生間隔
	int m_shotInterval;

	// パワーアップフラグ
	bool m_isPowerUp;

	// パワーアップフレーム
	int m_powerUpFrame;

	// パワーアップ番号
	int m_powerUpNum;

	// 移動スピード
	float m_moveSpeed;

	// ステータスを変えたかどうか
	bool m_isChangeStatus;

	// 表示位置
	VECTOR m_pos[kAfterimageNum];

	// 方向
	VECTOR m_dir;

	// 色
	VECTOR m_color;

	// クラスポインタ
	SceneMain* m_pSceneMain;
	std::shared_ptr<MainUI>m_pMainUI;
};

