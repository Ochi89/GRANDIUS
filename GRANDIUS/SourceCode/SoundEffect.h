
//=============================================================================
//	@file	SoundEffect.h
//	@brief	�T�E���h�G�t�F�N�g
//	@autor	���m ���
//	@date	2018/1/04
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
#include <list>

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class Sound;

//-----------------------------------------------------------------------------
//	@brief	�T�E���h�G�t�F�N�g�N���X
//-----------------------------------------------------------------------------
class SoundEffect final
{
public:
	
//==================== �񋓑� =====================//

	//	SE�̎��
	enum SE_KIND
	{
		SE_ITEM,			//	�A�C�e���擾SE
		SE_SHOT,			//	�V���b�gSE
		SE_MOVE_SHOT,		//	�؍݃V���b�gSE�P
		SE_STAY_SHOT,		//	�؍݃V���b�gSE�Q
		SE_HIT,				//	�q�b�gSE
		SE_EXPLOSION,		//	����SE
		SE_NUM,				//	SE�̐�
	};

	//	SE�̎��
	enum ONE_SE_KIND
	{
		ONE_SE_SELECT,				//	�Z���N�gSE
		ONE_SE_PLAYER_LASER,		//	�v���C���[���[�U�[SE
		ONE_SE_ENEMY_LASER,			//	�G�l�~�[���[�U�[SE
		ONE_SE_ROCKET,				//	���P�b�gSE
		ONE_SE_WARNING,				//	�x����SE
		ONE_SE_TITLE,				//	�^�C�g��SE
		ONE_SE_MENU_OPEN,			//	���j���[�J��SE
		ONE_SE_MENU_CLOSE,			//	���j���[����SE
		ONE_SE_MENU_BACK,			//	���j���[�o�b�NSE
		ONE_SE_MENU_CURSOR,			//	���j���[�J�[�\��SE
		ONE_SE_MENU_DECISION,		//	���j���[����SE
		ONE_SE_MENU_COUNTDOWN,		//	���j���[�J�E���g�_�E��SE
		ONE_SE_GAUGE_MAX,			//	�Q�[�W�ő�SE
		ONE_SE_STAY_SHOT_GAUGE_MAX,	//	�؍݃V���b�g�̃Q�[�W�ő�SE
		ONE_SE_WIND,				//	���o�̕�SE
		ONE_SE_SCORE_UP,				//	�X�R�A�A�b�vSE
		ONE_SE_NUM,					//	SE�̐�
	};

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	SoundEffect();
	~SoundEffect();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	�X�V����
	void Update();

	//	�Đ�����
	void OnPlaySound(const SE_KIND _kind);

	//	�Đ�����
	void OnPlaySound(const ONE_SE_KIND _kind);

private:

//==================== �\���� =====================//

	//	SE�o�b�t�@
	struct SeBuffer
	{
		Sound*	m_pBuf[CommonConstant::MAX_ENEMY_SE_NUM];		//	�o�b�t�@
		bool	m_isInUse[CommonConstant::MAX_ENEMY_SE_NUM];	//	�������̎g�p��
	};

	//	SE�o�b�t�@
	struct OneSeBuffer
	{
		Sound*	m_pBuf;			//	�o�b�t�@
		bool	m_isInUse;		//	�������̎g�p��
	};

//================== ���������֐� ==================//
	
	//	���X�g�̍X�V
	void _ListUpdate();

	//	���X�g������
	void _RemoveFromList();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int					m_sourceSoundHandle[SE_KIND::SE_NUM];				//	�T�E���h�n���h��
	int					m_sourceOneSoundHandle[ONE_SE_KIND::ONE_SE_NUM];	//	�T�E���h�n���h��
	SeBuffer			m_seBuffer[SE_KIND::SE_NUM];						//	�o�^�o�b�t�@
	OneSeBuffer			m_oneSeBuffer[ONE_SE_KIND::ONE_SE_NUM];				//	�o�^�o�b�t�@
	std::list<Sound*>	m_useList;											//	�g�p�G�l�~�[���X�g

};