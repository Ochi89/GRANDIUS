
//=============================================================================
//	@file	EnemyBase.cpp
//	@brief	�G�l�~�[�x�[�X
//	@autor	���m ���
//	@date	2018/11/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyBase.h"
#include "Common.h"
#include "PlayerManager.h"
#include "ShotManager.h"
#include "PlayerBase.h"
#include "EffekseerEmitter.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const VECTOR	EnemyBase::RECT_CORRECTION = VGet(6.0f, 6.0f, 6.0f);				//	���S���W�̕␳
const float		EnemyBase::SHOT_SPEED = 0.8f;										//	�V���b�g�̑��x
const float		EnemyBase::MAX_WAIT_TIME = 100.0f;									//	�V���b�g�̒x������
const float		EnemyBase::HIT_RADIUS = 6.0f;										//	�����蔻��p�̔��a
const float		EnemyBase::CENTER_CORRECTION = -1.0f;								//	���S���W�̕␳
const COLOR_F	EnemyBase::COLOR_NORMAL = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);		//	�f�t�H���g�F
const COLOR_F	EnemyBase::COLOR_DECAY_NORMAL = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);	//	�f�t�H���g�F�̌���
const COLOR_F	EnemyBase::COLOR_RED = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);			//	�ԐF
const COLOR_F	EnemyBase::COLOR_DECAY_RED = GetColorF(0.5f, 0.0f, 0.0f, 1.0f);		//	�ԐF�̌���

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
EnemyBase::EnemyBase(const int _modelHandle)
	: m_effectExplosion(NULL)
{
	//	���f���̕���
	m_modelHandle = MV1DuplicateModel(_modelHandle);
	CommonDebug::Assert((m_modelHandle <= -1), " [ EnemyBase.cpp ] : error : missing duplicat model.");

	m_aliveTime = 0.0f;
	m_isUseShot = false;
	m_isHavingItems = false;
 	m_shotWaitTime = 0.0f;
	m_formationID = 0;
	m_entryID = 0;
	m_entryKind = 0;
	m_isAttenuation = false;
	m_isHit = false;
	m_isOffDraw = false;
	m_isDeleate = false;

	//	�G�t�F�N�g�̓ǂݍ���
	m_effectExplosion = new EffekseerEmitter("Data/Effect/Explosion/Explosion3.efk");
	CommonDebug::Assert((m_effectExplosion == NULL), " [ EnemyBase.cpp ] : error : missing effect is null.");
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
EnemyBase::~EnemyBase()
{
	//	���f���̃A�����[�h
	MV1DeleteModel(m_modelHandle);

	//	�G�t�F�N�g�̉��
	CommonSafe::Delete(m_effectExplosion);
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void EnemyBase::Draw()
{
	const bool isDelete = m_isHit;
	if (!isDelete)
	{
		//	�����F�̐ݒ�
		_AttenuationColor();

		//	���f���̐F��ύX
		MV1SetDifColorScale(m_modelHandle, m_color);

		//	���f���̕`��
		if (!m_isOffDraw) { MV1DrawModel(m_modelHandle); }
	}
}

//-----------------------------------------------------------------------------
//	@brief	�F�̕ύX
//-----------------------------------------------------------------------------
void EnemyBase::_ChangeColor()
{
	//	�A�C�e���������Ă���Ȃ�
	//	�F��ύX����
	if (m_isHavingItems) { m_color = COLOR_RED; }
	else { m_color = COLOR_NORMAL; }
}

//-----------------------------------------------------------------------------
//	@brief	�V���b�g�̓o�^
//-----------------------------------------------------------------------------
void EnemyBase::_ShotEntry(PlayerManager& _playerManager, ShotManager& _shotManager)
{
	//	�����Ă���Ԃ̂�
	const bool isAlive = !m_isHit;
	if (isAlive)
	{
		//	�|�C���^�̎擾
		PlayerBase* player = _playerManager.GetPlayerPtr();
		if (player)
		{
			//	�o�����o���I����Ă�����A
			//	�v���C���[�ւ̃x�N�g�������߁A
			//	�e�̒ǉ�������
			const bool isPossible = !player->GetIsEmerge();
			if (isPossible)
			{
				const bool isActive = m_shotWaitTime++ == MAX_WAIT_TIME;
				if (isActive)
				{
					//	�e�𐶐�����
					VECTOR targetDir = VSub(player->GetCircle().m_centerPoint, m_pos);
					_shotManager.RegisterOnList(ShotManager::SHOT_KIND::ENEMY_SHOT, m_pos, targetDir, SHOT_SPEED);
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����G�t�F�N�g
//-----------------------------------------------------------------------------
void EnemyBase::_OnEffectExplosion(SoundEffect& _soundEffect)
{
	//	�q�b�g�����Ƃ�
	if (m_isHit)
	{
		const bool isExplosionStart = m_effectExplosion->GetPlayTime() == 0.0f;
		const bool isExplosionEnd = m_effectExplosion->GetPlayTime() == 200.0f;

		//	�����G�t�F�N�g�̊J�n
		if (isExplosionStart)
		{
			m_effectExplosion->SetPos(m_pos);
			m_effectExplosion->SetPlaySpeed(10.0f);
			m_effectExplosion->SetScale(VGet(2.0f, 2.0f, 2.0f));
			m_effectExplosion->OnPlayEffect();
			m_isOffDraw = true;

			//	�������̉��Z
			HAND_OVER_RESULT->AddDestructionNum();

			//	SE�̍Đ�
			_soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_EXPLOSION);
		}

		//	�����G�t�F�N�g�̏I��
		if (isExplosionEnd)
		{
			m_effectExplosion->OnEndEffect();
			m_isDeleate = true;
			return;
		}

		m_effectExplosion->AddPlayTime();
		m_effectExplosion->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	���F�ݒ�
//-----------------------------------------------------------------------------
void EnemyBase::_AttenuationColor()
{
	//	�����痈��G�́A
	//	��������
	if (m_isAttenuation)
	{
		//	�A�C�e���������Ă���Ȃ�
		//	�F��ύX����
		if (m_isHavingItems) { m_color = COLOR_DECAY_RED;}
		else { m_color = COLOR_DECAY_NORMAL; }
	}
	else
	{
		//	�A�C�e���������Ă���Ȃ�
		//	�F��ύX����
		const float lerpSpeed = 0.00001f;
		if (m_isHavingItems) { m_color = CommonFunction::AddColor(m_color, COLOR_RED, lerpSpeed); }
		else { m_color = CommonFunction::AddColor(m_color, COLOR_NORMAL, lerpSpeed); }
	}
}
