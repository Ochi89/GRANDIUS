
//=============================================================================
//	@file	LineEnemy.cpp
//	@brief	�����G�l�~�[
//	@autor	���m ���
//	@date	2018/11/16
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "LineEnemy.h"
#include "Common.h"
#include "MoveHelper.h"
#include "AngleHelper.h"
#include "PlayerManager.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
LineEnemy::LineEnemy(const int _modelHandle)
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
LineEnemy::~LineEnemy()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void LineEnemy::Create()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void LineEnemy::Release()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void LineEnemy::Initialize()
{
	//	�e�ϐ���������Ԃɐݒ�
	m_pos = CommonConstant::ORIGIN;
	m_dir = CommonConstant::ORIGIN;
	m_angle = VGet(0.0f, 5.0f, 0.0f);
	m_behaviorTime = 0.0f;
	m_moveSpeed = 1.0f;
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
void LineEnemy::Update(PlayerManager& _playerManager, ShotManager& _shotManager, SoundEffect& _soundEffect)
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
void LineEnemy::_ChangeDir()
{
	m_dir = VGet(-1.0f, 0.0f, 0.0f);
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̓_�̍X�V
//-----------------------------------------------------------------------------
void LineEnemy::_UpdateHitPoint()
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
void LineEnemy::_FinalRelease()
{
	// �����Ȃ�
}

