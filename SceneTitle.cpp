#include "game.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"
#include "BackGround.h"

namespace
{
	// 文字フォント
	const char* const kTextFontName = "NULL";

	// 文字フォントサイズ
	constexpr int kTextFontSize = 60;

	// 文字位置
	constexpr int kTextInitPosX = 650;
	constexpr int kTextInitPosY = 650;

	// 文字
	const char* const kText = "- P u s h ' A ' -";

	// 文字の振れ幅
	constexpr float kTextSinValue = 255.0f;

	// 文字のサインカーブのスピード
	constexpr float kTextSinSpeedValue = 0.03f;



	// モデルのグラフィックファイル名
	const char* const kModelGraphicFileName = "data/model/text.mv1";

	// モデルの初期位置
	constexpr int kModelInitPosX = 0;
	constexpr int kModelInitPosY = 15;
	constexpr int kModelInitPosZ = 0;

	// モデルのスケール
	constexpr float kModelScale = 1.5f;

	// ライトの初期位置
	constexpr int kLightInitPosX = 0;
	constexpr int kLightInitPosY = 30;
	constexpr int kLightInitPosZ = 40;

	// 振れ幅
	constexpr float kSinValue = 2.0f;

	// サインカーブのスピード
	constexpr float kSinSpeedValue = 0.01f;
}


SceneTitle::SceneTitle() :
	m_isEnd(false),
	m_fontHandle(-1),
	m_textSin(2.0f),
	m_fadeValue(0.0f),
	m_modelHandle(-1),
	m_lightPos(),
	m_titlePos(),
	m_sinRate(0.0f),
	m_pBackGround(std::make_shared<BackGround>())
{

}

SceneTitle::~SceneTitle()
{
	// モデルの削除
	MV1DeleteModel(m_modelHandle);

	// 作成したフォントデータを削除する
	DeleteFontToHandle(m_fontHandle);
}

void SceneTitle::init()
{

	// フォントの挿入・設定
	m_fontHandle = CreateFontToHandle(kTextFontName, kTextFontSize, 3);


	{
		// カメラの 手前クリップ距離と 奥クリップ距離を設定する
		SetCameraNearFar(0.1f, 1000.0f);
		// カメラの回転角度
		SetCameraPositionAndAngle(VGet(0,0,-100), 0.0f, 0.0f, 0.0f);
	}

	{
		// モデルを入れる
		m_modelHandle = MV1LoadModel(kModelGraphicFileName);

		m_titlePos = VGet(kModelInitPosX, kModelInitPosY, kModelInitPosZ);

		// モデルの位置
		MV1SetPosition(m_modelHandle, m_titlePos);

		// ３Ｄモデルのスケール設定
		MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));
	}

	// ライトの初期位置
	m_lightPos = VGet(kLightInitPosX, kLightInitPosY, kLightInitPosZ);

	// クラスの初期化処理
	m_pBackGround->init(0);

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	

	m_textSin += kTextSinSpeedValue;

	m_fadeValue = (((sinf(m_textSin) * kTextSinValue)+ kTextSinValue)/2);



	// モデルの移動処理
	ModelMove();



	


	// クラスのアップデート処理
	m_pBackGround->update();

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// Mainに切り替え
		return(new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{

	// テキスト
	{

		// 透明にして表示する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_fadeValue));

		int slide = 4;

		// 影みたいな表現
		DrawFormatStringToHandle(kTextInitPosX + slide, kTextInitPosY + slide,
			0x000000, m_fontHandle, kText);

		DrawFormatStringToHandle(kTextInitPosX, kTextInitPosY,
			0xff0000, m_fontHandle, kText);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	{
		VECTOR Direction = m_lightPos;
		ChangeLightTypeDir(Direction);

		// 球の表示
		DrawSphere3D(Direction, 2.0, 32, 0xffffff, GetColor(0, 0, 0), true);
	}

	// モデル描画
	MV1DrawModel(m_modelHandle);


	// クラスの描画処理
	m_pBackGround->draw();



	//XYZ軸、デバッグ描写
	float lineHeightSize = 1000.0f;
	DrawLine3D(VGet(-lineHeightSize, 0, 0), VGet(lineHeightSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineHeightSize, 0), VGet(0, lineHeightSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineHeightSize), VGet(0, 0, lineHeightSize), GetColor(0, 0, 255));


#if true
	
	DrawString(0, 0, "タイトル画面", GetColor(255, 255, 255));

	DrawFormatString(0, 15 * 1, 0xffffff, "m_fadeValue=%f", m_fadeValue);

#endif


}

void SceneTitle::ModelMove()
{
	m_sinRate += kSinSpeedValue;

	float moveY = sinf(m_sinRate) * kSinValue;

	m_titlePos = VGet(kModelInitPosX, kModelInitPosY + moveY, kModelInitPosY);

	// モデルの位置
	MV1SetPosition(m_modelHandle, m_titlePos);
}
