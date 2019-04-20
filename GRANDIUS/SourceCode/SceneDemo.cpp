
//=============================================================================
//	@file	SceneDemo.cpp
//	@brief	�f���V�[��
//	@autor	���m ���
//	@date	2018/1/13
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SceneDemo.h"
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
#include "UIDemoPlay.h"
#include "UIBackPixel.h"
#include "BackGround.h"
#include "EffekseerManager.h"
#include "SoundEffect.h"
#include "Sound.h"
#include "Warning.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float		SceneDemo::END_DEMO_TIME = 1600.0f;						//	�f���̏I��
const float		SceneDemo::MAX_CHANGE_LOSE_SCENE_WAIT_TIME = 60.0f;		//	�V�[���؂�ւ��̒x���̍ő�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
SceneDemo::SceneDemo()
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
	m_pUIDemoPlay = NULL;
	m_pUIBackPixel = NULL;
	m_pEffekseerManager = NULL;
	m_pBackgroundMusic = NULL;
	m_pWarning = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
SceneDemo::~SceneDemo()
{
	//	�ŏI�m�F
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void SceneDemo::Create()
{
	//	���[�h�̕`��
	LOADING->Draw();

	//	�G�t�F�N�g�̍쐬
	m_pEffekseerManager = new EffekseerManager();

    //  �v���C���[�̍쐬
    m_pPlayerManager = new PlayerManager();
    m_pPlayerManager->Create(m_pPlayerManager->PLAYER_INFO::PLAYER_DEMO);

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

	//	�X�e�C�V���b�gUI
	m_pUIStayShot = new UIStayShot();
    m_pUIStayShot->Create();

	//	�f���v���CUI1�̍쐬
	m_pUIDemoPlay = new UIDemoPlay();
    m_pUIDemoPlay->Create();

	//	�w�i�s�N�Z��UI�̍쐬
	m_pUIBackPixel = new UIBackPixel();

	//	�t�H���g�̍쐬����
	FONT->Create();

	//	�T�E���h�̍쐬
	m_pBackgroundMusic = new Sound("Data/Sound/BGM/Game.mp3");
	m_pBackgroundMusic->OnPlay(DX_PLAYTYPE_LOOP);

	//	�x���̍쐬
	m_pWarning = new Warning();
}

//-----------------------------------------------------------------------------
//	@brief	���
//-----------------------------------------------------------------------------
void SceneDemo::Release()
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

	//	�f���v���CUI�̉��
	CommonSafe::Release(m_pUIDemoPlay);

	//	�w�i�s�N�Z��UI�̉��
	CommonSafe::Delete(m_pUIBackPixel);

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
void SceneDemo::Initialize(Pad& _pad, Camera& _camera)
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

	//	�f�����Ԃ̏�����
	m_demoTime = 0.0f;

}

//-----------------------------------------------------------------------------
//	@brief	�X�V
//-----------------------------------------------------------------------------
void SceneDemo::Update(Pad& _pad, Camera& _camera, BackGround& _backGround, SoundEffect& _soundEffect, SceneManager* _sceneManager)
{
	//	�J�����̍X�V����
	_camera.Update(*m_pPlayerManager);

	//	�v���C���[�̍X�V����
    m_pPlayerManager->Update(*m_pShotManager, *m_pStayShotManager, _soundEffect, *m_pUIGauge, *m_pEnemyManager);

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

	//	�w�i�s�N�Z���̍X�V����
	m_pUIBackPixel->Update();

	//	�Q�[�WUI�̍X�V����
	m_pUIGauge->Update(_soundEffect);

	//	�X�e�C�V���b�gUI�̍X�V����
	m_pUIStayShot->Update(*m_pPlayerManager, _soundEffect);

	//	�f���v���CUI�̍X�V����
	m_pUIDemoPlay->Update();

	//	���o���̃Q�[�W�̍X�V����
	PRODUCTION->Update();

	//	�X�R�A�̍X�V����
	SCORE->Update();

	//	�G�t�F�N�g�̍X�V����
	m_pEffekseerManager->Update();

	//	�x��
	m_pWarning->Update();

	//	���ׂĂ̓����蔻��
	_AllHitChecker(_soundEffect);

	//	SE�̍X�V
	_soundEffect.Update();

	//	�V�[���̕ύX
	_ChangeScene(_pad, _soundEffect, _sceneManager);
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void SceneDemo::Draw(BackGround& _backGround)
{
	//	�w�i�̕`�揈��
	_backGround.Draw();

	//	�w�i�s�N�Z���̕`�揈��
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

	//	�X�R�A�̕`�揈��
	SCORE->Draw();

	//	���o���̃Q�[�W�̕`�揈��
	PRODUCTION->Draw();

	//	�f���v���CUI�̕`�揈��
	m_pUIDemoPlay->Draw();

	//	�G�t�F�N�g�̕`�揈��
	m_pEffekseerManager->Draw();

	//	���j���[�̕`�揈��
	MENU->Draw();
}

//-----------------------------------------------------------------------------
//	@brief	���ׂĂ̓����蔻��
//-----------------------------------------------------------------------------
void SceneDemo::_AllHitChecker(SoundEffect& _soundEffect)
{
	//	���o���͓����蔻��𖳎�
	const bool isProduction = PRODUCTION->GetIsSceneProduction() || PRODUCTION->GetIsSpecialProduction() || PRODUCTION->GetIsClearProduction();
	if (!isProduction)
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
	HitChecker::PlayerSpecialAttackToAllObject(*m_pPlayerManager, *m_pEnemyManager, *m_pBossManager, *m_pShotManager, *m_pItemManager);
}

//-----------------------------------------------------------------------------
//	@brief	�V�[���̐؂�ւ�
//-----------------------------------------------------------------------------
void SceneDemo::_ChangeScene(Pad& _pad, SoundEffect& _soundEffect, SceneManager* _sceneManager)
{
	//	�v���C���[�̎��S��
	PlayerBase* player = m_pPlayerManager->GetPlayerPtr();
	const bool isLoseActive = !player->GetIsAlive();
	if (isLoseActive)
	{
		m_changeSceneWaitTime++;
		const bool isChangeScene = m_changeSceneWaitTime >= MAX_CHANGE_LOSE_SCENE_WAIT_TIME;
		if (isChangeScene) { _sceneManager->ChangeScene(SceneManager::SCENE_KIND::TITLE_SCENE); }
		return;
	}

	const bool isKeyActive = KEY->Push(KEY_INPUT_RETURN) || KEY->Push(KEY_INPUT_SPACE) || KEY->Push(KEY_INPUT_X) || KEY->Push(KEY_INPUT_K) || KEY->Push(KEY_INPUT_A);
	const bool isNextActive = isKeyActive || _pad.GetXInputPushButton(PadInfo::PAD_BUTTON_KIND::BUTTON_ALL);
	if (isNextActive) { _soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_MENU_DECISION); }

	//	�f���I�����A�L�[���͂�����Ƃ�
	m_demoTime++;
	const bool isDemoEnd = m_demoTime >= END_DEMO_TIME;
	const bool isActive = isDemoEnd || isNextActive;
	
	//	�^�C�g���V�[����
	if (isActive) { _sceneManager->ChangeScene(SceneManager::SCENE_KIND::TITLE_SCENE); }
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void SceneDemo::_FinalRelease()
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

	//	�f���v���CUI�̉��
	CommonSafe::Release(m_pUIDemoPlay);

	//	�w�i�s�N�Z��UI�̉��
	CommonSafe::Delete(m_pUIBackPixel);

	//	�G�t�F�N�g�̉��
	CommonSafe::Delete(m_pEffekseerManager);

	//	BGM�̉��
	CommonSafe::Delete(m_pBackgroundMusic);

	//	�x���̉��
	CommonSafe::Delete(m_pWarning);
}
