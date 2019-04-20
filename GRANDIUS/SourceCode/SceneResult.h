
//=============================================================================
//	@file	SceneResult.h
//	@brief	���U���g�V�[��
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
class PlayerManager;
class SceneManager;
class UIBackPixel;
class Pad;
class Ranking;

//-----------------------------------------------------------------------------
//	@brief	���U���g�V�[���N���X
//-----------------------------------------------------------------------------
class SceneResult : public SceneBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^/ /�f�X�g���N�^
	SceneResult();
	~SceneResult();

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
	Ranking*			m_pRanking;				//	�����L���O
	UIBackPixel*		m_pUIBackPixel;			//	�w�i�s�N�Z��UI
	bool				m_isChangeScene;		//	�V�[���؂�ւ�

//===================== �ÓI�萔 ===================//

	static const float MAX_CHANGE_SCENE_WAIT_TIME;		//	�V�[���؂�ւ��̒x���̍ő�

};
