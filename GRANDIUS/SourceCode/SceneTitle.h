
//=============================================================================
//	@file	SceneTitle.h
//	@brief	�^�C�g���V�[��
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
#include "SceneBase.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class SceneManager;
class PlayerManager;
class UIBackPixel;
class Pad;
class Title;
class Opening;

//-----------------------------------------------------------------------------
//	@brief	�^�C�g���V�[���h���N���X
//-----------------------------------------------------------------------------
class SceneTitle : public SceneBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^/ /�f�X�g���N�^
	SceneTitle();
	~SceneTitle();

	//	�쐬����
	void Create() override;

	//	�������
	void Release() override;

	//	��������
	void Initialize(Pad& _pad, Camera& _camera) override;

	//	�X�V����
	void Update(Pad& _pad, Camera& _camera, BackGround& _backGround, SoundEffect& _soundEffect, SceneManager* _sceneManager) override;

	//	�`�揈��
	void Draw(BackGround& _backGround) override;

private:

//================== ���������֐� ==================//

	//	�V�[���؂�ւ�
	void _ChangeScene(Pad& _pad, SoundEffect& _soundEffect, SceneManager* _sceneManager) override;

	//	�ŏI�I�ȉ��
	void _FinalRelease() override;

//=================== �����o�ϐ� ===================//

    PlayerManager*		m_pPlayerManager;	    //	�v���C���[
	Title*				m_pTitle;				//	�^�C�g��
	UIBackPixel*		m_pUIBackPixel;			//	�w�i�s�N�Z��UI
	float				m_demoTime;				//	�f���̎���

//===================== �ÓI�萔 ===================//

	static const float MAX_CHANGE_SCENE_WAIT_TIME;		//	�V�[���؂�ւ��̒x���̍ő�
	static const float START_DEMO_TIME;					//	�f���J�n����

};
