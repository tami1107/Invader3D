#include "Bunker.h"
#include "SceneMain.h"

namespace
{
	// 初期位置
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = 10.0f;


	// 最大HP量
	constexpr int kMaxHp = 5;

	// モデルのスケール
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
	// ポインタの削除
	m_pSceneMain = nullptr;
	delete m_pSceneMain;

	// グラフィックの削除
	MV1DeleteModel(m_modeleHandle);
}

void Bunker::init(int savePosX)
{
	// 存在している
	m_isExist = true;


	// 位置の初期化
	m_pos = VGet(kInitPosX + savePosX, kInitPosY, kInitPosZ);

	// 最大HP量を代入
	m_hp = kMaxHp;


	// ３Ｄモデルのスケール変更
	MV1SetScale(m_modeleHandle, VGet(kModeleScale, kModeleScale, kModeleScale));

	// 位置情報をモデルに入れる
	MV1SetPosition(m_modeleHandle, m_pos);

	// ３Ｄモデルの不透明度
	MV1SetOpacityRate(m_modeleHandle, kAlphaValue);

	// カラー処理
	ColorProcess();
}

void Bunker::update()
{
	if (!m_isExist)return;

	// あたり判定処理
	Collision2D();
}

void Bunker::draw()
{
	if (!m_isExist)return;

	
	// モデルの描画
	MV1DrawModel(m_modeleHandle);



#if true

	// 球の表示
	DrawSphere3D(m_pos, kCircleSize, 32, 0x0000ff, GetColor(0, 0, 0), true);


#endif

}

void Bunker::DamegeProcess(int damages)
{
	// HPからダメージを引く
	m_hp -= damages;



	// カラー処理
	ColorProcess();


	// HPが0の場合、存在を消す
	if (m_hp <= 0)
	{
		m_isExist = false;

		m_pSceneMain->CreateParticle3D(m_pos, m_color, kParticleValue, kAlphaValue, kParticleScale);
	}
}

void Bunker::Collision2D()
{
	// トーチカとエネミーショットのあたり判定
	m_pSceneMain->BunkerToInvertShotCollision();
	// トーチカとプレイヤーショットのあたり判定
	m_pSceneMain->BunkerToShotCollision();
}

void Bunker::ColorProcess()
{
	// カラー処理
	{
		float H = m_hp * (512.0f / kMaxHp) - 100;

		float R = min(max((384 - H), 0), 0xff);
		float G = min(max((H + 64), 0), 0xff);
		float B = max((H - 384), 0);



		float color[3] = { R ,G ,B };


		// collarの値を求める
		{
			// 割合
			float ratio;

			// パーセントを入れる
			float percentage[3];

			// colorFを入れる
			float colorF[3];

			for (int i = 0; i < 3; i++)
			{
				ratio = 100.0 * color[i];
				percentage[i] = ratio / 255;

				colorF[i] = percentage[i] * 0.01;
			}

			// 色情報取得
			m_color = VGet(colorF[0], colorF[1], colorF[2]);
		}

		// 色設定
		MV1SetMaterialDifColor(m_modeleHandle, 0, GetColorF(m_color.x, m_color.y, m_color.z, 1.0f));

	}
}
