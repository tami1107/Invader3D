#pragma once
#include <memory>
#include "Vec2.h"


class SceneMain;
class Pause
{
public:
	Pause();
	virtual ~Pause();

	// ポインタの取得
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }

	void init();
	void update();
	void draw();

public:
	// ポーズ処理
	void PauseProcess();

	// 選択処理
	void SelectProcess();

	// フレームの描画
	void DrawFrame();


	// 項目テキストの描画
	void DrawSelectText();

	// タイトルに戻る選択時の処理
	void TitleSelectProcess();

private:


	// ポーズ中かどうか
	bool m_isPause;

	// 選択番号
	int m_selectNum;

	// 項目選択時の移動インターバル
	int m_selectInterval;

	// 文字フォント
	int m_textFont;

	// サイン
	float sinRate;

	// タイトルに戻るかどうかのフラグ
	int m_titleFlag;

	// 選択番号(タイトルに戻るときの番号)
	int m_selectNum2;



	// 座標情報
	Vec2 m_pos;




	// クラスポインタ
	SceneMain* m_pSceneMain;
};

