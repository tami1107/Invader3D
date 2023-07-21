#include "Particle.h"
#include "game.h"

namespace
{
	// �T�C�Y
	constexpr float kGraphicSize = 0.7;
	// �d��	
	constexpr float kGravity = 0.2f;

	// �ǂ��܂ŉ��ɍs�����瑶�݂������̂�
	constexpr float kDeletePosY = -100.0f;
}

Particle::Particle() :
	m_pos(),
	m_vec(),
	m_color(),
	m_handle(-1),
	m_isExist(false)
{	
	// �|���S���̏����ݒ�
	InitPolygon();
}

Particle::~Particle()
{
	// �O���t�B�b�N�̍폜
	DeleteGraph(m_handle);
}


void Particle::update()
{
	if (!m_isExist)	return;

	 
	// �|���S���̃A�b�v�f�[�g����
	UpdatePolygon();

	// �ړ�����
	Move();

	// �p�[�e�B�N���̈ړ�����
	MoveLimit();

}

void Particle::draw()
{
	if (!m_isExist)	return;
	

	MATERIALPARAM Material;

	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(m_color.x, m_color.y, m_color.z, 0.0f);
	Material.Power = 20.0f;

	SetMaterialParam(Material);

	// �Q�|���S���̕`��
	DrawPolygon3D(Vertex, 2, m_handle, true);


	// ���̕\��
	//DrawSphere3D(m_pos, kSize, 32, 0xffffff, GetColor(0, 0, 0), true);

	// �摜�`��
	//DrawBillboard3D(m_pos, 0.5, 0.5, kGraphicSize, 0.0, m_handle, true);

}

void Particle::start(VECTOR pos, VECTOR color)
{
	m_isExist = true;
	m_pos = pos;

	
	m_vec.x = static_cast<float>(GetRand(6) - 3);
	m_vec.y = static_cast<float>(GetRand(3)-1);
	m_vec.z = static_cast<float>(GetRand(6));

	m_color = color;
}

void Particle::InitPolygon()
{

	// �Q�|���S�����̒��_�̍��W�Ɩ@���ȊO�̃f�[�^���Z�b�g
	Vertex[0].dif = GetColorU8(0, 0, 0, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].dif = GetColorU8(0, 0, 0, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].dif = GetColorU8(0, 0, 0, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].dif = GetColorU8(0, 0, 0, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4] = Vertex[2];
	Vertex[5] = Vertex[1];

	// ��]�p�����[�^��������
	Angle.x = 0.0f;
	Angle.y = 0.0f;
	Angle.z = 0.0f;

}

void Particle::UpdatePolygon()
{
	MATRIX TransformMatrix;

	// ��]( x, y, z����]�̏� )�{���W�ړ��s��̍쐬
	TransformMatrix = MGetRotX(Angle.x);
	TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
	TransformMatrix = MMult(TransformMatrix, MGetRotZ(Angle.z));
	TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(0.0f, 0.0f, 0.0f)));

	// �s����g���ă��[���h���W���Z�o
	Vertex[0].pos = VTransform(VGet(m_pos.x + -kGraphicSize, m_pos.y + kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[1].pos = VTransform(VGet(m_pos.x + kGraphicSize, m_pos.y + kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[2].pos = VTransform(VGet(m_pos.x + -kGraphicSize, m_pos.y + -kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[3].pos = VTransform(VGet(m_pos.x + kGraphicSize, m_pos.y + -kGraphicSize, m_pos.z), TransformMatrix);

	Vertex[4].pos = Vertex[2].pos;
	Vertex[5].pos = Vertex[1].pos;

	// �s����g���Ė@�����Z�o
	Vertex[2].norm = Vertex[0].norm;
	Vertex[3].norm = Vertex[0].norm;
	Vertex[4].norm = Vertex[0].norm;
	Vertex[5].norm = Vertex[0].norm;

}

void Particle::Move()
{
	// �d�͂�^����
	m_vec.y -= kGravity;

	// �x�N�g���̉��Z
	m_pos = VAdd(m_pos, m_vec);

}

void Particle::MoveLimit()
{

	if (m_pos.y < kDeletePosY)
	{
		m_isExist = false;
	}
}
