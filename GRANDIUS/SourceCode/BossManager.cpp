
//=============================================================================
//	@file	BossManager.cpp
//	@brief	�{�X�}�l�[�W���[
//	@autor	���m ���
//	@date	2018/12/18
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BossManager.h"
#include "MediumBoss.h"
#include "LastBoss.h"
#include "ShotManager.h"
#include "Common.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float BossManager::OUT_RANGE_MEDIUM_BOSS = -100.0f;			//	���{�X�͈̔͊O
const float BossManager::OUT_RANGE_LAST_BOSS = -100.0f;				//	�ŏI�{�X�͈̔͊O

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
BossManager::BossManager()
{
	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL
	m_mediumBoss.m_pBuf = NULL;
	m_lastBoss.m_pBuf = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
BossManager::~BossManager()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void BossManager::Create()
{
	//	���{�X��{�̃��f���̓ǂݍ���
	m_mediumBoss.m_sourceModelHandle = MV1LoadModel("Data/Model/Boss/MediumBoss.mqo");
	CommonDebug::Assert((m_mediumBoss.m_sourceModelHandle <= -1), " [ BassManager.cpp ] : error : model loading failed.");

	//	�ŏI�{�X��{�̃��f���̓ǂݍ���
	m_lastBoss.m_sourceModelHandle = MV1LoadModel("Data/Model/Boss/BossBody.mqo");
	m_lastBoss.m_sideBarrelSourceModelHandle = MV1LoadModel("Data/Model/Boss/BossSideBarrel.mqo");
	m_lastBoss.m_armSourceModelHandle = MV1LoadModel("Data/Model/Boss/BossArm.mqo");
	m_lastBoss.m_coreSourceModelHandle = MV1LoadModel("Data/Model/Boss/BossCore.mqo");
	CommonDebug::Assert((m_lastBoss.m_sourceModelHandle <= -1), " [ BassManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_lastBoss.m_sideBarrelSourceModelHandle <= -1), " [ BassManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_lastBoss.m_armSourceModelHandle <= -1), " [ BassManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_lastBoss.m_coreSourceModelHandle <= -1), " [ BassManager.cpp ] : error : model loading failed.");

	//	���{�X�̍쐬
	m_mediumBoss.m_pBuf = new MediumBoss(m_mediumBoss.m_sourceModelHandle);
	m_mediumBoss.m_pBuf->Create();
	m_mediumBoss.m_isEmerge = false;

	//	�ŏI�{�X�̍쐬
	m_lastBoss.m_pBuf = new LastBoss(m_lastBoss.m_sourceModelHandle, m_lastBoss.m_sideBarrelSourceModelHandle, m_lastBoss.m_armSourceModelHandle, m_lastBoss.m_coreSourceModelHandle);
	m_lastBoss.m_pBuf->Create();
	m_lastBoss.m_isEmerge = false;
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void BossManager::Release()
{
	//	���{�X�̉��
	CommonSafe::Release(m_mediumBoss.m_pBuf);

	//	�ŏI�{�X�̉��
	CommonSafe::Release(m_lastBoss.m_pBuf);
}

//-----------------------------------------------------------------------------
//	@brief	�������u
//-----------------------------------------------------------------------------
void BossManager::Initialize()
{
	//	���{�X�̏�����
	if (m_mediumBoss.m_pBuf)
	{
		m_mediumBoss.m_pBuf->Initialize();
	}

	//	�ŏI�{�X�̏�����
	if (m_lastBoss.m_pBuf)
	{
		m_lastBoss.m_pBuf->Initialize();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void BossManager::Update(ShotManager& _shot, SoundEffect& _soundEffect)
{
	const bool isNotClear = !PRODUCTION->GetIsClearProduction();
	if (isNotClear)
	{
		//	���{�X�̍X�V
		if (m_mediumBoss.m_pBuf)
		{
			m_mediumBoss.m_pBuf->SetIsEmerge(m_mediumBoss.m_isEmerge);
			m_mediumBoss.m_pBuf->Update(_shot, _soundEffect);

			//	���񂾂�A���������������
			const bool isDead = m_mediumBoss.m_pBuf->GetIsDeleate() || m_mediumBoss.m_pBuf->GetPos().x <= OUT_RANGE_MEDIUM_BOSS;
			if (isDead) { CommonSafe::Release(m_mediumBoss.m_pBuf); }
		}

		//	�ŏI�{�X�̍X�V
		if (m_lastBoss.m_pBuf)
		{
			m_lastBoss.m_pBuf->SetIsEmerge(m_lastBoss.m_isEmerge);
			m_lastBoss.m_pBuf->Update(_shot, _soundEffect);

			//	���񂾂�A���������������
			const bool isDead = !m_lastBoss.m_pBuf->GetIsAlive() || m_lastBoss.m_pBuf->GetPos().x <= OUT_RANGE_LAST_BOSS;
			if (isDead) { CommonSafe::Release(m_lastBoss.m_pBuf); }
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void BossManager::Draw()
{
	//	���{�X�̕`��
	if (m_mediumBoss.m_pBuf)
	{
		m_mediumBoss.m_pBuf->Draw();
	}

	//	�ŏI�{�X�̕`��
	if (m_lastBoss.m_pBuf)
	{
		m_lastBoss.m_pBuf->Draw();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void BossManager::_FinalRelease()
{
	//	���{�X�̉��
	CommonSafe::Release(m_mediumBoss.m_pBuf);

	//	�ŏI�{�X�̉��
	CommonSafe::Release(m_lastBoss.m_pBuf);
}
