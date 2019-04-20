
//=============================================================================
//	@file	Main.h
//	@brief	���C��
//	@autor	���m ���
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Common.h"
#include "SceneManager.h"
#include "SceneBase.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
bool _isInitializeDxLib();              //  DxLib�̏���������
bool _isInitializeEffekseer();          //  Effekseer�̏���������

//-----------------------------------------------------------------------------
//	@brief	���C������
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//	DxLib�̏���������
	if (_isInitializeDxLib()) { DxLib_End(); return 0; }

	//	Effekseer�̏���������
	if (_isInitializeEffekseer()) { DxLib_End(); return 0; }

	//	�V�[���}�l�[�W���[�̍쐬
    SceneManager* pSceneManager = new SceneManager();
    if (CommonDebug::Assert((pSceneManager == NULL), " [ Main.cpp ] : error : create scene manager failed.")) { DxLib_End(); return 0; }

	//	�^�C�g���V�[���Ƃ��č쐬���A����������
    pSceneManager->Create();
    pSceneManager->ChangeScene(pSceneManager->SCENE_KIND::TITLE_SCENE);
    pSceneManager->Initialize();
	
	//	���C�����[�v
	pSceneManager->Ran();

	//	�V�[���Ǘ��N���X�̉��
    CommonSafe::Release(pSceneManager);

	//	�c�w���C�u�����̏I������
	DxLib_End();

	//	�\�t�g�̏I�� 
	return 0;
}

//-----------------------------------------------------------------------------
//	@brief	DxLib�̏���������
//-----------------------------------------------------------------------------
bool _isInitializeDxLib()
{
	//	�`���𗠉�ʂɕύX����B
	SetDrawScreen(DX_SCREEN_BACK);

	//	�c�w���C�u��������������
	//	�G���[���N�����璼���ɏI��
	if (DxLib_Init() == -1) { return true; }

	//	��ʃ��[�h�̃Z�b�g
	SetGraphMode(CommonConstant::WINDOW_WIDTH, CommonConstant::WINDOW_HEIGHT, CommonConstant::COLOR_BIT);
	ChangeWindowMode(FALSE);

	//	�}�E�X�̕\������
	SetMouseDispFlag(FALSE);

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	Effekseer�̏���������
//-----------------------------------------------------------------------------
bool _isInitializeEffekseer()
{
	//	�t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	//	DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N
	//	�E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	return false;
}
