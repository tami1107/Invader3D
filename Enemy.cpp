#include "Enemy.h"
#include "SceneMain.h"
#include "Setting.h"


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
	m_enemyLineNum(0),
	m_enemyNum(0),
	m_moveMaxInterval(EnemySet::kMoveInterval),
	m_moveInterval(EnemySet::kMoveInterval),
	m_movingDistance(0.0f),
	m_movingMaxDistance(0.0f),
	m_enemyEdgePosX(0.0f),
	m_pos(),
	m_color(),
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

void Enemy::init(int savePosX, int savePosZ, int enemyLineNum)
{
	
	// 存在している
	m_isExist = true;

	// 位置の代入
	m_savePosX = savePosX;
	m_savePosZ = savePosZ;

	// エネミーの列番号を代入
	m_enemyLineNum = enemyLineNum;

	
	// 移動インターバル減少値の初期化
	m_decrementTime = 0;

	// 位置の初期化
	m_pos = VGet(EnemySet::kInitPosX + m_savePosX, EnemySet::kInitPosY, EnemySet::kInitPosZ + savePosZ);

	// 移動の間隔
	m_frameCount = EnemySet::kMoveInterval;

	// 最初は右に進む
	m_isRightMove = true;

	// 最初は下に進まない
	m_isUnderMove = false;

	// ショットの発生間隔
	m_shotInterval = 0;

	// アニメーションナンバーの初期化
	m_animationNum = 0;

	// インターバルの代入
	m_moveInterval = m_moveMaxInterval;

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

	MATERIALPARAM Material;

	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(m_color.x, m_color.y, m_color.z, 0.0f);
	Material.Power = 20.0f;

	SetMaterialParam(Material);



	// 透明にして表示する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, EnemySet::kAlphaValue);

	// ２ポリゴンの描画
	DrawPolygon3D(Vertex, 2, m_handle[m_animationNum], true);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	//DrawFormatString(0, 15 * 10, 0xffffff, "インターバルmax%d", m_moveMaxInterval);
	//DrawFormatString(0, 15 * 11, 0xffffff, "インターバル%d", m_moveInterval);

	//DrawFormatString(300, 15 * m_enemyNum, 0xffffff, "[%d]移動量:%f 最大移動量:%f",
	//	m_enemyNum, m_movingDistance, m_movingMaxDistance);
	

		//DrawFormatString(300, 15 * 12+ m_enemyNum, 0xffffff, "移動量:%f", m_movingDistance);
		//DrawFormatString(300, 15 * 13+i, 0xffffff, "最大移動量:%f", m_movingMaxDistance);
	



	// Debug
	{
		if (!EnemySet::kDebug)return;
		// 当たり判定の表示（球体）
		DrawSphere3D(m_pos, EnemySet::kCircleSize, 32, 0xffffff, GetColor(0, 0, 0), true);
	}
}


void Enemy::InitPolygon()
{

	// ２ポリゴン分の頂点の座標と法線以外のデータをセット
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
	Vertex[0].pos = VTransform(VGet(m_pos.x + -EnemySet::kGraphicSize, m_pos.y + EnemySet::kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[1].pos = VTransform(VGet(m_pos.x + EnemySet::kGraphicSize, m_pos.y + EnemySet::kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[2].pos = VTransform(VGet(m_pos.x + -EnemySet::kGraphicSize, m_pos.y + -EnemySet::kGraphicSize, m_pos.z), TransformMatrix);
	Vertex[3].pos = VTransform(VGet(m_pos.x + EnemySet::kGraphicSize, m_pos.y + -EnemySet::kGraphicSize, m_pos.z), TransformMatrix);

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


	
	// frameCountが0になったら移動
	m_frameCount--;
	if (m_frameCount <= 0)
	{
		// アニメーションを動かす
		m_animationNum++;
		// 移動アニメーションは0・1しか使わない為、2以上になったとき0にする
		m_animationNum %= 2;


	
		// 右に進むかどうかのフラグ処理
		if (m_movingDistance >= m_movingMaxDistance)
		{
			if (m_isRightMove)
			{
				m_isRightMove = false;

				m_isUnderMove = true;

				m_movingDistance = 0.0f;

				m_movingMaxDistance = (EnemySet::kLimitMove + m_enemyEdgePosX) * -2;
			}
		}
		// 左に進むかどうかのフラグ処理
		if (m_movingDistance <= m_movingMaxDistance)
		{
			if (!m_isRightMove)
			{
				m_isRightMove = true;

				m_isUnderMove = true;

				m_movingDistance = 0.0f;

				m_movingMaxDistance = (EnemySet::kLimitMove + m_enemyEdgePosX) * 2;
			}
		}

		//// 右に進むかどうかのフラグ処理
		//if (m_pos.x >= (EnemySet::kMovePosX * EnemySet::kLimitMove) + m_savePosX)
		//{
		//	if (m_isRightMove)
		//	{
		//		m_isRightMove = false;

		//		m_isUnderMove = true;
		//	}
		//}
		//// 左に進むかどうかのフラグ処理
		//if (m_pos.x <= -(EnemySet::kMovePosX * EnemySet::kLimitMove) + m_savePosX)
		//{
		//	if (!m_isRightMove)
		//	{
		//		m_isRightMove = true;

		//		m_isUnderMove = true;
		//	}
		//}

		// 一段手前にいくかどうか
		if (m_isUnderMove)
		{
			// 一段手前に行く
			m_pos.z -= EnemySet::kMovePosZ;

			m_isUnderMove = false;


			m_frameCount = m_moveInterval;

			// ゲームオーバーするかどうか
			if (m_pos.z <= EnemySet::kGameOverLine * EnemySet::kMovePosZ)
			{
				m_pSceneMain->setIsGameOverFlag(true);
			}

			return;
		}


		// フラグによって移動方向を変える
		if (m_isRightMove)
		{
			m_pos.x += EnemySet::kMovePosX;

			m_movingDistance += EnemySet::kMovePosX;
		}
		else
		{
			m_pos.x -= EnemySet::kMovePosX;

			m_movingDistance -= EnemySet::kMovePosX;
		}

		// 移動フレームを戻す
		m_frameCount = m_moveInterval;
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
		// ショットを打つかどうか
		m_pSceneMain->IsShotEnemy(m_pos, m_enemyNum, m_enemyLineNum);

	
		m_shotInterval = EnemySet::kShotInterval;
	}
}

void Enemy::LevelUp(float IntervalDecrement)
{
	// 移動インターバルを減らす
	m_moveMaxInterval *= IntervalDecrement;

	// インターバルに代入
	m_moveInterval = m_moveMaxInterval;
}

void Enemy::EnemyNumInterval(int interval)
{

	// インターバルに代入
	m_moveInterval = interval;
}



void Enemy::Reset()
{
	// 移動インターバルの初期化
	m_moveMaxInterval = EnemySet::kMoveInterval;

	// インターバルに代入
	m_moveInterval = m_moveMaxInterval;
}

void Enemy::MoveSetting(float enemyEdgePosX)
{
	

	m_enemyEdgePosX = enemyEdgePosX;

	// 最大移動量
	m_movingMaxDistance = EnemySet::kLimitMove + enemyEdgePosX;

	m_movingDistance = 0.0f;
}

