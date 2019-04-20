
//=============================================================================
//	@file	SceneBase.h
//	@brief	�V�[���x�[�X
//	@autor	���m ���
//	@date	2018/9/28
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
class SceneManager;
class Pad;
class BackGround;
class Camera;
class Sound;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�V�[�����N���X
//-----------------------------------------------------------------------------
class SceneBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	SceneBase() {};
	virtual ~SceneBase() {};

	//	�쐬����
	virtual void Create() = 0;

	//	�������
	virtual void Release()	= 0;

	//	��������
	virtual void Initialize(Pad& _pad, Camera& _camera) = 0;

	//	�X�V����
	virtual void Update(Pad& _pad, Camera& _camera, BackGround& _backGround, SoundEffect& _soundEffect, SceneManager* _sceneManager) = 0;

	//	�`�揈��
	virtual void Draw(BackGround& _backGround) = 0;

protected:

//================== ���������֐� ==================//

	//	�V�[���؂�ւ�
	virtual void _ChangeScene(Pad& _pad, SoundEffect& _soundEffect, SceneManager* _sceneManager) {};

	//	�ŏI�I�ȉ��
	virtual void _FinalRelease() = 0;

//=================== �����o�ϐ� ===================//

	Sound*				m_pBackgroundMusic;		    //	BGM
	float				m_changeSceneWaitTime;	    //	�V�[���؂�ւ��̒x��

};