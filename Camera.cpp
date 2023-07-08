#include "Camera.h"
#include "Player.h"
#include "Pad.h"
#include "SceneMain.h"


namespace
{
	// �J�����̃Y�[��
	constexpr float kCameraZoom = -100.0f;

	// �J������Y���W�ʒu
	constexpr float kCameraPosY = 50.0f;

	// �J�����̉�]�ʒu
	constexpr float kCameraRot = 0.8f;

	// �h���傫��
	constexpr int kShakeMaxRand = 2;

	// �h�炷����
	constexpr int kShakeFrame = SceneMain::kFreezeFrameMaxCount;
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
	// �J������ ��O�N���b�v������ ���N���b�v������ݒ肷��
	SetCameraNearFar(0.1f, 1000.0f);

	// �ʒu�̏�����
	m_pos = VGet(0.0f, 0.0f, 0.0f);

	// �J�����̉�]�����l
	m_cameraRot = kCameraRot;
}

void Camera::update()
{
	// �v���C���[�̈ʒu������
	VECTOR playerPos = m_pPlayer->getPos();

	// �J�����̉�]��ύX����
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		m_cameraNum++;

		// 0��1�����g��Ȃ�
		if (m_cameraNum == 4)
		{
			m_cameraNum = 0;
		}
	}


	VECTOR cameraPos = {};

	if (m_cameraNum == 0)
	{
		m_cameraRot = kCameraRot;

		// �J�����̉�]�ʒu
		cameraPos = VGet(playerPos.x, playerPos.y + 50, playerPos.z-20);

	}
	else if (m_cameraNum == 1)
	{
		m_cameraRot = 0.2f;

		// �J�����̉�]�ʒu
		cameraPos = VGet(playerPos.x, playerPos.y+10, playerPos.z-20);
	}
	else if (m_cameraNum == 2)
	{
		m_cameraRot = 0.0f;

		// �J�����̉�]�ʒu
		cameraPos = VGet(playerPos.x, playerPos.y+5, playerPos.z);
	}
	else if (m_cameraNum == 3)
	{
		m_cameraRot = 1.0f;

		// �J�����̉�]�ʒu
		cameraPos = VGet(0.0f,  100.0f, -10.0f);
	}

	m_pos = cameraPos;


	



	//// �J�����ʒu�̍X�V
	//m_pos = VGet(playerPos.x, playerPos.y + kCameraPosY, kCameraZoom+ playerPos.z);

	//// �J�����̒����_( ���Ă�����W )
	//VECTOR targetPos = VGet(m_pos.x, m_pos.y, 0.0f);

	//// �J�����ʒu
	//SetCameraPositionAndTarget_UpVecY(m_pos, targetPos);
}

void Camera::draw()
{

	// �J�����̉�]�p�x
	SetCameraPositionAndAngle(m_pos, m_cameraRot, 0.0f, 0.0f);
	


}

void Camera::ShakeScreen(int frameCount)
{
	VECTOR shekePos = VGet(0.0f, 0.0f, 0.0f);

	// x,y���}�C�i�X���邩���Ȃ���
	int x = GetRand(1);
	int y = GetRand(1);


	// ����
	int ratio = 100 * frameCount;

	// �䗦
	float rate = ratio / kShakeFrame;

	// ������
	float decimal = rate * 0.01;


	// �U����(�v�Z)
	int afterShakeWidth = kShakeMaxRand * decimal;


	// �����_���l�ō��W��ϊ�����
	shekePos.x = GetRand(afterShakeWidth);
	shekePos.y = GetRand(afterShakeWidth);


	// x or y��0�̎��A�ʒu���}�C�i�X����
	if (x == 0)shekePos.x *= -1;
	if (y == 0)shekePos.y *= -1;

	m_pos = VAdd(m_pos, shekePos);
}
