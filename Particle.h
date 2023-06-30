#pragma once
#include "game.h"

class Particle
{
public:
	Particle();
	virtual ~Particle();

	void init();
	void end();

	void update();
	void draw();

	void start(VECTOR pos, int color);

	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }


	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) {m_handle= handle; }

private:
	// �\���ʒu
	VECTOR	m_pos;
	// �ړ���
	VECTOR	m_vec;

	// �F
	int		m_color;

	// �O���t�B�b�N�n���h��
	int		m_handle;

	// ���݂��邩
	bool m_isExist;
};
