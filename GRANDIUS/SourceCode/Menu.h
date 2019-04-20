
//=============================================================================
//	@file	Menu.h
//	@brief	���j���[
//	@autor	���m ���
//	@date	2018/1/8
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
class Pad;
struct Rect;
struct UI;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�X�R�A�N���X
//-----------------------------------------------------------------------------
class Menu final
{
public:

//===================== �֐� ======================//

	//	�f�X�g���N�^
	~Menu();

	//	����
	static Menu* GetInstance()
	{
		static Menu s_instance;
		return &s_instance;
	}

	//	��������
	void Initialize();

	//	�X�V
	void Update(Pad& _pad, SoundEffect& _soundEffect);

	//	�`��
	void Draw();

//==================== getter =====================//

	//	�^�C�g���t���O�� getter
	const bool& GetIsGoToTitle() const { return m_isGoToTitle; }

	//	�X�V�X�L�b�v�t���O�� getter
	const bool& GetIsSkipUpdate() const { return m_isSkipUpdate; }

private:

//================== �V���O���g�� ==================//

	//	�R���X�g���N�^
	Menu();

//==================== �񋓑� =====================//

	//	���[�h
	enum MODE
	{
		MODE_OPERATION,		//	�������
		MODE_TITLE,			//	�^�C�g����
		MODE_BACK,			//	�߂�
		MODE_NUM,			//	���[�h�̐�
	};

	//	�J�E���g�_�E��
	enum COUNTDOWN
	{
		COUNTDOWN_1,		//	�P
		COUNTDOWN_2,		//	�Q
		COUNTDOWN_3,		//	�R
		COUNTDOWN_NUM,		//	��
	};

//================== ���������֐� ==================//

	//	���j���[�J��
	void _MenuOpeningAndClosing(Pad& _pad, SoundEffect& _soundEffect);

	//	���[�h�؂�ւ�
	void _ChangeMode(Pad& _pad, SoundEffect& _soundEffect);

	//	�I���ʒu�̕ύX
	void _ChangeSelectPos();

	//	���[�h
	void _Mode(Pad& _pad, SoundEffect& _soundEffect);

	//	�I���t���[���̊g�嗦
	void _ChangeSelectScale();

	//	�J�E���g�_�E��
	void _Countdown(SoundEffect& _soundEffect);

	//	���j���[�̕`��
	void _MenuDraw();

	//	��������̕`��
	void _OperationDraw();

	//	�J�E���g�_�E���̕`��
	void _CountdownDraw();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int		m_modeNumber;								//	���[�h�ԍ�
	int		m_countdown;								//	�J�E���g�_�E��
	float	m_watiTime;									//	�x������
	float	m_countdownTime;							//	�J�E���g�_�E������
	bool	m_isMenuState;								//	���j���|�̏��
	bool	m_isMenuDraw;								//	���j���|�̕`��
	bool	m_isMenu;									//	���j���|
	bool	m_isOperation;								//	�������
	bool	m_isGoToTitle;								//	�^�C�g����
	bool	m_isSelectScaleState;						//	�I���t���[���̊g�嗦�̏��
	bool	m_isSkipUpdate;								//	�X�V�̃X�L�b�v
	bool	m_isCountdownStart;							//	�J�E���g�_�E���̊J�n
	Rect	m_menuFlame;								//	���j���[�t���[��
	UI		m_topFlame;									//	��t���[��UI
	UI		m_underFlame;								//	���t���[��UI
	UI		m_mode[MODE::MODE_NUM];						//	���[�hUI
	UI		m_select;									//	�I��UI
	UI		m_operation;								//	����UI
	UI		m_countdownUI[COUNTDOWN::COUNTDOWN_NUM];	//	�J�E���g�_�E��UI

//===================== �ÓI�萔 ===================//

	static const int		MAX_MODE;					//	�ő�
	static const int		MIN_MODE;					//	�ŏ�
	static const VECTOR		SELECT_CORRECTION;			//	�I���ʒu�̒���
	static const float		MAX_FLAME;					//	�ő�t���[��
	static const float		MIN_FLAME;					//	�ŏ��t���[��
	static const float		MAX_WAIT_TIME;				//	�x��
	static const float		FONT_SIZE;					//	�����T�C�Y
	static const float		SELECT_POS_1;				//	�I���t���[���̈ʒu�P
	static const float		SELECT_POS_2;				//	�I���t���[���̈ʒu�Q
	static const float		SELECT_POS_3;				//	�I���t���[���̈ʒu�R
	static const float		SELECT_SCALE_SPEED;			//	�I���t���[���̊g�嗦�̑��x
	static const float		MIN_SELECT_SCALE;			//	�I���t���[���̊g�嗦�̍ŏ�
	static const float		MAX_SELECT_SCALE;			//	�I���t���[���̊g�嗦�̍ő�
	static const float		MAX_COUNTDOWN_TIME;			//	�J�E���g�_�E�����Ԃ̍ő�
	static const int		MAX_COUNTDOWN;				//	�J�E���g�_�E���̍ő�
	static const float		COUNTDOWN_SCALE_SPEED;		//	�J�E���g�_�E���̊g�嗦�̑��x
};

#define MENU Menu::GetInstance()