
//=============================================================================
//	@file	UICongratulation.h
//	@brief	�Q�[���I�[�o�[UI
//	@autor	���m ���
//	@date	2018/12/30
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "UICongratulation.h"
#include "PlayerManager.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float		UICongratulation::MAAX_CLEAR_WAIT_TIME = 300.0f;	//	�N���A���̒x�����Ԃ̍ő�
const int		UICongratulation::MIN_ALPHA = 0;					//	�A���t�@�l�̍ŏ�
const int		UICongratulation::MAX_ALPHA = 255;					//	�A���t�@�l�̍ő�
const int		UICongratulation::ALPHA_SPEED = 2;					//	�A���t�@�l�̑��x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
UICongratulation::UICongratulation()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
UICongratulation::~UICongratulation()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void UICongratulation::Create()
{
	//	�N���AUI
	m_congratulationUI.m_spriteHendle = LoadGraph("Data/Sprite/Congratulation/Congratulation.png");
	CommonDebug::Assert((m_congratulationUI.m_spriteHendle <= -1), " [ UICongratulation.cpp ] : error : sprite loading failed.");
	m_congratulationUI.m_pos = VGet(350.0f, 200.0f, 0.0f);
	m_alpha = MIN_ALPHA;
	m_isClear = false;
	m_clearWaitTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void UICongratulation::Release()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_congratulationUI.m_spriteHendle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void UICongratulation::Update(PlayerManager & _playerManager)
{
	//	�N���A����
	const bool isClear = _playerManager.GetIsClear();
	if (isClear) 
	{
		m_clearWaitTime++;
		const bool isActive = m_clearWaitTime >= MAAX_CLEAR_WAIT_TIME;
		if (isActive) { m_isClear = true; }
 	}

	//	�A���t�@�l�̉��Z
	if (m_isClear) { m_alpha += ALPHA_SPEED; }

	//	�ő又��
	const bool isMaxVal = m_alpha >= MAX_ALPHA;
	if (isMaxVal) { m_alpha = MAX_ALPHA; }
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void UICongratulation::Draw()
{
	if (m_isClear)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
		DrawGraph((int)m_congratulationUI.m_pos.x, (int)m_congratulationUI.m_pos.y, m_congratulationUI.m_spriteHendle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void UICongratulation::_FinalRelease()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_congratulationUI.m_spriteHendle);
}
