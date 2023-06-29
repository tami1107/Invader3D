#include "Camera.h"
#include "Player.h"


namespace
{
	// カメラのズーム
	constexpr float kCameraZoom = -100.0f;

	// カメラのY座標位置
	constexpr float kCameraPosY = 50.0f;
}


Camera::Camera():
	m_pos(),
	m_pPlayer(std::make_shared<Player>())
{
}

Camera::~Camera()
{
}

void Camera::init()
{
	// カメラの 手前クリップ距離と 奥クリップ距離を設定する
	SetCameraNearFar(0.1f, 1000.0f);

	// 位置の初期化
	m_pos = VGet(0.0f, 0.0f, 0.0f);

}

void Camera::update()
{
	// プレイヤーの位置を入れる
	VECTOR playerPos = m_pPlayer->getPos();

	// カメラ位置の更新
	m_pos = VGet(playerPos.x, playerPos.y + kCameraPosY, kCameraZoom+ playerPos.z);


	// カメラの回転位置
	VECTOR cameraPos = VGet(playerPos.x, playerPos.y + 50, playerPos.z-20);

	// カメラの回転角度
	SetCameraPositionAndAngle(cameraPos, 0.8f, 0.0f, 0.0f);

	//// カメラの注視点( 見ている座標 )
	//VECTOR targetPos = VGet(m_pos.x, m_pos.y, 0.0f);

	//// カメラ位置
	//SetCameraPositionAndTarget_UpVecY(m_pos, targetPos);
}

void Camera::draw()
{
	//XYZ軸、デバッグ描写
	float lineSize = 1000.0f;
	DrawLine3D(VGet(-lineSize, 0, 0), VGet(lineSize, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -lineSize, 0), VGet(0, lineSize, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -lineSize), VGet(0, 0, lineSize), GetColor(0, 0, 255));

	float linePos = 10;
	lineSize = 100.0f;

	for (int i = 0; i < 10; i++)
	{
		DrawLine3D(VGet(-lineSize, 0, linePos * i), VGet(lineSize, 0, linePos * i), GetColor(255, 0, 0));

	}
	
	


}
