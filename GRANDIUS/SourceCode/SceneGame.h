
//=============================================================================
//	@file	SceneGame.h
//	@brief	�Q�[���V�[��
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
class EnemyManager;
class BossManager;
class ShotManager;
class StayShotManager;
class ItemManager;
class Camera;
class UILife;
class UIGauge;
class UIStayShot;
class UIGameOver;
class UIBackPixel;
class UICongratulation;
class BackGround;
class EffekseerManager;
class Warning;
class PlayCounter;

//-----------------------------------------------------------------------------
//	@brief	�^�C�g���V�[���h���N���X
//-----------------------------------------------------------------------------
class SceneGame : public SceneBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^/ /�f�X�g���N�^
	SceneGame();
	~SceneGame();

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

	//	�q�b�g�`�F�b�N�̕`��
	void _AllHitCheckerOfDraw();

	//	�f�o�b�O
	void _Debug();

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
	UIGameOver*			m_pUIGameOver;			//	�Q�[���I�[�o�[UI
	UIBackPixel*		m_pUIBackPixel;			//	�w�i�s�N�Z��UI
	UICongratulation*	m_pUICongratulation;	//	�N���AUI
	EffekseerManager*	m_pEffekseerManager;	//	�G�t�F�N�g
	Warning*			m_pWarning;				//	�x��
	PlayCounter*		m_pPlayCounter;			//	�v���C��
	bool				m_isDebug;				//	�f�o�b�O
	bool				m_isDebugDraw;			//	�f�o�b�O�`��

//===================== �ÓI�萔 ===================//

	static const float MAX_CHANGE_LOSE_SCENE_WAIT_TIME;		//	�V�[���؂�ւ��̒x���̍ő�
	static const float MAX_CHANGE_WIN_SCENE_WAIT_TIME;		//	�V�[���؂�ւ��̒x���̍ő�
	static const float MAX_CHANGE_TITLE_SCENE_WAIT_TIME;	//	�V�[���؂�ւ��̒x���̍ő�
	static const float MAX_CHANGE_BGM_WAIT_TIME;			//	BGM�؂�ւ��̒x���̍ő�
};
