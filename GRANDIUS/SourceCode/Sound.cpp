
//=============================================================================
//	@file	Sound.h
//	@brief	�T�E���h�x�[�X
//	@autor	���m ���
//	@date	2018/1/04
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Sound.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const int Sound::NO_SOUND = 0;	//	������

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Sound::Sound(const char* _soundName)
{
	//	�T�E���h�̓ǂݍ���
	m_soundHandle = LoadSoundMem(_soundName);
	CommonDebug::Assert((m_soundHandle <= -1), " [ Sound.cpp ] : error : sound loading failed.");
	m_isUsedStatus = false;
	m_isDelete = false;
	m_isChangeSound = false;
	m_nextWaitTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Sound::Sound(const char* _soundName, const char* _nextSoundName)
{
	//	�T�E���h�̓ǂݍ���
	m_soundHandle = LoadSoundMem(_soundName);
	m_nextSoundHandle = LoadSoundMem(_nextSoundName);
	CommonDebug::Assert((m_soundHandle <= -1), " [ Sound.cpp ] : error : sound loading failed.");
	CommonDebug::Assert((m_nextSoundHandle <= -1), " [ Sound.cpp ] : error : next sound loading failed.");
	m_isUsedStatus = false;
	m_isDelete = false;
	m_isChangeSound = false;
	m_nextWaitTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Sound::Sound(const int _soundHandle)
{
	//	�T�E���h�̓ǂݍ���
	m_soundHandle = _soundHandle;
	CommonDebug::Assert((m_soundHandle <= -1), " [ Sound.cpp ] : error : sound loading failed.");
	m_isUsedStatus = false;
	m_isDelete = false;
	m_isChangeSound = false;
	m_nextWaitTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Sound::~Sound()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void Sound::Initialize()
{
	m_isUsedStatus = false;
	m_isDelete = false;
	m_isChangeSound = false;
	m_nextWaitTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void Sound::Update()
{
	//	�Đ����Ă��Ȃ��Ƃ�
	const bool isEndSound = CheckSoundMem(m_soundHandle) == NO_SOUND;
	if (isEndSound) { m_isDelete = true; }
}

//-----------------------------------------------------------------------------
//	@brief	�Đ�����
//-----------------------------------------------------------------------------
void Sound::OnPlay(const int _playType)
{
	//	�Đ����ł͂Ȃ��Ƃ��́A
	//	�Đ�����
	if (!m_isUsedStatus)
	{
		PlaySoundMem(m_soundHandle, _playType);
		m_isUsedStatus = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�T�E���h�̐؂�ւ�
//-----------------------------------------------------------------------------
void Sound::ChangeSound(const int _nextPlayType, const float _nextSoundWaitTime)
{
	if (m_isChangeSound)
	{
		//	�O�̃T�E���h�̒�~
		StopSoundMem(m_soundHandle);
		m_isUsedStatus = false;

		//	���̃T�E���h�̊J�n
		const bool isActive = !m_isUsedStatus && m_nextWaitTime++ >= _nextSoundWaitTime;
		if (isActive)
		{
			PlaySoundMem(m_nextSoundHandle, _nextPlayType);
			m_isUsedStatus = true;
			m_isChangeSound = false;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void Sound::_FinalRelease()
{
	//	�T�E���h�̃A�����[�h
	DeleteSoundMem(m_soundHandle);
	DeleteSoundMem(m_nextSoundHandle);
}
