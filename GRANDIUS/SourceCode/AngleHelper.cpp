
//=============================================================================
//	@file	AngleHelper.cpp
//	@brief	�p�x����
//	@autor	���m ���
//	@date	2018/11/15
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "AngleHelper.h"
#include "Common.h"
#include "Pad.h"
#include "Key.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float AngleHelper::ADD_ANGLE_SPEED = 0.2f;	//	�p�x�̉��Z���x
const float AngleHelper::SUB_ANGLE_SPEED = -0.2f;	//	�p�x�̌��Z���x
const float AngleHelper::LERP_SPEED = 0.1f;			//	���`�ۊǂ̑��x
const float AngleHelper::LERP_RETURN_SPEED = 0.5f;	//	���`�ۊǂ̖߂鑬�x
const float AngleHelper::ANGLE_NONE = 0.0f;			//	�p�x�̏�����
const float AngleHelper::MAX_ANGLE = 0.2f;			//	���������̊p�x�̍ő�
const float AngleHelper::MIN_ANGLE = -0.2f;			//	���������̊p�x�̍ő�

//-----------------------------------------------------------------------------
//	@brief	�p�x�����߂�
//-----------------------------------------------------------------------------
void AngleHelper::AskAngle(VECTOR& _angle, Pad& _pad)
{
	//	�ړI�̊p�x�����߂�
	_angle = _GetTargetAngle(_angle, _pad);
}

//-----------------------------------------------------------------------------
//	@brief	�p�x�����߂�
//-----------------------------------------------------------------------------
void AngleHelper::AskAngle(VECTOR& _angle, VECTOR _dir)
{
	//	�ړI�̊p�x�����߂�
	_angle = _GetTargetAngle(_angle, _dir);
}

//-----------------------------------------------------------------------------
//	@brief	�ړI�̊p�x�����߂�
//-----------------------------------------------------------------------------
VECTOR AngleHelper::_GetTargetAngle(VECTOR& _angle, Pad& _pad)
{
	VECTOR targetAngle = _angle;

	//	���͂ɂ��p�x�̎擾
	const bool isUp = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_UP, PadInfo::STICK_DEAD_ZONE) || KEY->Press(KEY_INPUT_W) || KEY->Press(KEY_INPUT_UP);
	const bool isDown = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_DOWN, PadInfo::STICK_DEAD_ZONE) || KEY->Press(KEY_INPUT_S) || KEY->Press(KEY_INPUT_DOWN);

	//	���͂��ꂽ�����Ɋp�x�̕ύX
	_ChangeTargetAngleByInput(isUp, targetAngle.z, ADD_ANGLE_SPEED);	//	�����
	_ChangeTargetAngleByInput(isDown, targetAngle.z, SUB_ANGLE_SPEED);	//	������

	//	�ő�ŏ��̐ݒ�
	_SetMaxToMin(targetAngle.z, MAX_ANGLE, MIN_ANGLE);

	//	���͂��Ȃ��Ƃ��̏�����
	const bool isNotVertical = !isUp && !isDown;			//	���������̓��͂Ȃ�

	//	���͂��Ȃ���΁A���`�ۊǂ𗘗p��0�ɖ߂�
	_ChangeTargetAngleNoInput(isNotVertical, targetAngle.z);		//	���������̓��͂Ȃ�

		//	���`�ۊǂ𗘗p���p�x�����߂�
	VECTOR angle = _angle;
	angle = CommonFunction::Lerp(angle, targetAngle, LERP_SPEED);

	//	�p�x��Ԃ�
	return angle;
}

//-----------------------------------------------------------------------------
//	@brief	�ړI�̊p�x�����߂�
//-----------------------------------------------------------------------------
VECTOR AngleHelper::_GetTargetAngle(VECTOR& _angle, VECTOR _dir)
{
	VECTOR targetAngle = _angle;

	//	�����ɂ��p�x�̎擾
	const bool isUp = _dir.y > 0.0f;
	const bool isDown = _dir.y < 0.0f;

	//	���͂��ꂽ�����Ɋp�x�̕ύX
	_ChangeTargetAngleByInput(isUp, targetAngle.z, ADD_ANGLE_SPEED);	//	�����
	_ChangeTargetAngleByInput(isDown, targetAngle.z, SUB_ANGLE_SPEED);	//	������

	//	�ő�ŏ��̐ݒ�
	_SetMaxToMin(targetAngle.z, MAX_ANGLE, MIN_ANGLE);

	//	���͂��Ȃ��Ƃ��̏�����
	const bool isNotVertical = !isUp && !isDown;			//	���������̓��͂Ȃ�

	//	���͂��Ȃ���΁A���`�ۊǂ𗘗p��0�ɖ߂�
	_ChangeTargetAngleNoInput(isNotVertical, targetAngle.z);		//	���������̓��͂Ȃ�

		//	���`�ۊǂ𗘗p���p�x�����߂�
	VECTOR angle = _angle;
	angle = CommonFunction::Lerp(angle, targetAngle, LERP_SPEED);

	//	�p�x��Ԃ�
	return angle;
}

//-----------------------------------------------------------------------------
//	@brief	���͂ɂ��p�x�̕ύX
//-----------------------------------------------------------------------------
void AngleHelper::_ChangeTargetAngleByInput(const bool _isState, float& _angle, const float _speed)
{
	if(_isState) { _angle += _speed; }
}

//-----------------------------------------------------------------------------
//	@brief	�ő�ŏ��̐ݒ�
//-----------------------------------------------------------------------------
void AngleHelper::_SetMaxToMin(float& _angle, const float _maxAngle, const float _minAngle)
{
	if (_angle >= _maxAngle) { _angle = _maxAngle; }		//	�ő�p�x
	if (_angle <= _minAngle) { _angle = _minAngle; }		//	�ŏ��p�x
}

//-----------------------------------------------------------------------------
//	@brief	���͂��Ȃ����̑Ή�
//-----------------------------------------------------------------------------
void AngleHelper::_ChangeTargetAngleNoInput(const bool _isState, float& _angle)
{
	if (_isState) { _angle = CommonFunction::Lerp(_angle, ANGLE_NONE, LERP_RETURN_SPEED); }
}
