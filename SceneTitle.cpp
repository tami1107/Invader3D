#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"

namespace
{
	// モデルのグラフィックファイル名
	const char* const kModelGraphicFileName = "data/model/text.mv1";

	//// モデルのグラフィックファイル名
	//const char* const kModelGraphicFileName = "data/model/text.mv1";

	//// モデルのグラフィックファイル名
	//const char* const kModelGraphicFileName = "data/model/text.mv1";


	// モデルの初期位置
	constexpr int kInitPosX = 0;
	constexpr int kInitPosY = 20;
	constexpr int kInitPosZ = 0;
}


SceneTitle::SceneTitle() :
	m_isEnd(false)
{
	//// 位置情報の初期化
	//for (auto& textMove : m_textMove)
	//{
	//	textMove = VGet(0, 0, 0);
	//}
}

SceneTitle::~SceneTitle()
{
	// モデルの削除
	MV1DeleteModel(m_modelHandle[0]);
}

void SceneTitle::init()
{
	// カメラの 手前クリップ距離と 奥クリップ距離を設定する
	SetCameraNearFar(0.1f, 1000.0f);
	// カメラの回転角度
	SetCameraPositionAndAngle(VGet(0,0,-100), 0.0f, 0.0f, 0.0f);

	// モデルを入れる
	m_modelHandle[0] = MV1LoadModel(kModelGraphicFileName);

	// モデルの位置
	MV1SetPosition(m_modelHandle[0], VGet(kInitPosX, kInitPosY, kInitPosZ));

	m_isEnd = false;
}

SceneBase* SceneTitle::update()
{
	
	
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// Mainに切り替え
		return(new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{


	//VECTOR Direction = VGet(0, 30, 50);
	//ChangeLightTypeDir(Direction);

	//// 球の表示
	//DrawSphere3D(Direction, 1.0, 32, 0xffffff, GetColor(0, 0, 0), true);


	// スカイドーム描画
	MV1DrawModel(m_modelHandle[0]);

	//XYZ軸、デバッグ描写
	float lineHeightSize = 1000.0f;
	DrawLine3D(VGet(-lineHeightSize, 0, 0), VGet(lineHeightSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineHeightSize, 0), VGet(0, lineHeightSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineHeightSize), VGet(0, 0, lineHeightSize), GetColor(0, 0, 255));


	DrawString(0, 0, "タイトル画面", GetColor(255, 255, 255));
}