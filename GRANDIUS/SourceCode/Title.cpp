
//=============================================================================
//	@file	Title.cpp
//	@brief	�^�C�g��
//	@autor	���m ���
//	@date	2018/1/6
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Title.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float Title::EQUAL = 1.0f;				//	���{
const float Title::SUB_SCALE_SPEED = 1.0f;		//	�g�嗦�̑��x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Title::Title()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Title::~Title()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void Title::Create()
{
	//	�^�C�g�����S�̏�����
	m_titleLogo.m_spriteHendle = LoadGraph("Data/Sprite/Title/TitleLogo.png");
	CommonDebug::Assert((m_titleLogo.m_spriteHendle <= -1), " [ Title.cpp ] : error : sprite loading failed.");
	m_titleLogo.m_pos = VGet(1090.0f, 150.0f, 0.0f);

	//	�^�C�g���̏�����
	m_title.m_spriteHendle = LoadGraph("Data/Sprite/Title/Title.png");
	CommonDebug::Assert((m_title.m_spriteHendle <= -1), " [ Title.cpp ] : error : sprite loading failed.");
	m_title.m_pos = VGet(1430.0f, 425.0f, 0.0f);
	m_title.m_scale = 10.0f;
	m_title.m_angle = 0.0f;

	//	�X�^�[�g�̏�����
	m_start.m_spriteHendle = LoadGraph("Data/Sprite/Title/Start.png");
	CommonDebug::Assert((m_start.m_spriteHendle <= -1), " [ Title.cpp ] : error : sprite loading failed.");
	m_start.m_pos = VGet(550.0f, 925.0f, 0.0f);
	m_start.m_flashingTime = 0.0f;

	m_isSeStart = false;
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void Title::Release()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_titleLogo.m_spriteHendle);
	DeleteGraph(m_title.m_spriteHendle);
	DeleteGraph(m_start.m_spriteHendle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V
//-----------------------------------------------------------------------------
void Title::Update(SoundEffect& _soundEffect)
{
	//	�^�C�g���̊g�嗦
	_AskTitleScale(_soundEffect);
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void Title::Draw()
{
	DrawGraph((int)m_titleLogo.m_pos.x, (int)m_titleLogo.m_pos.y, m_titleLogo.m_spriteHendle, TRUE);
	DrawRotaGraph((int)m_title.m_pos.x, (int)m_title.m_pos.y, (double)m_title.m_scale, (double)m_title.m_angle, m_title.m_spriteHendle, TRUE);

	//	�_�ŕ`��
	_FlashingDraw(m_start);
}

//-----------------------------------------------------------------------------
//	@brief	�^�C�g���̊g�k�������߂�
//-----------------------------------------------------------------------------
void Title::_AskTitleScale(SoundEffect& _soundEffect)
{
	//	SE�̊J�n
	if (!m_isSeStart)
	{
		//	�g�嗦������������
		m_title.m_scale -= SUB_SCALE_SPEED;
		const bool isMinVal = m_title.m_scale <= EQUAL;
		if (isMinVal)
		{
			m_title.m_scale = EQUAL;
			_soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_TITLE);
			m_isSeStart = true;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�_�ŕ`��
//-----------------------------------------------------------------------------
void Title::_FlashingDraw(UI& _ui)
{
	const bool isDraw = _ui.m_flashingTime >= 0.0f && _ui.m_flashingTime <= 30.0f;
	const bool isReset = _ui.m_flashingTime >= 40.0f;

	if(isDraw) { DrawGraph((int)_ui.m_pos.x, (int)_ui.m_pos.y, _ui.m_spriteHendle, TRUE); }
	if (isReset) { _ui.m_flashingTime = 0.0f; }

	_ui.m_flashingTime++;
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void Title::_FinalRelease()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_titleLogo.m_spriteHendle);
	DeleteGraph(m_title.m_spriteHendle);
	DeleteGraph(m_start.m_spriteHendle);
}
