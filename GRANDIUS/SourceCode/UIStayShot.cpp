
//=============================================================================
//	@file	UIStayShot.h
//	@brief	�X�e�C�V���b�gUI
//	@autor	���m ���
//	@date	2018/1/10
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "UIStayShot.h"
#include "PlayerManager.h"
#include "PlayerBase.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const VECTOR	UIStayShot::START_POS = VGet(475.0f, 11.0f, 0.0f);	//	�J�n�ʒu
const VECTOR	UIStayShot::END_POS = VGet(674.0f, 109.0f, 0.0f);	//	�I���ʒu
const float		UIStayShot::MIN_BUTTON_SCALE = 1.0f;				//	�{�^���̊g�嗦�̍ŏ�
const float		UIStayShot::MAX_BUTTON_SCALE = 1.2f;				//	�{�^���̊g�嗦�̍ő�
const float		UIStayShot::BUTTON_SCALE_SPEED = 0.03f;				//	�{�^���̊g�嗦�̑��x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
UIStayShot::UIStayShot()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
UIStayShot::~UIStayShot()
{
	//	�ŏI�I�ȉ��
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void UIStayShot::Create()
{
	//	������
	LoadDivGraph("Data/Sprite/StayShot/StayShot.png", 10, 10, 1, 300, 150, m_stayShotSpriteHendle);
	CommonDebug::Assert((m_stayShotSpriteHendle[0] <= -1), " [ UIStayShot.cpp ] : error : sprite loading failed.");
	m_stayShotPos = VGet(575.0f, 60.0f, 0.0f);
	m_stayShotAnimation.m_count = 0;
	m_stayShotAnimation.m_time = 0.0f;
	m_stayShotAnimation.m_maxTime = 5.0f;
	m_stayShotAnimation.m_maxCount = CommonConstant::STAY_SHOT_UI_ANIM_NUM;
	m_stayShotScale = 0.7f;

	//	�{�^��UI
	m_buttonUI.m_spriteHendle = LoadGraph("Data/Sprite/StayShot/ButtonB.png");
	CommonDebug::Assert((m_buttonUI.m_spriteHendle <= -1), " [ UIStayShot.cpp ] : error : sprite loading failed.");
	m_buttonUI.m_pos = VGet(575.0f, 60.0f, 0.0f);
	m_buttonUI.m_scale = MIN_BUTTON_SCALE;
	m_isChangeButtonScale = false;

	//	�Q�[�W
	m_gauge.m_vertexTop = START_POS;
	m_gauge.m_vertexUnder = END_POS;
	m_gaugeAlpha = 180;

	//	�F
	m_gaugeColor.m_red = 50;
	m_gaugeColor.m_green = 50;
	m_gaugeColor.m_blue = 50;
	m_gaugeColor.m_color = CommonFunction::GetColor(m_gaugeColor);

	m_isOneTimeReset = false;
	m_isOneTimeSE = true;
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void UIStayShot::Release()
{
	//	�X�v���C�g�̃A�����[�h
	for (int i = 0; i < CommonConstant::STAY_SHOT_UI_ANIM_NUM; i++)
	{
		DeleteGraph(m_stayShotSpriteHendle[i]);
	}

	DeleteGraph(m_buttonUI.m_spriteHendle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void UIStayShot::Update(PlayerManager& _playerManager, SoundEffect& _soundEffect)
{
	PlayerBase* player = _playerManager.GetPlayerPtr();
	if (player)
	{
		//	�؍݃V���b�g�͎g�p�\
		const bool isUseStayShot = player->GetIsUseStayShot();
		if (isUseStayShot)
		{
			if (!m_isOneTimeSE) { _soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_STAY_SHOT_GAUGE_MAX); m_isOneTimeSE = true; }

			//	�A�j���[�V���������߂�
			CommonFunction::AskAnimationCount(m_stayShotAnimation);

			//	�{�^���̊g�嗦�̐؂�ւ�
			_ChangeButtonScale();

			m_isOneTimeReset = false;
		}
		else
		{
			//	�_���[�W���󂯂Ă��Ȃ��Ƃ�
			const bool isNotDamage = !player->GetIsDamage();
			if (isNotDamage)
			{
				//	���Z�b�g
				_Reset();

				//	�Q�[�W�̉��Z
				_AddGauge();
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void UIStayShot::Draw(PlayerManager& _playerManager)
{
	DrawRotaGraph((int)m_stayShotPos.x, (int)m_stayShotPos.y, (double)m_stayShotScale, 0, m_stayShotSpriteHendle[m_stayShotAnimation.m_count], TRUE);
	
	PlayerBase* player = _playerManager.GetPlayerPtr();
	if (player)
	{
		//	�؍݃V���b�g�͎g�p�\
		const bool isUseStayShot = player->GetIsUseStayShot();
		if (isUseStayShot)
		{
			DrawRotaGraph((int)m_buttonUI.m_pos.x, (int)m_buttonUI.m_pos.y, (double)m_buttonUI.m_scale, 0, m_buttonUI.m_spriteHendle, TRUE);
		}
		else
		{
			//	�Q�[�W�̕`��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_gaugeAlpha);
			DrawBox((int)m_gauge.m_vertexTop.x, (int)m_gauge.m_vertexTop.y, (int)m_gauge.m_vertexUnder.x, (int)m_gauge.m_vertexUnder.y, m_gaugeColor.m_color, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�{�^���̊g�嗦�̐؂�ւ�
//-----------------------------------------------------------------------------
void UIStayShot::_ChangeButtonScale()
{
	//	�{�^���̊g�嗦�̕ύX
	if (m_isChangeButtonScale) { m_buttonUI.m_scale -= BUTTON_SCALE_SPEED; }
	else { m_buttonUI.m_scale += BUTTON_SCALE_SPEED; }

	//	�ő�ŏ�����
	const bool isMaxVal = m_buttonUI.m_scale >= MAX_BUTTON_SCALE;
	const bool isMinVal = m_buttonUI.m_scale <= MIN_BUTTON_SCALE;
	if (isMaxVal) { m_buttonUI.m_scale = MAX_BUTTON_SCALE; m_isChangeButtonScale = true; }
	if (isMinVal) { m_buttonUI.m_scale = MIN_BUTTON_SCALE; m_isChangeButtonScale = false; }
}

//-----------------------------------------------------------------------------
//	@brief	���Z�b�g
//-----------------------------------------------------------------------------
void UIStayShot::_Reset()
{
	if (!m_isOneTimeReset)
	{
		//	�Q�[�W�̏�����
		m_gauge.m_vertexTop = START_POS;
		m_gauge.m_vertexUnder = END_POS;

		//	�A�j���[�V�����̃��Z�b�g
		m_stayShotAnimation.m_time = 0.0f;

		//	�{�^��������
		m_buttonUI.m_scale = MIN_BUTTON_SCALE;
		m_isChangeButtonScale = false;

		m_isOneTimeReset = true;
		m_isOneTimeSE = false;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�Q�[�W�̉��Z
//-----------------------------------------------------------------------------
void UIStayShot::_AddGauge()
{
	//	�Q�[�W�̉��Z
	m_gauge.m_vertexTop.x += 3.0f;

	//	�Q�[�W�̍ő�
	const bool isMaxVal = m_gauge.m_vertexTop.x >= END_POS.x;
	if (isMaxVal) { m_gauge.m_vertexTop.x = END_POS.x; }
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void UIStayShot::_FinalRelease()
{
	//	�X�v���C�g�̃A�����[�h
	for (int i = 0; i < CommonConstant::STAY_SHOT_UI_ANIM_NUM; i++)
	{
		DeleteGraph(m_stayShotSpriteHendle[i]);
	}

	DeleteGraph(m_buttonUI.m_spriteHendle);
}
