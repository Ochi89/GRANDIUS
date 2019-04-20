
//=============================================================================
//	@file	Pad.h
//	@brief	�p�b�h����
//	@autor	���m ���
//	@date	2018/9/2
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	���O���	[�p�b�h�̎��]
//-----------------------------------------------------------------------------
namespace PadInfo
{

//==================== �񋓑� =====================//

	//	�p�b�h�̎��
	enum PAD_KIND
	{
		PAD_1,	//	�p�b�h�P
		PAD_2,	//	�p�b�h�Q
		PAD_3,	//	�p�b�h�R
		PAD_4,	//	�p�b�h�S
	};

	//	�{�^���̎��
	enum PAD_BUTTON_KIND
	{
		BUTTON_A,			//	A�{�^��
		BUTTON_B,			//	B�{�^��
		BUTTON_X,			//	X�{�^��
		BUTTON_Y,			//	Y�{�^��
		BUTTON_LB,			//	L�{�^��
		BUTTON_RB,			//	R�{�^��
		BUTTON_START,		//	START�{�^��
		BUTTON_BACK,		//	BUCK�{�^��
		BUTTON_LSB,			//	L�X�e�B�b�N�������݃{�^��
		BUTTON_RSB,			//	R�X�e�B�b�N�������݃{�^��
		BUTTON_LT,			//	L�g���K�[
		BUTTON_RT,			//	R�g���K�[
		BUTTON_ALL,			//	���ׂẴ{�^��
	};

	//	DPAD�̎��
	enum PAD_DPAD_KIND
	{
		DPAD_UP,		//	DPAD�@�����
		DPAD_DOWN,		//	DPAD�@������
		DPAD_RIGHT,		//	DPAD�@�E����
		DPAD_LEFT,		//	DPAD�@������
	};

	//	�X�e�B�b�N�̎��
	enum PAD_STICK_KIND
	{
		LEFT_STICK_UP,		//	���X�e�B�b�N�̏����
		LEFT_STICK_DOWN,	//	���X�e�B�b�N�̉�����
		LEFT_STICK_RIGHT,	//	���X�e�B�b�N�̉E����
		LEFT_STICK_LEFT,	//	���X�e�B�b�N�̍�����
		RIGHT_STICK_UP,		//	�E�X�e�B�b�N�̏����
		RIGHT_STICK_DOWN,	//	�E�X�e�B�b�N�̉�����
		RIGHT_STICK_RIGHT,	//	�E�X�e�B�b�N�̉E����
		RIGHT_STICK_LEFT,	//	�E�X�e�B�b�N�̍�����
	};

	//	�X�e�B�b�N��DPAD�̎��
	enum PAD_STICK_TO_DPAD_KIND
	{
		LEFT_STICK_TO_DPAD_UP,		//	���X�e�B�b�N��DPAD�̏����
		LEFT_STICK_TO_DPAD_DOWN,	//	���X�e�B�b�N��DPAD�̉�����
		LEFT_STICK_TO_DPAD_RIGHT,	//	���X�e�B�b�N��DPAD�̉E����
		LEFT_STICK_TO_DPAD_LEFT,	//	���X�e�B�b�N��DPAD�̍�����
		RIGHT_STICK_TO_DPAD_UP,		//	�E�X�e�B�b�N��DPAD�̏����
		RIGHT_STICK_TO_DPAD_DOWN,	//	�E�X�e�B�b�N��DPAD�̉�����
		RIGHT_STICK_TO_DPAD_RIGHT,	//	�E�X�e�B�b�N��DPAD�̉E����
		RIGHT_STICK_TO_DPAD_LEFT,	//	�E�X�e�B�b�N��DPAD�̍�����
	};

//===================== �ÓI�萔 ===================//

	static const int TRIGGER_DEAD_ZONE = 128;		//	�g���K�[���͂̃f�b�h�]�[��
	static const int STICK_DEAD_ZONE = 10000;		//	�X�e�B�b�N���͂̃f�b�h�]�[��
	static const int PAD_VIBRATION_POWER = 1000;	//	�p�b�h�̐U���@�\ ����
	static const int PAD_VIBRATION_LOOP = -1;		//	�p�b�h�̐U���@�\ ���[�v

//===================== �֐� ======================//

	//-----------------------------------------------------------------------------
	//	@brief	���O���	[�֐�]
	//-----------------------------------------------------------------------------
	namespace Function
	{
		//	�U���@�\
		//	�U���̋���( 0�`1000 )
		void VibrationFunction(const PadInfo::PAD_KIND _padKind, const int _vibrationPower, const int _vibrationTime);

		//	�U���@�\
		//	�U���̋��� : �ő�
		//	�i�v���[�v
		void VibrationFunction(const PadInfo::PAD_KIND _padKind);

		//	�U���@�\
		//	�i�v���[�v
		void VibrationFunction(const PadInfo::PAD_KIND _padKind, const int _vibrationPower);

		//	�U���@�\�̏I��
		void EndVibrationFunction(const PadInfo::PAD_KIND _padKind);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�p�b�h���̓N���X
//-----------------------------------------------------------------------------
class Pad final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	Pad();
	~Pad();

	//	���ׂĎg�p���ɂ���
	//	�V�[���؂�ւ����̂Ƃ��̂݌Ă�
	void AllInUse();

	// �p�b�h�̓��͂����
	bool InputPadNum(const PadInfo::PAD_KIND _padKind);

	//	�{�^�����������u��
	bool GetXInputPushButton(const PadInfo::PAD_BUTTON_KIND _buttonKind);

	//	�{�^���𗣂����u��
	bool GetXInputDisuniteButton(const PadInfo::PAD_BUTTON_KIND _buttonKind);

	//	�{�^���̉����Ă����
	bool GetXInputButton(const PadInfo::PAD_BUTTON_KIND _buttonKind);

	//	�g���K�[���������u��
	bool GetXInputPushTrigger(const PadInfo::PAD_BUTTON_KIND _buttonKind, const short _deadZone);

	//	�g���K�[�𗣂����u��
	bool GetXInputDisuniteTrigger(const PadInfo::PAD_BUTTON_KIND _buttonKind, const short _deadZone);

	//	�g���K�[�̉����Ă����
	bool GetXInputTrigger(const PadInfo::PAD_BUTTON_KIND _buttonKind, const short _deadZone);

	//	DPAD�̓���
	bool GetXInputDpad(const PadInfo::PAD_DPAD_KIND _dpadKind);

	//	�X�e�B�b�N�̓���
	bool GetXInputStick(const PadInfo::PAD_STICK_KIND _stickKind, const short _deadZone);

	//	�X�e�b�N��DPAD�̓���
	bool GetXInputStickToDpad(const PadInfo::PAD_STICK_TO_DPAD_KIND _stickToDpadKind, const short _deadZone);

private:

//================== ���������֐� ==================//

	//	�{�^���̉������u��
	bool _PushButton(const int _button, const int _buttonNum);

	//	�{�^���̗������u��
	bool _DisuniteButton(const int _button, const int _buttonNum);

	//	�g���K�[�̉������u��
	bool _PushTrigger(const bool _trigger, const int _buttonNum);

	//	�g���K�[�̗������u��
	bool _DisuniteTrigger(const bool _trigger, const int _buttonNum);

//=================== �����o�ϐ� ===================//

	XINPUT_STATE	m_xInput;												//	xInput
	int				m_nowButton[PadInfo::PAD_BUTTON_KIND::BUTTON_ALL];		//	���t���[���̃{�^���̓���
	int				m_prevButton[PadInfo::PAD_BUTTON_KIND::BUTTON_ALL];		//	�O�t���[���̃{�^���̓���
};

