
//=============================================================================
//	@file	SceneGame.cpp
//	@brief	�Q�[���V�[��
//	@autor	���m ���
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SceneGame.h"
#include "SceneManager.h"
#include "Common.h"
#include "Pad.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "BossManager.h"
#include "ShotManager.h"
#include "StayShotManager.h"
#include "ItemManager.h"
#include "Camera.h"
#include "HitChecker.h"
#include "UILife.h"
#include "UIGauge.h"
#include "UIScore.h"
#include "UIStayShot.h"
#include "UIGameOver.h"
#include "UIBackPixel.h"
#include "UICongratulation.h"
#include "BackGround.h"
#include "EffekseerManager.h"
#include "SoundEffect.h"
#include "Sound.h"
#include "Warning.h"
#include "PlayCounter.h"
#include "LastBoss.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float SceneGame::MAX_CHANGE_LOSE_SCENE_WAIT_TIME = 180.0f;	//	�V�[���؂�ւ��̒x���̍ő�
const float SceneGame::MAX_CHANGE_WIN_SCENE_WAIT_TIME = 600.0f;		//	�V�[���؂�ւ��̒x���̍ő�
const float SceneGame::MAX_CHANGE_TITLE_SCENE_WAIT_TIME = 30.0f;	//	�V�[���؂�ւ��̒x���̍ő�
const float SceneGame::MAX_CHANGE_BGM_WAIT_TIME = 240.0f;			//	BGM�؂�ւ��̒x���̍ő�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
SceneGame::SceneGame()
{
	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
    m_pPlayerManager = NULL;
	m_pEnemyManager = NULL;
	m_pBossManager = NULL;
	m_pShotManager = NULL;
	m_pStayShotManager = NULL;
	m_pItemManager = NULL;
	m_pUILife = NULL;
	m_pUIGauge = NULL;
	m_pUIStayShot = NULL;
	m_pUIGameOver = NULL;
	m_pUIBackPixel = NULL;
	m_pUICongratulation = NULL;
	m_pEffekseerManager = NULL;
	m_pBackgroundMusic = NULL;
	m_pWarning = NULL;
	m_pPlayCounter = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
SceneGame::~SceneGame()
{
	//	�ŏI�m�F
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void SceneGame::Create()
{
	//	���[�h�̕`��
	LOADING->Draw();

	//	�G�t�F�N�g�̍쐬
	m_pEffekseerManager = new EffekseerManager();

    //  �v���C���[�̍쐬
    m_pPlayerManager = new PlayerManager();
    m_pPlayerManager->Create(m_pPlayerManager->PLAYER_INFO::PLAYER_GAME);
	
	//	�G�l�~�[�̍쐬
	m_pEnemyManager = new EnemyManager();
    m_pEnemyManager->Create();
    m_pEnemyManager->Initialize();

	//	�{�X�̍쐬
	m_pBossManager = new BossManager();
    m_pBossManager->Create();
    m_pBossManager->Initialize();

	//	�V���b�g�̍쐬
	m_pShotManager = new ShotManager();
    m_pShotManager->Create();

	//	�؍݃V���b�g�̍쐬
	m_pStayShotManager = new StayShotManager();
    m_pStayShotManager->Create();
    m_pStayShotManager->Initialize();

	//	�A�C�e���̍쐬
	m_pItemManager = new ItemManager();
    m_pItemManager->Create();

	//	���C�tUI�̍쐬
	m_pUILife = new UILife();
    m_pUILife->Create();

	//	�Q�[�WUI�̍쐬
	m_pUIGauge = new UIGauge();
    m_pUIGauge->Create();

	//	�X�e�C�V���b�gUI�̍쐬
	m_pUIStayShot = new UIStayShot();
    m_pUIStayShot->Create();

	//	�N���AUI
	m_pUICongratulation = new UICongratulation();
    m_pUICongratulation->Create();

	//	�w�i�s�N�Z��UI�̍쐬
	m_pUIBackPixel = new UIBackPixel();

	//	�Q�[���I�[�o�[UI�̍쐬
	m_pUIGameOver = new UIGameOver();
    m_pUIGameOver->Create();

	//	�t�H���g�̍쐬����
	FONT->Create();

	//	�T�E���h�̍쐬
	m_pBackgroundMusic = new Sound("Data/Sound/BGM/Game.mp3", "Data/Sound/BGM/Game2.mp3");
	m_pBackgroundMusic->OnPlay(DX_PLAYTYPE_LOOP);
	
	//	�x���̍쐬
	m_pWarning = new Warning();

	//	�v���C�񐔂̍쐬�A���Z��
	//	����ȏ�g�p���Ȃ��̂ŁA�폜����
	m_pPlayCounter = new PlayCounter();
	m_pPlayCounter->AddPlayCounter();
	CommonSafe::Delete(m_pPlayCounter);

	m_isDebug = false;
	m_isDebugDraw = false;
}

//-----------------------------------------------------------------------------
//	@brief	���
//-----------------------------------------------------------------------------
void SceneGame::Release()
{
    //	�v���C���[�̉��
    CommonSafe::Release(m_pPlayerManager);

	//	�G�l�~�[�̉��
	CommonSafe::Release(m_pEnemyManager);

	//	�{�X�̉��
	CommonSafe::Release(m_pBossManager);

	//	�V���b�g�̉��
	CommonSafe::Release(m_pShotManager);

	//	�؍݃V���b�g�̉��
	CommonSafe::Release(m_pStayShotManager);

	//	�A�C�e���̉��
	CommonSafe::Release(m_pItemManager);

	//	���C�tUI�̉��
	CommonSafe::Release(m_pUILife);

	//	�Q�[�WUI�̉��
	CommonSafe::Release(m_pUIGauge);

	//	�X�e�C�V���b�gUI�̉��
	CommonSafe::Release(m_pUIStayShot);

	//	�Q�[���I�[�o�[UI�̉��
	CommonSafe::Release(m_pUIGameOver);

	//	�w�i�s�N�Z��UI�̉��
	CommonSafe::Delete(m_pUIBackPixel);

	//	�N���AUI
	CommonSafe::Release(m_pUICongratulation);

	//	�G�t�F�N�g�̉��
	CommonSafe::Delete(m_pEffekseerManager);

	//	BGM�̉��
	CommonSafe::Delete(m_pBackgroundMusic);

	//	�x���̉��
	CommonSafe::Delete(m_pWarning);
}

//-----------------------------------------------------------------------------
//	@brief	������
//-----------------------------------------------------------------------------
void SceneGame::Initialize(Pad& _pad, Camera& _camera)
{
	//	�e�N���X�̏�������
	_camera.Initialize();
    m_pEnemyManager->Initialize();
    m_pBossManager->Initialize();
    m_pStayShotManager->Initialize();

	//	�L�[�̓��͂��g�p���ɂ���
	KEY->AllInUse();

	//	�p�b�h�̓��͂��g�p���ɂ���
	_pad.AllInUse();

	//	�V�[���J�ڒx�����Ԃ̏�����
	m_changeSceneWaitTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�X�V
//-----------------------------------------------------------------------------
void SceneGame::Update(Pad& _pad, Camera& _camera, BackGround& _backGround, SoundEffect& _soundEffect, SceneManager* _sceneManager)
{
	//	���j���[���ł͂���΁A�X�V����
	const bool isNotMenu = !MENU->GetIsSkipUpdate();
	if (isNotMenu)
	{
		//	�J�����̍X�V����
		_camera.Update(*m_pPlayerManager);

		//	�v���C���[�̍X�V����
        m_pPlayerManager->Update(_pad, *m_pShotManager, *m_pStayShotManager, _soundEffect, *m_pUIGauge);

		//	�G�l�~�[�̍X�V����
		m_pEnemyManager->Update(*m_pPlayerManager, *m_pShotManager, *m_pBossManager, *m_pItemManager, *m_pBackgroundMusic, _soundEffect, *m_pWarning);

		//	�{�X�̍X�V����
		m_pBossManager->Update(*m_pShotManager, _soundEffect);

		//	�V���b�g�̍X�V����
		m_pShotManager->Update();

		//	�؍݃V���b�g�̍X�V����
		m_pStayShotManager->Update(_soundEffect);

		//	�A�C�e���̍X�V����
		m_pItemManager->Update();

		//	�w�i�̍X�V����
		_backGround.Update();

		//	�Q�[�WUI�̍X�V����
		m_pUIGauge->Update(_soundEffect);

		//	�X�e�C�V���b�gUI�̍X�V����
		m_pUIStayShot->Update(*m_pPlayerManager,_soundEffect);

		//	�Q�[���I�[�o�[UI�̍X�V����
		m_pUIGameOver->Update(*m_pPlayerManager);

		//	�w�i�s�N�Z��UI�̍X�V����
		m_pUIBackPixel->Update();

		//	�N���AUI�̍X�V����
		m_pUICongratulation->Update(*m_pPlayerManager);

		//	���o���̃Q�[�W�̍X�V����
		PRODUCTION->Update();

		//	�X�R�A�̍X�V����
		SCORE->Update();

		//	�G�t�F�N�g�̍X�V����
		m_pEffekseerManager->Update();

		//	�x��
		m_pWarning->Update();

		//	BGM�̐؂�ւ�
		m_pBackgroundMusic->ChangeSound(DX_PLAYTYPE_LOOP, MAX_CHANGE_BGM_WAIT_TIME);

		//	���ׂĂ̓����蔻��
		_AllHitChecker(_soundEffect);
	}

	//	���j���[�̍X�V����
	MENU->Update(_pad, _soundEffect);

	//	SE�̍X�V
	_soundEffect.Update();

	//	�f�o�b�O
	_Debug();

	//	�V�[���̕ύX
	_ChangeScene(_pad, _soundEffect, _sceneManager);
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void SceneGame::Draw(BackGround& _backGround)
{
	//	�w�i�̕`�揈��
	_backGround.Draw();

	//	�w�i�s�N�Z��UI�̕`�揈��
	m_pUIBackPixel->Draw();

	//	�G�l�~�[�̕`�揈��
	m_pEnemyManager->Draw();

	//	�{�X�̕`�揈��
	m_pBossManager->Draw();

	//	�V���b�g�̕`�揈��
	m_pShotManager->Draw();

	//	�v���C���[�̕`�揈��
    m_pPlayerManager->Draw();

	//	�A�C�e���̕`�揈��
	m_pItemManager->Draw();

	//	���C�tUI�̕`�揈��
	m_pUILife->Draw(*m_pPlayerManager);

	//	�Q�[�WUI�̕`�揈��
	m_pUIGauge->Draw();

	//	�X�e�C�V���b�gUI�̕`�揈��
	m_pUIStayShot->Draw(*m_pPlayerManager);

	//	�Q�[���I�[�o�[UI�̕`�揈��
	m_pUIGameOver->Draw();

	//	�N���AUI�̕`�揈��
	m_pUICongratulation->Draw();

	//	�x���̕`��
	m_pWarning->Draw();

	//	�X�R�A�̕`�揈��
	SCORE->Draw();

	//	�G�t�F�N�g�̕`�揈��
	m_pEffekseerManager->Draw();

	//	���j���[�̕`�揈��
	MENU->Draw();

	//	���o���̃Q�[�W�̕`�揈��
	PRODUCTION->Draw();

	//	���ׂĂ̓����蔻��̕`��
	_AllHitCheckerOfDraw();
}

//-----------------------------------------------------------------------------
//	@brief	���ׂĂ̓����蔻��
//-----------------------------------------------------------------------------
void SceneGame::_AllHitChecker(SoundEffect& _soundEffect)
{
	//	���o���͓����蔻��𖳎�
	const bool isProduction = PRODUCTION->GetIsSceneProduction() || PRODUCTION->GetIsSpecialProduction() || PRODUCTION->GetIsClearProduction();
	if (!isProduction)
	{
		
		//	�{�X�������Ă���ԂƁA�f�o�b�O���ȊO�́A
		//	�v���C���[�̋@�̂̓����蔻������
		LastBoss* lastBoss = m_pBossManager->GetLastBossPtr();
		const bool isNntDeath = !lastBoss->GetIsDeath();
		const bool isNotDebug = !m_isDebug;
		const bool isActive = isNntDeath && isNotDebug;
		if (isActive)
		{
			//	�v���C���[�ƃG�l�~�[�̓����蔻��
			//	�G�l�~�[�̎��S���ɃA�C�e���̐������s��
			HitChecker::PlayerToEnemy(*m_pPlayerManager, *m_pEnemyManager, *m_pItemManager);

			//	�v���C���[�ƒ��{�X�̓����蔻��
			HitChecker::PlayerToMediumBoss(*m_pPlayerManager, *m_pBossManager);

			//	�v���C���[�ƍŏI�{�X�̓����蔻��
			HitChecker::PlayerToLastBoss(*m_pPlayerManager, *m_pBossManager);

			//	�v���C���[�ƃG�l�~�[�̒e�̓����蔻��
			HitChecker::PlayerToEnemyShot(*m_pPlayerManager, *m_pShotManager);
		}

		//	�v���C���[�̒e�ƃG�l�~�[�̓����蔻��
		//	�G�l�~�[�̎��S���ɃA�C�e���̐������s��
		HitChecker::PlayerShotToEnemy(*m_pShotManager, *m_pEnemyManager, *m_pItemManager, *m_pUIGauge);

		//	�v���C���[�̒e�ƒ��{�X�̓����蔻��
		HitChecker::PlayerShotToMediumBoss(*m_pShotManager, *m_pBossManager, *m_pUIGauge);

		//	�v���C���[�̒e�ƍŏI�{�X�̓����蔻��
		HitChecker::PlayerShotToLastBoss(*m_pPlayerManager, *m_pShotManager, *m_pBossManager, *m_pUIGauge);

		//	�v���C���[�؍ݒe�ƃG�l�~�[�̓����蔻��
		HitChecker::PlayerStayShotToEnemy(*m_pStayShotManager, *m_pEnemyManager, *m_pItemManager, *m_pUIGauge);

		//	�v���C���[�؍ݒe�ƒ��{�X�̓����蔻��
		HitChecker::PlayerStayShotToMediumBoss(*m_pStayShotManager, *m_pBossManager, *m_pUIGauge);

		//	�v���C���[�؍ݒe�ƍŏI�{�X�̓����蔻��
		HitChecker::PlayerStayShotToLastBoss(*m_pPlayerManager, *m_pStayShotManager, *m_pBossManager, *m_pUIGauge);
	}

	//	�v���C���[�ƃA�C�e���̓����蔻��
	HitChecker::PlayerToItem(*m_pPlayerManager, *m_pItemManager, _soundEffect, *m_pUIGauge);

	//	�K�E�Z�̓����蔻��
	HitChecker::PlayerSpecialAttackToAllObject(*m_pPlayerManager, *m_pEnemyManager,  *m_pBossManager, *m_pShotManager, *m_pItemManager);
}

//-----------------------------------------------------------------------------
//	@brief	���ׂĂ̓����蔻��̕`��
//-----------------------------------------------------------------------------
void SceneGame::_AllHitCheckerOfDraw()
{
	//	�f�o�b�O���͕`��
	const bool isDebug = m_isDebug || m_isDebugDraw;
	if (isDebug)
	{
		//	�v���C���[�ƃG�l�~�[�̓����蔻��̕`��
		HitChecker::PlayerToEnemyOfDraw(*m_pPlayerManager, *m_pEnemyManager);

		//	�v���C���[�ƒ��{�X�̓����蔻��̕`��
		HitChecker::PlayerToMediumBossOfDraw(*m_pPlayerManager, *m_pBossManager);

		//	�v���C���[�ƍŏI�{�X�̓����蔻��̕`��
		HitChecker::PlayerToLastBossOfDraw(*m_pPlayerManager, *m_pBossManager);

		// �v���C���[�ƃG�l�~�[�̒e�̓����蔻��̕`��
		HitChecker::PlayerToEnemyShotOfDraw(*m_pPlayerManager, *m_pShotManager);

		// �v���C���[�̒e�ƃG�l�~�[�̓����蔻��̕`��
		HitChecker::PlayerShotToEnemyOfDraw(*m_pShotManager, *m_pEnemyManager);

		//	�v���C���[�̒e�ƒ��{�X�̓����蔻��̕`��
		HitChecker::PlayerShotToMediumBossOfDraw(*m_pShotManager, *m_pBossManager);

		//	�v���C���[�e�ƍŏI�{�X�̓����蔻��̕`��
		HitChecker::PlayerShotToLastBossOfDraw(*m_pShotManager, *m_pBossManager);

		//	�v���C���[�؍ݒe�ƃG�l�~�[�̓����蔻��
		HitChecker::PlayerStayShotToEnemyOfDraw(*m_pStayShotManager, *m_pEnemyManager);

		//	�v���C���[�̑؍ݒe�ƒ��{�X�̓����蔻��̕`��
		HitChecker::PlayerStayShotToMediumBossOfDraw(*m_pStayShotManager, *m_pBossManager);

		//	�v���C���[�؍ݒe�ƍŏI�{�X�̓����蔻��̕`��
		HitChecker::PlayerStayShotToLastBossOfDraw(*m_pStayShotManager, *m_pBossManager);

		//	�v���C���[�ƃA�C�e���̓����蔻��̕`��
		HitChecker::PlayerToItemOfDraw(*m_pPlayerManager, *m_pItemManager);

		//	�K�E�Z�̓����蔻��
		HitChecker::PlayerSpecialAttackToAllObjectOfDraw(*m_pPlayerManager, *m_pEnemyManager, *m_pBossManager);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�f�o�b�O
//-----------------------------------------------------------------------------
void SceneGame::_Debug()
{
	//	�f�o�b�O�̐؂�ւ�
	const bool isDebug = KEY->Push(KEY_INPUT_F4);
	if (isDebug) { m_isDebug = !m_isDebug; }

	//	�f�o�b�O�`��̐؂�ւ�
	const bool isDebugDraw = KEY->Push(KEY_INPUT_F3);
	if (isDebugDraw) { m_isDebugDraw = !m_isDebugDraw; }
}

//-----------------------------------------------------------------------------
//	@brief	�V�[���̐؂�ւ�
//-----------------------------------------------------------------------------
void SceneGame::_ChangeScene(Pad& _pad, SoundEffect& _soundEffect, SceneManager* _sceneManager)
{
	//	���U���g�V�[����
	PlayerBase* player = m_pPlayerManager->GetPlayerPtr();
	const bool isLoseActive = !player->GetIsAlive();
	if (isLoseActive)
	{
		m_changeSceneWaitTime++;
		const bool isChangeScene = m_changeSceneWaitTime >= MAX_CHANGE_LOSE_SCENE_WAIT_TIME;
		if (isChangeScene) { _sceneManager->ChangeScene(SceneManager::SCENE_KIND::RESULT_SCENE); }
		return;
	}

	//	���U���g�V�[����
	const bool isWinActive = m_pPlayerManager->GetIsClear();
	if (isWinActive)
	{
		m_changeSceneWaitTime++;
		const bool isChangeScene = m_changeSceneWaitTime >= MAX_CHANGE_WIN_SCENE_WAIT_TIME;
		if (isChangeScene) { _sceneManager->ChangeScene(SceneManager::SCENE_KIND::RESULT_SCENE); }
		return;
	}

	//	�^�C�g����
	const bool isTitle = MENU->GetIsGoToTitle();
	if (isTitle)
	{
		m_changeSceneWaitTime++;
		const bool isChangeScene = m_changeSceneWaitTime >= MAX_CHANGE_TITLE_SCENE_WAIT_TIME;
		if (isChangeScene) { _sceneManager->ChangeScene(SceneManager::SCENE_KIND::TITLE_SCENE); }
		return;
	}

}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void SceneGame::_FinalRelease()
{
    //	�v���C���[�̉��
    CommonSafe::Release(m_pPlayerManager);

	//	�G�l�~�[�̉��
	CommonSafe::Release(m_pEnemyManager);

	//	�{�X�̉��
	CommonSafe::Release(m_pBossManager);

	//	�V���b�g�̉��
	CommonSafe::Release(m_pShotManager);

	//	�؍݃V���b�g�̉��
	CommonSafe::Release(m_pStayShotManager);

	//	�A�C�e���̉��
	CommonSafe::Release(m_pItemManager);

	//	���C�tUI�̉��
	CommonSafe::Release(m_pUILife);

	//	�Q�[�WUI�̉��
	CommonSafe::Release(m_pUIGauge);

	//	�X�e�C�V���b�gUI�̉��
	CommonSafe::Release(m_pUIStayShot);

	//	�Q�[���I�[�o�[UI�̉��
	CommonSafe::Release(m_pUIGameOver);

	//	�w�i�s�N�Z��UI�̉��
	CommonSafe::Delete(m_pUIBackPixel);

	//	�N���AUI
	CommonSafe::Release(m_pUICongratulation);

	//	�G�t�F�N�g�̉��
	CommonSafe::Delete(m_pEffekseerManager);

	//	BGM�̉��
	CommonSafe::Delete(m_pBackgroundMusic);

	//	�x���̉��
	CommonSafe::Delete(m_pWarning);
}
