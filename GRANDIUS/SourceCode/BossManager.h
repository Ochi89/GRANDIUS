
//=============================================================================
//	@file	BassManager.cpp
//	@brief	�{�X�}�l�[�W���[
//	@autor	���m ���
//	@date	2018/12/18
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class LastBoss;
class MediumBoss;
class ShotManager;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�{�X�Ǘ��N���X
//-----------------------------------------------------------------------------
class BossManager final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	BossManager();
	~BossManager();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	��������
	void Initialize();

	//	�X�V����
	void Update(ShotManager& _shot, SoundEffect& _soundEffect);

	//	�`�揈��
	void Draw();

//==================== getter =====================//

	//	���{�X�ւ̃|�C���^�� getter
	MediumBoss* GetMediumBoss() { return m_mediumBoss.m_pBuf; }

	//	�{�X�ւ̃|�C���^�� getter
	LastBoss* GetLastBossPtr() { return m_lastBoss.m_pBuf; }

//==================== setter =====================//

	//	�o���t���O
	void SetIsMediumBossEmerge(const bool _set) { m_mediumBoss.m_isEmerge = _set; }

	//	�o���t���O
	void SetIsLastBossEmerge(const bool _set) { m_lastBoss.m_isEmerge = _set; }

private:

//===================== �\���� =====================//

	//	���{�X�o�b�t�@
	struct MediumBossBuffer
	{
		int				m_sourceModelHandle;				//	��{�n���h��
		MediumBoss*		m_pBuf;								//	�o�b�t�@
		bool			m_isEmerge;							//	�o���t���O
	};

	//	�ŏI�{�X�o�b�t�@
	struct LastBossBuffer
	{
		int				m_sourceModelHandle;				//	��{�n���h��
		int				m_coreSourceModelHandle;			//	�R�A�̑�{�n���h��
		int				m_sideBarrelSourceModelHandle;		//	�T�C�h�o�����̑�{�n���h��
		int				m_armSourceModelHandle;				//	�A�[���̑�{�n���h��
		LastBoss*		m_pBuf;								//	�o�b�t�@
		bool			m_isEmerge;							//	�o���t���O
	};

//================== ���������֐� ==================//

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	MediumBossBuffer	m_mediumBoss;						//	���{�X
	LastBossBuffer		m_lastBoss;							//	�ŏI�{�X

//===================== �ÓI�萔 ===================//

	static const float OUT_RANGE_MEDIUM_BOSS;			//	���{�X�͈̔͊O
	static const float OUT_RANGE_LAST_BOSS;				//	�ŏI�{�X�͈̔͊O

};