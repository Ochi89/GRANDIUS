
//=============================================================================
//	@file	PlayerManager.cpp
//	@brief	�v���C���[�}�l�[�W���[
//	@autor	���m ���
//	@date	2018/11/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerManager.h"
#include "PlayerBase.h"
#include "TitlePlayer.h"
#include "GamePlayer.h"
#include "DemoPlayer.h"
#include "ResultPlayer.h"
#include "Common.h"
#include "ShotManager.h"
#include "StayShotManager.h"
#include "SoundEffect.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "SceneManager.h"

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
PlayerManager::PlayerManager()
	: m_sourceModelHandle(-1)
{
	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL
	m_pPlayer = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
PlayerManager::~PlayerManager()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void PlayerManager::Create(PLAYER_INFO _playerInfo)
{
    //	��{�̃��f���̓ǂݍ���
    m_sourceModelHandle = MV1LoadModel("Data/Model/Player/Player.pmx");
    CommonDebug::Assert((m_sourceModelHandle <= -1), " [ PlayerManager.cpp ] : error : model loading failed.");

    //	�v���C���[�̐؂�ւ�
    switch (_playerInfo)
    {
        //	�^�C�g���V�[��
    case PLAYER_INFO::PLAYER_TITLE:
        m_pPlayer = new TitlePlayer(m_sourceModelHandle);
        m_pPlayer->Create();
        m_pPlayer->Initialize();
        break;

        //	�Q�[���V�[��
    case PLAYER_INFO::PLAYER_GAME:
        m_isClear = false;
        m_isProduction = false;
        m_pPlayer = new GamePlayer(m_sourceModelHandle);
        m_pPlayer->Create();
        m_pPlayer->Initialize();
        break;

        //	���U���g�V�[��
    case PLAYER_INFO::PLAYER_RESULT:
        m_pPlayer = new ResultPlayer(m_sourceModelHandle);
        m_pPlayer->Create();
        m_pPlayer->Initialize();
        break;

        //	�f���V�[��
    case PLAYER_INFO::PLAYER_DEMO:
        m_pPlayer = new DemoPlayer(m_sourceModelHandle);
        m_pPlayer->Create();
        m_pPlayer->Initialize();
        break;
    }
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void PlayerManager::Release()
{
	//	�v���C���[�̉��
	CommonSafe::Release(m_pPlayer);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void PlayerManager::Update()
{
    //	�v���C���[�̍X�V
    m_pPlayer->Update();
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void PlayerManager::Update(Pad& _pad, ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gauge)
{
    //	�N���A�����Ƃ��͈ړ���~
    if (m_isClear)
    {
        m_pPlayer->SetIsStopMove(m_isClear);
    }

    //	�N���A�󋵂����U���g�ֈ����n��
    HAND_OVER_RESULT->SetIsClear(m_isClear);

    //	�v���C���[�̍X�V
    m_pPlayer->Update(_pad, _shot, _stayShot, _soundEffect, _gauge);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void PlayerManager::Update(ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gauge, EnemyManager& _enemyManager)
{
    //	�v���C���[�̍X�V
    m_pPlayer->Update(_shot, _stayShot, _soundEffect, _gauge, _enemyManager);
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void PlayerManager::Draw()
{
	//	�v���C���[�̕`��
	m_pPlayer->Draw();
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void PlayerManager::_FinalRelease()
{
	//	�v���C���[�̉��
	CommonSafe::Release(m_pPlayer);
}
