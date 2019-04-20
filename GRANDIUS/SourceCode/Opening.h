
//=============================================================================
//	@file	Opening.h
//	@brief	�I�[�v�j���O
//	@autor	���m ���
//	@date	2018/1/18
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
//	@brief	�O���錾
//-----------------------------------------------------------------------------
struct UI;
struct Rect;
struct Color;
class Pad;

//-----------------------------------------------------------------------------
//	@brief	�I�[�v�j���O�N���X
//-----------------------------------------------------------------------------
class Opening final
{
public:

//===================== �֐� ======================//

	// �R���X�g���N�^ / �f�X�g���N�^
	Opening();
	~Opening();

	//	����
	static Opening* GetInstance()
	{
		static Opening m_instance;
		return &m_instance;
	}

	//	�X�V����
	void Update(Pad& _pad);

	//	�`�揈��
	void Draw();

//==================== getter =====================//

	//	�I�[�v�j���O�I���t���O�́@getter
	const bool GetIsEndOpening() const { return m_isEndOpening; }

private:

//==================== �񋓑� =====================//

	//	�I�[�v�j���O�̎��
	enum OPENING_KIND
	{
		OPENING_NONE,		//	�Ȃ�
		OPENING_1,			//	�I�[�v�j���O�P
		OPENING_2,			//	�I�[�v�j���O�Q
		OPENING_3,			//	�I�[�v�j���O�R
		OPENING_4,			//	�I�[�v�j���O�S
		OPENING_5,			//	�I�[�v�j���O�T
		OPENING_6,			//	�I�[�v�j���O�U
		OPENING_NUM,		//	�I�[�v�j���O�̐�
	};

//================== ���������֐� ==================//

	//	UI�̓ǂݍ���
	void _LoadUI(UI& _ui, const char* _fileName);

	//	UI�̕`��
	void _DrawUI(UI _ui);

	//	�A���t�@�l�̕ύX
	void _ChangeAlpha();

	//	�A���t�@�l�̉���
	void _AcceleAlpha(Pad& _pad);

	//	�I�[�v�j���O�̃X�L�b�v
	void _OpeningSkip(Pad& _pad);

	//	�I��
	void _EndOpening();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	UI		m_OpeningUI1;			//	�I�[�v�j���OUI 1
	UI		m_OpeningUI2;			//	�I�[�v�j���OUI 2
	UI		m_OpeningUI3;			//	�I�[�v�j���OUI 3
	UI		m_OpeningUI4;			//	�I�[�v�j���OUI 4
	UI		m_OpeningUI5;			//	�I�[�v�j���OUI 5
	UI		m_OpeningUI6;			//	�I�[�v�j���OUI 6
	Rect	m_backGroundRect;		//	�w�i
	Color	m_backGroundColor;		//	�w�i�F
	int		m_openingCount;			//	�I�[�v�j���O�J�E���g
	int		m_alpha;				//	�A���t�@�l
	int		m_alphaSpeed;			//	�A���t�@���x
	float	m_waitTime;				//	�x������
	bool	m_isChangeAlpha;		//	�A���t�@�l�̐؂�ւ��t���O
	bool	m_isStart;				//	�J�n�t���O
	bool	m_isEndOpening;			//	�I�[�v�j���O�I���t���O

//===================== �ÓI�萔 ===================//

	static const int		MIN_ALPHA;				//	�A���t�@�l�̍ŏ�
	static const int		MAX_ALPHA;				//	�A���t�@�l�̍ő�
	static const int		ALPHA_DEFAULT_SPEED;	//	�A���t�@�l�̃f�t�H���g���x
	static const int		ALPHA_ACCELE_SPEED;		//	�A���t�@�l�̃A�N�Z�����x

};

#define OPENING Opening::GetInstance()
