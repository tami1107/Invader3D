#include "Particle3D.h"


namespace
{
	// �T�C�Y
	constexpr float kGraphicSize = 0.7;
	// �d��	
	constexpr float kGravity = 0.2f;

	// �ǂ��܂ŉ��ɍs�����瑶�݂������̂�
	constexpr float kDeletePosY = -100.0f;
}

Particle3D::Particle3D() :
	m_pos(),
	m_vec(),
	m_modeleHandle(-1),
	m_isExist(false)
{

}

Particle3D::~Particle3D()
{
	// ���f���̍폜
	MV1DeleteModel(m_modeleHandle);
}




void Particle3D::update()
{
	if (!m_isExist)	return;


	// �ړ�����
	Move();

	// �p�[�e�B�N���̈ړ�����
	MoveLimit();

}

void Particle3D::draw()
{
	if (!m_isExist)	return;


	// ���f���̕`��
	MV1DrawModel(m_modeleHandle);


	// ���̕\��
	//DrawSphere3D(m_pos, kSize, 32, 0xffffff, GetColor(0, 0, 0), true);


}

void Particle3D::start(VECTOR pos, VECTOR color, float modeleScale, float alphaValue)
{
	m_isExist = true;
	m_pos = pos;

	// �R�c���f���̃X�P�[���ύX
	MV1SetScale(m_modeleHandle, VGet(modeleScale, modeleScale, modeleScale));

	m_vec.x = static_cast<float>(GetRand(10) - 5);
	m_vec.y = static_cast<float>(-GetRand(6));
	m_vec.z = static_cast<float>(GetRand(6));

	// �F�ݒ�
	MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(color.x, color.y, color.z, 1.0f));

	// �R�c���f���̕s�����x
	MV1SetOpacityRate(m_modeleHandle, alphaValue);
}




void Particle3D::Move()
{
	// �d�͂�^����
	m_vec.y -= kGravity;

	// �x�N�g���̉��Z
	m_pos = VAdd(m_pos, m_vec);

	// �ʒu�������f���ɓ����
	MV1SetPosition(m_modeleHandle, m_pos);
}

void Particle3D::MoveLimit()
{

	if (m_pos.y < kDeletePosY)
	{
		m_isExist = false;
	}
}
