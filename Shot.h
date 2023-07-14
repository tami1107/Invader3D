#pragma once
#include "game.h"
#include <memory>
#include "SceneMain.h"


class SceneMain;
class Shot
{
public:

	// �V���b�g�̃T�C�Y
	static constexpr float kShotSize = 1.1f;

	// �V���b�g1�J���[R
	static constexpr float kShotCollarR = 1.0f;
	// �V���b�g1�J���[G
	static constexpr float kShotCollarG = 1.0f;
	// �V���b�g1�J���[B
	static constexpr float kShotCollarB = 1.0f;

public:
	Shot();
	virtual ~Shot();


	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_SceneMain = sceneMain; }
	

	// ����
	void start(VECTOR pos);

	// ����������
	void init();

	// �X�V
	void update();
	// �\��
	void draw();

	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

	// ���̎擾
	VECTOR getPos() const { return m_pos; }
public:
	// �O���t�B�b�N���󂯎��
	void getShotGraphic(int handle) { m_modeleHandle = handle; }

public:

	// �e���̋O��
	void BulletTrajectory();

	// 2D�̓����蔻��
	void Collision2D();

	// �ړ���������
	void LimitMove();

private:

	// 3D���f���n���h��
	int m_modeleHandle;

	// ���݃t���O
	bool m_isExist;


	// �\���ʒu
	VECTOR m_pos;

	// �N���X�|�C���^
	SceneMain* m_SceneMain;

};


