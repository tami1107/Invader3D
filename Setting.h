#pragma once

namespace EnemySet
{
	//////////////////////////////////////////
	//			�O���t�B�b�N�֘A			//
	//////////////////////////////////////////

	// �G�l�~�[�O���t�B�b�N�̃t�@�C����
	const char* const kEnemy1_1GraphicFileName = "data/enemy1_1.png";
	const char* const kEnemy1_2GraphicFileName = "data/enemy1_2.png";
	const char* const kEnemy2_1GraphicFileName = "data/enemy2_1.png";
	const char* const kEnemy2_2GraphicFileName = "data/enemy2_2.png";


	// �G�l�~�[�O���t�B�b�N���i�A�j���[�V�������j
	constexpr int kEnemyGraphicNum = 2;


	// �O���t�B�b�N�̃T�C�Y
	constexpr float kGraphicSize = 5.0f;


	//////////////////////////////////////////
	//				�J���[�֘A				//
	//////////////////////////////////////////

	// �G�l�~�[1�J���[
	constexpr float kEnemy1CollarR = 0.0f;
	constexpr float kEnemy1CollarG = 1.0f;
	constexpr float kEnemy1CollarB = 0.0f;

	// �G�l�~�[2�J���[
	constexpr float kEnemy2CollarR = 1.0f;
	constexpr float kEnemy2CollarG = 1.0f;
	constexpr float kEnemy2CollarB = 0.0f;


	//////////////////////////////////////////
	//				���W�֘A				//
	//////////////////////////////////////////

	// �����ʒu
	constexpr float kInitPosX = 0.0f;
	constexpr float kInitPosY = 5.0f;
	constexpr float kInitPosZ = 100.0f;

	// �G�l�~�[�̉�����
	constexpr float kEnemyWidthDistance = 20.0;

	// �Q�[���I�[�o�[���W�ɂȂ���W
	constexpr float kGameOverPosZ = 0.0f;


	//////////////////////////////////////////
	//				�ړ��֘A				//
	//////////////////////////////////////////

	// ��x�̈ړ��Ői�ދ���
	constexpr float kMovePosX = 5.0f;
	constexpr float kMovePosZ = 10.0f;


	// ���E�̂ǂ��܂ňړ�����̂� (kMovePosX * kLimitMove)
	constexpr int kLimitMove = 6;



	// �ړ��X�s�[�h
	constexpr int kMoveInterval = 60;	// �ړ��Ԋu(�t���[����)
	constexpr float kEnemyMoveLevel1 = 0.5;	// �G�l�~�[�̈ړ����x��1�i�G�l�~�[�������ȉ��ő��x���グ��̂��j
	constexpr int kEnemyMoveInterval1 = 10;	// �C���^�[�o�������l���x��1
	constexpr float kEnemyMoveLevel2 = 0.2;	// �G�l�~�[�̈ړ����x��2�i�����ȉ��ő��x���グ��̂��j
	constexpr int kEnemyMoveInterva2 = 20;	// �C���^�[�o�������l���x��2


	// �G�l�~�[�ɉ����牽��ڂ܂Ői�܂��邩�i����ȏ�i�ނ��Ƃ͂ł��Ȃ��j
	constexpr int kEnemyEndCol = 3;



	//////////////////////////////////////////
	//				�����蔻��				//
	//////////////////////////////////////////

	// �����蔻��i�����T�C�Y�j
	constexpr float kCircleSize = 5.0f;

	//////////////////////////////////////////
	//				�X�R�A					//
	//////////////////////////////////////////

	// �G�l�~�[��|�����Ƃ��̃X�R�A
	constexpr int kEnemy1KillScore = 30;// �G�l�~�[1�̏ꍇ
	constexpr int kEnemy2KillScore = 10;// �G�l�~�[2�̏ꍇ

	//////////////////////////////////////////
	//				�V���b�g�֘A			//
	//////////////////////////////////////////

	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 60;

	//////////////////////////////////////////
	//				�f�o�b�O				//
	//////////////////////////////////////////

	// �f�o�b�N�\�������邩�ǂ���
	constexpr bool kDebug = false;
}

namespace PlayerSet
{
	//////////////////////////////////////////
	//			�O���t�B�b�N�֘A			//
	//////////////////////////////////////////

	// �O���t�B�b�N�̃t�@�C����
	const char* const kPlayerGraphicFileName = "data/model/player.mv1";

	// ���f���̃X�P�[��
	static constexpr float kModeleScale = 2.5f;

	// �����x(1.0f���s�����A0.0f������)
	static constexpr float kAlphaValue = 1.0f;

	//////////////////////////////////////////
	//				�J���[�֘A				//
	//////////////////////////////////////////

	// �v���C���[�J���[
	static constexpr float kCollarR = 0.0f;
	static constexpr float kCollarG = 1.0f;
	static constexpr float kCollarB = 0.0f;



	//////////////////////////////////////////
	//				���W�֘A				//
	//////////////////////////////////////////

	// �����ʒu
	static constexpr float kInitPosX = 0.0f;
	static constexpr float kInitPosY = 3.0f;
	static constexpr float kInitPosZ = 0.0f;


	//////////////////////////////////////////
	//				�ړ��֘A				//
	//////////////////////////////////////////

	// �ړ��X�s�[�h
	constexpr float kMoveSpeed = 0.5f;
	

	// �v���C���[�̈ړ��͈�
	constexpr int kMoveLimit = 80;


	//////////////////////////////////////////
	//				�����蔻��				//
	//////////////////////////////////////////

	// �����蔻��i�����T�C�Y�j
	constexpr float kCircleSize = 3.0f;

	//////////////////////////////////////////
	//				�V���b�g�֘A			//
	//////////////////////////////////////////

	// �V���b�g�̐����Ԋu(�t���[����)
	constexpr int kShotInterval = 8;

	//////////////////////////////////////////
	//				�f�o�b�O				//
	//////////////////////////////////////////

	// �f�o�b�N�\�������邩�ǂ���
	constexpr bool kDebug = false;
}
