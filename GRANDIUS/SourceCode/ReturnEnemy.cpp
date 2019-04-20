
//=============================================================================
//	@file	ReturnEnemy.cpp
//	@brief	�J���o�b�N�G�l�~�[
//	@autor	���m ���
//	@date	2018/11/16
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ReturnEnemy.h"
#include "Common.h"
#include "MoveHelper.h"
#include "AngleHelper.h"
#include "PlayerManager.h"
#include "ShotManager.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float ReturnEnemy::ADD_RADIAN_SPEED = 0.1f;	//	���W�A���p�̉��Z���x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
ReturnEnemy::ReturnEnemy(const int _modelHandle)
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
ReturnEnemy::~ReturnEnemy()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void ReturnEnemy::Create()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void ReturnEnemy::Release()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void ReturnEnemy::Initialize()
{
	//	�e�ϐ���������Ԃɐݒ�
	m_pos = VGet(0.0f, 50.0f, 0.0f);
	m_dir = CommonConstant::ORIGIN;
	m_angle = VGet(0.0f, 5.0f, 0.0f);
	m_behaviorTime = 0.0f;
	m_moveSpeed = 0.0f;
	m_radian = 0.0f;
	m_shotWaitTime = 0.0f;
	m_aliveTime = 0.0f;
	m_formationID = 0;
	m_entryID = 0;
	m_entryKind = 0;
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
void ReturnEnemy::Update(PlayerManager& _playerManager, ShotManager& _shotManager, SoundEffect& _soundEffect)
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
void ReturnEnemy::_ChangeDir()
{
	m_behaviorTime++;

	bool isPattern1 = m_behaviorTime >= 0.0f && m_behaviorTime <= 60.0f;
	bool isPattern2 = m_behaviorTime >= 60.0f && m_behaviorTime <= 90.0f;
	bool isPattern3 = m_behaviorTime >= 90.0f && m_behaviorTime <= 1000.0f;

	if (isPattern1)
	{
		const float lerpSpeed = 0.2f;
		VECTOR tergetDir = VGet(1.0f, 0.0f, 0.0f);
		m_dir = CommonFunction::Lerp(m_dir, tergetDir, lerpSpeed);
		m_moveSpeed = 3.0f;
		m_isAttenuation = true;
	}
	if (isPattern2)
	{
		const float lerpSpeed = 0.2f;
		VECTOR tergetDir = VGet(0.0f, 0.0f, -1.0f);
		m_dir = CommonFunction::Lerp(m_dir, tergetDir, lerpSpeed);
		m_moveSpeed = 3.0f;
		m_isAttenuation = false;
	}
	if (isPattern3)
	{
		const float lerpSpeed = 0.5f;

		//	���W�A���p�̉��Z
		m_radian += ADD_RADIAN_SPEED;
		VECTOR tergetDir = VGet(-1.0f, sinf(m_radian), 0.0f);
		m_dir = CommonFunction::Lerp(m_dir, tergetDir, lerpSpeed);
		m_moveSpeed = 1.0f;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̓_�̍X�V
//-----------------------------------------------------------------------------
void ReturnEnemy::_UpdateHitPoint()
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
void ReturnEnemy::_FinalRelease()
{
	// �����Ȃ�
}

