#pragma once
#include "SceneBase.h"
#include <memory>
#include "game.h"


class Player;
class Camera;
class Shot;
class InvertShot;
class Enemy;
class SceneMain : public SceneBase
{
public:
	// �I�u�W�F�N�g�̍ő吔
	static constexpr int kObjectMaxNumber = 10;
public:
	SceneMain();

	virtual ~SceneMain();


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

public:
	// �v���C���[���V���b�g������
	bool createShotPlayer(VECTOR pos);

	// �G�l�~�[���V���b�g������
	bool createShotEnemy(VECTOR pos);


private:

	// �N���X�|�C���^
	std::shared_ptr<Player>m_pPlayer;
	std::shared_ptr<Camera>m_pCamera;
	std::shared_ptr<Shot>m_pShot[kObjectMaxNumber];
	std::shared_ptr<InvertShot>m_pInvertShot[kObjectMaxNumber];
	std::shared_ptr<Enemy>m_pEnemy;


};