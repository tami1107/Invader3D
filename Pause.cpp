#include "Pause.h"
#include "Pad.h"
#include "game.h"
#include "SceneMain.h"
#include <cmath>


namespace
{


    // �����t�H���g
    const char* const kTextFontName = "NULL";

    // �����t�H���g�T�C�Y
    constexpr int kTextFontSize = 40;


    // ��ʂ̒��S�ʒu
    constexpr int kScreenCenterPositionX = Game::kScreenWidth / 2;
    constexpr int kScreenCenterPositionY = Game::kScreenHeight / 2;

    // �|�[�Y��ʂ̃T�C�Y
    constexpr int kPoseScreenSizeX = 500;
    constexpr int kPoseScreenSizeY = 300;

    // ���ڂ̍ő吔
    constexpr int kSelectMaxNumber = 2;

    // ���ڑI�����̈ړ��C���^�[�o���̍ő�l
    constexpr int kIntervalMaximumValue = 15;


    // �e�L�X�g�����ʒu
    constexpr int kModeInitialposX = 600;
    constexpr int kModeInitialposY = 330;

    // 2��ڈȍ~��Y���W�����炷
    constexpr int kSlidePosY = 70;

    // �e�L�X�g�ɉe�݂����ȕ\�������邽�߂̍��̒l
    constexpr int kTextSlide = 3;


    // �e�L�X�g�����ʒu
    constexpr int kModeInitialposX2 = 550;
    constexpr int kModeInitialposY2 = 450;

    // 2��ڈȍ~��Y���W�����炷
    constexpr int kSlidePosX = 170;







    // �g���C�A���O���̍���
    constexpr float kHeight = 25.0f;

    // �e�L�X�g�̒��S�Ɉʒu�����킹��
    constexpr int kPosSet = kTextFontSize / 2;

    // �g���C�A���O���̕�
    constexpr int kTriangleWidth = 40;

    // �g���C�A���O���̃e�L�X�g�Ƃ̋���
    constexpr int kTextDistancePos = 20;

    // �g���C�A���O���̉�]�X�s�[�h
    constexpr float kTriangleRotSpeed = 0.1f;

}


// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct {
    int x, y;       // ���W�i�[�p�ϐ�
    char name[128]; // ���ږ��i�[�p�ϐ�
    int Cr;			// �J���[�p�ϐ�
} MenuElement_p;

// ���j���[���ڗv�f��5���
MenuElement_p MenuElement[kSelectMaxNumber] = {
    // �^�O�̒��g�̏��ԂŊi�[�����B
    { kModeInitialposX, kModeInitialposY + (kSlidePosY * 0) , "�Q�[���𑱂���" , 0xff0000},
    { kModeInitialposX, kModeInitialposY + (kSlidePosY * 1), "�^�C�g���ɖ߂�", 0xffffff}
};

// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct {
    int x, y;       // ���W�i�[�p�ϐ�
    char name[128]; // ���ږ��i�[�p�ϐ�
    int Cr;			// �J���[�p�ϐ�
} MenuElement_p2;

// ���j���[���ڗv�f��5���
MenuElement_p2 MenuElement2[kSelectMaxNumber] = {
    // �^�O�̒��g�̏��ԂŊi�[�����B
    { kModeInitialposX2 + (kSlidePosX * 0), kModeInitialposY2 , "�͂�" , 0xff0000},
    { kModeInitialposX2 + (kSlidePosX * 1), kModeInitialposY2, "������", 0xffffff}
};





Pause::Pause():
	m_isPause(false),
    m_selectNum(0),
    m_selectInterval(0),
    m_textFont(-1),
    sinRate(0.0f),
    m_titleFlag(false),
    m_selectNum2(0),
    m_pos(Vec2()),
    m_pSceneMain(nullptr)
{
}

Pause::~Pause()
{
    // �N���X�|�C���^�̍폜
    m_pSceneMain = nullptr;
    delete m_pSceneMain;


    // �쐬�����t�H���g�f�[�^���폜����
    DeleteFontToHandle(m_textFont);
    
}

void Pause::init()
{
	// �|�[�Y���Ă��Ȃ��̂�false
	m_isPause = false;

    // �I��ԍ��̏�����
    m_selectNum = 0;

    // ���ڑI�����̈ړ��C���^�[�o��
    m_selectInterval = 0;

    // �T�C���l�̏�����
    sinRate = 0.0f;

    // �^�C�g���ɖ߂�t���O�̏�����
    m_titleFlag = false;

    // �I��ԍ��̏�����
    m_selectNum2 = 1;

    // �t�H���g�̑}���E�ݒ�
    m_textFont = CreateFontToHandle(kTextFontName, kTextFontSize, 3);

    // �g���C�A���O���̏����ʒu
    m_pos.x = (MenuElement[m_selectNum].x - kTextDistancePos);
    m_pos.y = MenuElement[m_selectNum].y;

}

void Pause::update()
{
	// �|�[�Y����
	PauseProcess();

    // �|�[�Y���ĂȂ������炱���ŏ������I����
    if (!m_isPause)return;

    // �I������
    SelectProcess();
}

void Pause::draw()
{
    // �|�[�Y���ĂȂ������炱���ŏ������I����
    if (!m_isPause)return;

    // �t���[���̕`��
    DrawFrame();

    // ���ڃe�L�X�g�̕\��
    DrawSelectText();

   

#if true
    DrawFormatString(0, 15 * 8, 0xff0000, "m_selectNum=%d", m_selectNum);
    DrawFormatString(0, 15 * 9, 0xff0000, "m_selectNum2=%d", m_selectNum2);
#endif
}

void Pause::PauseProcess()
{
    // �{�^�����������Ƃ��|�[�Y���ĂȂ�������|�[�Y�ɂ���
    if (Pad::isTrigger(PAD_INPUT_8))
    {

        if (m_isPause)
        {
            m_isPause = false;
        }
        else
        {
            // �|�[�Y��
            m_isPause = true;
        }
        // �ύX�������g��SceneMain�ɑ���
        m_pSceneMain->setIsPause(m_isPause);
    }
}

void Pause::SelectProcess()
{
    // �I���̈ړ��C���^�[�o������
    {
        m_selectInterval--;
        if (m_selectInterval < 0)m_selectInterval = 0;
    }


    // �^�C�g���ɖ߂邪�I������Ă��Ȃ��ꍇ�̏���
    if (!m_titleFlag)
    {

    
        // �ԍ�����
        {
            if (m_selectInterval == 0)
            { 
                if (Pad::isPress(PAD_INPUT_UP))
                {
                    m_selectNum = (m_selectNum + (kSelectMaxNumber - 1)) % kSelectMaxNumber; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)

                     // ���ݑI������Ă���e�L�X�g�̈ʒu������
                    m_pos.y = MenuElement[m_selectNum].y;

                    // m_selectInterval��kIntervalMaximumValue�̒l�������邱�Ƃɂ���āAm_selectInterval�̒l��0�ɂȂ�܂�m_selectNumber��ύX�ł��Ȃ�����
                    m_selectInterval = kIntervalMaximumValue;
                }
                if (Pad::isPress(PAD_INPUT_DOWN))
                {
                    m_selectNum = (m_selectNum + 1) % kSelectMaxNumber; // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)

                     // ���ݑI������Ă���e�L�X�g�̈ʒu������
                    m_pos.y = MenuElement[m_selectNum].y;

                    // m_selectInterval��kIntervalMaximumValue�̒l�������邱�Ƃɂ���āAm_selectInterval�̒l��0�ɂȂ�܂�m_selectNumber��ύX�ł��Ȃ�����
                    m_selectInterval = kIntervalMaximumValue;
                }

            
            }
        }


        // �J���[����
        for (int i = 0; i < kSelectMaxNumber; i++)
        {
            // ���j���[���ڐ��ł���4���[�v����

            // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ���W�ύX�A�F�ύX���s��
            if (i == m_selectNum)
            {
                MenuElement[i].Cr = 0xff0000;
            }
            // ���������Ă���̂��A�I��ԍ��Ɠ����ł͂Ȃ��v�f�Ȃ���W�ύX�A�F�ύX���s��Ȃ�
            else
            {
                MenuElement[i].Cr = 0xffffff;
            }
        }



        // �I���������ڂ̏���
        {
            // ����{�^�����������Ƃ�
            if (Pad::isTrigger(PAD_INPUT_1))
            {
                switch (m_selectNum)
                {
                    // �|�[�Y����������
                case 0:
                    // �|�[�Y
                    m_isPause = false;

                    // �ύX�������g��SceneMain�ɑ���
                    m_pSceneMain->setIsPause(m_isPause);

                    break;

                    // �^�C�g���ɖ߂�
                case 1:
           
                    // �^�C�g���ɖ߂�t���O��true�ɂ���
                    m_titleFlag = true;

                    // ���ݑI������Ă���e�L�X�g�̈ʒu������
                    m_pos.x = (MenuElement2[m_selectNum].x - kTextDistancePos);
                    m_pos.y = MenuElement2[m_selectNum].y;
                    

                    break;
                }
            }
        }
    }
    else
    {

        // �ԍ�����
        {
            if (m_selectInterval == 0)
            {
                if (Pad::isPress(PAD_INPUT_RIGHT))
                {
                    m_selectNum2 = (m_selectNum2 + (kSelectMaxNumber - 1)) % kSelectMaxNumber; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)

                    // ���ݑI������Ă���e�L�X�g�̈ʒu������
                    m_pos.x = (MenuElement2[m_selectNum2].x - kTextDistancePos);
                    


                    // m_selectInterval��kIntervalMaximumValue�̒l�������邱�Ƃɂ���āAm_selectInterval�̒l��0�ɂȂ�܂�m_selectNumber��ύX�ł��Ȃ�����
                    m_selectInterval = kIntervalMaximumValue;
                }
                if (Pad::isPress(PAD_INPUT_LEFT))
                {
                    m_selectNum2 = (m_selectNum2 + 1) % kSelectMaxNumber; // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)

                    // ���ݑI������Ă���e�L�X�g�̈ʒu������
                    m_pos.x = (MenuElement2[m_selectNum2].x - kTextDistancePos);

                    // m_selectInterval��kIntervalMaximumValue�̒l�������邱�Ƃɂ���āAm_selectInterval�̒l��0�ɂȂ�܂�m_selectNumber��ύX�ł��Ȃ�����
                    m_selectInterval = kIntervalMaximumValue;
                }
            }
        }


        // �J���[����
        for (int i = 0; i < kSelectMaxNumber; i++)
        {
            // ���j���[���ڐ��ł���4���[�v����

            // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ���W�ύX�A�F�ύX���s��
            if (i == m_selectNum2)
            {
                MenuElement2[i].Cr = 0xff0000;
            }
            // ���������Ă���̂��A�I��ԍ��Ɠ����ł͂Ȃ��v�f�Ȃ���W�ύX�A�F�ύX���s��Ȃ�
            else
            {
                MenuElement2[i].Cr = 0xffffff;
            }
        }



        // �I���������ڂ̏���
        {
            // ����{�^�����������Ƃ�
            if (Pad::isTrigger(PAD_INPUT_1))
            {
                switch (m_selectNum2)
                {
                    // �^�C�g���ɖ߂�
                case 0:
                
                    m_pSceneMain->setIsTurnTitle(true);
                
                    break;

                    // �|�[�Y�I����ʂɖ߂�
                case 1:

                    // �^�C�g���ɖ߂�t���O��false�ɂ���
                    m_titleFlag = false;

                    // ���ݑI������Ă���e�L�X�g�̈ʒu������
                    m_pos.x = (MenuElement[m_selectNum].x - kTextDistancePos);
                    m_pos.y = MenuElement[m_selectNum].y;

                    break;
                }
            }
        }
    }

}

void Pause::DrawFrame()
{
    int LeftX = kScreenCenterPositionX - kPoseScreenSizeX;	    // �|�[�Y��ʂ̍��ӂ� X ���W
    int RightX = kScreenCenterPositionX + kPoseScreenSizeX;		// �|�[�Y��ʂ̉E�ӂ� X ���W

    int TopY = kScreenCenterPositionY - kPoseScreenSizeY;	    // �|�[�Y��ʂ̏�ӂ� Y ���W
    int BottomY = kScreenCenterPositionY + kPoseScreenSizeY;	// �|�[�Y��ʂ̉��ӂ� Y ���W


    // �|�[�Y�E�B���h�E�Z���t�@��(����)
    SetDrawBlendMode(DX_BLENDMODE_MULA, 100);

    // �S�̓I�ɈÂ�����
    DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight,
        0x000000, true);


    // �|�[�Y��ʂ̕`��
    DrawBox(LeftX, TopY, RightX, BottomY,
        0x000000, true);

    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // �|�[�Y��ʂ̕`��
    DrawBox(LeftX, TopY, RightX, BottomY,
        0xffffff, false);


    // �^�C�g���ɖ߂邪�I������Ă��Ȃ������炱���ŏ������I������
    if (!m_titleFlag)return;

    // �^�C�g���ɖ߂�ɖ߂邪�I�����ꂽ�Ƃ��̏���
    TitleSelectProcess();

}



void Pause::DrawSelectText()
{
    sinRate += kTriangleRotSpeed;

   
    {
        int cursorHeight = sinf(sinRate) * kHeight;	// ���ۂɂ�Height/2
        DrawTriangle((m_pos.x - kTriangleWidth) + kTriangleWidth, m_pos.y + kPosSet,
            m_pos.x - kTriangleWidth, m_pos.y + kPosSet - cursorHeight,
            m_pos.x - kTriangleWidth, m_pos.y + kPosSet + cursorHeight, 0xff0000, true);


        DrawTriangle((m_pos.x - kTriangleWidth) + kTriangleWidth, m_pos.y + kPosSet,
            m_pos.x - kTriangleWidth, m_pos.y + kPosSet - cursorHeight,
            m_pos.x - kTriangleWidth, m_pos.y + kPosSet + cursorHeight, 0xffffff, false);
    }


    // ���ڃe�L�X�g�̕\��
    for (int i = 0; i < kSelectMaxNumber; i++)
    {
        // �������ɂ���
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

        // ��d�Ɍ�����
        DrawFormatStringToHandle(MenuElement[i].x + kTextSlide, MenuElement[i].y+ kTextSlide, 
            0x696969,m_textFont, MenuElement[i].name);

        // �`��u�����h���[�h���m�[�u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


        DrawFormatStringToHandle(MenuElement[i].x, MenuElement[i].y, MenuElement[i].Cr,
            m_textFont, MenuElement[i].name);

    }

}

void Pause::TitleSelectProcess()
{



    int LeftX2 = kScreenCenterPositionX - kPoseScreenSizeX;	    // �|�[�Y��ʂ̍��ӂ� X ���W
    int RightX2 = kScreenCenterPositionX + kPoseScreenSizeX;		// �|�[�Y��ʂ̉E�ӂ� X ���W

    int TopY2 = kScreenCenterPositionY - kPoseScreenSizeY;	    // �|�[�Y��ʂ̏�ӂ� Y ���W
    int BottomY2 = kScreenCenterPositionY + kPoseScreenSizeY;	// �|�[�Y��ʂ̉��ӂ� Y ���W


    // �|�[�Y�E�B���h�E�Z���t�@��(����)
    SetDrawBlendMode(DX_BLENDMODE_MULA, 100);


    // �|�[�Y��ʂ̕`��
    DrawBox(LeftX2, TopY2, RightX2, BottomY2,
        0x000000, true);

    // �`��u�����h���[�h���m�[�u�����h�ɂ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // �|�[�Y��ʂ̕`��
    DrawBox(LeftX2, TopY2, RightX2, BottomY2,
        0xff0000, false);





    // ���ڃe�L�X�g�̕\��
    for (int i = 0; i < kSelectMaxNumber; i++)
    {
        // �������ɂ���
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

        // ��d�Ɍ�����
        DrawFormatStringToHandle(MenuElement2[i].x + kTextSlide, MenuElement2[i].y + kTextSlide,
            0x696969, m_textFont, MenuElement2[i].name);

        // �`��u�����h���[�h���m�[�u�����h�ɂ���
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


        DrawFormatStringToHandle(MenuElement2[i].x, MenuElement2[i].y, MenuElement2[i].Cr,
            m_textFont, MenuElement2[i].name);

    }


}
