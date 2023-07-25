#include "Pause.h"
#include "Pad.h"
#include "game.h"
#include "SceneMain.h"
#include <cmath>


namespace
{


    // 文字フォント
    const char* const kTextFontName = "NULL";

    // 文字フォントサイズ
    constexpr int kTextFontSize = 40;


    // 画面の中心位置
    constexpr int kScreenCenterPositionX = Game::kScreenWidth / 2;
    constexpr int kScreenCenterPositionY = Game::kScreenHeight / 2;

    // ポーズ画面のサイズ
    constexpr int kPoseScreenSizeX = 500;
    constexpr int kPoseScreenSizeY = 300;

    // 項目の最大数
    constexpr int kSelectMaxNumber = 2;

    // 項目選択時の移動インターバルの最大値
    constexpr int kIntervalMaximumValue = 15;


    // テキスト初期位置
    constexpr int kModeInitialposX = 600;
    constexpr int kModeInitialposY = 330;

    // 2列目以降のY座標をずらす
    constexpr int kSlidePosY = 70;

    // テキストに影みたいな表現をするための差の値
    constexpr int kTextSlide = 3;


    // テキスト初期位置
    constexpr int kModeInitialposX2 = 550;
    constexpr int kModeInitialposY2 = 450;

    // 2列目以降のY座標をずらす
    constexpr int kSlidePosX = 170;







    // トライアングルの高さ
    constexpr float kHeight = 25.0f;

    // テキストの中心に位置を合わせる
    constexpr int kPosSet = kTextFontSize / 2;

    // トライアングルの幅
    constexpr int kTriangleWidth = 40;

    // トライアングルのテキストとの距離
    constexpr int kTextDistancePos = 20;

    // トライアングルの回転スピード
    constexpr float kTriangleRotSpeed = 0.1f;

}


// メニュー項目の表示に必要な構造体を用意する
typedef struct {
    int x, y;       // 座標格納用変数
    char name[128]; // 項目名格納用変数
    int Cr;			// カラー用変数
} MenuElement_p;

// メニュー項目要素を5つ作る
MenuElement_p MenuElement[kSelectMaxNumber] = {
    // タグの中身の順番で格納される。
    { kModeInitialposX, kModeInitialposY + (kSlidePosY * 0) , "ゲームを続ける" , 0xff0000},
    { kModeInitialposX, kModeInitialposY + (kSlidePosY * 1), "タイトルに戻る", 0xffffff}
};

// メニュー項目の表示に必要な構造体を用意する
typedef struct {
    int x, y;       // 座標格納用変数
    char name[128]; // 項目名格納用変数
    int Cr;			// カラー用変数
} MenuElement_p2;

// メニュー項目要素を5つ作る
MenuElement_p2 MenuElement2[kSelectMaxNumber] = {
    // タグの中身の順番で格納される。
    { kModeInitialposX2 + (kSlidePosX * 0), kModeInitialposY2 , "はい" , 0xff0000},
    { kModeInitialposX2 + (kSlidePosX * 1), kModeInitialposY2, "いいえ", 0xffffff}
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
    // クラスポインタの削除
    m_pSceneMain = nullptr;
    delete m_pSceneMain;


    // 作成したフォントデータを削除する
    DeleteFontToHandle(m_textFont);
    
}

void Pause::init()
{
	// ポーズしていないのでfalse
	m_isPause = false;

    // 選択番号の初期化
    m_selectNum = 0;

    // 項目選択時の移動インターバル
    m_selectInterval = 0;

    // サイン値の初期化
    sinRate = 0.0f;

    // タイトルに戻るフラグの初期化
    m_titleFlag = false;

    // 選択番号の初期化
    m_selectNum2 = 1;

    // フォントの挿入・設定
    m_textFont = CreateFontToHandle(kTextFontName, kTextFontSize, 3);

    // トライアングルの初期位置
    m_pos.x = (MenuElement[m_selectNum].x - kTextDistancePos);
    m_pos.y = MenuElement[m_selectNum].y;

}

void Pause::update()
{
	// ポーズ処理
	PauseProcess();

    // ポーズしてなかったらここで処理を終える
    if (!m_isPause)return;

    // 選択処理
    SelectProcess();
}

void Pause::draw()
{
    // ポーズしてなかったらここで処理を終える
    if (!m_isPause)return;

    // フレームの描画
    DrawFrame();

    // 項目テキストの表示
    DrawSelectText();

   

#if true
    DrawFormatString(0, 15 * 8, 0xff0000, "m_selectNum=%d", m_selectNum);
    DrawFormatString(0, 15 * 9, 0xff0000, "m_selectNum2=%d", m_selectNum2);
#endif
}

void Pause::PauseProcess()
{
    // ボタンを押したときポーズしてなかったらポーズにする
    if (Pad::isTrigger(PAD_INPUT_8))
    {

        if (m_isPause)
        {
            m_isPause = false;
        }
        else
        {
            // ポーズ音
            m_isPause = true;
        }
        // 変更した中身をSceneMainに送る
        m_pSceneMain->setIsPause(m_isPause);
    }
}

void Pause::SelectProcess()
{
    // 選択の移動インターバル処理
    {
        m_selectInterval--;
        if (m_selectInterval < 0)m_selectInterval = 0;
    }


    // タイトルに戻るが選択されていない場合の処理
    if (!m_titleFlag)
    {

    
        // 番号処理
        {
            if (m_selectInterval == 0)
            { 
                if (Pad::isPress(PAD_INPUT_UP))
                {
                    m_selectNum = (m_selectNum + (kSelectMaxNumber - 1)) % kSelectMaxNumber; // 現在の選択項目を一つ上にずらす(逆ループする)

                     // 現在選択されているテキストの位置を入れる
                    m_pos.y = MenuElement[m_selectNum].y;

                    // m_selectIntervalにkIntervalMaximumValueの値を代入することによって、m_selectIntervalの値が0になるまでm_selectNumberを変更できなくする
                    m_selectInterval = kIntervalMaximumValue;
                }
                if (Pad::isPress(PAD_INPUT_DOWN))
                {
                    m_selectNum = (m_selectNum + 1) % kSelectMaxNumber; // 現在の選択項目を一つ下にずらす(ループする)

                     // 現在選択されているテキストの位置を入れる
                    m_pos.y = MenuElement[m_selectNum].y;

                    // m_selectIntervalにkIntervalMaximumValueの値を代入することによって、m_selectIntervalの値が0になるまでm_selectNumberを変更できなくする
                    m_selectInterval = kIntervalMaximumValue;
                }

            
            }
        }


        // カラー処理
        for (int i = 0; i < kSelectMaxNumber; i++)
        {
            // メニュー項目数である4個ループ処理

            // 今処理しているのが、選択番号と同じ要素なら座標変更、色変更を行う
            if (i == m_selectNum)
            {
                MenuElement[i].Cr = 0xff0000;
            }
            // 今処理しているのが、選択番号と同じではない要素なら座標変更、色変更を行わない
            else
            {
                MenuElement[i].Cr = 0xffffff;
            }
        }



        // 選択した項目の処理
        {
            // 決定ボタンを押したとき
            if (Pad::isTrigger(PAD_INPUT_1))
            {
                switch (m_selectNum)
                {
                    // ポーズを解除する
                case 0:
                    // ポーズ
                    m_isPause = false;

                    // 変更した中身をSceneMainに送る
                    m_pSceneMain->setIsPause(m_isPause);

                    break;

                    // タイトルに戻る
                case 1:
           
                    // タイトルに戻るフラグをtrueにする
                    m_titleFlag = true;

                    // 現在選択されているテキストの位置を入れる
                    m_pos.x = (MenuElement2[m_selectNum].x - kTextDistancePos);
                    m_pos.y = MenuElement2[m_selectNum].y;
                    

                    break;
                }
            }
        }
    }
    else
    {

        // 番号処理
        {
            if (m_selectInterval == 0)
            {
                if (Pad::isPress(PAD_INPUT_RIGHT))
                {
                    m_selectNum2 = (m_selectNum2 + (kSelectMaxNumber - 1)) % kSelectMaxNumber; // 現在の選択項目を一つ上にずらす(逆ループする)

                    // 現在選択されているテキストの位置を入れる
                    m_pos.x = (MenuElement2[m_selectNum2].x - kTextDistancePos);
                    


                    // m_selectIntervalにkIntervalMaximumValueの値を代入することによって、m_selectIntervalの値が0になるまでm_selectNumberを変更できなくする
                    m_selectInterval = kIntervalMaximumValue;
                }
                if (Pad::isPress(PAD_INPUT_LEFT))
                {
                    m_selectNum2 = (m_selectNum2 + 1) % kSelectMaxNumber; // 現在の選択項目を一つ下にずらす(ループする)

                    // 現在選択されているテキストの位置を入れる
                    m_pos.x = (MenuElement2[m_selectNum2].x - kTextDistancePos);

                    // m_selectIntervalにkIntervalMaximumValueの値を代入することによって、m_selectIntervalの値が0になるまでm_selectNumberを変更できなくする
                    m_selectInterval = kIntervalMaximumValue;
                }
            }
        }


        // カラー処理
        for (int i = 0; i < kSelectMaxNumber; i++)
        {
            // メニュー項目数である4個ループ処理

            // 今処理しているのが、選択番号と同じ要素なら座標変更、色変更を行う
            if (i == m_selectNum2)
            {
                MenuElement2[i].Cr = 0xff0000;
            }
            // 今処理しているのが、選択番号と同じではない要素なら座標変更、色変更を行わない
            else
            {
                MenuElement2[i].Cr = 0xffffff;
            }
        }



        // 選択した項目の処理
        {
            // 決定ボタンを押したとき
            if (Pad::isTrigger(PAD_INPUT_1))
            {
                switch (m_selectNum2)
                {
                    // タイトルに戻る
                case 0:
                
                    m_pSceneMain->setIsTurnTitle(true);
                
                    break;

                    // ポーズ選択画面に戻る
                case 1:

                    // タイトルに戻るフラグをfalseにする
                    m_titleFlag = false;

                    // 現在選択されているテキストの位置を入れる
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
    int LeftX = kScreenCenterPositionX - kPoseScreenSizeX;	    // ポーズ画面の左辺の X 座標
    int RightX = kScreenCenterPositionX + kPoseScreenSizeX;		// ポーズ画面の右辺の X 座標

    int TopY = kScreenCenterPositionY - kPoseScreenSizeY;	    // ポーズ画面の上辺の Y 座標
    int BottomY = kScreenCenterPositionY + kPoseScreenSizeY;	// ポーズ画面の下辺の Y 座標


    // ポーズウィンドウセロファン(黒い)
    SetDrawBlendMode(DX_BLENDMODE_MULA, 100);

    // 全体的に暗くする
    DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight,
        0x000000, true);


    // ポーズ画面の描画
    DrawBox(LeftX, TopY, RightX, BottomY,
        0x000000, true);

    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // ポーズ画面の描画
    DrawBox(LeftX, TopY, RightX, BottomY,
        0xffffff, false);


    // タイトルに戻るが選択されていなかったらここで処理を終了する
    if (!m_titleFlag)return;

    // タイトルに戻るに戻るが選択されたときの処理
    TitleSelectProcess();

}



void Pause::DrawSelectText()
{
    sinRate += kTriangleRotSpeed;

   
    {
        int cursorHeight = sinf(sinRate) * kHeight;	// 実際にはHeight/2
        DrawTriangle((m_pos.x - kTriangleWidth) + kTriangleWidth, m_pos.y + kPosSet,
            m_pos.x - kTriangleWidth, m_pos.y + kPosSet - cursorHeight,
            m_pos.x - kTriangleWidth, m_pos.y + kPosSet + cursorHeight, 0xff0000, true);


        DrawTriangle((m_pos.x - kTriangleWidth) + kTriangleWidth, m_pos.y + kPosSet,
            m_pos.x - kTriangleWidth, m_pos.y + kPosSet - cursorHeight,
            m_pos.x - kTriangleWidth, m_pos.y + kPosSet + cursorHeight, 0xffffff, false);
    }


    // 項目テキストの表示
    for (int i = 0; i < kSelectMaxNumber; i++)
    {
        // 半透明にする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

        // 二重に見せる
        DrawFormatStringToHandle(MenuElement[i].x + kTextSlide, MenuElement[i].y+ kTextSlide, 
            0x696969,m_textFont, MenuElement[i].name);

        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


        DrawFormatStringToHandle(MenuElement[i].x, MenuElement[i].y, MenuElement[i].Cr,
            m_textFont, MenuElement[i].name);

    }

}

void Pause::TitleSelectProcess()
{



    int LeftX2 = kScreenCenterPositionX - kPoseScreenSizeX;	    // ポーズ画面の左辺の X 座標
    int RightX2 = kScreenCenterPositionX + kPoseScreenSizeX;		// ポーズ画面の右辺の X 座標

    int TopY2 = kScreenCenterPositionY - kPoseScreenSizeY;	    // ポーズ画面の上辺の Y 座標
    int BottomY2 = kScreenCenterPositionY + kPoseScreenSizeY;	// ポーズ画面の下辺の Y 座標


    // ポーズウィンドウセロファン(黒い)
    SetDrawBlendMode(DX_BLENDMODE_MULA, 100);


    // ポーズ画面の描画
    DrawBox(LeftX2, TopY2, RightX2, BottomY2,
        0x000000, true);

    // 描画ブレンドモードをノーブレンドにする
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // ポーズ画面の描画
    DrawBox(LeftX2, TopY2, RightX2, BottomY2,
        0xff0000, false);





    // 項目テキストの表示
    for (int i = 0; i < kSelectMaxNumber; i++)
    {
        // 半透明にする
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

        // 二重に見せる
        DrawFormatStringToHandle(MenuElement2[i].x + kTextSlide, MenuElement2[i].y + kTextSlide,
            0x696969, m_textFont, MenuElement2[i].name);

        // 描画ブレンドモードをノーブレンドにする
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


        DrawFormatStringToHandle(MenuElement2[i].x, MenuElement2[i].y, MenuElement2[i].Cr,
            m_textFont, MenuElement2[i].name);

    }


}
