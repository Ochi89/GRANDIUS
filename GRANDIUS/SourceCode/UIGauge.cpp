
//=============================================================================
//	@file	UIGauge.cpp
//	@brief	�Q�[�W
//	@autor	���m ���
//	@date	2018/12/23
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "UIGauge.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const VECTOR	UIGauge::START_POS = VGet(700.0f, 50.0f, 0.0f);		//	�J�n�ʒu
const VECTOR	UIGauge::END_POS = VGet(1400.0f, 75.0f, 0.0f);		//	�I���ʒu
const float		UIGauge::FLAME_INTERVAL = 3.0f;						//	�t���[���Ԋu
const float		UIGauge::ADD_GAUGE_ENEMY = 8.0f;					//	�G�l�~�[�������̉��Z��
const float		UIGauge::ADD_GAUGE_BOSS = 8.0f;						//	�{�X�������̉��Z��
const float		UIGauge::ADD_GAUGE_ITEM = 28.0f;					//	�A�C�e���擾���̉��Z��
const float		UIGauge::MIN_BUTTON_SCALE = 1.0f;					//	�{�^���̊g�嗦�̍ŏ�
const float		UIGauge::MAX_BUTTON_SCALE = 1.2f;					//	�{�^���̊g�嗦�̍ő�
const float		UIGauge::BUTTON_SCALE_SPEED = 0.03f;				//	�{�^���̊g�嗦�̑��x
const int		UIGauge::MAX_COLOR = 255;							//	�F�̍ő�
const int		UIGauge::MIN_COLOR = 180;							//	�F�̍ŏ�
const int		UIGauge::COLOR_SPEED = 5;							//	�F�̑��x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
UIGauge::UIGauge()
{
	//	���u�Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
UIGauge::~UIGauge()
{
	//	�ŏI�I�ȉ��
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void UIGauge::Create()
{
	//	�e�ϐ��̏�����
	m_gaugeFlame.m_vertexTop = START_POS;
	m_gaugeFlame.m_vertexUnder = END_POS;
	m_gauge.m_vertexTop = START_POS;
	m_gauge.m_vertexUnder = VGet(START_POS.x, END_POS.y, START_POS.z);

	//	�t���[���F
	m_gaugeFlameColor.m_red = 128;
	m_gaugeFlameColor.m_green = 128;
	m_gaugeFlameColor.m_blue = 128;
	m_gaugeFlameColor.m_color = CommonFunction::GetColor(m_gaugeFlameColor);

	//	�Q�[�W�F
	m_gaugeColor.m_red = 255;
	m_gaugeColor.m_green = 255;
	m_gaugeColor.m_blue = 255;
	m_gaugeColor.m_color = CommonFunction::GetColor(m_gaugeColor);

	m_targetGauge = START_POS.x;
	m_isGaugeMax = false;

	//	�{�^��UI
	m_buttonUI.m_spriteHendle = LoadGraph("Data/Sprite/Gauge/ButtonX.png");
	CommonDebug::Assert((m_buttonUI.m_spriteHendle <= -1), " [ UIGauge.cpp ] : error : sprite loading failed.");
	m_buttonUI.m_pos = VGet(1050.0f, 65.0f, 0.0f);
	m_buttonUI.m_scale = MIN_BUTTON_SCALE;
	m_isChangeButtonScale = false;
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void UIGauge::Release()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_buttonUI.m_spriteHendle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void UIGauge::Update(SoundEffect& _soundEffect)
{
	//	�Q�[�W�̉��Z
	m_gauge.m_vertexUnder.x = m_targetGauge;

	//	�Q�[�W�����܂�����A
	//	�J�E���g�����Z���A�Q�[�W�������l�ɂ���
	const bool isOutRange = m_gauge.m_vertexUnder.x > END_POS.x;
	if (isOutRange)
	{
		//	�Q�[�W�����܂����u�Ԃ̂�SE�Đ�
		const bool isOnSe = !m_isGaugeMax;
		if (isOnSe) { _soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_GAUGE_MAX); }

		m_isGaugeMax = true;

		//	�傫���̕ύX
		m_gauge.m_vertexTop = VGet(START_POS.x - FLAME_INTERVAL, START_POS.y - FLAME_INTERVAL, START_POS.z);
		m_gauge.m_vertexUnder = VGet(END_POS.x + FLAME_INTERVAL, END_POS.y + FLAME_INTERVAL, END_POS.z);

		//	�F�̕ύX
		m_gaugeColor.m_red -= COLOR_SPEED;
		m_gaugeColor.m_green -= COLOR_SPEED;
		m_gaugeColor.m_blue -= COLOR_SPEED;
		
		//	�ŏ�����
		const bool isMinColor = m_gaugeColor.m_red <= MIN_COLOR;
		if(isMinColor)
		{
			m_gaugeColor.m_red = MAX_COLOR;
			m_gaugeColor.m_green = MAX_COLOR;
			m_gaugeColor.m_blue = MAX_COLOR;
		}

		//	�{�^���̊g�嗦�̕ύX
		if(m_isChangeButtonScale) { m_buttonUI.m_scale -= BUTTON_SCALE_SPEED; }
		else { m_buttonUI.m_scale += BUTTON_SCALE_SPEED; }

		//	�ő�ŏ�����
		const bool isMaxVal = m_buttonUI.m_scale >= MAX_BUTTON_SCALE;
		const bool isMinVal = m_buttonUI.m_scale <= MIN_BUTTON_SCALE;
		if (isMaxVal) { m_buttonUI.m_scale = MAX_BUTTON_SCALE; m_isChangeButtonScale = true; }
		if (isMinVal) { m_buttonUI.m_scale = MIN_BUTTON_SCALE; m_isChangeButtonScale = false; }
	}

	//	�F�����߂�	
	m_gaugeColor.m_color = CommonFunction::GetColor(m_gaugeColor);
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void UIGauge::Draw()
{
	//	�Q�[�W�̕`��
	DrawBox((int)m_gaugeFlame.m_vertexTop.x, (int)m_gaugeFlame.m_vertexTop.y, (int)m_gaugeFlame.m_vertexUnder.x, (int)m_gaugeFlame.m_vertexUnder.y, m_gaugeFlameColor.m_color, TRUE);
	DrawBox((int)m_gauge.m_vertexTop.x, (int)m_gauge.m_vertexTop.y, (int)m_gauge.m_vertexUnder.x, (int)m_gauge.m_vertexUnder.y, m_gaugeColor.m_color, TRUE);

	//	�{�^���̕`��
	if(m_isGaugeMax) { DrawRotaGraph((int)m_buttonUI.m_pos.x, (int)m_buttonUI.m_pos.y, (double)m_buttonUI.m_scale, 0, m_buttonUI.m_spriteHendle, TRUE); }
}

//-----------------------------------------------------------------------------
//	@brief	�Q�[�W�̉��Z
//-----------------------------------------------------------------------------
void UIGauge::AddGauge(const ADD_GAUGE_KIND _addGaugeKind)
{
	switch (_addGaugeKind)
	{

	case ADD_GAUGE_KIND::ENEMY:
		m_targetGauge += ADD_GAUGE_ENEMY;
		break;

	case ADD_GAUGE_KIND::BOSS:
		m_targetGauge += ADD_GAUGE_BOSS;
		break;

	case ADD_GAUGE_KIND::ITEM:
		m_targetGauge += ADD_GAUGE_ITEM;
		break;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�Q�[�W�̏�����
//-----------------------------------------------------------------------------
void UIGauge::ResetGauge()
{
	//	������
	m_targetGauge = START_POS.x;
	m_isGaugeMax = false;

	//	�ʒu�̏�����
	m_gauge.m_vertexTop = START_POS;
	m_gauge.m_vertexUnder = VGet(START_POS.x, END_POS.y, START_POS.z);

	//	�Q�[�W�F
	m_gaugeColor.m_red = 255;
	m_gaugeColor.m_green = 255;
	m_gaugeColor.m_blue = 255;
	m_gaugeColor.m_color = CommonFunction::GetColor(m_gaugeColor);

	//	�{�^���̃T�C�Y
	m_buttonUI.m_scale = MIN_BUTTON_SCALE;
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void UIGauge::_FinalRelease()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_buttonUI.m_spriteHendle);
}

