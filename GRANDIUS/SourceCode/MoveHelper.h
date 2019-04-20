
//=============================================================================
//	@file	Moving.h
//	@brief	�ړ�����
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
//	@brief	�ړ������N���X
//-----------------------------------------------------------------------------
class MoveHelper final
{
public:

//===================== �֐� ======================//

	//	�ړ��ʂ����߂�
	static VECTOR AskMoveAmount(VECTOR& _dir, Pad& _pad, const float _moveSpeed, const bool _isInputKey, const bool _isUseAxisXY);

	//	�ړ��ʂ����߂�
	static VECTOR AskMoveAmount(VECTOR& _dir, const float _moveSpeed);

private:

//================== ���������֐� ==================//

	//	���Z�b�g
	static void _ResetDir(VECTOR& _dir);

	//	3D���̈ړ�����
	static VECTOR _MoveAxisXZ(VECTOR& _dir, Pad& _pad, const float _moveSpeed, const bool _isInputKey);

	//	2D���̈ړ�����
	static VECTOR _MoveAxisXY(VECTOR& _dir, Pad& _pad, const float _moveSpeed, const bool _isInputKey);

	//	��Ɉړ�����
	static VECTOR _AlwaysMove(VECTOR& _dir, const float _moveSpeed);

	//	�ړ�����
	static VECTOR _Move(VECTOR& _dir, const float _moveSpeed);

	//	���͎��̌�����ݒ肷��
	static void _SetInputDirKeyToPad(float& _verticalAxis, float& _horizontalAxis, Pad& _pad);

	//	���͎��̌�����ݒ肷��
	static void _SetInputDirPad(float& _verticalAxis, float& _horizontalAxis, Pad& _pad);

};