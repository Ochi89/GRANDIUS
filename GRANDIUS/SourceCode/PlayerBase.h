
//=============================================================================
//	@file	PlayerBase.h
//	@brief	�v���C���[�x�[�X
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
#include "CharacterBase.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
struct Circle;
struct Rect;
class Pad;
class ShotManager;
class StayShotManager;
class UIGauge;
class EffekseerEmitter;
class SoundEffect;
class EnemyManager;

//-----------------------------------------------------------------------------
//	@brief	�v���C���[���N���X
//-----------------------------------------------------------------------------
class PlayerBase : public CharacterBase
{
public:
	
	//	�R���X�g���N�^ / �f�X�g���N�^
	PlayerBase(const int _modelHandle);
	virtual ~PlayerBase();

	//	�쐬����
	virtual void Create() override = 0;

	//	�������
	virtual void Release() override = 0;

	//	��������
	virtual void Initialize() override = 0;

	//	�X�V����
    virtual void Update() {};
    virtual void Update(Pad& _pad, ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gaugeUI) {};
    virtual void Update(ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gaugeUI, EnemyManager& _enemyManager) {};

	//	�`�揈��
	virtual void Draw() override final;

	//	�_���[�W����
	void OnHitDamage() { m_life--; }

//==================== getter =====================//

	//	�c�胉�C�t�� getter
	const int& GetLife() const { return m_life; }

	//	�o���t���O�� getter
	const bool& GetIsEmerge() const { return m_isEmerge; }

	//	�_���[�W�t���O�� getter
	const bool& GetIsDamage() const { return m_isDamage; }

	//	���G�t���O�� getter
	const bool& GetIsInvincible() const { return m_isInvincible; }

	//	���[�U�[�g�p��̖��G�t���O�� getter
	const bool& GetIsInvincibleAfterLaser() const { return m_isInvincibleAfterLaser; }

	//	�c�@�����邩�� getter
	const bool GetIsAlive() const { return (m_life > 0); }

	//	���[�U�[�̃|�W�V������ getter
	const Rect& GetLaserHitRect() const { return m_laserHitRect; }

	//	�؍ݒe�̒x�����Ԃ� getter
	const float& GetStayShotWaitTime() const { return m_stayShotWaitTime; }

	//	�����ʒu�� getter
	const VECTOR GetStartPos() const;

	//	�؍݃V���b�g�̎g�p�󋵂� getter
	const bool& GetIsUseStayShot() const { return m_isUseStayShot; }

	//	�A�C�e���p�̓����蔻��� getter
	const Rect& GetItemHitRect() const { return m_itemHitRect; }

	//	�A�C�e���擾���̃G�t�F�N�g�̊J�n�t���O�� getter
	const bool& GetIsStartEffectGetItem() const { return m_isStartEffectGetItem; }

//==================== setter =====================//
		
	//	�o���t���O�� setter
	void SetIsEmerge(const bool _set) { m_isEmerge = _set; }

	//	�_���[�W�t���O�� setter
	void SetIsDamage(const bool _set) { m_isDamage = _set; }

	//	���G�t���O�� setter
	void SetIsInvincible(const bool _set) { m_isInvincible = _set; }

	//	���[�U�[�g�p��̖��G�t���O�� setter
	void SetIsInvincibleAfterLaser(const bool _set) { m_isInvincibleAfterLaser = _set; }

	//	�ړ���~�t���O�� setter
	void SetIsStopMove(const bool _set) { m_isStopMove = _set; }

	//	�V�[�����o�t���O�� setter
	void SetIsSceneProduction(const bool _set) { m_isSceneProduction = _set; }

	//	�N���A���o�t���O�� setter
	void SetIsClearProduction(const bool _set) { m_isClearProduction = _set; }

	//	�A�C�e���擾���̃G�t�F�N�g�̊J�n�t���O�� setter
	void SetIsStartEffectGetItem(const bool _set) { m_isStartEffectGetItem = _set; }

protected:

//================== ���������֐� ==================//

    //  sin�J�[�u�ɂ����������߂�
    void _AskSinCurveDirection();

	//	�ŏI�I�ȉ������
	virtual void _FinalRelease() = 0;

//=================== �����o�ϐ� ===================//

	float	m_emergeMoveTaim;				//	�o�����̈ړ�����
	bool	m_isEmerge;						//	�o���t���O
	float	m_speed;						//	���x
	int		m_life;							//	�c�@
	bool	m_isDamage;						//	�_���[�W�t���O
	bool	m_offDraw;						//	�`�悵�Ȃ��t���O
	float	m_invincibleTime;				//	�����蔻��̖�������
	bool	m_isInvincible;					//	���G�t���O
	bool	m_isInvincibleAfterLaser;		//	���[�U�[�g�p��̖��G�t���O
	bool	m_isMove;						//	�ړ������̃t���O
	bool	m_isStopMove;					//	�ړ���~�t���O
	bool	m_isSceneProduction;			//	�V�[�����o�t���O
	bool	m_isClearProduction;			//	�N���A���o�t���O
	Rect	m_laserHitRect;					//	���[�U�[�̓����蔻��
	float	m_laserTime;					//	���[�U�[�̏o������
	bool	m_isStartLaser;					//	���[�U�[�J�n�t���O
	float	m_stayShotWaitTime;				//	�؍ݒe�̒x������
	float	m_radian;						//	���W�A��
	bool	m_isUseStayShot;				//	�؍݃V���b�g�̎g�p��
	Rect	m_itemHitRect;					//	�A�C�e���p�̓����蔻��
	bool	m_isStartEffectGetItem;			//	�A�C�e���擾���̃G�t�F�N�g�̊J�n�t���O

	//	�f���p
	float	m_demoDirChangeTime;			//	�f���p�̌����؂�ւ��x������
	VECTOR	m_demoTargetPos;				//	�f���p�̖ړI�̈ʒu

	//	�G�t�F�N�g�֌W
	EffekseerEmitter*	m_effectLaser;		//	���[�U�[�G�t�F�N�g
	EffekseerEmitter*	m_effectHit;		//	�q�b�g�G�t�F�N�g
	EffekseerEmitter*	m_effectExplosion;	//	�����G�t�F�N�g
	EffekseerEmitter*	m_effectSpeedUp;	//	���x�A�b�v�G�t�F�N�g
	EffekseerEmitter*	m_effectGetItem;	//	�A�C�e���擾�G�t�F�N�g

//===================== �ÓI�萔 ===================//
	
	static const VECTOR		TITLE_POS;							//	�^�C�g�����̍��W
	static const VECTOR		RESULT_POS;							//	���U���g���̍��W
	static const VECTOR		EMERGE_POS;							//	�o�����̍��W
	static const VECTOR		START_POS;							//	�J�n���̍��W
	static const VECTOR		RECT_CORRECTION;					//	���W�̕␳
	static const VECTOR		ITEM_RECT_CORRECTION;				//	�A�C�e�����W�̕␳
	static const float		EMERGE_MOVE_SPEED;					//	�o�����̈ړ����x
	static const float		SHOT_SPEED;							//	�V���b�g���x
	static const float		MAX_SHOT_WAIT_TIME;					//	�V���b�g�̒x������
	static const float		MAX_STAY_SHOT_WAIT_TIME;			//	�؍݃V���b�g�̒x������
	static const float		CENTER_CORRECTION;					//	���S���W�̕␳
	static const float		HIT_RADIUS;							//	�����蔻��p�̔��a
	static const float		MAX_INVINCIBLE_TIME_1;				//	�����蔻��̖������Ԃ̍ő�
	static const float		MAX_INVINCIBLE_TIME_2;				//	�����蔻��̖������Ԃ̍ő�
	static const float		MOVE_SPEED;							//	�ړ����x
	static const float		MIN_POS_X;							//	�����W�̍ŏ�
	static const float		MAX_POS_X;							//	�����W�̍ő�
	static const float		MIN_POS_Y;							//	�����W�̍ŏ�
	static const float		MAX_POS_Y;							//	�����W�̍ő�
	static const float		LASER_SIZE;							//	���[�U�[�T�C�Y
	static const float		LASER_SIZE_DEPTH;					//	���[�U�[�T�C�Y�̉��s��
	static const float		LASER_SPEED;						//	���[�U�[���x
	static const float		ADD_RADIAN_SPEED;					//	���W�A���p�̉��Z���x
	static const float		MAX_DEMO_SHOT_FIRING_TIME;			//	�V���b�g�̒x������
	static const float		MAX_DEMO_STAY_SHOT_FIRING_TIME;		//	�؍݃V���b�g�̔��ˎ���
	static const float		MAX_DEMO_CHANGE_DIR_WAIT_TIME;		//	�f���p�̌����؂�ւ��x������
	static const float		MAX_DEMO_DISTANCE_TO_ENEMY;			//	�f���p�̓G�Ƃ̋����̊Ԋu
	static const int		START_LIFE;							//	�J�n���̎c�@
	static const int		ZERO_LIFE;							//	�c�@�Ȃ�

private:

//=================== �����o�ϐ� ===================//

	float m_flashingTime;	//	�_�Ŏ���

};