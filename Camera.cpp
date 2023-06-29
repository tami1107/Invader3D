#include "Camera.h"
#include "Player.h"


namespace
{
	// �J�����̃Y�[��
	constexpr float kCameraZoom = -100.0f;

	// �J������Y���W�ʒu
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
	// �J������ ��O�N���b�v������ ���N���b�v������ݒ肷��
	SetCameraNearFar(0.1f, 1000.0f);

	// �ʒu�̏�����
	m_pos = VGet(0.0f, 0.0f, 0.0f);

}

void Camera::update()
{
	// �v���C���[�̈ʒu������
	VECTOR playerPos = m_pPlayer->getPos();

	// �J�����ʒu�̍X�V
	m_pos = VGet(playerPos.x, playerPos.y + kCameraPosY, kCameraZoom+ playerPos.z);


	// �J�����̉�]�ʒu
	VECTOR cameraPos = VGet(playerPos.x, playerPos.y + 50, playerPos.z-20);

	// �J�����̉�]�p�x
	SetCameraPositionAndAngle(cameraPos, 0.8f, 0.0f, 0.0f);

	//// �J�����̒����_( ���Ă�����W )
	//VECTOR targetPos = VGet(m_pos.x, m_pos.y, 0.0f);

	//// �J�����ʒu
	//SetCameraPositionAndTarget_UpVecY(m_pos, targetPos);
}

void Camera::draw()
{
	//XYZ���A�f�o�b�O�`��
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
