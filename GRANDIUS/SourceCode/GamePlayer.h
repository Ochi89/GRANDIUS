
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
#include "PlayerBase.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class Pad;
class ShotManager;
class StayShotManager;
class UIGauge;
class SoundEffect;
class EnemyManager;

//-----------------------------------------------------------------------------
//	@brief	�v���C���[�N���X
//-----------------------------------------------------------------------------
class GamePlayer : public PlayerBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
    GamePlayer(const int _modelHandle);
	~GamePlayer();

	//	�쐬����
    virtual void Create() override;

	//	�������
    virtual void Release() override;

	//	��������
    virtual void Initialize() override;

	//	�X�V����
    virtual void Update(Pad& _pad, ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gaugeUI) override;

protected:

//================== ���������֐� ==================//

	//	�e�̏���
	void _Shot(Pad& _pad, ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect);

	//	�K�E�Z��
	void _SpecialAttack(Pad& _pad, UIGauge& _gaugeUI);

	//	���[�U�[
	void _Laser();

	//	�͈͊O����
	void _OutOfRange();

	//	�J�n���̈ړ�
	void _EmergeMove();

	//	�����蔻��p�̓_�̍X�V
	void _UpdateHitPoint();

	//	���[�U�[�G�t�F�N�g
	void _LaseEffect(SoundEffect& _soundEffect);

	//	�q�b�g�G�t�F�N�g
	void _OnHitEffect(SoundEffect& _soundEffect);

	//	�����G�t�F�N�g
	void _OnEffectExplosion(SoundEffect& _soundEffect);

	//	���x�A�b�v�G�t�F�N�g
	void _OnEffectSpeedUp(SoundEffect& _soundEffect);

	//	�A�C�e���擾���̃G�t�F�N�g
	void _OnEffectGetItem();

	//	���G���Ԃ̌v��
	void _MeasuringInvincibleTime();

	//	�ŏI�I�ȉ������
    virtual void _FinalRelease() override;
};