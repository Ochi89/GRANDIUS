
//=============================================================================
//	@file	Pad.h
//	@brief	�p�b�h
//	@autor	���m ���
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Pad.h"

//-----------------------------------------------------------------------------
//	@brief	���O���	[�p�b�h��]���
//-----------------------------------------------------------------------------
namespace PadInfo
{
	//-----------------------------------------------------------------------------
	//	@brief	�p�b�h�̐U���@�\�̃J�o�[�֐�
	//-----------------------------------------------------------------------------
	namespace Function
	{
		//-----------------------------------------------------------------------------
		//	@brief	�U���@�\
		//			�U���̋���( 0�`1000 )
		//-----------------------------------------------------------------------------
		void VibrationFunction(const PAD_KIND _padKind, const int _vibrationPower, const int _vibrationTime)
		{
			//	�p�b�h�̐U���@�\
			switch (_padKind)
			{
				//	�p�b�h�P
			case PadInfo::PAD_KIND::PAD_1:
				StartJoypadVibration(DX_INPUT_PAD1, _vibrationPower, _vibrationTime);
				break;

				//	�p�b�h�Q
			case PadInfo::PAD_KIND::PAD_2:
				StartJoypadVibration(DX_INPUT_PAD2, _vibrationPower, _vibrationTime);
				break;

				//	�p�b�h�R
			case PadInfo::PAD_KIND::PAD_3:
				StartJoypadVibration(DX_INPUT_PAD3, _vibrationPower, _vibrationTime);
				break;

				//	�p�b�h�S
			case PadInfo::PAD_KIND::PAD_4:
				StartJoypadVibration(DX_INPUT_PAD4, _vibrationPower, _vibrationTime);
				break;
			}
		}
		
		//-----------------------------------------------------------------------------
		//	@brief	�U���@�\
		//			�U���̋��� : �ő�
		//			�i�v���[�v
		//-----------------------------------------------------------------------------
		void VibrationFunction(const PadInfo::PAD_KIND _padKind)
		{
			//	�p�b�h�̐U���@�\
			switch (_padKind)
			{
				//	�p�b�h�P
			case PadInfo::PAD_KIND::PAD_1:
				StartJoypadVibration(DX_INPUT_PAD1, PAD_VIBRATION_POWER, PAD_VIBRATION_LOOP);
				break;

				//	�p�b�h�Q
			case PadInfo::PAD_KIND::PAD_2:
				StartJoypadVibration(DX_INPUT_PAD2, PAD_VIBRATION_POWER, PAD_VIBRATION_LOOP);
				break;

				//	�p�b�h�R
			case PadInfo::PAD_KIND::PAD_3:
				StartJoypadVibration(DX_INPUT_PAD3, PAD_VIBRATION_POWER, PAD_VIBRATION_LOOP);
				break;

				//	�p�b�h�S
			case PadInfo::PAD_KIND::PAD_4:
				StartJoypadVibration(DX_INPUT_PAD4, PAD_VIBRATION_POWER, PAD_VIBRATION_LOOP);
				break;
			}
		}

		//-----------------------------------------------------------------------------
		//	@brief	�U���@�\
		//			�U���̋���( 0�`1000 )
		//			�i�v���[�v
		//-----------------------------------------------------------------------------
		void VibrationFunction(const PAD_KIND _padKind, const int _vibrationPower)
		{
			//	�p�b�h�̐U���@�\
			switch (_padKind)
			{
				//	�p�b�h�P
			case PadInfo::PAD_KIND::PAD_1:
				StartJoypadVibration(DX_INPUT_PAD1, _vibrationPower, PAD_VIBRATION_LOOP);
				break;

				//	�p�b�h�Q
			case PadInfo::PAD_KIND::PAD_2:
				StartJoypadVibration(DX_INPUT_PAD2, _vibrationPower, PAD_VIBRATION_LOOP);
				break;

				//	�p�b�h�R
			case PadInfo::PAD_KIND::PAD_3:
				StartJoypadVibration(DX_INPUT_PAD3, _vibrationPower, PAD_VIBRATION_LOOP);
				break;

				//	�p�b�h�S
			case PadInfo::PAD_KIND::PAD_4:
				StartJoypadVibration(DX_INPUT_PAD4, _vibrationPower, PAD_VIBRATION_LOOP);
				break;
			}
		}

		//-----------------------------------------------------------------------------
		//	@brief	�U���@�\�̏I��
		//-----------------------------------------------------------------------------
		void EndVibrationFunction(const PAD_KIND _padKind)
		{
			//	�U���@�\�̃��[�v���I������
			switch (_padKind)
			{
				//	�p�b�h�P
			case PadInfo::PAD_KIND::PAD_1:
				StopJoypadVibration(DX_INPUT_PAD1);
				break;

				//	�p�b�h�Q
			case PadInfo::PAD_KIND::PAD_2:
				StopJoypadVibration(DX_INPUT_PAD2);
				break;

				//	�p�b�h�R
			case PadInfo::PAD_KIND::PAD_3:
				StopJoypadVibration(DX_INPUT_PAD3);
				break;

				//	�p�b�h�S
			case PadInfo::PAD_KIND::PAD_4:
				StopJoypadVibration(DX_INPUT_PAD4);
				break;
			}
		}
	}
}



//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Pad::Pad()
{
	for (int i = 0; i < PadInfo::PAD_BUTTON_KIND::BUTTON_ALL; i++)
	{
		m_nowButton[i] = 0;
		m_prevButton[i] = 0;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Pad::~Pad()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	���ׂĎg�p���ɂ���
//			�V�[���؂�ւ����̂Ƃ��̂݌Ă�
//-----------------------------------------------------------------------------
void Pad::AllInUse()
{
	for (int i = 0; i < PadInfo::PAD_BUTTON_KIND::BUTTON_ALL; i++)
	{
		m_prevButton[i] = 1;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�p�b�h�̓o�^
//-----------------------------------------------------------------------------
bool Pad::InputPadNum(const PadInfo::PAD_KIND _padKind)
{
	//	�p�b�h�̓��͂����
	switch (_padKind)
	{
		//	�p�b�h�P
	case PadInfo::PAD_KIND::PAD_1:
		GetJoypadXInputState(DX_INPUT_PAD1, &m_xInput);
		return true;

		//	�p�b�h�Q
	case PadInfo::PAD_KIND::PAD_2:
		GetJoypadXInputState(DX_INPUT_PAD2, &m_xInput);
		return true;

		//	�p�b�h�R
	case PadInfo::PAD_KIND::PAD_3:
		GetJoypadXInputState(DX_INPUT_PAD3, &m_xInput);
		return true;

		//	�p�b�h�S
	case PadInfo::PAD_KIND::PAD_4:
		GetJoypadXInputState(DX_INPUT_PAD4, &m_xInput);
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�{�^���������ꂽ�u��
//-----------------------------------------------------------------------------
bool Pad::GetXInputPushButton(const PadInfo::PAD_BUTTON_KIND _buttonKind)
{
	switch (_buttonKind)
	{

	//	A�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_A:
		if (_PushButton(XINPUT_BUTTON_A, PadInfo::PAD_BUTTON_KIND::BUTTON_A)) { return true; }
		return false;

	//	B�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_B:
		if (_PushButton(XINPUT_BUTTON_B, PadInfo::PAD_BUTTON_KIND::BUTTON_B)) { return true; }
		return false;

	//	X�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_X:
		if (_PushButton(XINPUT_BUTTON_X, PadInfo::PAD_BUTTON_KIND::BUTTON_X)) { return true; }
		return false;

	//	Y�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_Y:
		if (_PushButton(XINPUT_BUTTON_Y, PadInfo::PAD_BUTTON_KIND::BUTTON_Y)) { return true; }
		return false;

	//	LB�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LB:
		if (_PushButton(XINPUT_BUTTON_LEFT_SHOULDER, PadInfo::PAD_BUTTON_KIND::BUTTON_LB)) { return true; }
		return false;

	//	RB�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RB:
		if (_PushButton(XINPUT_BUTTON_RIGHT_SHOULDER, PadInfo::PAD_BUTTON_KIND::BUTTON_RB)) { return true; }
		return false;

	//	START�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_START:
		if (_PushButton(XINPUT_BUTTON_START, PadInfo::PAD_BUTTON_KIND::BUTTON_START)) { return true; }
		return false;

	//	BACK�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_BACK:
		if (_PushButton(XINPUT_BUTTON_BACK, PadInfo::PAD_BUTTON_KIND::BUTTON_BACK)) { return true; }
		return false;

	//	���X�`�b�N�������݃{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LSB:
		if (_PushButton(XINPUT_BUTTON_LEFT_THUMB, PadInfo::PAD_BUTTON_KIND::BUTTON_LSB)) { return true; }
		return false;

	//	�E�X�e�B�b�N�������݃{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RSB:
		if (_PushButton(XINPUT_BUTTON_RIGHT_THUMB, PadInfo::PAD_BUTTON_KIND::BUTTON_RSB)) { return true; }
		return false;

	//	���ׂ�
	case PadInfo::PAD_BUTTON_KIND::BUTTON_ALL:
		if (_PushButton(XINPUT_BUTTON_A, PadInfo::PAD_BUTTON_KIND::BUTTON_A)) { return true; }				//	A�{�^��
		if (_PushButton(XINPUT_BUTTON_B, PadInfo::PAD_BUTTON_KIND::BUTTON_B)) { return true; }				//	B�{�^��
		if (_PushButton(XINPUT_BUTTON_X, PadInfo::PAD_BUTTON_KIND::BUTTON_X)) { return true; }				//	X�{�^��
		if (_PushButton(XINPUT_BUTTON_Y, PadInfo::PAD_BUTTON_KIND::BUTTON_Y)) { return true; }				//	Y�{�^��
		if (_PushButton(XINPUT_BUTTON_LEFT_SHOULDER, PadInfo::PAD_BUTTON_KIND::BUTTON_LB)) { return true; }	//	LB�{�^��
		if (_PushButton(XINPUT_BUTTON_RIGHT_SHOULDER, PadInfo::PAD_BUTTON_KIND::BUTTON_RB)) { return true; }	//	RB�{�^��
		if (_PushButton(XINPUT_BUTTON_START, PadInfo::PAD_BUTTON_KIND::BUTTON_START)) { return true; }		//	START�{�^��
		if (_PushButton(XINPUT_BUTTON_BACK, PadInfo::PAD_BUTTON_KIND::BUTTON_BACK)) { return true; }			//	BACK�{�^��
		if (_PushButton(XINPUT_BUTTON_LEFT_THUMB, PadInfo::PAD_BUTTON_KIND::BUTTON_LSB)) { return true; }	//	���X�`�b�N�������݃{�^��
		if (_PushButton(XINPUT_BUTTON_RIGHT_THUMB, PadInfo::PAD_BUTTON_KIND::BUTTON_RSB)) { return true; }	//	�E�X�e�B�b�N�������݃{�^��
		return false;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�{�^���������ꂽ�u��
//-----------------------------------------------------------------------------
bool Pad::GetXInputDisuniteButton(const PadInfo::PAD_BUTTON_KIND _buttonKind)
{
	switch (_buttonKind)
	{

		//	A�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_A:
		if (_DisuniteButton(XINPUT_BUTTON_A, PadInfo::PAD_BUTTON_KIND::BUTTON_A)) { return true; }
		return false;

		//	B�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_B:
		if (_DisuniteButton(XINPUT_BUTTON_B, PadInfo::PAD_BUTTON_KIND::BUTTON_B)) { return true; }
		return false;

		//	X�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_X:
		if (_DisuniteButton(XINPUT_BUTTON_X, PadInfo::PAD_BUTTON_KIND::BUTTON_X)) { return true; }
		return false;

		//	Y�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_Y:
		if (_DisuniteButton(XINPUT_BUTTON_Y, PadInfo::PAD_BUTTON_KIND::BUTTON_Y)) { return true; }
		return false;

		//	LB�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LB:
		if (_DisuniteButton(XINPUT_BUTTON_LEFT_SHOULDER, PadInfo::PAD_BUTTON_KIND::BUTTON_LB)) { return true; }
		return false;

		//	RB�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RB:
		if (_DisuniteButton(XINPUT_BUTTON_RIGHT_SHOULDER, PadInfo::PAD_BUTTON_KIND::BUTTON_RB)) { return true; }
		return false;

		//	START�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_START:
		if (_DisuniteButton(XINPUT_BUTTON_START, PadInfo::PAD_BUTTON_KIND::BUTTON_START)) { return true; }
		return false;

		//	BACK�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_BACK:
		if (_DisuniteButton(XINPUT_BUTTON_BACK, PadInfo::PAD_BUTTON_KIND::BUTTON_BACK)) { return true; }
		return false;

		//	���X�`�b�N�������݃{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LSB:
		if (_DisuniteButton(XINPUT_BUTTON_LEFT_THUMB, PadInfo::PAD_BUTTON_KIND::BUTTON_LSB)) { return true; }
		return false;

		//	�E�X�e�B�b�N�������݃{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RSB:
		if (_DisuniteButton(XINPUT_BUTTON_RIGHT_THUMB, PadInfo::PAD_BUTTON_KIND::BUTTON_RSB)) { return true; }
		return false;

		//	���ׂ�
	case PadInfo::PAD_BUTTON_KIND::BUTTON_ALL:
		if (_DisuniteButton(XINPUT_BUTTON_A, PadInfo::PAD_BUTTON_KIND::BUTTON_A)) { return true; }				//	A�{�^��
		if (_DisuniteButton(XINPUT_BUTTON_B, PadInfo::PAD_BUTTON_KIND::BUTTON_B)) { return true; }				//	B�{�^��
		if (_DisuniteButton(XINPUT_BUTTON_X, PadInfo::PAD_BUTTON_KIND::BUTTON_X)) { return true; }				//	X�{�^��
		if (_DisuniteButton(XINPUT_BUTTON_Y, PadInfo::PAD_BUTTON_KIND::BUTTON_Y)) { return true; }				//	Y�{�^��
		if (_DisuniteButton(XINPUT_BUTTON_LEFT_SHOULDER, PadInfo::PAD_BUTTON_KIND::BUTTON_LB)) { return true; }	//	LB�{�^��
		if (_DisuniteButton(XINPUT_BUTTON_RIGHT_SHOULDER, PadInfo::PAD_BUTTON_KIND::BUTTON_RB)) { return true; }	//	RB�{�^��
		if (_DisuniteButton(XINPUT_BUTTON_START, PadInfo::PAD_BUTTON_KIND::BUTTON_START)) { return true; }		//	START�{�^��
		if (_DisuniteButton(XINPUT_BUTTON_BACK, PadInfo::PAD_BUTTON_KIND::BUTTON_BACK)) { return true; }			//	BACK�{�^��
		if (_DisuniteButton(XINPUT_BUTTON_LEFT_THUMB, PadInfo::PAD_BUTTON_KIND::BUTTON_LSB)) { return true; }	//	���X�`�b�N�������݃{�^��
		if (_DisuniteButton(XINPUT_BUTTON_RIGHT_THUMB, PadInfo::PAD_BUTTON_KIND::BUTTON_RSB)) { return true; }	//	�E�X�e�B�b�N�������݃{�^��
		return false;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�{�^������
//-----------------------------------------------------------------------------
bool Pad::GetXInputButton(const PadInfo::PAD_BUTTON_KIND _buttonKind)
{
	switch (_buttonKind)
	{
		//	A�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_A:
		if (m_xInput.Buttons[XINPUT_BUTTON_A]) { return true; }
		return false;

		//	B�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_B:
		if (m_xInput.Buttons[XINPUT_BUTTON_B]) { return true; }
		return false;

		//	X�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_X:
		if (m_xInput.Buttons[XINPUT_BUTTON_X]) { return true; }
		return false;

		//	Y�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_Y:
		if (m_xInput.Buttons[XINPUT_BUTTON_Y]) { return true; }
		return false;

		//	LB�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LB:
		if (m_xInput.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]) { return true; }
		return false;

		//	RB�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RB:
		if (m_xInput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]) { return true; }
		return false;

		//	START�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_START:
		if (m_xInput.Buttons[XINPUT_BUTTON_START]) { return true; }
		return false;

		//	BACK�{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_BACK:
		if (m_xInput.Buttons[XINPUT_BUTTON_BACK]) { return true; }
		return false;

		//	���X�`�b�N�������݃{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LSB:
		if (m_xInput.Buttons[XINPUT_BUTTON_LEFT_THUMB]) { return true; }
		return false;

		//	�E�X�e�B�b�N�������݃{�^��
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RSB:
		if (m_xInput.Buttons[XINPUT_BUTTON_RIGHT_THUMB]) { return true; }
		return false;

		//	���ׂ�
	case PadInfo::PAD_BUTTON_KIND::BUTTON_ALL:
		if (m_xInput.Buttons[XINPUT_BUTTON_A]) { return true; }					//	A�{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_B]) { return true; }					//	B�{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_X]) { return true; }					//	X�{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_Y]) { return true; }					//	Y�{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_LEFT_SHOULDER]) { return true; }		//	LB�{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER]) { return true; }	//	RB�{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_START]) { return true; }				//	START�{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_BACK]) { return true; }				//	BACK�{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_LEFT_THUMB]) { return true; }		//	���X�`�b�N�������݃{�^��
		if (m_xInput.Buttons[XINPUT_BUTTON_RIGHT_THUMB]) { return true; }		//	�E�X�e�B�b�N�������݃{�^��
		return false;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�g���K�[�������u��
//-----------------------------------------------------------------------------
bool Pad::GetXInputPushTrigger(const PadInfo::PAD_BUTTON_KIND _buttonKind, const short _deadZone)
{
	switch (_buttonKind)
	{
		//	���g���K�[
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LT:
		if (_PushTrigger(m_xInput.LeftTrigger >= _deadZone, PadInfo::PAD_BUTTON_KIND::BUTTON_LT)) { return true; }
		return false;

		//	�E�g���K�[
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RT:
		if (_PushTrigger(m_xInput.RightTrigger >= _deadZone, PadInfo::PAD_BUTTON_KIND::BUTTON_RT)) { return true; }
		return false;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�g���K�[�������u��
//-----------------------------------------------------------------------------
bool Pad::GetXInputDisuniteTrigger(const PadInfo::PAD_BUTTON_KIND _buttonKind, const short _deadZone)
{
	switch (_buttonKind)
	{
		//	���g���K�[
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LT:
		if (_DisuniteTrigger(m_xInput.LeftTrigger >= _deadZone, PadInfo::PAD_BUTTON_KIND::BUTTON_LT)) { return true; }
		return false;

		//	�E�g���K�[
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RT:
		if (_DisuniteTrigger(m_xInput.RightTrigger >= _deadZone, PadInfo::PAD_BUTTON_KIND::BUTTON_RT)) { return true; }
		return false;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�g���K�[����
//-----------------------------------------------------------------------------
bool Pad::GetXInputTrigger(const PadInfo::PAD_BUTTON_KIND _buttonKind, const short _deadZone)
{
	switch (_buttonKind)
	{
		//	���g���K�[
	case PadInfo::PAD_BUTTON_KIND::BUTTON_LT:
		if (m_xInput.LeftTrigger >= _deadZone) { return true; }
		return false;

		//	�E�g���K�[
	case PadInfo::PAD_BUTTON_KIND::BUTTON_RT:
		if (m_xInput.RightTrigger >= _deadZone) { return true; }
		return false;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	DPAD����
//-----------------------------------------------------------------------------
bool Pad::GetXInputDpad(const PadInfo::PAD_DPAD_KIND _dpadKind)
{
	switch (_dpadKind)
	{
		//	�\���L�[�̏����
	case PadInfo::PAD_DPAD_KIND::DPAD_UP:
		if (m_xInput.Buttons[XINPUT_BUTTON_DPAD_UP]) { return true; }
		return false;

	//	�\���L�[�̉�����
	case PadInfo::PAD_DPAD_KIND::DPAD_DOWN:
		if (m_xInput.Buttons[XINPUT_BUTTON_DPAD_DOWN]) { return true; }
		return false;

	//	�\���L�[�̉E����
	case PadInfo::PAD_DPAD_KIND::DPAD_RIGHT:
		if (m_xInput.Buttons[XINPUT_BUTTON_DPAD_RIGHT]) { return true; }
		return false;

	//	�\���L�[�̍�����
	case PadInfo::PAD_DPAD_KIND::DPAD_LEFT:
		if (m_xInput.Buttons[XINPUT_BUTTON_DPAD_LEFT]) { return true; }
		return false;
	}
	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�X�e�b�N����
//-----------------------------------------------------------------------------
bool Pad::GetXInputStick(const PadInfo::PAD_STICK_KIND _stickKind, const short _deadZone)
{
	switch (_stickKind)
	{

		//	���X�e�B�b�N�@�����
	case PadInfo::PAD_STICK_KIND::LEFT_STICK_UP:
		if (m_xInput.ThumbLY >= _deadZone) { return true; }
		return false;

		//	���X�e�B�b�N�@������
	case PadInfo::PAD_STICK_KIND::LEFT_STICK_DOWN:
		if (m_xInput.ThumbLY <= -_deadZone) { return true; }
		return false;

		//	���X�e�B�b�N�@�E����
	case PadInfo::PAD_STICK_KIND::LEFT_STICK_RIGHT:
		if (m_xInput.ThumbLX >= _deadZone) { return true; }
		return false;

		//	���X�e�B�b�N�@������
	case PadInfo::PAD_STICK_KIND::LEFT_STICK_LEFT:
		if (m_xInput.ThumbLX <= -_deadZone) { return true; }
		return false;

		//	�E�X�e�B�b�N�@�����
	case PadInfo::PAD_STICK_KIND::RIGHT_STICK_UP:
		if (m_xInput.ThumbRY >= _deadZone) { return true; }
		return false;

		//	�E�X�e�B�b�N�@������
	case PadInfo::PAD_STICK_KIND::RIGHT_STICK_DOWN:
		if (m_xInput.ThumbRY <= -_deadZone) { return true; }
		return false;

		//	�E�X�e�B�b�N�@�E����
	case PadInfo::PAD_STICK_KIND::RIGHT_STICK_RIGHT:
		if (m_xInput.ThumbRX >= _deadZone) { return true; }
		return false;

		//	�E�X�e�B�b�N�@������
	case PadInfo::PAD_STICK_KIND::RIGHT_STICK_LEFT:
		if (m_xInput.ThumbRX <= -_deadZone) { return true; }
		return false;
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�X�e�b�N���͂�DPAD����
//-----------------------------------------------------------------------------
bool Pad::GetXInputStickToDpad(const PadInfo::PAD_STICK_TO_DPAD_KIND _stickToDpadKind, const short _deadZone)
{
	switch (_stickToDpadKind)
	{
		//	���X�e�B�b�N�Ə\���L�[�̏����
	case PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_UP:
	{
		const bool isActive = m_xInput.Buttons[XINPUT_BUTTON_DPAD_UP] || m_xInput.ThumbLY >= _deadZone;
		if (isActive) { return true; }
		return false;
	}

	//	���X�e�B�b�N�Ə\���L�[�̉�����
	case PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_DOWN:
	{
		const bool isActive = m_xInput.Buttons[XINPUT_BUTTON_DPAD_DOWN] || m_xInput.ThumbLY <= -_deadZone;
		if (isActive) { return true; }
		return false;
	}

	//	���X�e�B�b�N�Ə\���L�[�̉E����
	case PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_RIGHT:
	{
		const bool isActive = m_xInput.Buttons[XINPUT_BUTTON_DPAD_RIGHT] || m_xInput.ThumbLX >= _deadZone;
		if (isActive) { return true; }
		return false;
	}

	//	���X�e�B�b�N�Ə\���L�[�̍�����
	case PadInfo::PAD_STICK_TO_DPAD_KIND::LEFT_STICK_TO_DPAD_LEFT:
	{
		const bool isActive = m_xInput.Buttons[XINPUT_BUTTON_DPAD_LEFT] || m_xInput.ThumbLX <= -_deadZone;
		if (isActive) { return true; }
		return false;
	}

	//	�E�X�e�B�b�N�Ə\���L�[�̏����
	case PadInfo::PAD_STICK_TO_DPAD_KIND::RIGHT_STICK_TO_DPAD_UP:
	{
		const bool isActive = m_xInput.Buttons[XINPUT_BUTTON_DPAD_UP] || m_xInput.ThumbRY >= _deadZone;
		if (isActive) { return true; }
		return false;
	}

	//	�E�X�e�B�b�N�Ə\���L�[�̉�����
	case PadInfo::PAD_STICK_TO_DPAD_KIND::RIGHT_STICK_TO_DPAD_DOWN:
	{
		const bool isActive = m_xInput.Buttons[XINPUT_BUTTON_DPAD_DOWN] || m_xInput.ThumbRY <= -_deadZone;
		if (isActive) { return true; }
		return false;
	}

	//	�E�X�e�B�b�N�Ə\���L�[�̉E����
	case PadInfo::PAD_STICK_TO_DPAD_KIND::RIGHT_STICK_TO_DPAD_RIGHT:
	{
		const bool isActive = m_xInput.Buttons[XINPUT_BUTTON_DPAD_RIGHT] || m_xInput.ThumbRX >= _deadZone;
		if (isActive) { return true; }
		return false;
	}

	//	�E�X�e�B�b�N�Ə\���L�[�̍�����
	case PadInfo::PAD_STICK_TO_DPAD_KIND::RIGHT_STICK_TO_DPAD_LEFT:
	{
		const bool isActive = m_xInput.Buttons[XINPUT_BUTTON_DPAD_LEFT] || m_xInput.ThumbRX <= -_deadZone;
		if (isActive) { return true; }
		return false;
	}

	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�{�^�����������u��
//-----------------------------------------------------------------------------
bool Pad::_PushButton(const int _button, const int _buttonNum)
{
	if (m_xInput.Buttons[_button])
	{
		if (m_prevButton[_buttonNum] == 0)
		{
			//	������
			m_prevButton[_buttonNum] = 1;
			return true;
		}
		return false;
	}
	else
	{
		//	������
		m_prevButton[_buttonNum] = 0;
		return false;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�{�^���𗣂����u��
//-----------------------------------------------------------------------------
bool Pad::_DisuniteButton(const int _button, const int _buttonNum)
{
	if (m_xInput.Buttons[_button])
	{
		if (m_prevButton[_buttonNum] == 0)
		{
			//	������
			m_nowButton[_buttonNum] = 1;
		}
	}
	else
	{
		if (m_prevButton[_buttonNum] == 1)
		{
			//	������
			m_nowButton[_buttonNum] = 0;
			m_prevButton[_buttonNum] = m_nowButton[_buttonNum];
			return true;
		}
	}

	m_prevButton[_buttonNum] = m_nowButton[_buttonNum];
	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�{�^�����������u��
//-----------------------------------------------------------------------------
bool Pad::_PushTrigger(const bool _trigger, const int _buttonNum)
{
	if (_trigger)
	{
		if (m_prevButton[_buttonNum] == 0)
		{
			//	������
			m_prevButton[_buttonNum] = 1;
			return true;
		}
		return false;
	}
	else
	{
		//	������
		m_prevButton[_buttonNum] = 0;
		return false;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�{�^���𗣂����u��
//-----------------------------------------------------------------------------
bool Pad::_DisuniteTrigger(const bool _trigger, const int _buttonNum)
{
	if (_trigger)
	{
		if (m_prevButton[_buttonNum] == 0)
		{
			//	������
			m_nowButton[_buttonNum] = 1;
		}
	}
	else
	{
		if (m_prevButton[_buttonNum] == 1)
		{
			//	������
			m_nowButton[_buttonNum] = 0;
			m_prevButton[_buttonNum] = m_nowButton[_buttonNum];
			return true;
		}
	}

	m_prevButton[_buttonNum] = m_nowButton[_buttonNum];
	return false;
}
