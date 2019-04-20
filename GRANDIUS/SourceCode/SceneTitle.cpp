
//=============================================================================
//	@file	SceneTitle.cpp
//	@brief	�^�C�g���V�[��
//	@autor	���m ���
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SceneTitle.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#include "Common.h"
#include "Pad.h"
#include "Camera.h"
#include "BackGround.h"
#include "Production.h"
#include "UIScore.h"
#include "UIBackPixel.h"
#include "SoundEffect.h"
#include "Sound.h"
#include "Title.h"
#include "Opening.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float		SceneTitle::MAX_CHANGE_SCENE_WAIT_TIME = 80.0f;		//	�V�[���؂�ւ��̒x���̍ő�
const float		SceneTitle::START_DEMO_TIME = 600.0f;				//	�f���J�n����

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
SceneTitle::SceneTitle()
{
	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
    m_pPlayerManager = NULL;
    m_pBackgroundMusic = NULL;
	m_pUIBackPixel = NULL;
	m_pTitle = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
SceneTitle::~SceneTitle()
{
	//	�ŏI�m�F
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void SceneTitle::Create()
{
    //  �v���C���[�̍쐬
    m_pPlayerManager = new PlayerManager();
    m_pPlayerManager->Create(m_pPlayerManager->PLAYER_INFO::PLAYER_TITLE);

	//	�^�C�g���̍쐬
	m_pTitle = new Title();
    m_pTitle->Create();

	//	�w�i�s�N�Z��UI�̍쐬
	m_pUIBackPixel = new UIBackPixel();

	//	�T�E���h�̍쐬
	m_pBackgroundMusic = new Sound("Data/Sound/BGM/Title.mp3");
}

//-----------------------------------------------------------------------------
//	@brief	���
//-----------------------------------------------------------------------------   
void SceneTitle::Release()
{
    //	�v���C���[�̉��
    CommonSafe::Release(m_pPlayerManager);

	//	�^�C�g���̉��
	CommonSafe::Release(m_pTitle);

	//	�w�i�s�N�Z��UI�̉��
	CommonSafe::Delete(m_pUIBackPixel);

	//	BGM�̉��
	CommonSafe::Delete(m_pBackgroundMusic);
}

//-----------------------------------------------------------------------------
//	@brief	������
//-----------------------------------------------------------------------------
void SceneTitle::Initialize(Pad& _pad, Camera& _camera)
{
	//	�e�N���X�̏�������
	_camera.InitializeForTitle();

	//	�V�[���J�ڒx�����Ԃ̏�����
	m_changeSceneWaitTime = 0.0f;

	//	���o�̏�����
	PRODUCTION->AllReset();

	//	�X�R�A�̏�����
	SCORE->ScoreReset();

	//	���j���[�̏�����
	MENU->Initialize();

	//	���Z�b�g
	HAND_OVER_RESULT->Reset();

	//	�L�[�̓��͂��g�p���ɂ���
	KEY->AllInUse();

	//	�p�b�h�̓��͂��g�p���ɂ���
	_pad.AllInUse();

	//	�f���J�n���Ԃ̏�����
	m_demoTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�X�V
//-----------------------------------------------------------------------------
void SceneTitle::Update(Pad& _pad, Camera& _camera, BackGround& _backGround, SoundEffect& _soundEffect, SceneManager* _sceneManager)
{
	//	�I�[�v�j���O���I��������
	const bool isOpeningEnd = OPENING->GetIsEndOpening();
	if (isOpeningEnd)
	{
		//	BGM�̍Đ�
		m_pBackgroundMusic->OnPlay(DX_PLAYTYPE_LOOP);

		//	�J�����̍X�V����
		_camera.UpdateForTitle(*m_pPlayerManager);

		//	�v���C���[�̍X�V����
        m_pPlayerManager->Update();

		//	�w�i�̍X�V����
		_backGround.Update();

		//	�w�i�s�N�Z���̍X�V����
		m_pUIBackPixel->Update();

		//	�^�C�g���̍X�V����
		m_pTitle->Update(_soundEffect);

		//	SE�̍X�V
		_soundEffect.Update();

		//	�V�[���̕ύX
		_ChangeScene(_pad, _soundEffect, _sceneManager);

		//	�f���J�n����
		if (!PRODUCTION->GetIsTitleProduction()) { m_demoTime++; }
	}
	else
	{
		//	�I�[�v�j���O�̍X�V����
		OPENING->Update(_pad);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void SceneTitle::Draw(BackGround& _backGround)
{
	//	�I�[�v�j���O���I��������
	const bool isOpeningEnd = OPENING->GetIsEndOpening();
	if (isOpeningEnd)
	{
		//	�w�i�̕`�揈��
		_backGround.Draw();

		//	�w�i�s�N�Z��UI�̕`�揈��
		m_pUIBackPixel->Draw();

		//	�v���C���[�̕`�揈��
        m_pPlayerManager->Draw();

		//	�^�C�g���̕`�揈��
		m_pTitle->Draw();
	}
	else
	{
		//	�I�[�v�j���O�̕`�揈��
		OPENING->Draw();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�V�[���̐؂�ւ�
//-----------------------------------------------------------------------------
void SceneTitle::_ChangeScene(Pad& _pad, SoundEffect& _soundEffect, SceneManager* _sceneManager)
{
	//	���K�J�n
	const bool isKeyActive = KEY->Push(KEY_INPUT_RETURN) || KEY->Push(KEY_INPUT_SPACE) || KEY->Push(KEY_INPUT_X) || KEY->Push(KEY_INPUT_K) || KEY->Push(KEY_INPUT_A);
	const bool isNextActive = isKeyActive || _pad.GetXInputPushButton(PadInfo::PAD_BUTTON_KIND::BUTTON_A);
	const bool isActive = isNextActive && !PRODUCTION->GetIsTitleProduction();
	if (isActive) { PRODUCTION->SetIsTitleProduction(true); _soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_SELECT); }

	//	�Q�[���V�[���̐؂�ւ�
	if (PRODUCTION->GetIsTitleProduction())
	{
		m_changeSceneWaitTime++;
		const bool isChangeScene = m_changeSceneWaitTime >= MAX_CHANGE_SCENE_WAIT_TIME;
		if (isChangeScene) { _sceneManager->ChangeScene(SceneManager::SCENE_KIND::GAME_SCENE); }
		return;
	}

	//	�f���V�[���̐؂�ւ�
	const bool isDemoStart = m_demoTime >= START_DEMO_TIME;
	if (isDemoStart)
	{
		_sceneManager->ChangeScene(SceneManager::SCENE_KIND::DEMO_SCENE);
		return;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void SceneTitle::_FinalRelease()
{
    //	�v���C���[�̉��
    CommonSafe::Release(m_pPlayerManager);

	//	�^�C�g���̉��
	CommonSafe::Release(m_pTitle);

	//	�w�i�s�N�Z��UI�̉��
	CommonSafe::Delete(m_pUIBackPixel);

	//	BGM�̉��
	CommonSafe::Delete(m_pBackgroundMusic);
}
