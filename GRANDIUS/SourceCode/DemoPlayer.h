
//=============================================================================
//	@file	Player.cpp
//	@brief	�v���C���[
//	@autor	���m ���
//	@date	2018/11/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "GamePlayer.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class ShotManager;
class StayShotManager;
class UIGauge;
class SoundEffect;
class EnemyManager;

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�N���X
//-----------------------------------------------------------------------------
class DemoPlayer : public GamePlayer
{
public:

    //===================== �֐� ======================//

    //	�R���X�g���N�^ / �f�X�g���N�^
    DemoPlayer(const int _modelHandle);
    ~DemoPlayer();

    //	�쐬����
    void Create() override final;

    //	�������
    void Release() override final;

    //	��������
    void Initialize() override final;

    //	�X�V����
    void Update(ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gaugeUI, EnemyManager& _enemyManager) override final;

private:

//================== ���������֐� ==================//

    //	�ړ������̐؂�ւ�
    void _ChangeDir(EnemyManager& _enemyManager);

    //	�e�̏���
    void _Shot(ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect);

    //	�ŏI�I�ȉ������
    void _FinalRelease() override final;
};