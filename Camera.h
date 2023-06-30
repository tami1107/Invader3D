#pragma once
#include "game.h"
#include <memory>


class Player;
class Camera
{
public:
	Camera();
	virtual~Camera();

	// �N���X�|�C���^�̎擾
	void getPlayerPointer(std::shared_ptr<Player>player) { m_pPlayer = player; }


	void init();
	void update();
	void draw();


private:
	// �\���ʒu
	VECTOR m_pos;

	// �J�����̉�]
	float m_cameraRot;

	// �J�����̕\���ԍ�
	int m_cameraNum;

	// �N���X�|�C���^
	std::shared_ptr<Player>m_pPlayer;

};

