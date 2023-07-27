#pragma once

namespace EnemySet
{
	//////////////////////////////////////////
	//			グラフィック関連			//
	//////////////////////////////////////////

	// エネミーグラフィックのファイル名
	const char* const kEnemy1_1GraphicFileName = "data/enemy1_1.png";
	const char* const kEnemy1_2GraphicFileName = "data/enemy1_2.png";
	const char* const kEnemy2_1GraphicFileName = "data/enemy2_1.png";
	const char* const kEnemy2_2GraphicFileName = "data/enemy2_2.png";


	// エネミーグラフィック数（アニメーション数）
	constexpr int kEnemyGraphicNum = 2;


	// グラフィックのサイズ
	constexpr float kGraphicSize = 5.0f;


	//////////////////////////////////////////
	//				カラー関連				//
	//////////////////////////////////////////

	// エネミー1カラー
	constexpr float kEnemy1CollarR = 0.0f;
	constexpr float kEnemy1CollarG = 1.0f;
	constexpr float kEnemy1CollarB = 0.0f;

	// エネミー2カラー
	constexpr float kEnemy2CollarR = 1.0f;
	constexpr float kEnemy2CollarG = 1.0f;
	constexpr float kEnemy2CollarB = 0.0f;


	//////////////////////////////////////////
	//				座標関連				//
	//////////////////////////////////////////

	// 初期位置
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = 100.0f;

	// エネミーの横距離
	constexpr float kEnemyWidthDistance = 20.0;

	// ゲームオーバー座標になる座標
	constexpr float kGameOverPosZ = 0.0f;


	//////////////////////////////////////////
	//				移動関連				//
	//////////////////////////////////////////

	// 一度の移動で進む距離
	constexpr float kMovePosX = 5.0f;
	constexpr float kMovePosZ = 10.0f;


	// 左右のどこまで移動するのか (kMovePosX * kLimitMove)
	constexpr int kLimitMove = 6;



	// 移動スピード
	constexpr int kMoveInterval = 60;	// 移動間隔(フレーム数)
	constexpr float kEnemyMoveLevel1 = 0.5;	// エネミーの移動レベル1（エネミーが何割以下で速度を上げるのか）
	constexpr int kEnemyMoveInterval1 = 10;	// インターバル減少値レベル1
	constexpr float kEnemyMoveLevel2 = 0.2;	// エネミーの移動レベル2（何割以下で速度を上げるのか）
	constexpr int kEnemyMoveInterva2 = 20;	// インターバル減少値レベル2


	// エネミーに下から何列目まで進ませるか（それ以上進むことはできない）
	constexpr int kEnemyEndCol = 3;



	//////////////////////////////////////////
	//				当たり判定				//
	//////////////////////////////////////////

	// 当たり判定（半球サイズ）
	constexpr float kCircleSize = 5.0f;

	//////////////////////////////////////////
	//				スコア					//
	//////////////////////////////////////////

	// エネミーを倒したときのスコア
	constexpr int kEnemy1KillScore = 30;// エネミー1の場合
	constexpr int kEnemy2KillScore = 10;// エネミー2の場合

	//////////////////////////////////////////
	//				ショット関連			//
	//////////////////////////////////////////

	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 60;

	//////////////////////////////////////////
	//				デバッグ				//
	//////////////////////////////////////////

	// デバック表示をするかどうか
	constexpr bool kDebug = false;
}

namespace PlayerSet
{
	//////////////////////////////////////////
	//			グラフィック関連			//
	//////////////////////////////////////////

	// グラフィックのファイル名
	const char* const kPlayerGraphicFileName = "data/model/player.mv1";

	// モデルのスケール
	static constexpr float kModeleScale = 2.5f;

	// 透明度(1.0fが不透明、0.0fが透明)
	static constexpr float kAlphaValue = 1.0f;

	//////////////////////////////////////////
	//				カラー関連				//
	//////////////////////////////////////////

	// プレイヤーカラー
	static constexpr float kCollarR = 0.0f;
	static constexpr float kCollarG = 1.0f;
	static constexpr float kCollarB = 0.0f;



	//////////////////////////////////////////
	//				座標関連				//
	//////////////////////////////////////////

	// 初期位置
	static constexpr float kInitPosX = 0.0f;
	static constexpr float kInitPosY = 3.0f;
	static constexpr float kInitPosZ = 0.0f;


	//////////////////////////////////////////
	//				移動関連				//
	//////////////////////////////////////////

	// 移動スピード
	constexpr float kMoveSpeed = 0.5f;
	

	// プレイヤーの移動範囲
	constexpr int kMoveLimit = 80;


	//////////////////////////////////////////
	//				当たり判定				//
	//////////////////////////////////////////

	// 当たり判定（半球サイズ）
	constexpr float kCircleSize = 3.0f;

	//////////////////////////////////////////
	//				ショット関連			//
	//////////////////////////////////////////

	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 8;

	//////////////////////////////////////////
	//				デバッグ				//
	//////////////////////////////////////////

	// デバック表示をするかどうか
	constexpr bool kDebug = false;
}
