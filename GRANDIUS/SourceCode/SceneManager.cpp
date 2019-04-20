
//=============================================================================
//	@file	SceneManager.cpp
//	@brief	�V�[���}�l�[�W���[
//	@autor	���m ���
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneDemo.h"
#include "Common.h"
#include "Pad.h"
#include "BackGround.h"
#include "Camera.h"
#include "Sound.h"
#include "SoundEffect.h"

//#define CREATE_GRID 0

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
SceneManager::SceneManager()
{
	//	�܂��ǂ����w���Ă��Ȃ��̂� NULL
	m_pScene = NULL;
	m_pPad1 = NULL;
	m_pPad2 = NULL;
	m_pPad3 = NULL;
	m_pPad4 = NULL;
	m_pCamera = NULL;
	m_pBackGround = NULL;
	m_pSoundEffect = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
SceneManager::~SceneManager()
{
	//	�ŏI�m�F
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void SceneManager::Create()
{
	//	�J�����̍쐬
	m_pCamera = new Camera;

	//	�w�i�̍쐬
	m_pBackGround = new BackGround();
	m_pBackGround->Create();

	//	�p�b�h�̓ǂݍ���
	m_pPad1 = new Pad();
	m_pPad2 = new Pad();
	m_pPad3 = new Pad();
	m_pPad4 = new Pad();

	//	SE�̍쐬
	m_pSoundEffect = new SoundEffect();
	m_pSoundEffect->Create();
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void SceneManager::Release()
{
	//	�p�b�h�̉��
	_PadRelease();

	//	�J�����̉��
	CommonSafe::Delete(m_pCamera);

	//	�w�i�̉��
	CommonSafe::Release(m_pBackGround);

	//	SE�̉��
	CommonSafe::Release(m_pSoundEffect);

	//	�V�[���̉��
	CommonSafe::Release(m_pScene);
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void SceneManager::Initialize()
{
	//	���C�g�̒���
	int lightHandle = CreateDirLightHandle(VGet(1.0f, -1.0f, 1.0f));
	SetLightDirectionHandle(lightHandle, VGet(-0.5f, 0.0f, 0.0f));
}

//-----------------------------------------------------------------------------
//	@brief	�V�[���̐؂�ւ�
//-----------------------------------------------------------------------------
void SceneManager::ChangeScene(SCENE_KIND _sceneKind)
{
	//	�V�[�������݂��؂�ւ����s�����Ƃ��ɁA�������
	if (m_pScene) { CommonSafe::Release(m_pScene); }

	//	�V�[���̎�ނŐ؂�ւ���
	switch (_sceneKind)
	{

		//	�^�C�g���V�[��
	case SCENE_KIND::TITLE_SCENE:
		m_pScene = new SceneTitle();
        m_pScene->Create();
		m_pScene->Initialize(*m_pPad1, *m_pCamera);
		break;

		//	�Q�[���V�[��
	case SCENE_KIND::GAME_SCENE:
		m_pScene = new SceneGame();
        m_pScene->Create();
		m_pScene->Initialize(*m_pPad1, *m_pCamera);
		break;

		//	���U���g�V�[��
	case SCENE_KIND::RESULT_SCENE:
		m_pScene = new SceneResult();
        m_pScene->Create();
		m_pScene->Initialize(*m_pPad1, *m_pCamera);
		break;

		//	�f���V�[��
	case SCENE_KIND::DEMO_SCENE:
		m_pScene = new SceneDemo();
        m_pScene->Create();
		m_pScene->Initialize(*m_pPad1, *m_pCamera);
		break;
	}
}

//-----------------------------------------------------------------------------
//	@brief	���C�����[�v
//-----------------------------------------------------------------------------
void SceneManager::Ran()
{
	//	�G�X�P�[�v�L�[��������邩�A�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	�X�V
		_Update();

		//	�`��
		_Draw();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�X�V
//-----------------------------------------------------------------------------
void SceneManager::_Update()
{
	//	�p�b�h�̓��͂����
	_PadInput();

	//	�X�V����
    //  �����͖��񐶐�����ƃQ�[�����d���Ȃ�̂ŁA
    //  �e�V�[���Ŏg���܂킵������̂�n���Ă���
	m_pScene->Update(*m_pPad1, *m_pCamera, *m_pBackGround, *m_pSoundEffect, this);

	//	��ʂ̃N���A
	ClearDrawScreen();
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void SceneManager::_Draw()
{
#ifdef CREATE_GRID
	
	//	�O���b�h�̕`��
	CommonFunction::CreateGrid();
	
#endif // CREATE_GRID

	//	�`�揈��
	m_pScene->Draw(*m_pBackGround);

	//	��ʂ̍X�V
	ScreenFlip();
}

//-----------------------------------------------------------------------------
//	@brief	�p�b�h�̓��͂����
//-----------------------------------------------------------------------------
void SceneManager::_PadInput()
{
	//	�p�b�h�̓��͂����
	m_pPad1->InputPadNum(PadInfo::PAD_KIND::PAD_1);
	m_pPad2->InputPadNum(PadInfo::PAD_KIND::PAD_2);
	m_pPad3->InputPadNum(PadInfo::PAD_KIND::PAD_3);
	m_pPad4->InputPadNum(PadInfo::PAD_KIND::PAD_4);
}

//-----------------------------------------------------------------------------
//	@brief	�p�b�h���������
//-----------------------------------------------------------------------------
void SceneManager::_PadRelease()
{
	//	�p�b�h�P�̉��
	CommonSafe::Delete(m_pPad1);

	//	�p�b�h�Q�̉��
	CommonSafe::Delete(m_pPad2);

	//	�p�b�h�R�̉��
	CommonSafe::Delete(m_pPad3);

	//	�p�b�h�S�̉��
	CommonSafe::Delete(m_pPad4);
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void SceneManager::_FinalRelease()
{
	//	�p�b�h�̉��
	_PadRelease();

	//	�J�����̉��
	CommonSafe::Delete(m_pCamera);

	//	�w�i�̉��
	CommonSafe::Release(m_pBackGround);

	//	SE�̉��
	CommonSafe::Release(m_pSoundEffect);

	//	�V�[���̉��
    CommonSafe::Release(m_pScene);
}
