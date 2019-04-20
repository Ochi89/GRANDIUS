
//=============================================================================
//	@file	UIStayShot.h
//	@brief	�X�e�C�V���b�gUI
//	@autor	���m ���
//	@date	2018/1/10
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
struct Rect;
struct UI;
struct Color;
struct Animation;
class SoundEffect;
class PlayerManager;

//-----------------------------------------------------------------------------
//	@brief	UIStayShot�N���X
//-----------------------------------------------------------------------------
class UIStayShot final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^/�f�X�g���N�^
	UIStayShot();
	~UIStayShot();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	�X�V����
	void Update(PlayerManager& _playerManager, SoundEffect& _soundEffect);

	//	�`�揈��
	void Draw(PlayerManager& _playerManager);

private:

//================== ���������֐� ==================//

	//	�{�^���̊g�嗦�̐؂�ւ�
	void _ChangeButtonScale();

	//	���Z�b�g
	void _Reset();

	//	�Q�[�W�̉��Z
	void _AddGauge();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int			m_stayShotSpriteHendle[CommonConstant::STAY_SHOT_UI_ANIM_NUM];	//	�X�e�C�V���b�gUI�̃X�v���C�g�n���h��
	VECTOR		m_stayShotPos;													//	�X�e�C�V���b�gUI�̃|�W�V����
	Animation	m_stayShotAnimation;											//	�X�e�C�V���b�gUI�̃A�j���[�V����
	float		m_stayShotScale;												//	�X�e�C�V���b�gUI�̊g�嗦
	UI			m_buttonUI;														//	�{�^��UI
	bool		m_isChangeButtonScale;											//	�{�^���T�C�Y�؂�ւ�
	Rect		m_gauge;														//	�Q�[�W
	int			m_gaugeAlpha;													//	�Q�[�W�̃A���t�@�l
	Color		m_gaugeColor;													//	�Q�[�W�̐F
	bool		m_isOneTimeReset;												//	���Z�b�g�t���O
	bool		m_isOneTimeSE;													//	SE�t���O

//===================== �ÓI�萔 ===================//

	static const VECTOR		START_POS;					//	�J�n�ʒu
	static const VECTOR		END_POS;					//	�I���ʒu
	static const float		MIN_BUTTON_SCALE;			//	�{�^���̊g�嗦�̍ŏ�
	static const float		MAX_BUTTON_SCALE;			//	�{�^���̊g�嗦�̍ő�
	static const float		BUTTON_SCALE_SPEED;			//	�{�^���̊g�嗦�̑��x

};