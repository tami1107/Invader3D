#include "MainUI.h"
#include "game.h"
#include "SceneMain.h"
#include "Player.h"
#include <math.h>

namespace
{
	// 空ハートのグラフィックのファイル名
	const char* const kEmptyHeartGraphicFileName = "data/emptyHeart.png";
	// ハートのグラフィックのファイル名
	const char* const kHeartGraphicFileName = "data/heart.png";
	// 文字フォント
	const char* const kTextFontName = "ベストテン-CRT";

	// 文字グラフィックハンドル
	const char* const kTextGraphicFileName = "data/levelUp.png";

	// ダメージグラフィックハンドル
	const char* const kDamageGraphicFileName = "data/damage.png";

	// 文字フォントサイズ
	constexpr int kTextFontSize = 30;

	// 文字グラフィックサイズ
	constexpr float kTextGraphicSize = 1.0;


	// スコアテキスト位置
	constexpr int kScoreTextPosX = 10;
	constexpr int kScoreTextPosY = 10;

	// スコア位置（テキストからの距離）
	constexpr int kTextDistance = 120;
	
	// スコアの文字距離
	constexpr int kScoreDistance = 30;

	// グラフィックのサイズ
	constexpr float kGraphicSize = 0.6;


	// テキストグラフィック位置
	constexpr int kTextGraphicPosX = -400;
	constexpr int kTextGraphicPosY = Game::kScreenHeight * 0.5;

	// テキストを止める時間
	constexpr int kTextStopCount = 50;

	// テキストの移動スピード
	constexpr int kTextMoveSpeed = 30;

	// テキストの画面外位置
	constexpr int kTextGraphicOutPosX = Game::kScreenWidth + 50;


	// ライフテキスト位置
	constexpr int kLifeTextPosX = 10;
	constexpr int kLifeTextPosY = 50;

	// ライフ位置
	constexpr int kGraphicPosX = 140;
	constexpr int kGraphicPosY = 70;


	// グラフィック同士の距離
	constexpr int kGraphicDistance = 50;


	// エネミーレベルテキスト位置
	constexpr int kLevelTextPosX = 10;
	constexpr int kLevelTextPosY = 90;

	// エネミーレベル位置（テキストからの距離）
	constexpr int kLevelDistance = 120;


	// グラフィックファイル名
	const char* const kTimerGraphicFileName = "data/test.png";


	// 残像の数
	constexpr int kAfterimageNum = 5;

	// 残像の値
	constexpr float kAfterimageValue = 0.2;

	// 残像の透明度
	constexpr int kAfterimageAlpha = 100;

	// タイマーグラフィックサイズ
	constexpr float kTimerGraphicSize = 1.0;

	// HPの透明度
	constexpr int kAlpha = 255;


	// 文字の振れ幅
	constexpr float kSinValue = 255.0f;

	// 文字のサインカーブのスピード
	constexpr float kSinSpeedValue = 0.03f;
}


MainUI::MainUI() :
	m_fontHandle(-1),
	m_playerHp(0),
	m_enemyLv(0),
	m_score(0),
	m_textHandle(-1),
	m_textPos(Vec2()),
	m_isTextMove(false),
	m_textStopCount(0),
	m_timer(0),
	m_percentage(0),
	m_damageHandle(-1),
	m_sin(0.0f)
{

	for (auto& handle : m_graphicHandle)
	{
		handle = -1;
	}
	for (auto& handle : m_timerHandle)
	{
		handle = -1;
	}

	for (auto& score : m_scoreNum)
	{
		score = 0;
	}
}

MainUI::~MainUI()
{

	// グラフィックの削除
	for (auto& handle : m_graphicHandle)
	{
		DeleteGraph(handle);
	}
	for (auto& handle : m_timerHandle)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_textHandle);
	DeleteGraph(m_damageHandle);


	// 作成したフォントデータを削除する
	DeleteFontToHandle(m_fontHandle);
}

void MainUI::init()
{

	// グラフィックの挿入
	m_graphicHandle[0] = LoadGraph(kEmptyHeartGraphicFileName);
	m_graphicHandle[1] = LoadGraph(kHeartGraphicFileName);
	m_textHandle = LoadGraph(kTextGraphicFileName);
	m_damageHandle = LoadGraph(kDamageGraphicFileName);

	int W = 0;// グラフィックの横幅
	int H = 0;// グラフィックの縦幅
	int G = 0;// グラフィックの代入


	// グラフィックサイズを取得
	{
		G = LoadGraph(kTimerGraphicFileName);
		GetGraphSize(G, &W, &H);
	}

	LoadDivGraph(kTimerGraphicFileName, kGraphicDivNum,
		kGraphicDivX, kGraphicDivY,
		W / kGraphicDivX, H / kGraphicDivY, m_timerHandle);





	// フォントの挿入・設定
	m_fontHandle = CreateFontToHandle(kTextFontName, kTextFontSize, 3);

	// テキストの表示位置
	m_textPos = Vec2(kTextGraphicPosX, kTextGraphicPosY);
	// テキストストップカウント
	m_textStopCount = kTextStopCount;


	// プレイヤーのHP
	m_playerHp = SceneMain::kPlayerRemaining;
	// エネミーのレベル
	m_enemyLv = 0;
	// スコア
	m_score = 0;


	// タイマーに最大秒数を代入
	m_timer = Player::kPowerUpMaxNum;
}

void MainUI::update()
{


	// テキスト処理
	TextProcess();



}

void MainUI::draw()
{






	// ライフ
	{
		// テキストをずらす値
		int slide = 2;

		// ライフテキスト(影)
		DrawStringToHandle(kLifeTextPosX + slide, kLifeTextPosY + slide, "LIFE :",
			0x696969, m_fontHandle);

		// ライフテキスト
		DrawStringToHandle(kLifeTextPosX, kLifeTextPosY, "LIFE :",
			0xffffff, m_fontHandle);


		for (int i = 0; i < SceneMain::kPlayerRemaining; i++)
		{
			DrawRotaGraph(kGraphicPosX + (kGraphicDistance * i), kGraphicPosY,
				kGraphicSize, 0.0, m_graphicHandle[0], true);
		}

		for (int i = 0; i < m_playerHp; i++)
		{
			DrawRotaGraph(kGraphicPosX + (kGraphicDistance * i), kGraphicPosY,
				kGraphicSize, 0.0, m_graphicHandle[1], true);
		}
	}




	// スコア
	{
		// テキストをずらす値
		int slide = 2;

		// スコアテキスト(影)
		DrawStringToHandle(kScoreTextPosX+ slide, kScoreTextPosY+ slide, "SCORE:",
			0x696969, m_fontHandle);

		// スコアテキスト
		DrawStringToHandle(kScoreTextPosX, kScoreTextPosY, "SCORE:",
			0xffffff, m_fontHandle);


		for (int i = 0; i < kScoreMaxNum; i++)
		{
			// スコア表示（影）
			DrawFormatStringToHandle((kScoreTextPosX + kTextDistance) + (kScoreDistance * i) + slide, kScoreTextPosY + slide,
				0x696969, m_fontHandle, "%d", m_scoreNum[i]);

			// スコア表示
			DrawFormatStringToHandle((kScoreTextPosX + kTextDistance) + (kScoreDistance * i), kScoreTextPosY,
				0xffffff, m_fontHandle, "%d", m_scoreNum[i]);
		}
	}



	// エネミーレベル
	{
		// テキストをずらす値
		int slide = 2;

		// レベルの表示（影）
		DrawFormatStringToHandle(kLevelTextPosX + slide, kLevelTextPosY + slide,
			0x696969, m_fontHandle, "LEVEL: %d", m_enemyLv);


		// レベルの表示
		DrawFormatStringToHandle(kLevelTextPosX, kLevelTextPosY,
			0xffffff, m_fontHandle, "LEVEL: %d", m_enemyLv);
	}

	// ダメージ処理
	DamageProcess();





#if false

	// プレイヤーのHpの描画
	DrawFormatString(0, 15 * 2, 0xffffff, "playerHp : %d", m_playerHp);
	// スコア
	DrawFormatString(0, 15 * 4, 0xffffff, "score : %d", m_score);
	// エネミーのレベルの描画
	DrawFormatString(0, 15 * 3, 0xffffff, "enemyLv : %d", m_enemyLv);


	DrawFormatString(0, 15 * 13, 0xffffff, "1の位:%d", m_scoreNum[3]);
	DrawFormatString(0, 15 * 14, 0xffffff, "10の位:%d", m_scoreNum[2]);
	DrawFormatString(0, 15 * 15, 0xffffff, "100の位:%d", m_scoreNum[1]);
	DrawFormatString(0, 15 * 16, 0xffffff, "1000の位:%d", m_scoreNum[0]);

#endif
}

void MainUI::ScoreArray(int score)
{
	// スコア代入
	m_score += score;

	// 送られた数値が0だった場合、m_scoreを0にする
	if (score == 0)
	{
		m_score = 0;
	}


	//1の位
	m_scoreNum[kScoreMaxNum - 1] = (m_score % 10);				


	for (int i = 1; i < kScoreMaxNum; i++)
	{
		int num = pow(10, static_cast<float>((kScoreMaxNum - 1) - i));

		m_scoreNum[i] = ((m_score / (num) % 10));
	}
}

void MainUI::TextProcess()
{

	// m_isTextMoveがfalseならここで処理を終了する
	if (!m_isTextMove)return;

	// テキストが画面外に行ったとき
	if (m_textPos.x >= kTextGraphicOutPosX)
	{
		m_isTextMove = false;

		// テキストの表示位置
		m_textPos = Vec2(kTextGraphicPosX, kTextGraphicPosY);
		// テキストストップカウント
		m_textStopCount = kTextStopCount;
	}

	// テキストの位置が中心まで来てなおかつテキストカウントの値が0ならばテキストの動きを止める
	if (m_textPos.x >= Game::kScreenWidth * 0.5 && m_textStopCount != 0)
	{
		m_textStopCount--;
	}
	else
	{
		m_textPos.x += kTextMoveSpeed;
	}



	// テキスト描画処理
	DrawRotaGraph(m_textPos.x, m_textPos.y,
		kTextGraphicSize, 0.0, m_textHandle, true);


}

void MainUI::TimerProcess(int timer)
{

	// m_timerを減らし、0になると最大値に戻す
	{
		m_timer--;
	}

	// m_timerのパーセントを求める
	{
		// 割合
		float ratio = 100.0 * timer;

		// パーセントを入れる
		m_percentage = ratio / Player::kPowerUpMaxFrame;
	}



	// 描画処理
	{
		float H = timer * (512.0f / Player::kPowerUpMaxFrame) - 100;

		int R = min(max((384 - H), 0), 0xff);

		int G = min(max((H + 64), 0), 0xff);

		int B = max((H - 384), 0);

		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlpha);

			// 円形で表示
			DrawCircleGauge(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
				100, m_timerHandle[1], 0.0, kTimerGraphicSize, 0, 0);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);           //ブレンドモードをオフ
		}


		SetDrawBright(R, G, B);

		// 円形で表示
		DrawCircleGauge(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
			m_percentage, m_timerHandle[0], 0.0, kTimerGraphicSize, 0, 0);



		// 残像処理
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAfterimageAlpha);             //ブレンドモードを加算(255/255)に設定

			// 残像のパーセント
			float afterimagePercentage = 0.0;

			for (int i = 0; i < kAfterimageNum; i++)
			{

				// 残像のパーセントを求める
				afterimagePercentage = m_percentage + (kAfterimageValue * i);

				// 円形で表示
				DrawCircleGauge(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
					afterimagePercentage, m_timerHandle[0], 0.0, kTimerGraphicSize, 0, 0);

			}



			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);           //ブレンドモードをオフ
		}
		

		SetDrawBright(255, 255, 255);
	}

}

void MainUI::DamageProcess()
{
	if (m_playerHp != 1)return;

	m_sin += kSinSpeedValue;

	m_fadeValue = (((sinf(m_sin) * kSinValue) + kSinValue) / 2);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeValue);

	DrawModiGraph(0, 0, Game::kScreenWidth, 0,
		Game::kScreenWidth, Game::kScreenHeight, 0, Game::kScreenHeight,
		m_damageHandle, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);           //ブレンドモードをオフ

}
