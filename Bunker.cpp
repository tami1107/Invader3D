#include "bunker.h"
#include "SceneMain.h"

namespace
{
	// �����ʒu
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = 10.0f;


	// �ő�HP��
	constexpr int kMaxHp = 5;
}

Bunker::Bunker():
	m_isExist(true),
	m_hp(0),
	m_alphaValue(0),
	m_alphaValueDecrement(0),
	m_pos(),
	m_pSceneMain(nullptr)
{
}

Bunker::~Bunker()
{
	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;
}

void Bunker::init(int savePosX, int savePosY)
{
	// ���݂��Ă���
	m_isExist = true;


	// �ʒu�̏�����
	m_pos = VGet(kInitPosX + savePosX, kInitPosY + savePosY, kInitPosZ);

	// �ő�HP�ʂ���
	m_hp = kMaxHp;

	// �A���t�@�u�����h�̍ő�l����
	m_alphaValue = 255;

	// �A���t�@�u�����h�̌����l����
	m_alphaValueDecrement = m_alphaValue / kMaxHp;
}

void Bunker::update()
{
	if (!m_isExist)return;

	// �����蔻�菈��
	Collision2D();
}

void Bunker::draw()
{
	if (!m_isExist)return;

	// �_���[�W���󂯂邽�тɔ�������
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alphaValue);
	// ���̕\��
	DrawSphere3D(m_pos, kCircleSize, 32, 0x0000ff, GetColor(0, 0, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Bunker::DamegeProcess(int damages)
{
	// HP����_���[�W������
	m_hp -= damages;

	// �A���t�@�u�����h������
	m_alphaValue -= m_alphaValueDecrement;

	// HP��0�̏ꍇ�A���݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}

void Bunker::Collision2D()
{
	// �g�[�`�J�ƃG�l�~�[�V���b�g�̂����蔻��
	m_pSceneMain->BunkerToInvertShotCollision();
	// �g�[�`�J�ƃv���C���[�V���b�g�̂����蔻��
	m_pSceneMain->BunkerToShotCollision();
}
