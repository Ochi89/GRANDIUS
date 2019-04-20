
//=============================================================================
//	@file	LineEnemy.h
//	@brief	�����G�l�~�[
//	@autor	���m ���
//	@date	2018/11/16
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "EnemyBase.h"
#include "ShotManager.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class PlayerManager;
class ShotManager;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�����G�l�~�[�N���X
//-----------------------------------------------------------------------------
class LineEnemy : public EnemyBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	LineEnemy(const int _modelHandle);
	~LineEnemy();

	//	�쐬����
	void Create() override final;

	//	�������
	void Release() override final;

	//	��������
	void Initialize() override final;

	//	�X�V����
	void Update(PlayerManager& _playerManager, ShotManager& _shotManager, SoundEffect& _soundEffect) override final;

private:

//================== ���������֐� ==================//

	//	�����̐؂�ւ�����
	void _ChangeDir() override final;
	
	//	�����蔻��p�̓_�̍X�V
	void _UpdateHitPoint() override final;

	//	�ŏI�I�ȉ������
	void _FinalRelease() override final;

};