#pragma once
#include "game.h"

class SceneMain;
class Bunker
{
public:
	// 半球サイズ
	static constexpr float kCircleSize = 2.0f;

	// カラーR
	static constexpr float kCollarR = 0.0f;
	// カラーG
	static constexpr float kCollarG = 1.0f;
	// カラーB
	static constexpr float kCollarB = 0.0f;

	// 透明度(1.0fが不透明、0.0fが透明)
	static constexpr float kAlphaValue = 0.5f;

	// パーティクルの量
	static constexpr int kParticleValue = 32;

	// パーティクルのスケール
	static constexpr float kParticleScale = 5.0;

public:
	Bunker();
	virtual ~Bunker();

	// クラスポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX);

	void update();

	void draw();

	// 位置情報を返す
	VECTOR getPos() const { return m_pos; }

	// 色情報を返す
	VECTOR getColor() const { return m_color; }

	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// 番号の取得
	void setNumber(int number) { m_number = number; }

public:
	// グラフィックを受け取る
	void setGraphic(int handle) { m_modeleHandle = handle; }
public:
	// ダメージ処理
	void DamegeProcess(int damages);

private:

	// あたり判定
	void Collision2D();

	// カラー処理
	void ColorProcess();

private:

	// 3Dモデルハンドル
	int m_modeleHandle;


	// 存在フラグ
	bool m_isExist;


	// ヒットポイント
	int m_hp;

	// 番号
	int m_number;


	// 表示位置
	VECTOR m_pos;

	// 色指定
	VECTOR m_color;

	// クラスポインタ
	SceneMain* m_pSceneMain;
};

