#include "Bunker.h"
#include "SceneMain.h"

namespace
{
	// �����ʒu
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = 10.0f;


	// �ő�HP��
	constexpr int kMaxHp = 5;

	// ���f���̃X�P�[��
	constexpr float kModeleScale = 5.5f;


}

Bunker::Bunker():
	m_isExist(true),
	m_modeleHandle(-1),
	m_hp(0),
	m_number(),
	m_pos(),
	m_color(),
	m_pSceneMain(nullptr)
{
}

Bunker::~Bunker()
{
	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// �O���t�B�b�N�̍폜
	MV1DeleteModel(m_modeleHandle);
}

void Bunker::init(int savePosX)
{
	// ���݂��Ă���
	m_isExist = true;


	// �ʒu�̏�����
	m_pos = VGet(kInitPosX + savePosX, kInitPosY, kInitPosZ);

	// �ő�HP�ʂ���
	m_hp = kMaxHp;


	// �R�c���f���̃X�P�[���ύX
	MV1SetScale(m_modeleHandle, VGet(kModeleScale, kModeleScale, kModeleScale));

	// �ʒu�������f���ɓ����
	MV1SetPosition(m_modeleHandle, m_pos);

	// �R�c���f���̕s�����x
	MV1SetOpacityRate(m_modeleHandle, kAlphaValue);

	// �J���[����
	ColorProcess();
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

	
	// ���f���̕`��
	MV1DrawModel(m_modeleHandle);



#if true

	// ���̕\��
	DrawSphere3D(m_pos, kCircleSize, 32, 0x0000ff, GetColor(0, 0, 0), true);


#endif

}

void Bunker::DamegeProcess(int damages)
{
	// HP����_���[�W������
	m_hp -= damages;



	// �J���[����
	ColorProcess();


	// HP��0�̏ꍇ�A���݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;

		m_pSceneMain->CreateParticle3D(m_pos, m_color, kParticleValue, kAlphaValue, kParticleScale);
	}
}

void Bunker::Collision2D()
{
	// �g�[�`�J�ƃG�l�~�[�V���b�g�̂����蔻��
	m_pSceneMain->BunkerToInvertShotCollision();
	// �g�[�`�J�ƃv���C���[�V���b�g�̂����蔻��
	m_pSceneMain->BunkerToShotCollision();
}

void Bunker::ColorProcess()
{
	// �J���[����
	{
		float H = m_hp * (512.0f / kMaxHp) - 100;

		float R = min(max((384 - H), 0), 0xff);
		float G = min(max((H + 64), 0), 0xff);
		float B = max((H - 384), 0);



		float color[3] = { R ,G ,B };


		// collar�̒l�����߂�
		{
			// ����
			float ratio;

			// �p�[�Z���g������
			float percentage[3];

			// colorF������
			float colorF[3];

			for (int i = 0; i < 3; i++)
			{
				ratio = 100.0 * color[i];
				percentage[i] = ratio / 255;

				colorF[i] = percentage[i] * 0.01;
			}

			// �F���擾
			m_color = VGet(colorF[0], colorF[1], colorF[2]);
		}

		// �F�ݒ�
		MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));

	}
}
