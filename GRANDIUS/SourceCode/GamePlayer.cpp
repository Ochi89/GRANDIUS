
//=============================================================================
//	@file	Player.cpp
//	@brief	�v���C���[
//	@autor	���m ���
//	@date	2018/11/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GamePlayer.h"
#include "Common.h"
#include "Pad.h"
#include "MoveHelper.h"
#include "AngleHelper.h"
#include "ShotManager.h"
#include "StayShotManager.h"
#include "EffekseerEmitter.h"
#include "UIGauge.h"
#include "SoundEffect.h"
#include "EnemyManager.h"
#include "EnemyBase.h"

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
GamePlayer::GamePlayer(const int _modelHandle)
	: PlayerBase(_modelHandle)
{
	//	�e�ϐ���������
	m_pos = CommonConstant::ORIGIN;
	m_dir = CommonConstant::ORIGIN;
	m_angle = CommonConstant::ORIGIN;
	m_size = CommonConstant::ORIGIN;
	m_life = START_LIFE;
	m_speed = 0.0f;
	m_emergeMoveTaim = 0.0f;
	m_invincibleTime = 0.0f;
	m_isInvincible = false;
	m_hitCircle.m_radius = HIT_RADIUS;
	m_hitCircle.m_centerPoint = CommonConstant::ORIGIN;

	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
	m_effectLaser = NULL;
	m_effectHit = NULL;
	m_effectExplosion = NULL;
	m_effectSpeedUp = NULL;
	m_effectGetItem = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
GamePlayer::~GamePlayer()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void GamePlayer::Create()
{
	//	�G�t�F�N�g�̓ǂݍ���
	m_effectLaser = new EffekseerEmitter("Data/Effect/Player/Laser/Laser.efk");
	m_effectHit = new EffekseerEmitter("Data/Effect/Hit/Hit.efk");
	m_effectExplosion = new EffekseerEmitter("Data/Effect/Explosion/Explosion.efk");
	m_effectSpeedUp = new EffekseerEmitter("Data/Effect/Player/SpeedUp/SpeedUp.efk");
	m_effectGetItem = new EffekseerEmitter("Data/Effect/Player/GetItem/GetItem.efk");
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void GamePlayer::Release()
{
	//	�G�t�F�N�g�̍폜
	CommonSafe::Delete(m_effectLaser);
	CommonSafe::Delete(m_effectHit);
	CommonSafe::Delete(m_effectExplosion);
	CommonSafe::Delete(m_effectSpeedUp);
	CommonSafe::Delete(m_effectGetItem);
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void GamePlayer::Initialize()
{
	//	�e�ϐ���������Ԃɐݒ�
	m_pos = EMERGE_POS;
	m_dir = CommonConstant::ORIGIN;
	m_angle = VGet(0.0f, 1.4f, 0.0f);
	m_size = VGet(0.4f, 0.4f, 0.4f);
	m_life = START_LIFE;
	m_speed = MOVE_SPEED;
	m_emergeMoveTaim = 0.0f;
	m_isEmerge = true;
	m_invincibleTime = 0.0f;
	m_isInvincible = false;
	m_isInvincibleAfterLaser = false;
	m_isMove = false;
	m_shotWaitTime = 0.0f;
	m_isStopMove = false;
	m_isSceneProduction = false;
	m_isClearProduction = false;
	m_laserTime = 0.0f;
	m_isStartLaser = false;
	m_stayShotWaitTime = 0.0f;
	m_radian = 0.0f;
	m_isUseStayShot = true;
	m_laserHitRect.m_vertexTop = CommonConstant::ORIGIN;
	m_laserHitRect.m_vertexUnder = CommonConstant::ORIGIN;
	m_itemHitRect.m_vertexTop = CommonConstant::ORIGIN;
	m_itemHitRect.m_vertexUnder = CommonConstant::ORIGIN;
	m_offDraw = false;
	m_isStartEffectGetItem = false;

	//	�f���p
	m_demoDirChangeTime = 0.0f;
	m_demoTargetPos = CommonConstant::ORIGIN;

	//	�����蔻��p�̉~�`�\���̂̏�����
	m_hitCircle.m_radius = HIT_RADIUS;
	m_hitCircle.m_centerPoint = CommonConstant::ORIGIN;

	//	�����蔻��p�̒����`�\���̂̏�����
	m_hitRect.m_vertexTop = CommonConstant::ORIGIN;
	m_hitRect.m_vertexUnder = CommonConstant::ORIGIN;

	//	�p�x�ƃT�C�Y�����蓖�Ă�
	MV1SetRotationXYZ(m_modelHandle, m_angle);
	MV1SetScale(m_modelHandle, m_size);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void GamePlayer::Update(Pad& _pad, ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gaugeUI)
{
	//	�c�@������A�ړ��\�̂Ƃ��̂ݍX�V����
	const int notLife = 0;
	const bool isAlive = m_life > notLife;
	const bool isActive = !m_isStopMove && isAlive && !m_isDamage;
	if (isActive)
	{
		//	�J�n���̈ړ�
		_EmergeMove();

		//	���G���Ԃ̌v��
		_MeasuringInvincibleTime();

		//	�o�����I����Ă�����A
		//	������悤�ɂ���
		if (!m_isEmerge)
		{
			//	�ړ�����
			//	moving �̃m������0�ȊO�̂Ƃ��́A�ړ���
			VECTOR moving = MoveHelper::AskMoveAmount(m_dir, _pad, m_speed, true, true);
			m_isMove = VSize(moving) != 0;

			//	�|�W�V�����̍X�V
			m_pos = VAdd(m_pos, moving);

			//	�͈͊O�w��
			_OutOfRange();

			//	�ˌ�����
			_Shot(_pad, _shot, _stayShot, _soundEffect);

			//	�K�E�Z����
			_SpecialAttack(_pad, _gaugeUI);

			//	�p�x����
			AngleHelper::AskAngle(m_angle, _pad);
		}
	}

	//	�V�[�����o�̊J�n
	if (m_isSceneProduction)
	{
		VECTOR tmpDir = VGet(1.0f, 0.0f, 0.0f);
		const float tmpSpeed = 5.0f;
		VECTOR moving = MoveHelper::AskMoveAmount(tmpDir, tmpSpeed);

		//	�|�W�V�����̍X�V
		m_pos = VAdd(m_pos, moving);
	}

	//	�N���A���o�̊J�n
	if (m_isClearProduction)
	{
		VECTOR tmpDir = VGet(1.0f, 0.0f, 0.0f);
		const float tmpSpeed = 10.0f;
		VECTOR moving = MoveHelper::AskMoveAmount(tmpDir, tmpSpeed);

		//	�|�W�V�����̍X�V
		m_pos = VAdd(m_pos, moving);
	}

	//	���[�U�[����
	_Laser();

	//	���[�U�[�G�t�F�N�g
	_LaseEffect(_soundEffect);

	//	�q�b�g�G�t�F�N�g
	_OnHitEffect(_soundEffect);

	//	�����G�t�F�N�g
	_OnEffectExplosion(_soundEffect);

	//	���x�A�b�v
	_OnEffectSpeedUp(_soundEffect);

	//	�A�C�e���擾�G�t�F�N�g
	_OnEffectGetItem();

	//	���f���Ƀ|�W�V���������蓖�Ă�
	MV1SetPosition(m_modelHandle, m_pos);

	//	���f���Ɋp�x�����蓖�Ă�
	MV1SetRotationXYZ(m_modelHandle, m_angle);

	//	�����蔻�肪�����̂ŁA
	//	���f���Ƀ|�W�V���������蓖�Ă���ɁA
	//	�����蔻��p�̍��W�̍X�V����
	_UpdateHitPoint();

	//	�c�@�����U���g�ֈ����n��
	HAND_OVER_RESULT->SetLife(m_life);
}

//-----------------------------------------------------------------------------
//	@brief	�e�̏���
//-----------------------------------------------------------------------------
void GamePlayer::_Shot(Pad& _pad, ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect)
{
	//	�L�[��������Ă���Ƃ��A�e�𐶐�����
	const bool isInputActiveShot = KEY->Press(KEY_INPUT_K) || KEY->Press(KEY_INPUT_X) || _pad.GetXInputButton(PadInfo::PAD_BUTTON_KIND::BUTTON_A);
	const bool isActiveShot = isInputActiveShot && m_shotWaitTime-- <= 0.0f;
	if (isActiveShot)
	{
		//	�e���X�g�ɒǉ�����
		_shot.RegisterOnList(ShotManager::SHOT_KIND::PLAYER_SHOT, m_pos, VGet(1.0f, 0.0f, 0.0f), SHOT_SPEED, _soundEffect);
		m_shotWaitTime = MAX_SHOT_WAIT_TIME;
	}

	//	���͂��Ȃ����́A�x��������
	if (!isInputActiveShot) { m_shotWaitTime = 0.0f; }

	//	�؍݃V���b�g�̎g�p��
	m_stayShotWaitTime--;
	m_isUseStayShot = (m_stayShotWaitTime <= 0.0f);

	//	�L�[��������Ă��āA�x�����Ȃ�����
	//	�؍ݒe�𐶐�����
	const bool isInputActiveStayShot = KEY->Press(KEY_INPUT_L) || KEY->Press(KEY_INPUT_C) || _pad.GetXInputButton(PadInfo::PAD_BUTTON_KIND::BUTTON_B);
	const bool isActiveStayShot = isInputActiveStayShot && m_stayShotWaitTime <= 0.0f;
	if (isActiveStayShot)
	{
		_stayShot.RegisterOnList(m_pos);
		m_stayShotWaitTime = MAX_STAY_SHOT_WAIT_TIME;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�K�E�Z����
//-----------------------------------------------------------------------------
void GamePlayer::_SpecialAttack(Pad& _pad, UIGauge& _gaugeUI)
{
	//	�L�[��������Ă��āA�Q�[�W���ő�̂Ƃ��́A�K�E����
	const bool isInputActive = KEY->Press(KEY_INPUT_J) || KEY->Press(KEY_INPUT_Z) || _pad.GetXInputButton(PadInfo::PAD_BUTTON_KIND::BUTTON_X);
	const bool isActive = isInputActive && _gaugeUI.GetIsGaugeMax() && !PRODUCTION->GetIsSceneProduction();
	if (isActive)
	{
		//	�K�E�Z�𔭓����A
		//	�Q�[�W�̏�����
		PRODUCTION->SetIsSpecialProduction(true);
		_gaugeUI.ResetGauge();
		m_isStartLaser = true;
	}

}

//-----------------------------------------------------------------------------
//	@brief	���[�U�[
//-----------------------------------------------------------------------------
void GamePlayer::_Laser()
{
	//	���[�U�[�J�n
	if (m_isStartLaser)
	{
		m_laserTime++;

		const bool isStart = m_laserTime <= 100.0f;
		const bool isLaser1 = m_laserTime >= 100.0f && m_laserTime <= 300.0f;
		const bool isReset = m_laserTime >= 300.0f;
		const bool isEnd = m_laserTime >= 360.0f;
		if(isStart) 
		{
			m_laserHitRect.m_vertexTop = VGet(m_pos.x, m_pos.y - LASER_SIZE, m_pos.z - LASER_SIZE_DEPTH);
			m_laserHitRect.m_vertexUnder = VGet(m_pos.x, m_pos.y + LASER_SIZE, m_pos.z + LASER_SIZE_DEPTH);

			//	�p�b�h�̐U���@�\
			const int vibrationPower = 500;
			PadInfo::Function::VibrationFunction(PadInfo::PAD_KIND::PAD_1, vibrationPower);
		}
		if (isLaser1)
		{
			//	�p�b�h�̐U���@�\�̏I��
			PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);

			m_laserHitRect.m_vertexUnder.x += LASER_SPEED;
			
			//	�p�b�h�̐U���@�\
			PadInfo::Function::VibrationFunction(PadInfo::PAD_KIND::PAD_1);
		}
		if (isReset)
		{
			m_laserHitRect.m_vertexTop = CommonConstant::ORIGIN;
			m_laserHitRect.m_vertexUnder = CommonConstant::ORIGIN;

			//	�p�b�h�̐U���@�\�̏I��
			PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);
		}
		if (isEnd)
		{
			m_laserTime = 0.0f;
			m_isStartLaser = false;

			//	�p�b�h�̐U���@�\�̏I��
			PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�͈͊O����
//-----------------------------------------------------------------------------
void GamePlayer::_OutOfRange()
{
	//	��ʊO�ɍs���Ȃ��悤�ɂ���
	const bool isOverX1 = m_pos.x <= MIN_POS_X;
	if (isOverX1) { m_pos.x = MIN_POS_X; }

	const bool isOverX2 = m_pos.x >= MAX_POS_X;
	if (isOverX2) { m_pos.x = MAX_POS_X; }

	const bool isOverY1 = m_pos.y <= MIN_POS_Y;
	if (isOverY1) { m_pos.y = MIN_POS_Y; }

	const bool isOverY2 = m_pos.y >= MAX_POS_Y;
	if (isOverY2) { m_pos.y = MAX_POS_Y; }
}

//-----------------------------------------------------------------------------
//	@brief	�J�n���̈ړ�
//-----------------------------------------------------------------------------
void GamePlayer::_EmergeMove()
{
	//	�o�����̉��o
	if (m_isEmerge)
	{
		//	���Ԃɂ�鉉�o�̐؂�ւ�
		m_emergeMoveTaim++;
		const bool isEmergeMoveStart = m_emergeMoveTaim <= 30.0f;
		const bool isEmergeMove1 = m_emergeMoveTaim >= 30.0f && m_emergeMoveTaim <= 45.0f;
		const bool isEmergeMove2 = m_emergeMoveTaim >= 45.0f && m_emergeMoveTaim <= 70.0f;
		const bool isEmergeMoveEnd = m_emergeMoveTaim >= 70.0f;
		
		//	�J�n�J�n
		if (isEmergeMoveStart)
		{
			m_angle = VGet(0.0f, 1.4f, 0.0f);
			m_pos = EMERGE_POS;
			m_offDraw = false;
		}

		//	�J�n�ړ��P
		if (isEmergeMove1)
		{
			//	��i
			m_dir = VGet(1.0f, 0.0f, 0.0f);
			VECTOR moving = MoveHelper::AskMoveAmount(m_dir, EMERGE_MOVE_SPEED);
			m_pos = VAdd(m_pos, moving);

			//	��]����
			m_angle.x++;
			m_angle.z++;
		}

		//	�J�n�ړ��Q
		if (isEmergeMove2)
		{
			//	�J�n�ʒu�܂Ő��`�ۊǂňړ�
			float lerpSpeed = 0.1f;
			m_pos = CommonFunction::Lerp(m_pos, START_POS, lerpSpeed);

			//	��]����
			m_angle.x++;
			m_angle.z++;
		}

		//	�J�n���̏�����
		if(isEmergeMoveEnd)
		{
			m_dir = CommonConstant::ORIGIN;
			m_angle = VGet(0.0f, 1.4f, 0.0f);
			m_pos = START_POS;
			m_emergeMoveTaim = 0.0f;
			m_isEmerge = false;
		}
	}

}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̓_�̍X�V
//-----------------------------------------------------------------------------
void GamePlayer::_UpdateHitPoint()
{
	//	�����蔻��p�̒��S���W�̍X�V
	m_hitCircle.m_centerPoint = VGet(m_pos.x - CENTER_CORRECTION, m_pos.y, m_pos.z);

	//	�����蔻��p�̍��W�̍X�V
	m_hitRect.m_vertexTop = VGet(m_pos.x + RECT_CORRECTION.x - CENTER_CORRECTION, m_pos.y + RECT_CORRECTION.y, m_pos.z + RECT_CORRECTION.z);
	m_hitRect.m_vertexUnder = VGet(m_pos.x - RECT_CORRECTION.x - CENTER_CORRECTION, m_pos.y - RECT_CORRECTION.y, m_pos.z - RECT_CORRECTION.z);

	//	�A�C�e���p�̓����蔻����W�̍X�V
	//	�����蔻��p�̍��W�̍X�V
	m_itemHitRect.m_vertexTop = VSub(m_pos, ITEM_RECT_CORRECTION);
	m_itemHitRect.m_vertexUnder = VAdd(m_pos, ITEM_RECT_CORRECTION);
	m_itemHitRect.m_vertexTop.x -= CENTER_CORRECTION;
	m_itemHitRect.m_vertexUnder.x -= CENTER_CORRECTION;
}

//-----------------------------------------------------------------------------
//	@brief	���[�U�[�G�t�F�N�g
//-----------------------------------------------------------------------------
void GamePlayer::_LaseEffect(SoundEffect& _soundEffect)
{
	//	���[�U�[�J�n
	if (m_isStartLaser)
	{
		const bool isLaseStart = m_effectLaser->GetPlayTime() == 0.0f;
		const bool isLaseStop = m_effectLaser->GetPlayTime() == 360.0f;

		//	���[�U�[�G�t�F�N�g�̊J�n
		if (isLaseStart)
		{
			m_effectLaser->SetPos(VGet(m_pos.x + CENTER_CORRECTION, m_pos.y, m_pos.z));
			m_effectLaser->SetPlaySpeed(1.5f);
			m_effectLaser->SetScale(VGet(25.0f, 25.0f, 25.0f));
			m_effectLaser->SetAngle(VGet(0.0f, -90.0f, 0.0f));
			m_effectLaser->OnPlayEffect();
			_soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_PLAYER_LASER);
		}

		//	���[�U�[�G�t�F�N�g�̏I��
		if (isLaseStop)
		{
			m_effectLaser->OnEndEffect();
			return;
		}

		m_effectLaser->AddPlayTime();
		m_effectLaser->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�q�b�g�G�t�F�N�g
//-----------------------------------------------------------------------------
void GamePlayer::_OnHitEffect(SoundEffect& _soundEffect)
{
	//	�_���[�W���������Ƃ�
	if (m_isDamage)
	{
		const bool isHitStart = m_effectHit->GetPlayTime() == 0.0f;
		const bool isHitEnd = m_effectHit->GetPlayTime() == 100.0f;

		//	�G�t�F�N�g�̊J�n����
		if(isHitStart) 
		{
			m_effectHit->SetPos(VGet(m_pos.x - CENTER_CORRECTION, m_pos.y, m_pos.z));
			m_effectHit->SetScale(VGet(3.0f, 3.0f, 3.0f));
			m_effectHit->OnPlayEffect();
			_soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_HIT);
		}

		//	�G�t�F�N�g�̏I������
		if (isHitEnd)
		{
			m_effectHit->OnEndEffect();
			return;
		}

		//	�G�t�F�N�g�̍X�V
		m_effectHit->AddPlayTime();
		m_effectHit->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����G�t�F�N�g
//-----------------------------------------------------------------------------
void GamePlayer::_OnEffectExplosion(SoundEffect& _soundEffect)
{
	//	�_���[�W���������Ƃ�
	if (m_isDamage)
	{
		const bool isExplosionStart = m_effectExplosion->GetPlayTime() == 0.0f;
		const bool isExplosion1 = m_effectExplosion->GetPlayTime() == 50.0f;
		const bool isExplosionEnd = m_effectExplosion->GetPlayTime() == 100.0f;

		//	�����G�t�F�N�g�̊J�n
		if (isExplosionStart)
		{
			m_effectExplosion->SetPos(m_pos);
			m_effectExplosion->SetPlaySpeed(3.0f);
			m_effectExplosion->SetScale(VGet(2.0f, 2.0f, 2.0f));
			m_effectExplosion->OnPlayEffect();

			//	�p�b�h�̐U���@�\
			PadInfo::Function::VibrationFunction(PadInfo::PAD_KIND::PAD_1);
		}

		//	�v���C���[���f���̔�\����
		//	SE�̍Đ�
		if (isExplosion1) 
		{
			m_offDraw = true;
			_soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_EXPLOSION);

			//	�p�b�h�̐U���@�\�̏I��
			PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);
		}

		//	�����G�t�F�N�g�̏I��
		if (isExplosionEnd)
		{
			m_effectExplosion->OnEndEffect();
			m_isInvincible = true;
			m_isEmerge = true;
			m_isDamage = false;

			return;
		}
		
		//	�G�t�F�N�g�̍X�V
		m_effectExplosion->AddPlayTime();
		m_effectExplosion->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	���x�A�b�v�G�t�F�N�g
//-----------------------------------------------------------------------------
void GamePlayer::_OnEffectSpeedUp(SoundEffect& _soundEffect)
{
	//	�V�[�����o��
	if (m_isSceneProduction)
	{
		const bool isSpeedUpStart = m_effectSpeedUp->GetPlayTime() == 0.0f;
		const bool isSpeedUpEnd = m_effectSpeedUp->GetPlayTime() == 120.0f;

		//	�G�t�F�N�g�̊J�n����
		if (isSpeedUpStart)
		{
			const float effectPosX = -50.0f;
			m_effectSpeedUp->SetPos(VGet(effectPosX, m_pos.y, m_pos.z));
			m_effectSpeedUp->SetScale(VGet(3.0f, 3.0f, 3.0f));
			m_effectSpeedUp->SetAngle(VGet(20.0f, 0.0f, 0.0f));
			m_effectSpeedUp->OnPlayEffect();
			_soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_WIND);
		}

		//	�G�t�F�N�g�̏I������
		if (isSpeedUpEnd)
		{
			m_effectSpeedUp->OnEndEffect();
			return;
		}

		//	�G�t�F�N�g�̍X�V
		m_effectSpeedUp->AddPlayTime();
		m_effectSpeedUp->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�A�C�e���擾���̃G�t�F�N�g
//-----------------------------------------------------------------------------
void GamePlayer::_OnEffectGetItem()
{
	//	�A�C�e���擾��
	if (m_isStartEffectGetItem)
	{
		const bool isGetItemStart = m_effectGetItem->GetPlayTime() == 0.0f;
		const bool isGetItemEnd = m_effectGetItem->GetPlayTime() == 110.0f;
		
		//	��Ƀv���C���[��ǂ�
		m_effectGetItem->SetPos(VGet(m_pos.x - CENTER_CORRECTION, m_pos.y, m_pos.z));
		
		//	�G�t�F�N�g�̊J�n����
		if (isGetItemStart)
		{
			m_effectGetItem->SetScale(VGet(7.0f, 5.0f, 7.0f));
			m_effectGetItem->SetPlaySpeed(2.0f);
			m_effectGetItem->OnPlayEffect();
		}

		//	�G�t�F�N�g�̏I������
		if (isGetItemEnd)
		{
			m_effectGetItem->OnEndEffect();
			m_isStartEffectGetItem = false;
			return;
		}

		//	�G�t�F�N�g�̍X�V
		m_effectGetItem->AddPlayTime();
		m_effectGetItem->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	���G���Ԃ̌v��
//-----------------------------------------------------------------------------
void GamePlayer::_MeasuringInvincibleTime()
{
	//	���G��Ԃ̂Ƃ�
	const bool isInvincible = m_isInvincible && !m_isEmerge;
	if (isInvincible)
	{
		//	���G���Ԃ̌v�����A
		//	�ő�ɂȂ�����A���G����������
		m_invincibleTime++;
		const bool isMaxInvincibleTime = m_invincibleTime >= MAX_INVINCIBLE_TIME_1;
		if (isMaxInvincibleTime)
		{
			//	���G��Ԃ���������
			m_invincibleTime = 0.0f;
			m_isInvincible = false;
		}
	}

	//	���[�U�[�g�p��̖��G����
	if (m_isInvincibleAfterLaser)
	{
		//	���G���Ԃ̌v�����A
		//	�ő�ɂȂ�����A���G����������
		m_invincibleTime++;
		const bool isMaxInvincibleTime = m_invincibleTime >= MAX_INVINCIBLE_TIME_2;
		if (isMaxInvincibleTime)
		{
			//	���G��Ԃ���������
			m_invincibleTime = 0.0f;
			m_isInvincibleAfterLaser = false;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void GamePlayer::_FinalRelease()
{
	//	�G�t�F�N�g�̍폜
	CommonSafe::Delete(m_effectLaser);
	CommonSafe::Delete(m_effectHit);
	CommonSafe::Delete(m_effectExplosion);
	CommonSafe::Delete(m_effectSpeedUp);
	CommonSafe::Delete(m_effectGetItem);
}
