
//=============================================================================
//	@file	EffekseerEmitter.cpp
//	@brief	EffekseerEmitter
//	@autor	���m ���
//	@date	2018/12/26
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EffekseerEmitter.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
EffekseerEmitter::EffekseerEmitter(const char* _fileName)
{
	//	�G�t�F�N�g�̓ǂݍ���
	m_effectResourceHandle = LoadEffekseerEffect(_fileName);
	CommonDebug::Assert((m_effectResourceHandle <= -1), " [ EffekseerEmitter.cpp ] : error : effect resource loading failed.");

	//	�e�ϐ��̏�����
	m_playingEffectHandle = -1;
	m_pos = CommonConstant::ORIGIN;
	m_scale = CommonConstant::ORIGIN;
	m_angle = CommonConstant::ORIGIN;
	m_speed = 0.0f;
	m_isUsePos = false;
	m_isUseAngle = false;
	m_isUseScale = false;
	m_isUseSpeed = false;
	m_isPlayEffect = false;
	m_isStartEffect = false;
	m_isPrevConditions = false;
	m_playTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
EffekseerEmitter::~EffekseerEmitter()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�G�t�F�N�g�̍Đ�����
//-----------------------------------------------------------------------------
void EffekseerEmitter::OnPlayEffect()
{
	//	�܂��G�t�F�N�g���J�n���Ă��Ȃ���΁A�J�n
	if (!m_isPlayEffect)
	{
		//	�G�t�F�N�g�̍Đ�
		m_playingEffectHandle = PlayEffekseer3DEffect(m_effectResourceHandle);
		m_isPlayEffect = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�G�t�F�N�g�̏I������
//-----------------------------------------------------------------------------
void EffekseerEmitter::OnEndEffect()
{
	//	�ϐ��̏�����
	m_pos = CommonConstant::ORIGIN;
	m_scale = CommonConstant::ORIGIN;
	m_angle = CommonConstant::ORIGIN;
	m_speed = 0.0f;
	m_isUsePos = false;
	m_isUseAngle = false;
	m_isUseScale = false;
	m_isUseSpeed = false;
	m_isPlayEffect = false;
	m_isStartEffect = false;
	m_isPrevConditions = false;
	m_playTime = 0.0f;

	SetPosPlayingEffekseer3DEffect(m_playingEffectHandle, m_pos.x, m_pos.y, m_pos.z);
	SetRotationPlayingEffekseer3DEffect(m_playingEffectHandle, m_angle.x, m_angle.y, m_angle.z);
	SetScalePlayingEffekseer3DEffect(m_playingEffectHandle, m_scale.x, m_scale.y, m_scale.z);
	SetSpeedPlayingEffekseer3DEffect(m_playingEffectHandle, m_speed);

	//	�G�t�F�N�g�̒�~
	StopEffekseer3DEffect(m_playingEffectHandle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void EffekseerEmitter::Update()
{
	if (m_isUsePos)
	{
		//	�|�W�V������ݒ肷��
		SetPosPlayingEffekseer3DEffect(m_playingEffectHandle, m_pos.x, m_pos.y, m_pos.z);
	}

	if (m_isUseAngle)
	{
		//	���W�A���ɕϊ����A�ݒ肷��
		VECTOR radian = CommonFunction::DegToRad(m_angle);
		SetRotationPlayingEffekseer3DEffect(m_playingEffectHandle, radian.x, radian.y, radian.z);
	}

	if (m_isUseScale)
	{
		//	�g�嗦��ݒ肷��
		SetScalePlayingEffekseer3DEffect(m_playingEffectHandle, m_scale.x, m_scale.y, m_scale.z);
	}

	if (m_isUseSpeed)
	{
		//	�Đ����x��ݒ肷��
		SetSpeedPlayingEffekseer3DEffect(m_playingEffectHandle, m_speed);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�Đ����x�� getter
//-----------------------------------------------------------------------------
const float EffekseerEmitter::GetPlaySpeed() const
{
	//	�Đ����x���擾����
	return GetSpeedPlayingEffekseer3DEffect(m_playingEffectHandle);
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void EffekseerEmitter::_FinalRelease()
{
	//	�G�t�F�N�g���\�[�X�̃A�����[�h
	DeleteEffekseerEffect(m_playingEffectHandle);
	DeleteEffekseerEffect(m_effectResourceHandle);
}
