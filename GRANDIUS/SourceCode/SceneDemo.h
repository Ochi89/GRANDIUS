
//=============================================================================
//	@file	SceneDemo.h
//	@brief	�f���V�[��
//	@autor	���m ���
//	@date	2018/1/13
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
class EnemyManager;
class BossManager;
class ShotManager;
class StayShotManager;
class ItemManager;
class Camera;
class UILife;
class UIGauge;
class UIStayShot;
class UIDemoPlay;
class UIBackPixel;
class BackGround;
class EffekseerManager;
class Warning;

//-----------------------------------------------------------------------------
//	@brief	�^�C�g���V�[���h���N���X
//-----------------------------------------------------------------------------
class SceneDemo : public SceneBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^/ /�f�X�g���N�^
	SceneDemo();
	~SceneDemo();

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

	//	�q�b�g�`�F�b�N
	void _AllHitChecker(SoundEffect& _soundEffect);

	//	�V�[���؂�ւ�
	void _ChangeScene(Pad& _pad, SoundEffect& _soundEffect, SceneManager* _sceneManager) override;

	//	�ŏI�I�ȉ��
	void _FinalRelease() override;

//=================== �����o�ϐ� ===================//

    PlayerManager*		m_pPlayerManager;	    //	�v���C���[
	EnemyManager*		m_pEnemyManager;		//	�G�l�~�[
	BossManager*		m_pBossManager;			//	�{�X
	ShotManager*		m_pShotManager;			//	�V���b�g
	StayShotManager*	m_pStayShotManager;		//	�؍݃V���b�g
	ItemManager*		m_pItemManager;			//	�A�C�e��
	UILife*				m_pUILife;				//	���C�tUI
	UIGauge*			m_pUIGauge;				//	�Q�[�WUI
	UIStayShot*			m_pUIStayShot;			//	�X�e�C�V���b�gUI
	UIDemoPlay*			m_pUIDemoPlay;			//	�f���v���CUI
	UIBackPixel*		m_pUIBackPixel;			//	�w�i�s�N�Z��UI
	EffekseerManager*	m_pEffekseerManager;	//	�G�t�F�N�g
	Warning*			m_pWarning;				//	�x��
	float				m_demoTime;				//	�f���̎���

//===================== �ÓI�萔 ===================//

	static const float END_DEMO_TIME;						//	�f���̏I��
	static const float MAX_CHANGE_LOSE_SCENE_WAIT_TIME;		//	�V�[���؂�ւ��̒x���̍ő�
};
