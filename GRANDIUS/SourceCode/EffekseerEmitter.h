
//=============================================================================
//	@file	EffekseerEmitter.h
//	@brief	EffekseerEmitter
//	@autor	���m ���
//	@date	2018/12/26
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	EffekseerEmitter�N���X
//-----------------------------------------------------------------------------
class EffekseerEmitter final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	EffekseerEmitter(const char* _fileName);
	~EffekseerEmitter();

	//	�G�t�F�N�g�̍Đ�����
	void OnPlayEffect();

	//	�G�t�F�N�g�̏I������
	void OnEndEffect();

	//	�G�t�F�N�g�̍X�V����
	void Update();

	//	�Đ����Ԃ̉��Z
	void AddPlayTime() { m_playTime++; }

//==================== setter =====================//

	//	�|�W�V������ setter
	void SetPos(const VECTOR _set) { m_pos = _set; m_isUsePos = true; }

	//	�p�x�� setter
	void SetAngle(const VECTOR _set) { m_angle = _set; m_isUseAngle = true; }

	//	�䗦�� setter
	void SetScale(const VECTOR _set) { m_scale = _set; m_isUseScale = true; }

	//	�Đ����x�� setter
	void SetPlaySpeed(const float _set) { m_speed = _set; m_isUseSpeed = true; }

	//	�Đ������� setter
	void SetIsPlayEffect(const bool _set) { m_isPlayEffect = _set; }

	//	�J�n���邩�� setter
	void SetIsStartEffect(const bool _set) { m_isStartEffect = _set; }

	//	�Đ����Ԃ� setter
	void SetPlayTime(const float _set) { m_playTime = _set; }

//==================== getter =====================//
	
	//	�Đ����x�� getter
	const float GetPlaySpeed() const;

	//	�Đ����Ԃ� getter
	const float& GetPlayTime() const { return m_playTime; }

	//	�Đ������� getter
	const bool& GetIsPlayEffect() const { return m_isPlayEffect; }

	//	�J�n���邩�� getter
	const bool& GetIsStartEffect() const { return m_isStartEffect; }

private:

//================== ���������֐� ==================//

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int			m_effectResourceHandle;		//	�G�t�F�N�g���\�[�X�n���h��
	int			m_playingEffectHandle;		//	�Đ����̃G�t�F�N�g�̃n���h��
	VECTOR		m_pos;						//	�|�W�V����
	VECTOR		m_scale;					//	�g�嗦
	VECTOR		m_angle;					//	�p�x
	float		m_speed;					//	���x
	bool		m_isUsePos;					//	�|�W�V�����̐ݒ���g��
	bool		m_isUseAngle;				//	�p�x�̐ݒ���g��
	bool		m_isUseScale;				//	�g�嗦�̐ݒ���g��
	bool		m_isUseSpeed;				//	���x�̐ݒ���g��
	bool		m_isPlayEffect;				//	�Đ������̃t���O
	bool		m_isStartEffect;			//	�J�n���邩�̃t���O
	float		m_playTime;					//	�G�t�F�N�g�̍Đ�����
	bool		m_isPrevConditions;			//	�O�̏����̕ۑ�

//===================== �ÓI�萔 ===================//

};