
//=============================================================================
//	@file	UIDemoPlay.cpp
//	@brief	�f���v���CUI
//	@autor	���m ���
//	@date	2018/1/15
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "UIDemoPlay.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const int		UIDemoPlay::MIN_ALPHA = 128;			//	�A���t�@�l�̍ŏ�
const int		UIDemoPlay::MAX_ALPHA = 255;			//	�A���t�@�l�̍ő�
const int		UIDemoPlay::ALPHA_SPEED = 5;			//	�A���t�@�l�̑��x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
UIDemoPlay::UIDemoPlay()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
UIDemoPlay::~UIDemoPlay()
{
	//	�ŏI�I�ȉ��
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬
//-----------------------------------------------------------------------------
void UIDemoPlay::Create()
{
	//	�^�C�g�����S�̏�����
	m_titleLogo.m_spriteHendle = LoadGraph("Data/Sprite/DemoPlay/DemoLog.png");
	CommonDebug::Assert((m_titleLogo.m_spriteHendle <= -1), " [ UIDemoPlay.cpp ] : error : sprite loading failed.");
	m_titleLogo.m_pos = VGet(1600.0f, 0.0f, 0.0f);

	//	�X�^�[�g�̏�����
	m_start.m_spriteHendle = LoadGraph("Data/Sprite/DemoPlay/Start.png");
	CommonDebug::Assert((m_start.m_spriteHendle <= -1), " [ UIDemoPlay.cpp ] : error : sprite loading failed.");
	m_start.m_pos = VGet(550.0f, 925.0f, 0.0f);
	m_start.m_flashingTime = 0.0f;

	//	�f���v���CUI
	m_demoPlayUI.m_spriteHendle = LoadGraph("Data/Sprite/DemoPlay/DemoPlay.png");
	CommonDebug::Assert((m_demoPlayUI.m_spriteHendle <= -1), " [ UIDemoPlay.cpp ] : error : sprite loading failed.");
	m_demoPlayUI.m_pos = VGet(575.0f, 475.0f, 0.0f);
	m_alpha = MAX_ALPHA;
	m_isChangeAlpha = false;
}

//-----------------------------------------------------------------------------
//	@brief	���
//-----------------------------------------------------------------------------
void UIDemoPlay::Release()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_titleLogo.m_spriteHendle);
	DeleteGraph(m_start.m_spriteHendle);
	DeleteGraph(m_demoPlayUI.m_spriteHendle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void UIDemoPlay::Update()
{
	//	�A���t�@�l�̉��Z���Z�̐؂�ւ�
	if (m_isChangeAlpha) { m_alpha -= ALPHA_SPEED; }
	else { m_alpha += ALPHA_SPEED; }

	//	�ő�ŏ�����
	const bool isMaxVal = m_alpha >= MAX_ALPHA;
	const bool isMinVal = m_alpha <= MIN_ALPHA;
	if (isMaxVal) { m_alpha = MAX_ALPHA; m_isChangeAlpha = true; }
	if (isMinVal) { m_alpha = MIN_ALPHA; m_isChangeAlpha = false; }

}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void UIDemoPlay::Draw()
{
	//�_�ŕ`��
	_FlashingDraw(m_start);

	//	�^�C�g�����S�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, MIN_ALPHA);
	DrawGraph((int)m_titleLogo.m_pos.x, (int)m_titleLogo.m_pos.y, m_titleLogo.m_spriteHendle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//	�f���v���CUI�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawGraph((int)m_demoPlayUI.m_pos.x , (int)m_demoPlayUI.m_pos.y, m_demoPlayUI.m_spriteHendle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//-----------------------------------------------------------------------------
//	@brief	�_�ŕ`��
//-----------------------------------------------------------------------------
void UIDemoPlay::_FlashingDraw(UI& _ui)
{
	const bool isDraw = _ui.m_flashingTime >= 0.0f && _ui.m_flashingTime <= 30.0f;
	const bool isReset = _ui.m_flashingTime >= 40.0f;

	if (isDraw) { DrawGraph((int)_ui.m_pos.x, (int)_ui.m_pos.y, _ui.m_spriteHendle, TRUE); }
	if (isReset) { _ui.m_flashingTime = 0.0f; }

	_ui.m_flashingTime++;
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void UIDemoPlay::_FinalRelease()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_titleLogo.m_spriteHendle);
	DeleteGraph(m_start.m_spriteHendle);
	DeleteGraph(m_demoPlayUI.m_spriteHendle);
}
