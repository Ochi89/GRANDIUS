
//=============================================================================
//	@file	SceneResult.cpp
//	@brief	���U���g�V�[��
//	@autor	���m ���
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SceneResult.h"
#include "PlayerManager.h"
#include "SceneManager.h"
#include "Common.h"
#include "Pad.h"
#include "Ranking.h"
#include "Camera.h"
#include "BackGround.h"
#include "UIBackPixel.h"
#include "SoundEffect.h"
#include "Sound.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float SceneResult::MAX_CHANGE_SCENE_WAIT_TIME = 60.0f;		//	�V�[���؂�ւ��̒x���̍ő�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
SceneResult::SceneResult()
{
	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
    m_pPlayerManager = NULL;
	m_pRanking = NULL;
	m_pUIBackPixel = NULL;
	m_pBackgroundMusic = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
SceneResult::~SceneResult()
{
	// �ŏI�m�F
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void SceneResult::Create()
{
    //  �v���C���[�̍쐬
    m_pPlayerManager = new PlayerManager();
    m_pPlayerManager->Create(m_pPlayerManager->PLAYER_INFO::PLAYER_RESULT);

	//	�����L���O�̍쐬
	m_pRanking = new Ranking();
    m_pRanking->Initialize();

	//	�w�i�s�N�Z��UI�̍쐬
	m_pUIBackPixel = new UIBackPixel();

	//	�T�E���h�̍쐬
	m_pBackgroundMusic = new Sound("Data/Sound/BGM/Result.mp3");
	m_pBackgroundMusic->OnPlay(DX_PLAYTYPE_LOOP);
}

//-----------------------------------------------------------------------------
//	@brief	���
//-----------------------------------------------------------------------------
void SceneResult::Release()
{
    //	�v���C���[�̉��
    CommonSafe::Release(m_pPlayerManager);

	//	�����L���O�̉��
	CommonSafe::Delete(m_pRanking);

	//	�w�i�s�N�Z��UI�̉��
	CommonSafe::Delete(m_pUIBackPixel);

	//	BGM�̉��
	CommonSafe::Delete(m_pBackgroundMusic);
}

//-----------------------------------------------------------------------------
//	@brief	������
//-----------------------------------------------------------------------------
void SceneResult::Initialize(Pad& _pad, Camera& _camera)
{
	//	������
    m_pRanking->Initialize();
	_camera.Initialize();

	//	�V�[���J�ڒx�����Ԃ̏�����
	m_changeSceneWaitTime = 0.0f;

	//	�L�[�̓��͂��g�p���ɂ���
	KEY->AllInUse();

	//	�p�b�h�̓��͂��g�p���ɂ���
	_pad.AllInUse();

	//	�V�[���J�ڃt���O�̏�����
	m_isChangeScene = false;

	//	�p�b�h�̐U���@�\�̏I��
	PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V
//-----------------------------------------------------------------------------
void SceneResult::Update(Pad& _pad, Camera& _camera, BackGround& _backGround, SoundEffect& _soundEffect, SceneManager* _sceneManager)
{
	//	�����L���O�̍X�V����
	m_pRanking->Update(_pad, _soundEffect);

	//	�J�����̍X�V����
	_camera.UpdateForResult(*m_pPlayerManager);

	//	�v���C���[�̍X�V����
    m_pPlayerManager->Update();

	//	�w�i�̍X�V����
	_backGround.Update();

	//	�w�i�s�N�Z���̍X�V����
	m_pUIBackPixel->Update();

	//	SE�̍X�V
	_soundEffect.Update();

	//�V�[���̕ύX
	_ChangeScene(_pad, _soundEffect, _sceneManager);
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void SceneResult::Draw(BackGround& _backGround)
{
	//	�w�i�̕`�揈��
	_backGround.Draw();
	
	//	�w�i�s�N�Z��UI�̕`�揈��
	m_pUIBackPixel->Draw();
	
	//	�v���C���[�̕`�揈��
    m_pPlayerManager->Draw();

	//	�����L���O�̕`�揈��
	m_pRanking->Draw();
}

//-----------------------------------------------------------------------------
//	@brief	�V�[���̐؂�ւ�
//-----------------------------------------------------------------------------
void SceneResult::_ChangeScene(Pad& _pad, SoundEffect& _soundEffect, SceneManager* _sceneManager)
{
	//	�����L���O���J�n������
	const bool isRankingStart = m_pRanking->GetIsRankingStart();
	if (isRankingStart)
	{
		//	���͂��������玟��
		const bool isKeyActive = KEY->Push(KEY_INPUT_RETURN) || KEY->Push(KEY_INPUT_SPACE) || KEY->Push(KEY_INPUT_X) || KEY->Push(KEY_INPUT_K) || KEY->Push(KEY_INPUT_A);
		const bool isNextActive = isKeyActive || _pad.GetXInputPushButton(PadInfo::PAD_BUTTON_KIND::BUTTON_A);
		const bool isActive = isNextActive && !m_isChangeScene;
		if (isActive) { m_isChangeScene = true; _soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_MENU_DECISION); }

		//	�^�C�g���V�[����
		//	�V�[���̐؂�ւ�
		if (m_isChangeScene)
		{
			m_changeSceneWaitTime++;
			const bool isChangeScene = m_changeSceneWaitTime >= MAX_CHANGE_SCENE_WAIT_TIME;
			if (isChangeScene) { _sceneManager->ChangeScene(SceneManager::SCENE_KIND::TITLE_SCENE); }
			return;
		}
	}

	//	���Ԍo�߂ɂ��A�V�[���؂�ւ�
	const bool isSceneChange = m_pRanking->GetIsSceneChange();
	if (isSceneChange) { _sceneManager->ChangeScene(SceneManager::SCENE_KIND::TITLE_SCENE); }
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void SceneResult::_FinalRelease()
{
    //	�v���C���[�̉��
    CommonSafe::Release(m_pPlayerManager);

	//	�����L���O�̉��
	CommonSafe::Delete(m_pRanking);

	//	�w�i�s�N�Z��UI�̉��
	CommonSafe::Delete(m_pUIBackPixel);

	//	BGM�̉��
	CommonSafe::Delete(m_pBackgroundMusic);
}
