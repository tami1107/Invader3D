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


	// 存在するか
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }


public:
	// グラフィックを受け取る
	void getGraphic(int handle) { m_modeleHandle = handle; }
public:
	// ダメージ処理
	void DamegeProcess(int damages);

	// あたり判定
	void Collision2D();

private:

	// 3Dモデルハンドル
	int m_modeleHandle;


	// 存在フラグ
	bool m_isExist;


	// ヒットポイント
	int m_hp;

	// アルファブレンドの値
	int m_alphaValue;

	// アルファブレンドの減少値
	int m_alphaValueDecrement;


	// 表示位置
	VECTOR m_pos;
	
	// クラスポインタ
	SceneMain* m_pSceneMain;
};

