#include "GameOver.h"
#include "Pad.h"
#include "SceneMain.h"

namespace
{
	// �Q�[���I�[�o�[�O���t�B�b�N�̑}��
	const char* const kGameOverGraphic = "data/gameOver.png";
}


GameOver::GameOver():
	m_graphic(-1),
	m_pSceneMain(nullptr)
{
}

GameOver::~GameOver()
{
	// �O���t�B�b�N�̍폜
	DeleteGraph(m_graphic);

	// �|�C���^�̍폜
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

}

void GameOver::init()
{
	// �O���t�B�b�N��}������
	m_graphic = LoadGraph(kGameOverGraphic);


}

void GameOver::update()
{
	// �Q�[���I�[�o�[�t���O��false����
	if (Pad::isTrigger(PAD_INPUT_10))
	{
		m_pSceneMain->getIsGameOverFlag(false);
		m_pSceneMain->getIsResetFlag(true);
	}
}

void GameOver::draw()
{

	// ��ʂ𔖈Â�����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);

	int x1 = 0;
	int y1 = 0;
	int x2 = Game::kScreenWidth;
	int y2 = Game::kScreenHeight;


	//DrawBox(x1, y1, x2, y2, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	VECTOR pos = VGet(0, 50, 0);

	// �Q�[���I�[�o�[�̃O���t�B�b�N�`��
	DrawBillboard3D(pos, 0.5, 0.5, 100.0, 0.0, m_graphic, true);


}
