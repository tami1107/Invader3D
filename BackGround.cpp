#include "BackGround.h"
#include "Enemy.h"

namespace
{
	// モデルのグラフィックファイル名
	const char* const kModelGraphicFileName = "data/model/Dome_Y301.mv1";

	// 増えていく角度の値
	constexpr float kDegreeAdd = 0.02;
}


BackGround::BackGround():
	m_modelHandle(-1),
	m_degree(0)
{
}

BackGround::~BackGround()
{
	// モデルの削除
	MV1DeleteModel(m_modelHandle);
}

void BackGround::init(int num)
{
	// スカイドームのモデルを入れる
	m_modelHandle = MV1LoadModel(kModelGraphicFileName);

	switch (num)
	{
	case 0:
		// スカイドームの中心位置
		MV1SetPosition(m_modelHandle, VGet(0, 0, -200));
		break;
	case 1:
		// スカイドームの中心位置
		MV1SetPosition(m_modelHandle, VGet(0, 200, 0));
		break;
	}

}

void BackGround::update()
{
	// スカイドームの回転処理
	RotSkyDome();
}

void BackGround::draw()
{
	// ラインの描画
	DrawLine();

	// スカイドーム描画
	DrawSkyDome();


	// ライティング関連
#if true
	VECTOR Direction = VGet(0, 30, 50);
	ChangeLightTypeDir(Direction);

	// 球の表示
	DrawSphere3D(Direction, 1.0, 32, 0xffffff, GetColor(0, 0, 0), true);
#endif
}

void BackGround::RotSkyDome()
{
	// 角度の値を増やす
	m_degree += kDegreeAdd;

	// 角度の値が360°を超えた場合、0にする
	if (m_degree >= 360.0f)
	{
		m_degree = 0.0f;
	}

	// ラジアン変換
	float rot = m_degree * (DX_PI / 180);


	MV1SetRotationXYZ(m_modelHandle, VGet(0,rot,0));
}

void BackGround::DrawLine()
{
	//XYZ軸、デバッグ描写
	float lineHeightSize = 1000.0f;
	//DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineHeightSize, 0), VGet(0, lineHeightSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineHeightSize), VGet(0, 0, lineHeightSize), GetColor(0, 0, 255));

	// ラインの縦幅
	float lineWidthPos = EnemySet::kMovePosZ;
	

	lineHeightSize = EnemySet::kLimitMove * 1.1;
	// ラインの列（0も含むので+１する）
	float lineArray = (EnemySet::kInitPosZ / lineWidthPos) + 1;



	for (int i = 0; i < lineArray; i++)
	{
		DrawLine3D(VGet(-lineHeightSize, 0, lineWidthPos * i), VGet(lineHeightSize, 0, lineWidthPos * i), GetColor(255, 0, 0));
	}
}

void BackGround::DrawSkyDome()
{
	// スカイドーム描画
	MV1DrawModel(m_modelHandle);
}
