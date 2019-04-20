
//=============================================================================
//	@file	AngleHelper.h
//	@brief	�p�x����
//	@autor	���m ���
//	@date	2018/11/15
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
class Pad;

//-----------------------------------------------------------------------------
//	@brief	�p�x�����N���X
//-----------------------------------------------------------------------------
class AngleHelper final
{
public:

//===================== �֐� ======================//

	//	�p�x�����߂�
	static void AskAngle(VECTOR& _angle, Pad& _pad);

	//	�p�x�����߂�
	static void AskAngle(VECTOR& _angle, VECTOR _dir);

private:

//================== ���������֐� ==================//

	//	�ړI�̊p�x�����߂�
	static VECTOR _GetTargetAngle(VECTOR& _angle, Pad& _pad);

	//	�ړI�̊p�x�����߂�
	static VECTOR _GetTargetAngle(VECTOR& _angle, VECTOR _dir);

	//	���͂ɂ��p�x�̕ύX
	static void _ChangeTargetAngleByInput(const bool _isState, float& _angle, const float _speed);

	//	�ړI�̊p�x�̍ő�ƍŏ��̐ݒ�
	static void _SetMaxToMin(float& _angle, const float _maxAngle, const float _minAngle);

	//	���͂��Ȃ��Ƃ��̊p�x�̕ύX
	static void _ChangeTargetAngleNoInput(const bool _isState, float& _angle);

//===================== �ÓI�萔 ===================//

	static const float ADD_ANGLE_SPEED;		//	�p�x�̉��Z���x
	static const float SUB_ANGLE_SPEED;		//	�p�x�̌��Z���x
	static const float LERP_SPEED;			//	���`�ۊǂ̑��x
	static const float LERP_RETURN_SPEED;	//	���`�ۊǂ̖߂鑬�x
	static const float ANGLE_NONE;			//	�p�x�̏�����
	static const float MAX_ANGLE;			//	���������̊p�x�̍ő�
	static const float MIN_ANGLE;			//	���������̊p�x�̍ŏ�
};