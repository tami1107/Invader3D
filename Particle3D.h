#pragma once
#include "game.h"


class Particle3D
{
public:
	Particle3D();
	virtual ~Particle3D();


	void update();
	void draw();

	void start(VECTOR pos, VECTOR color, float modeleScale, float alphaValue);

	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }


	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_modeleHandle = handle; }

public:

	// �ړ�����
	void Move();

	// �ړ�����
	void MoveLimit();

private:
	// �\���ʒu
	VECTOR	m_pos;
	// �ړ���
	VECTOR	m_vec;


	// �O���t�B�b�N�n���h��
	int		m_modeleHandle;

	// ���݂��邩
	bool m_isExist;
};
