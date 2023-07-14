#include "Camera.h"
#include "Player.h"
#include "Pad.h"
#include "SceneMain.h"


namespace
{
	// カメラのズーム
	constexpr float kCameraZoom = -100.0f;

	// カメラのY座標位置
	constexpr float kCameraPosY = 50.0f;

	// カメラの回転位置
	constexpr float kCameraRot = 0.8f;

	// 揺れる大きさ
	constexpr int kShakeMaxRand = 2;

	// 揺らす時間
	constexpr int kShakeFrame = SceneMain::kFreezeFrameMaxCount;

	// カメラの数
	constexpr int kCamaraNum = 4;

	// カメラ1の角度
	constexpr int kCamera1Degree = 45;
	// カメラ2の角度
	constexpr int kCamera2Degree = 20;
	// カメラ3の角度
	constexpr int kCamera3Degree = 0;
	// カメラ4の角度
	constexpr int kCamera4Degree = 57;
}


Camera::Camera():
	m_pos(),
	m_cameraRot(0.0f),
	m_cameraNum(0),
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

	// カメラの回転初期値
	m_cameraRot = kCamera1Degree * (DX_PI / 180);

}

void Camera::update()
{
	// プレイヤーの位置を入れる
	VECTOR playerPos = m_pPlayer->getPos();

	// カメラを変更する
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_cameraNum++;

		// m_cameraNumの値をループさせる
		if (m_cameraNum % kCamaraNum == 0)
		{
			m_cameraNum = 0;
		}
		
		switch (m_cameraNum)
		{
		case 0:
			// ラジアン変換
			m_cameraRot = kCamera1Degree * (DX_PI / 180);
			break;
		case 1:
			// ラジアン変換
			m_cameraRot = kCamera2Degree * (DX_PI / 180);
			break;
		case 2:
			// ラジアン変換
			m_cameraRot = kCamera3Degree * (DX_PI / 180);
			break;
		case 3:
			// ラジアン変換
			m_cameraRot = kCamera4Degree * (DX_PI / 180);
			break;
		}

	}



	if (m_cameraNum == 0)
	{
		// カメラの位置
		m_pos = VGet(playerPos.x, playerPos.y + 50, playerPos.z-20);

	}
	else if (m_cameraNum == 1)
	{
		// カメラの位置
		m_pos = VGet(playerPos.x, playerPos.y+10, playerPos.z-20);
	}
	else if (m_cameraNum == 2)
	{

		// カメラの位置
		m_pos = VGet(playerPos.x, playerPos.y+5, playerPos.z);
	}
	else if (m_cameraNum == 3)
	{
		//m_cameraRot = 1.0f;

		// カメラの回転位置
		m_pos = VGet(0.0f,  100.0f, -10.0f);
	}

}

void Camera::draw()
{

	// カメラの回転角度
	SetCameraPositionAndAngle(m_pos, m_cameraRot, 0.0f, 0.0f);
	


}

void Camera::ShakeScreen(int frameCount)
{
	VECTOR shekePos = VGet(0.0f, 0.0f, 0.0f);

	// x,yをマイナスするかしないか
	int x = GetRand(1);
	int y = GetRand(1);


	// 割合
	int ratio = 100 * frameCount;

	// 比率
	float rate = ratio / kShakeFrame;

	// 小数化
	float decimal = rate * 0.01;


	// 振動幅(計算)
	int afterShakeWidth = kShakeMaxRand * decimal;


	// ランダム値で座標を変換する
	shekePos.x = GetRand(afterShakeWidth);
	shekePos.y = GetRand(afterShakeWidth);


	// x or yが0の時、位置をマイナスする
	if (x == 0)shekePos.x *= -1;
	if (y == 0)shekePos.y *= -1;

	m_pos = VAdd(m_pos, shekePos);
}
