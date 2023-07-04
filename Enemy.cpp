#include "Enemy.h"
#include "SceneMain.h"

namespace
{
	// 初期位置
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = Enemy::kInitPosZ;


	// ショットの生成間隔(フレーム数)
	constexpr int kShotInterval = 60;


	// 移動間隔(フレーム数)
	//constexpr int kMoveInterval = 120;

	// 移動間隔(フレーム数)デバッグ
	constexpr int kMoveInterval = 60;

	// 移動量X
	constexpr float kMovePosX = Enemy::kMovePosX;
	// 移動量Y
	constexpr float kMovePosZ = Enemy::kMovePosZ;

	// どこまで移動するのか
	constexpr int kLimitMove = Enemy::kLimitMove;


	// ゲームオーバー座標
	constexpr float kGameOverPosY = 0.0f;


	// グラフィックサイズ
	constexpr float kGraphicSize = 5.0f;

}


Enemy::Enemy() :
	m_isExist(true),
	m_savePosX(0),
	m_savePosZ(0),
	m_frameCount(0),
	m_isRightMove(true),
	m_isUnderMove(false),
	m_shotInterval(0),
	m_decrementTime(0),
	m_animationNum(0),
	m_pos(),
	m_pSceneMain(nullptr)
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}

	// ポリゴンの初期設定
	InitPolygon();
}

Enemy::~Enemy()
{
	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// グラフィックの削除
	for (auto handle : m_handle)
	{
		DeleteGraph(handle);
	}
}

void Enemy::init(int savePosX, int savePosZ, int decrementTime)
{
	
	// スピードを代入
	m_decrementTime = decrementTime;

	// 存在している
	m_isExist = true;

	// 位置の保存
	m_savePosX = savePosX;
	m_savePosZ = savePosZ;


	// 位置の初期化
	m_pos = VGet(kInitPosX + m_savePosX, kInitPosY, kInitPosZ + savePosZ);

	// 移動の間隔
	m_frameCount = kMoveInterval - m_decrementTime;

	// 最初は右に進む
	m_isRightMove = true;

	// 最初は下に進まない
	m_isUnderMove = false;

	// ショットの発生間隔
	m_shotInterval = 0;

	// アニメーションナンバーの初期化
	m_animationNum = 0;



}

void Enemy::update()
{
	// エネミーが存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;


	// 移動処理
	Move();

	// ポリゴンのアップデート処理
	UpdatePolygon();

	// ショット処理
	Shot();

}

void Enemy::draw()
{
	// エネミーが存在しなかった場合、ここで処理を終了する
	if (!m_isExist) return;


	// ２ポリゴンの描画
	DrawPolygon3D(Vertex, 2, m_handle[m_animationNum], true);

	// 画像描画
	//DrawBillboard3D(m_pos, 0.5, 0.5, kGraphicSize, 0.0, m_handle[m_animationNum], true);

	
	// 当たり判定の表示
#if false
	// 球の表示
	DrawSphere3D(m_pos, kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);
#endif
}


void Enemy::InitPolygon()
{

	// ２ポリゴン分の頂点の座標と法線以外のデータをセット
	Vertex[0].dif = GetColorU8(255, 255, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].dif = GetColorU8(255, 255, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].dif = GetColorU8(255, 255, 255, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;

	Vertex[3].dif = GetColorU8(255, 255, 255, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4] = Vertex[2];
	Vertex[5] = Vertex[1];

	// 回転パラメータを初期化
	Angle.x = 0.0f;
	Angle.y = 0.0f;
	Angle.z = 0.0f;

}

void Enemy::UpdatePolygon()
{
	MATRIX TransformMatrix;

	// 回転( x, y, z軸回転の順 )＋座標移動行列の作成
	TransformMatrix = MGetRotX(Angle.x);
	TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
	TransformMatrix = MMult(TransformMatrix, MGetRotZ(Angle.z));
	TransformMatrix = MMult(TransformMatrix, MGetTranslate(VGet(0.0f, 0.0f, 0.0f)));

	// 行列を使ってワールド座標を算出
	Vertex[0].pos = VTransform(VGet(m_pos.x + -kGraphicSize, m_pos.y + kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[1].pos = VTransform(VGet(m_pos.x + kGraphicSize, m_pos.y + kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[2].pos = VTransform(VGet(m_pos.x + -kGraphicSize, m_pos.y + -kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[3].pos = VTransform(VGet(m_pos.x + kGraphicSize, m_pos.y + -kGraphicSize, m_pos.z), TransformMatrix);

	Vertex[4].pos = Vertex[2].pos;
	Vertex[5].pos = Vertex[1].pos;

	// 行列を使って法線を算出
	Vertex[2].norm = Vertex[0].norm;
	Vertex[3].norm = Vertex[0].norm;
	Vertex[4].norm = Vertex[0].norm;
	Vertex[5].norm = Vertex[0].norm;

}

void Enemy::Move()
{
	// 移動インターバル


	// 移動するまでにかかるフレーム
	int moveFrame = kMoveInterval - m_decrementTime;


	// frameCountが0になったら移動
	m_frameCount--;
	if (m_frameCount <= 0)
	{
		// アニメーションを動かす
		m_animationNum++;
		// 移動アニメーションは0・1しか使わない為、2以上になったとき0にする
		if (m_animationNum == 2)
		{
			m_animationNum = 0;
		}
		

		// 右に進むかどうかのフラグ処理
		if (m_pos.x >= (kMovePosX * kLimitMove) + m_savePosX)
		{
			if (m_isRightMove)
			{
				m_isRightMove = false;

				m_isUnderMove = true;
			}
		}
		// 左に進むかどうかのフラグ処理
		if (m_pos.x <= -(kMovePosX * kLimitMove)+ m_savePosX)
		{
			if (!m_isRightMove)
			{
				m_isRightMove = true;

				m_isUnderMove = true;
			}
		}

		// 一段手前にいくかどうか
		if (m_isUnderMove)
		{
			// 一段手前に行く
			m_pos.z -= kMovePosZ;

			m_isUnderMove = false;


			m_frameCount = moveFrame;

			// ゲームオーバーするかどうか
			if (m_pos.z <= kGameOverPosY)
			{
				//m_pSceneMain->getIsGameOverFlag(true);
			}

			return;
		}


		// フラグによって移動方向を変える
		if (m_isRightMove)
		{
			m_pos.x += kMovePosX;
		}
		else
		{
			m_pos.x -= kMovePosX;
		}

		// 移動フレームを戻す
		m_frameCount = moveFrame;
	}
}

void Enemy::Shot()
{
	// ショットインターバル
	m_shotInterval--;
	if (m_shotInterval <= 0)
	{
		m_shotInterval = 0;
	}

	// ショットを撃つ
	if (m_shotInterval <= 0)
	{
		// ショットを撃つか撃たないかの変数
		int isShot = 0;

		// 乱数を取得
		isShot = GetRand(1);

		if (isShot == 1)
		{
			m_pSceneMain->CreateShotEnemy(m_pos);
		}
		m_shotInterval = kShotInterval;
	}
}




