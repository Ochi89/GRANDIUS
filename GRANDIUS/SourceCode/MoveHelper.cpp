
//=============================================================================
//	@file	Moving.cpp
//	@brief	�ړ�����
//	@autor	���m ���
//	@date	2018/11/15
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "MoveHelper.h"
#include "Common.h"
#include "Pad.h"
#include "Key.h"

//-----------------------------------------------------------------------------
//	@brief	�ړ��ʂ����߂�
//-----------------------------------------------------------------------------
VECTOR MoveHelper::AskMoveAmount(VECTOR& _dir, Pad& _pad, const float _moveSpeed, const bool _isInputKey, const bool _isUseAxisXY)
{
	if (_isUseAxisXY) { return _MoveAxisXY(_dir, _pad, _moveSpeed, _isInputKey); }		//	XY���ł̈ړ�
	else { return _MoveAxisXZ(_dir, _pad, _moveSpeed, _isInputKey); }					//	XZ���ł̈ړ�
}

//-----------------------------------------------------------------------------
//	@brief	�ړ��ʂ����߂�
//-----------------------------------------------------------------------------
VECTOR MoveHelper::AskMoveAmount(VECTOR& _dir, const float _moveSpeed)
{
	return _AlwaysMove(_dir, _moveSpeed);
}

//-----------------------------------------------------------------------------
//	@brief	���Z�b�g
//-----------------------------------------------------------------------------
void MoveHelper::_ResetDir(VECTOR& _dir)
{
	_dir = CommonConstant::ORIGIN;
}

//-----------------------------------------------------------------------------
//	@brief	XZ���ł̈ړ�����
//-----------------------------------------------------------------------------
VECTOR MoveHelper::_MoveAxisXZ(VECTOR& _dir, Pad& _pad, const float _moveSpeed, const bool _isInputKey)
{
	//	�����̃��Z�b�g
	_ResetDir(_dir);

	if (_isInputKey)
	{
		//	�X�e�b�N�ƃL�[���͂ɂ������̐ݒ�
		_SetInputDirKeyToPad(_dir.z, _dir.x, _pad);
	}
	else
	{
		//	�X�e�b�N���͂ɂ������̐ݒ�
		_SetInputDirPad(_dir.z, _dir.x, _pad);
	}

	//	�ړ�����
	return _Move(_dir, _moveSpeed);
}

//-----------------------------------------------------------------------------
//	@brief	XY���ł̈ړ�����
//-----------------------------------------------------------------------------
VECTOR MoveHelper::_MoveAxisXY(VECTOR& _dir, Pad& _pad, const float _moveSpeed, const bool _isInputKey)
{
	//	�����̃��Z�b�g
	_ResetDir(_dir);

	if (_isInputKey)
	{
		//	�X�e�b�N�ƃL�[���͂ɂ������̐ݒ�
		_SetInputDirKeyToPad(_dir.y, _dir.x, _pad);
	}
	else
	{
		//	�X�e�b�N���͂ɂ������̐ݒ�
		_SetInputDirPad(_dir.y, _dir.x, _pad);
	}

	//	�ړ�����
	return _Move(_dir, _moveSpeed);
}

//-----------------------------------------------------------------------------
//	@brief	XY���ł̈ړ�����
//-----------------------------------------------------------------------------
VECTOR MoveHelper::_AlwaysMove(VECTOR& _dir, const float _moveSpeed)
{
	//	�ړ�����
	return _Move(_dir, _moveSpeed);
}

//-----------------------------------------------------------------------------
//	@brief	���͎��̌�����ݒ肷��
//-----------------------------------------------------------------------------
void MoveHelper::_SetInputDirKeyToPad(float& _verticalAxis, float& _horizontalAxis, Pad& _pad)
{
	//	�L�[����
	const bool isUpKey = KEY->Press(KEY_INPUT_W) || KEY->Press(KEY_INPUT_UP);
	const bool isDownKey = KEY->Press(KEY_INPUT_S) || KEY->Press(KEY_INPUT_DOWN);
	const bool isRightKey = KEY->Press(KEY_INPUT_D) || KEY->Press(KEY_INPUT_RIGHT);
	const bool isLeftKey = KEY->Press(KEY_INPUT_A) || KEY->Press(KEY_INPUT_LEFT);

	//	�p�b�h����
	const bool isUpStick = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_UP, PadInfo::STICK_DEAD_ZONE);
	const bool isDownStick = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_DOWN, PadInfo::STICK_DEAD_ZONE);
	const bool isRightStick = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_RIGHT, PadInfo::STICK_DEAD_ZONE);
	const bool isLeftStick = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_LEFT, PadInfo::STICK_DEAD_ZONE);

	//	�L�[�ƃp�b�h�̓���
	const bool isUp = isUpStick || isUpKey;
	const bool isDown = isDownStick || isDownKey;
	const bool isRight = isRightStick || isRightKey;
	const bool isLeft = isLeftStick || isLeftKey;

	//	���͂�����Ό������擾
	if (isUp) { _verticalAxis = 1; }
	if (isDown) { _verticalAxis = -1; }
	if (isRight) { _horizontalAxis = 1; }
	if (isLeft) { _horizontalAxis = -1; }
}

//-----------------------------------------------------------------------------
//	@brief	���͎��̌�����ݒ肷��
//-----------------------------------------------------------------------------
void MoveHelper::_SetInputDirPad(float& _verticalAxis, float& _horizontalAxis, Pad& _pad)
{
	//	�p�b�h����
	const bool isUpStick = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_UP, PadInfo::STICK_DEAD_ZONE);
	const bool isDownStick = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_DOWN, PadInfo::STICK_DEAD_ZONE);
	const bool isRightStick = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_RIGHT, PadInfo::STICK_DEAD_ZONE);
	const bool isLeftStick = _pad.GetXInputStickToDpad(PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_LEFT, PadInfo::STICK_DEAD_ZONE);

	//	���͂�����Ό������擾
	if (isUpStick) { _verticalAxis = 1; }
	if (isDownStick) { _verticalAxis = -1; }
	if (isRightStick) { _horizontalAxis = 1; }
	if (isLeftStick) { _horizontalAxis = -1; }
}

//-----------------------------------------------------------------------------
//	@brief	�ړ�����
//-----------------------------------------------------------------------------
VECTOR MoveHelper::_Move(VECTOR& _dir, const float _moveSpeed)
{
	//	�ړ��ʂ̌v��
	VECTOR velocity = VScale(_dir, _moveSpeed);

	//	���K��
	if (VSquareSize(_dir) != 0) { _dir = VNorm(_dir); }

	//	�ړ��ʂ�Ԃ�
	return velocity;
}
