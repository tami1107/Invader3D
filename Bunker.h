#pragma once
#include "game.h"

class SceneMain;
class Bunker
{
public:
	// �����T�C�Y
	static constexpr float kCircleSize = 2.0f;
public:
	Bunker();
	virtual ~Bunker();

	// �N���X�|�C���^�̎擾
	void getSceneMainPointer(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void init(int savePosX, int savePosY);

	void update();

	void draw();

	// �ʒu����Ԃ�
	VECTOR getPos() const { return m_pos; }


	// ���݂��邩
	bool isExist() const { return m_isExist; }
	void setExist(bool isExist) { m_isExist = isExist; }

public:
	// �_���[�W����
	void DamegeProcess(int damages);

	// �����蔻��
	void Collision2D();

private:
	// ���݃t���O
	bool m_isExist;

	// �ۑ��ʒu
	int m_savePosX;
	int m_savePosY;

	// �q�b�g�|�C���g
	int m_hp;

	// �A���t�@�u�����h�̒l
	int m_alphaValue;

	// �A���t�@�u�����h�̌����l
	int m_alphaValueDecrement;


	// �\���ʒu
	VECTOR m_pos;
	
	// �N���X�|�C���^
	SceneMain* m_pSceneMain;
};

