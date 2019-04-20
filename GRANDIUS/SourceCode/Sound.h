
//=============================================================================
//	@file	Sound.h
//	@brief	�T�E���h
//	@autor	���m ���
//	@date	2018/1/04
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�T�E���h�N���X
//-----------------------------------------------------------------------------
class Sound
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	Sound(const char* _soundName);
	Sound(const char* _soundName, const char* _nextSoundName);
	Sound(const int _soundHandle);
	~Sound();

	//	��������
	void Initialize();
	
	//	�X�V����
	void Update();

	//	�Đ�����
	void OnPlay(const int _playType);

	//	�T�E���h�̐؂�ւ�
	void ChangeSound(const int _nextPlayType, const float _nextSoundWaitTime);

//==================== getter =====================//

	//	�g�p��ԃt���O�� getter
	const bool& GetIsUsedStatus() const { return m_isUsedStatus; }

	//	�폜�t���O�� getter
	const bool& GetIsDelete() const { return m_isDelete; }

	//	�T�E���h�̐؂�ւ��t���O�� getter
	const bool& GetIsChageSound() const { return m_isChangeSound; }

//==================== setter =====================//

	//	�g�p��ԃt���O�� setter
	void SetIsUsedStatus(const bool& _set) { m_isUsedStatus = _set; }
	
	//	�폜�t���O�� setter
	void SetIsDelete(const bool& _set) { m_isDelete = _set; }

	//	�T�E���h�̐؂�ւ��t���O�� setter
	void SetIsChageSound(const bool& _set) { m_isChangeSound = _set; }

private:

//================== ���������֐� ==================//

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int		m_soundHandle;			//	�T�E���h�n���h��
	int		m_nextSoundHandle;		//	���̃T�E���h�n���h��
	bool	m_isUsedStatus;			//	�g�p��ԃt���O
	bool	m_isDelete;				//	�폜�t���O
	bool	m_isChangeSound;		//	�T�E���h�̐؂�ւ��t���O
	float	m_nextWaitTime;			//	�T�E���h�̒x������

//===================== �ÓI�萔 ===================//

	static const int NO_SOUND;	//	������

};