
//=============================================================================
//	@file	CurveEnemy.cpp
//	@brief	�Ȑ��G�l�~�[
//	@autor	���m ���
//	@date	2018/11/16
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CurveEnemy.h"
#include "Common.h"
#include "MoveHelper.h"
#include "AngleHelper.h"
#include "PlayerManager.h"
#include "ShotManager.h"
#include "SoundEffect.h"
#include <math.h>

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float CurveEnemy::MOVE_ANGLE_SPEED = 15.0f;				//	��]�p�x�̉�]���x
const float CurveEnemy::MAX_MOVE_ANGLE_WAIT_TIME = 6.5f;		//	��]���x�̑ҋ@���Ԃ̍ő�
const float CurveEnemy::MAX_MOVE_ANGLE = 150.0f;				//	��]�p�x�̍ő�
const float CurveEnemy::MIN_MOVE_ANGLE = -150.0f;				//	��]�p�x�̍ŏ�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
CurveEnemy::CurveEnemy(const int _modelHandle)
	: EnemyBase(_modelHandle)
{
	//	�e�ϐ���������
	m_pos = CommonConstant::ORIGIN;
	m_dir = CommonConstant::ORIGIN;
	m_angle = CommonConstant::ORIGIN;
	m_isOnReverse = false;
	m_isOneTime = false;
	m_shotWaitTime = MAX_WAIT_TIME;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
CurveEnemy::~CurveEnemy()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void CurveEnemy::Create()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void CurveEnemy::Release()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void CurveEnemy::Initialize()
{
	//	�e�ϐ���������Ԃɐݒ�
	m_pos = VGet(0.0f, 50.0f, 0.0f);
	m_dir = CommonConstant::ORIGIN;
	m_angle = VGet(0.0f, 5.0f, 0.0f);
	m_behaviorTime = 0.0f;
	m_moveSpeed = 1.0f;
	m_isOnReverse = false;
	m_isOneTime = false;
	m_moveAngle = 0.0f;
	m_moveAngleWaitTime = 0.0f;
	m_shotWaitTime = 0.0f;
	m_aliveTime = 0.0f;
	m_formationID = 0;
	m_entryID = 0;
	m_entryKind = 0;
	m_isHavingItems = false;
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
void CurveEnemy::Update(PlayerManager& _playerManager, ShotManager& _shotManager, SoundEffect& _soundEffect)
{
	//	�q�b�g���Ă��Ȃ��Ƃ����A
	//	�K�E�Z�ȊO�̂Ƃ�
	const bool isActive = !m_isHit && !PRODUCTION->GetIsSpecialProduction();
	if(isActive)
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
void CurveEnemy::_ChangeDir()
{
	m_behaviorTime++;

	//	���Ԃ���p�^�[���̐؂�ւ�
	bool isPattern1 = m_behaviorTime >= 0.0f && m_behaviorTime <= 180.0f;
	bool isPattern2 = m_behaviorTime >= 180.0f && m_behaviorTime <= 1000.0f;

	//	���]����
	if (!m_isOneTime)
	{
		//	y���������Ⴉ������A
		//	�ړ������𔽓]������
		bool isActiveReverse = m_pos.y <= 50.0f;
		if (isActiveReverse) { m_isOnReverse = true; }
		m_isOneTime = true;
	}

	//	���������߂�
	if (m_isOnReverse)
	{
		//	��������
		if (isPattern1) { m_dir = VGet(-1.0f, 0.0f, 0.0f); }
		if (isPattern2)
		{
			//	�p�x�����߂�
			bool isMaximumValue = m_moveAngle >= MAX_MOVE_ANGLE;
			_ChangeMoveAngle(MOVE_ANGLE_SPEED, isMaximumValue, MAX_MOVE_ANGLE);

			//	�ړ��p�x����ړ����������߂�
			m_dir = CommonFunction::AskDirFromAngle(m_moveAngle);
		}
	}
	else
	{
		//	�ォ�牺��
		if (isPattern1) { m_dir = VGet(-1.0f, 0.0f, 0.0f); }
		if (isPattern2)
		{
			//	�p�x�����߂�
			bool isMinimumValue = m_moveAngle <= MIN_MOVE_ANGLE;
			_ChangeMoveAngle(MOVE_ANGLE_SPEED, isMinimumValue, MIN_MOVE_ANGLE);

			//	�ړ��p�x����ړ����������߂�
			m_dir = CommonFunction::AskDirFromAngle(m_moveAngle);
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�p�x�����߂�
//-----------------------------------------------------------------------------
void CurveEnemy::_ChangeMoveAngle(const float _moveAngleSpeed, const bool _isScalingSize, const float _ScalingSize)
{
	//	5�t���[����1��A�ړ��p�x��ύX����
	//	�ړ��p�x����ړ����������߂�
	m_moveAngleWaitTime++;
	if (m_moveAngleWaitTime >= MAX_MOVE_ANGLE_WAIT_TIME)
	{
		if (m_isOnReverse)
		{
			//	������ɐi�ނ̂ŁA
			//	�p�x�̉��Z
			m_moveAngle += _moveAngleSpeed;
		}
		else
		{
			//	�������ɐi�ނ̂ŁA
			//	�p�x�̌��Y
			m_moveAngle -= _moveAngleSpeed;
		}

		//	�ő�ŏ�����
		if (_isScalingSize) { m_moveAngle = _ScalingSize; }

		//	�ҋ@���Ԃ̏�����
		m_moveAngleWaitTime = 0.0f;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̓_�̍X�V
//-----------------------------------------------------------------------------
void CurveEnemy::_UpdateHitPoint()
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
void CurveEnemy::_FinalRelease()
{
	// �����Ȃ�
}

