#include "game.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"
#include "BackGround.h"

namespace
{
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
	m_modelHandle(-1),
	m_lightPos(),
	m_titlePos(),
	sinRate(0.0f),
	m_pBackGround(std::make_shared<BackGround>())
{

}

SceneTitle::~SceneTitle()
{
	// モデルの削除
	MV1DeleteModel(m_modelHandle);

}

void SceneTitle::init()
{
	// カメラの 手前クリップ距離と 奥クリップ距離を設定する
	SetCameraNearFar(0.1f, 1000.0f);
	// カメラの回転角度
	SetCameraPositionAndAngle(VGet(0,0,-100), 0.0f, 0.0f, 0.0f);

	// モデルを入れる
	m_modelHandle = MV1LoadModel(kModelGraphicFileName);

	m_titlePos = VGet(kModelInitPosX, kModelInitPosY, kModelInitPosZ);

	// モデルの位置
	MV1SetPosition(m_modelHandle, m_titlePos);

	// ３Ｄモデルのスケール設定
	MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));


	// ライトの初期位置
	m_lightPos = VGet(kLightInitPosX, kLightInitPosY, kLightInitPosZ);

	// クラスの初期化処理
	m_pBackGround->init(0);

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	

	sinRate += kSinSpeedValue;

	float moveY = sinf(sinRate) * kSinValue;

	m_titlePos = VGet(kModelInitPosX, kModelInitPosY + moveY, kModelInitPosY);

	// モデルの位置
	MV1SetPosition(m_modelHandle, m_titlePos);
	


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


	DrawString(0, 0, "タイトル画面", GetColor(255, 255, 255));
}