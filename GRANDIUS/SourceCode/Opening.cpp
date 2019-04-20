
//=============================================================================
//	@file	Opening.h
//	@brief	�I�[�v�j���O
//	@autor	���m ���
//	@date	2018/1/18
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Opening.h"
#include "Pad.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const int		Opening::MIN_ALPHA = 0;				//	�A���t�@�l�̍ŏ�
const int		Opening::MAX_ALPHA = 255;			//	�A���t�@�l�̍ő�
const int		Opening::ALPHA_DEFAULT_SPEED = 3;	//	�A���t�@�l�̃f�t�H���g���x
const int		Opening::ALPHA_ACCELE_SPEED = 9;	//	�A���t�@�l�̃A�N�Z�����x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Opening::Opening()
{
	//	�I�[�v�j���O�̓ǂݍ���
	_LoadUI(m_OpeningUI1, "Data/Sprite/Opening/Opening01.png");
	_LoadUI(m_OpeningUI2, "Data/Sprite/Opening/Opening02.png");
	_LoadUI(m_OpeningUI3, "Data/Sprite/Opening/Opening03.png");
	_LoadUI(m_OpeningUI4, "Data/Sprite/Opening/Opening04.png");
	_LoadUI(m_OpeningUI5, "Data/Sprite/Opening/Opening05.png");
	_LoadUI(m_OpeningUI6, "Data/Sprite/Opening/Opening06.png");

	//	�w�i�̐ݒ�
	m_backGroundRect.m_vertexTop = VGet(0.0f, 0.0f, 0.0f);
	m_backGroundRect.m_vertexUnder = VGet((float)CommonConstant::WINDOW_WIDTH, (float)CommonConstant::WINDOW_HEIGHT, 0.0f);
	m_backGroundColor.m_red = 0;
	m_backGroundColor.m_green = 0;
	m_backGroundColor.m_blue = 0;
	m_backGroundColor.m_color = CommonFunction::GetColor(m_backGroundColor);

	//	���̂ق��̏�����
	m_openingCount = OPENING_KIND::OPENING_NONE;
	m_alpha = MIN_ALPHA;
	m_isChangeAlpha = false;
	m_isStart = false;
	m_isEndOpening = false;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Opening::~Opening()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void Opening::Update(Pad& _pad)
{
	//	�I�[�v�j���O���I�����Ă��Ȃ��Ƃ�
	if (!m_isEndOpening)
	{
		//	�A���t�@�l�̕ύX
		_ChangeAlpha();

		//	�A���t�@�l�̉���
		_AcceleAlpha(_pad);

		//	�I�[�v�j���O�̃X�L�b�v
		_OpeningSkip(_pad);

		//	�I�[�v�j���O�̏I��
		_EndOpening();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void Opening::Draw()
{
	//	�w�i�̕`��
	DrawBox(
		(int)m_backGroundRect.m_vertexTop.x, 
		(int)m_backGroundRect.m_vertexTop.y, 
		(int)m_backGroundRect.m_vertexUnder.x,
		(int)m_backGroundRect.m_vertexUnder.y,
		m_backGroundColor.m_color,
		TRUE
	);

	//	�I�[�v�j���O�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	switch (m_openingCount)
	{
	case OPENING_KIND::OPENING_1:
		_DrawUI(m_OpeningUI1);
		break;

	case OPENING_KIND::OPENING_2:
		_DrawUI(m_OpeningUI2);
		break;

	case OPENING_KIND::OPENING_3:
		_DrawUI(m_OpeningUI3);
		break;

	case OPENING_KIND::OPENING_4:
		_DrawUI(m_OpeningUI4);
		break;

	case OPENING_KIND::OPENING_5:
		_DrawUI(m_OpeningUI5);
		break;

	case OPENING_KIND::OPENING_6:
		_DrawUI(m_OpeningUI6);
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MIN_ALPHA);
}

//-----------------------------------------------------------------------------
//	@brief	UI�̓ǂݍ���
//-----------------------------------------------------------------------------
void Opening::_LoadUI(UI& _ui, const char* _fileName)
{
	_ui.m_spriteHendle = LoadGraph(_fileName);
	CommonDebug::Assert((_ui.m_spriteHendle <= -1), " [ Opening.cpp ] : error : sprite loading failed.");
	_ui.m_pos = VGet(0.0f, 0.0f, 0.0f);
}

//-----------------------------------------------------------------------------
//	@brief	UI�̕`��
//-----------------------------------------------------------------------------
void Opening::_DrawUI(UI _ui)
{
	DrawGraph((int)_ui.m_pos.x, (int)_ui.m_pos.y, _ui.m_spriteHendle, TRUE);
}

//-----------------------------------------------------------------------------
//	@brief	�A���t�@�l�̕ύX
//-----------------------------------------------------------------------------
void Opening::_ChangeAlpha()
{
	if (!m_isStart)
	{
		m_alphaSpeed = ALPHA_DEFAULT_SPEED;
		m_openingCount++;
		m_alpha = MIN_ALPHA;
		m_isStart = true;
	}

	//	�A���t�@�l�̉��Z���Z�̐؂�ւ�
	if (m_isChangeAlpha) { m_alpha -= m_alphaSpeed; }
	else { m_alpha += m_alphaSpeed; }

	//	�ő�ŏ�����
	const bool isMaxVal = m_alpha >= MAX_ALPHA;
	const bool isMinVal = m_alpha <= MIN_ALPHA;
	if (isMaxVal) { m_alpha = MAX_ALPHA; m_isChangeAlpha = true; }
	if (isMinVal) { m_alpha = MIN_ALPHA; m_isChangeAlpha = false; m_isStart = false; }
}

//-----------------------------------------------------------------------------
//	@brief	�A���t�@�l�̉���
//-----------------------------------------------------------------------------
void Opening::_AcceleAlpha(Pad& _pad)
{
	const bool isKeyActive = KEY->Press(KEY_INPUT_SPACE) || KEY->Press(KEY_INPUT_X) || KEY->Press(KEY_INPUT_K) || KEY->Press(KEY_INPUT_A);
	const bool isNextActive = isKeyActive || _pad.GetXInputButton(PadInfo::PAD_BUTTON_KIND::BUTTON_ALL);
	if (isNextActive)
	{
		m_alphaSpeed = ALPHA_ACCELE_SPEED;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�I�[�v�j���O�̃X�L�b�v
//-----------------------------------------------------------------------------
void Opening::_OpeningSkip(Pad& _pad)
{
	const bool isNextActive = KEY->Press(KEY_INPUT_RETURN) || _pad.GetXInputButton(PadInfo::PAD_BUTTON_KIND::BUTTON_START);
	if (isNextActive)
	{
		m_isEndOpening = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�I������
//-----------------------------------------------------------------------------
void Opening::_EndOpening()
{
	const bool isOpeningEnd = m_openingCount >= OPENING_KIND::OPENING_NUM;
	if (isOpeningEnd)
	{
		m_isEndOpening = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void Opening::_FinalRelease()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_OpeningUI1.m_spriteHendle);
	DeleteGraph(m_OpeningUI2.m_spriteHendle);
	DeleteGraph(m_OpeningUI3.m_spriteHendle);
	DeleteGraph(m_OpeningUI4.m_spriteHendle);
	DeleteGraph(m_OpeningUI5.m_spriteHendle);
	DeleteGraph(m_OpeningUI6.m_spriteHendle);
}
