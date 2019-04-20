
//=============================================================================
//	@file	TurningEnemy.h
//	@brief	����G�l�~�[
//	@autor	���m ���
//	@date	2018/12/20
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

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class PlayerManager;
class ShotManager;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	����G�l�~�[�N���X
//-----------------------------------------------------------------------------
class TurningEnemy : public EnemyBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	TurningEnemy(const int _modelHandle);
	~TurningEnemy();

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

	//	�p�x������������߂�
	void _ChangeMoveAngle(const float _moveAngleSpeed, const bool _isScalingSize, const float _ScalingSize);

	//	�����蔻��p�̓_�̍X�V
	void _UpdateHitPoint() override final;

	//	�ŏI�I�ȉ������
	void _FinalRelease() override final;

//=================== �����o�ϐ� ===================//

	float	m_moveAngle;			//	�ړ��p�x
	float	m_moveAngleWaitTime;	//	�ړ��p�x�̑ҋ@����
	bool	m_isOnReverse;			//	���]�����t���O
	bool	m_isOneTime;			//	��x�̂݃t���O

//===================== �ÓI�萔 ===================//

	static const float MOVE_ANGLE_SPEED;			//	��]�p�x�̉�]���x
	static const float MAX_MOVE_ANGLE_WAIT_TIME;	//	��]���x�̑ҋ@���Ԃ̍ő�
	static const float MAX_MOVE_ANGLE;				//	��]�p�x�̍ő�
	static const float MIN_MOVE_ANGLE;				//	��]�p�x�̍ŏ�

};