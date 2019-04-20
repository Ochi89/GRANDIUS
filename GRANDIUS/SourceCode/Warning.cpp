
//=============================================================================
//	@file	Warning.cpp
//	@brief	�x������
//	@autor	���m ���
//	@date	2018/1/6
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Warning.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const int		Warning::ALPHA_SPEED = 10;				//	�A���t�@���x
const int		Warning::MAX_ALPHA = 255;				//	�A���t�@�l�̍ő�
const int		Warning::MIN_ALPHA = 0;					//	�A���t�@�l�̍ŏ�
const float		Warning::MAX_WARNING_TIME = 300.0f;		//	�x�����Ԃ̍ő�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Warning::Warning()
{
	//	������
	m_spriteHandle = LoadGraph("Data/Sprite/Warning/Warning.png");
	m_pos = VGet(500.0f, 450.0f, 0.0f);
	m_alpha = 0;
	m_warningTime = 0.0f;
	m_isWarningStart = false;
	m_isSubAlpha = false;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Warning::~Warning()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
void Warning::Update()
{
	if (m_isWarningStart)
	{
		//	�A���t�@�l
		_Alpha();

		//	�x���̏I��
		m_warningTime++;
		const bool isEndWarning = m_warningTime >= MAX_WARNING_TIME;
		if (isEndWarning) { m_warningTime = 0.0f; m_isWarningStart = false; }
	}
}

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
void Warning::Draw()
{
	if (m_isWarningStart)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
		DrawGraph((int)m_pos.x, (int)m_pos.y, m_spriteHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�A���t�@�l
//-----------------------------------------------------------------------------
void Warning::_Alpha()
{
	//	���Z���Z
	if (m_isSubAlpha) { m_alpha -= ALPHA_SPEED; }
	else { m_alpha += ALPHA_SPEED; }

	//	�ő�ŏ�
	const bool isMaxAlpha = m_alpha >= MAX_ALPHA;
	const bool isMinAlpha = m_alpha <= MIN_ALPHA;
	if (isMaxAlpha) { m_alpha = MAX_ALPHA; m_isSubAlpha = true; }
	if (isMinAlpha) { m_alpha = MIN_ALPHA; m_isSubAlpha = false; }
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void Warning::_FinalRelease()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_spriteHandle);
}
