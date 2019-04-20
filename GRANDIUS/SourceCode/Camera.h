
//=============================================================================
//	@file	Camera.h
//	@brief	�J����
//	@autor	���m ���
//	@date	2018/9/29
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class PlayerManager;

//-----------------------------------------------------------------------------
//	@brief	�J�����N���X
//-----------------------------------------------------------------------------
class Camera final
{
public:

//===================== �֐� ======================//

	// �R���X�g���N�^ / �f�X�g���N�^
	Camera();
	~Camera();

	//	�^�C�g���p�̏�������
	void InitializeForTitle();

	//	��������
	void Initialize();

	//	�^�C�g���p�̍X�V����
	void UpdateForTitle(PlayerManager& _playerManager);

	//	���U���g�p�̍X�V����
	void UpdateForResult(PlayerManager& _playerManager);

	//	�X�V����
	void Update(PlayerManager& _playerManager);

//==================== getter =====================//

	//	�����p�x�� getter
	const float& GetHorizontalAngle() const { return m_horizontalAngle; }

private:

//================== ���������֐� ==================//

	//	�^�C�g���p�̉��o
	void _ProductionForTitle(PlayerManager& _playerManager);

	//	���o
	void _Production(PlayerManager& _playerManager);

	//	�V�[�����o
	void _SceneProduction(PlayerManager& _playerManager);

	//	�K�E���o
	void _SpecialProduction(PlayerManager& _playerManager);

	//	�N���A���o
	void _ClearProduction(PlayerManager& _playerManager);

	//	�^�C�g���p�̒����_�̐ݒ�
	void _SetGazingPointForTitle(PlayerManager& _playerManager);

	//	�����_�̐ݒ�
	void _SetGazingPoint();

	//	�J�����̊p�x�ɂ��|�W�V�����̕ύX
	VECTOR _PosAccordingToAngle();

//=================== �����o�ϐ� ===================//

	VECTOR		m_pos;					//	�|�W�V����
	VECTOR		m_lookAtPos;			//	�����_
	float		m_verticalAngle;		//	�����p�x
	float		m_horizontalAngle;		//	�����p�x
	float		m_productionTime;		//	���o����
	bool		m_isProduction;			//	���o�t���O

//===================== �ÓI�萔 ===================//

	static const float		V_ANGLE_SPEED_MOUSE;	// �����p�x�̉�]���x
	static const float		H_ANGLE_SPEED_MOUSE;	// �����p�x�̉�]���x
	static const float		V_ANGLE_SPEED_PAD;		// �����p�x�̉�]���x
	static const float		H_ANGLE_SPEED_PAD;		// �����p�x�̉�]���x
	static const int		MAX_H_ANGLE;			// �����p�x�̍ő�
	static const int		MIN_H_ANGLE;			// �����p�x�̍ŏ�
	static const int		MAX_V_ANGLE;			// �����p�x�̍ő�
	static const int		MIN_V_ANGLE;			// �����p�x�̍ŏ�
	static const float		LERP_SPEED;				//	���`�ۊǂ̑��x
	static const float		HEIGHT_LENGTH;			//	�����̒���
	static const float		DEPTH_LENGTH;			//	���s���̒���
};