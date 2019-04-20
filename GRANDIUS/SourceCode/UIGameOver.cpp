
//=============================================================================
//	@file	UIGameOver.cpp
//	@brief	UIGameOver
//	@autor	���m ���
//	@date	2018/12/15
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "UIGameOver.h"
#include "PlayerManager.h"
#include "PlayerBase.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const int		UIGameOver::MIN_ALPHA = 128;			//	�A���t�@�l�̍ŏ�
const int		UIGameOver::MAX_ALPHA = 255;			//	�A���t�@�l�̍ő�
const int		UIGameOver::ALPHA_SPEED = 5;			//	�A���t�@�l�̑��x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
UIGameOver::UIGameOver()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
UIGameOver::~UIGameOver()
{
	//	�ŏI�I�ȉ��
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬
//-----------------------------------------------------------------------------
void UIGameOver::Create()
{
	//	�Q�[���I�[�o�[UI
	m_gameOverUI.m_spriteHendle = LoadGraph("Data/Sprite/GameOver/GameOver.png");
	CommonDebug::Assert((m_gameOverUI.m_spriteHendle <= -1), " [ UIGameOver.cpp ] : error : sprite loading failed.");

	m_gameOverUI.m_pos = VGet(450.0f, 500.0f, 0.0f);
	m_alpha = MAX_ALPHA;
	m_isChangeAlpha = false;
	m_isGameOver = false;
}

//-----------------------------------------------------------------------------
//	@brief	���
//-----------------------------------------------------------------------------
void UIGameOver::Release()
{
	//	�Q�[���I�[�o�[UI�̃X�v���C�g�̃A�����[�h
	DeleteGraph(m_gameOverUI.m_spriteHendle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void UIGameOver::Update(PlayerManager& _playerManager)
{
	//	�Q�[���I�[�o�[UI�̕`��
	PlayerBase* player = _playerManager.GetPlayerPtr();
	const bool isGameOver = !player->GetIsAlive();
	if (isGameOver) { m_isGameOver = true; }

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
void UIGameOver::Draw()
{
	if (m_isGameOver)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
		DrawGraph((int)m_gameOverUI.m_pos.x, (int)m_gameOverUI.m_pos.y, m_gameOverUI.m_spriteHendle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void UIGameOver::_FinalRelease()
{
	//	�Q�[���I�[�o�[���C�tUI�̃X�v���C�g�̃A�����[�h
	DeleteGraph(m_gameOverUI.m_spriteHendle);
}
