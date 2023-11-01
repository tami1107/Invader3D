#pragma once
#include "Vec2.h"
#include <memory>

class MainUI
{
public:
	// �X�R�A�̍ő包��
	static constexpr int kScoreMaxNum = 6;
	

	// �O���t�B�b�N������
	static constexpr int kGraphicDivX = 2;
	static constexpr int kGraphicDivY = 1;
	static constexpr int kGraphicDivNum = kGraphicDivX * kGraphicDivY;
public:
	MainUI();
	virtual~MainUI();


	void init();

	void update();

	void draw();
public:

	void getPlayerHp(int playerHp) { m_playerHp = playerHp; }
	void getEnemyLv(int enemyLv) { m_enemyLv = enemyLv; }
	void getIsTextMove(bool textMove) { m_isTextMove = textMove; }

public:
	// �X�R�A��z��ɕϊ�
	void ScoreArray(int score);

	// �e�L�X�g����
	void TextProcess();

	// �^�C�}�[����
	void TimerProcess(int timer);

	// �_���[�W����
	void DamageProcess();

private:
	// �O���t�B�b�N�n���h��
	int m_graphicHandle[2];

	// �t�H���g�n���h��
	int m_fontHandle;

	// �^�C�}�[�n���h��
	int m_timerHandle[kGraphicDivNum];


	// �v���C���[��HP
	int m_playerHp;
	// �G�l�~�[�̃��x��
	int m_enemyLv;
	// �X�R�A
	int m_score;


	// �X�R�A�̔z��
	int m_scoreNum[kScoreMaxNum];

	// �e�L�X�g�n���h��
	int m_textHandle;

	// �e�L�X�g���ړ������邩
	bool m_isTextMove;

	// �e�L�X�g�X�g�b�v�J�E���g
	int m_textStopCount;


	// �^�C�}�[
	int m_timer;

	// �p�[�Z���g
	float m_percentage;

	// �_���[�W�n���h��
	int m_damageHandle;

	// �T�C��
	float m_sin;

	// �t�F�[�h�l
	float m_fadeValue;

	// �e�L�X�g�\���ʒu
	Vec2 m_textPos;

};