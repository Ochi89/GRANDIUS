
//=============================================================================
//	@file	UpDownEnemy.cpp
//	@brief	����G�l�~�[
//	@autor	���m ���
//	@date	2018/12/20
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "UpDownEnemy.h"
#include "Common.h"
#include "MoveHelper.h"
#include "AngleHelper.h"
#include "PlayerManager.h"
#include "ShotManager.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float UpDownEnemy::MOVE_ANGLE_SPEED = 20.0f;				//	��]�p�x�̉�]���x
const float UpDownEnemy::MAX_MOVE_ANGLE_WAIT_TIME = 6.5f;		//	��]���x�̑ҋ@���Ԃ̍ő�
const float UpDownEnemy::MAX_MOVE_ANGLE = 150.0f;				//	��]�p�x�̍ő�
const float UpDownEnemy::MIN_MOVE_ANGLE = -150.0f;				//	��]�p�x�̍ŏ�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
UpDownEnemy::UpDownEnemy(const int _modelHandle)
	: EnemyBase(_modelHandle)
{
	//	�e�ϐ���������
	m_pos = CommonConstant::ORIGIN;
	m_dir = CommonConstant::ORIGIN;
	m_angle = CommonConstant::ORIGIN;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
UpDownEnemy::~UpDownEnemy()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void UpDownEnemy::Create()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void UpDownEnemy::Release()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void UpDownEnemy::Initialize()
{
	//	�e�ϐ���������Ԃɐݒ�
	m_pos = VGet(0.0f, 50.0f, 0.0f);
	m_dir = CommonConstant::ORIGIN;
	m_angle = VGet(0.0f, 5.0f, 0.0f);
	m_behaviorTime = 0.0f;
	m_moveSpeed = 1.5f;
	m_moveAngle = 180.0f;
	m_moveAngleWaitTime = 0.0f;
	m_shotWaitTime = 0.0f;
	m_aliveTime = 0.0f;
	m_formationID = 0;
	m_entryID = 0;
	m_entryKind = 0;
	m_isOnReverse = false;
	m_isOneTime = false;
	m_isHavingItems = false;
	m_isAttenuation = false;
	m_isHit = false;
	m_isOffDraw = false;
	m_isDeleate = false;

	//	�����蔻��p�̍\���̂̏�����
	m_hitCircle.m_radius = HIT_RADIUS;
	m_hitCircle.m_centerPoint = CommonConstant::ORIGIN;

	//	�p�x�����蓖�Ă�
	MV1SetRotationXYZ(m_modelHandle, m_angle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void UpDownEnemy::Update(PlayerManager& _playerManager, ShotManager& _shotManager, SoundEffect& _soundEffect)
{
	//	�q�b�g���Ă��Ȃ��Ƃ����A
	//	�K�E�Z�ȊO�̂Ƃ�
	const bool isActive = !m_isHit && !PRODUCTION->GetIsSpecialProduction();
	if (isActive)
	{
		//	�����̐؂�ւ�
		_ChangeDir();

		//	�ړ�����
		VECTOR moving = MoveHelper::AskMoveAmount(m_dir, m_moveSpeed);

		//	�V���b�g���g�p����
		if (m_isUseShot)
		{
			//	�V���b�g�̓o�^
			_ShotEntry(_playerManager, _shotManager);
		}

		//	�|�W�V�����̍X�V
		m_pos = VAdd(m_pos, moving);

		//	���s���̍ŏ��l
		if (m_pos.z <= 0.0f) { m_pos.z = 0.0f; }

		//	���f���Ƀ|�W�V���������蓖�Ă�
		MV1SetPosition(m_modelHandle, m_pos);

		//	���f���Ɋp�x�����蓖�Ă�
		MV1SetRotationXYZ(m_modelHandle, m_angle);
	}

	//	���f���̐F�̊��蓖��
	_ChangeColor();

	//	�����G�t�F�N�g
	_OnEffectExplosion(_soundEffect);

	//	�����蔻�肪�����̂ŁA
	//	���f���Ƀ|�W�V���������蓖�Ă���ɁA
	//	�����蔻��p�̍��W�̍X�V����
	_UpdateHitPoint();
}

//-----------------------------------------------------------------------------
//	@brief	�����̐؂�ւ�
//-----------------------------------------------------------------------------
void UpDownEnemy::_ChangeDir()
{
	m_behaviorTime++;

	//	���Ԃ���p�^�[���̐؂�ւ�
	bool isPattern1 = m_behaviorTime >= 0.0f && m_behaviorTime <= 90.0f;
	bool isPattern2 = m_behaviorTime >= 90.0f && m_behaviorTime <= 180.0f;
	bool isPattern3 = m_behaviorTime >= 180.0f && m_behaviorTime <= 270.0f;

	//	���]����
	if (!m_isOneTime)
	{
		//	y���������Ⴉ������A
		//	�ړ������𔽓]������
		bool isActiveReverse = m_pos.y <= 0.0f;
		if (isActiveReverse) { m_isOnReverse = true; }
		m_isOneTime = true;
	}

	//	���������߂�
	if (m_isOnReverse)
	{
		//	��������
		if (isPattern1) { m_dir = VGet(0.0f, 1.0f, 0.0f); 	m_isAttenuation = true; }
		if (isPattern2)
		{
			const float lerpSpeed = 0.2f;
			VECTOR tergetDir = VGet(0.0f, 0.0f, -1.0f);
			m_dir = CommonFunction::Lerp(m_dir, tergetDir, lerpSpeed);
			m_isAttenuation = false;
		}
		if (isPattern3)
		{
			const float lerpSpeed = 0.2f;
			VECTOR tergetDir = VGet(0.0f, -1.0f, 0.0f);
			m_dir = CommonFunction::Lerp(m_dir, tergetDir, lerpSpeed);

		}
	}
	else
	{
		//	�ォ�牺��
		if (isPattern1) { m_dir = VGet(0.0f, -1.0f, 0.0f); 	m_isAttenuation = true; }
		if (isPattern2)
		{
			const float lerpSpeed = 0.2f;
			VECTOR tergetDir = VGet(0.0f, 0.0f, -1.0f);
			m_dir = CommonFunction::Lerp(m_dir, tergetDir, lerpSpeed);
			m_isAttenuation = false;
		}
		if (isPattern3)
		{
			const float lerpSpeed = 0.2f;
			VECTOR tergetDir = VGet(0.0f, 1.0f, 0.0f);
			m_dir = CommonFunction::Lerp(m_dir, tergetDir, lerpSpeed);

		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̓_�̍X�V
//-----------------------------------------------------------------------------
void UpDownEnemy::_UpdateHitPoint()
{
	//	�����蔻��p�̒��S���W�̍X�V
	m_hitCircle.m_centerPoint = VGet(m_pos.x, m_pos.y - CENTER_CORRECTION, m_pos.z);

	//	�����蔻��p�̍��W�̍X�V
	m_hitRect.m_vertexTop = VGet(m_pos.x + RECT_CORRECTION.x, m_pos.y + RECT_CORRECTION.y, m_pos.z + RECT_CORRECTION.z);
	m_hitRect.m_vertexUnder = VGet(m_pos.x - RECT_CORRECTION.x, m_pos.y - RECT_CORRECTION.y, m_pos.z - RECT_CORRECTION.z);
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void UpDownEnemy::_FinalRelease()
{
	// �����Ȃ�
}

