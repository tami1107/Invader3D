#pragma once
#include "game.h"

class Particle
{
public:
	Particle();
	virtual ~Particle();

	void update();
	void draw();

	void start(VECTOR pos, VECTOR color);

	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }


	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) {m_handle= handle; }

public:
	// �|���S�������ݒ�
	void InitPolygon();

	// �|���S���̃A�b�v�f�[�g
	void UpdatePolygon();

	// �ړ�����
	void Move();

	// �ړ�����
	void MoveLimit();

private:
	// �\���ʒu
	VECTOR	m_pos;
	// �ړ���
	VECTOR	m_vec;

	// �F
	VECTOR	m_color;

	// �O���t�B�b�N�n���h��
	int		m_handle;

	// ���݂��邩
	bool m_isExist;

	// ���̕\��
	VERTEX3D Vertex[6];

	// ��]
	VECTOR Angle;
};
