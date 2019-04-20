
//=============================================================================
//	@file	StayShot.cpp
//	@brief	�؍ݒe�ЂƂ��̏���
//	@autor	���m ���
//	@date	2018/12/25
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "StayShot.h"
#include "Common.h"
#include "EffekseerEmitter.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const VECTOR	StayShot::MOVE_DIR = VGet(1.0f, 0.0f, 0.0f);			//	�ړ�����
const float		StayShot::MOVE_SPEED = 0.5f;							//	�ړ����x
const float		StayShot::MOVE_HIT_RADIUS = 2.0f;						//	�ړ����̓����蔻��p�̔��a
const float		StayShot::STAY_HIT_RADIUS = 5.0f;						//	�؍ݒ��̓����蔻��p�̔��a
const float		StayShot::MIN_HIT_RADIUS = 0.1f;						//	�����蔻��p�̍ŏ����a
const float		StayShot::MAX_STAY_TIME = 80.0f;						//	�؍ݒ��̎��Ԃ̍ő�
const float		StayShot::EFFECT_SCALE = 0.01f;							//	�G�t�F�N�g�̊g�呬�x
const float		StayShot::MAX_X_POS = 110.0f;							//	X���W�̍ő�
const VECTOR	StayShot::ADJUSTMENT_RECT = VGet(2.0f, 2.0f, 2.0f);		//	�����蔻�蒲���p

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
StayShot::StayShot()
{
	//	�e�ϐ��̏�����
	m_pos = CommonConstant::ORIGIN;
	m_isOneTime = false;
	m_isChangeStay = false;
	m_stayTime = 0.0f;
	m_isShotEnd = false;
	m_isMoveShotSeStart = false;
	m_isStayShotSeStart = false;

	//	�����蔻��p�̍\���̂̏�����
	m_hitCircle.m_radius = MOVE_HIT_RADIUS;
	m_hitCircle.m_centerPoint = CommonConstant::ORIGIN;

	m_hitRect.m_vertexTop = CommonConstant::ORIGIN;
	m_hitRect.m_vertexUnder = CommonConstant::ORIGIN;

	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
	m_effectMove = NULL;
	m_effectStay = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
StayShot::~StayShot()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void StayShot::Initialize()
{
	//	�e�ϐ��̏�����
	m_pos = CommonConstant::ORIGIN;
	m_isOneTime = false;
	m_isChangeStay = false;
	m_stayTime = 0.0f;
	m_isShotEnd = false;
	m_isMoveShotSeStart = false;
	m_isStayShotSeStart = false;

	//	�����蔻��p�̍\���̂̏�����
	m_hitCircle.m_radius = MOVE_HIT_RADIUS;
	m_hitCircle.m_centerPoint = CommonConstant::ORIGIN;

	m_hitRect.m_vertexTop = CommonConstant::ORIGIN;
	m_hitRect.m_vertexUnder = CommonConstant::ORIGIN;

	//	�G�t�F�N�g�̓ǂݍ���
	m_effectMove = new EffekseerEmitter("Data/Effect/Player/StayShot/Move/Move.efk");
	m_effectStay = new EffekseerEmitter("Data/Effect/Player/StayShot/Stay/Stay.efk");
	m_effectScale = 1.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void StayShot::Update(SoundEffect& _soundEffect)
{
	if (m_isChangeStay)
	{
		//	�؍ݏ���
		_Stay(_soundEffect);
	}
	else
	{
		//	�ړ�����
		_Move(_soundEffect);
	}

	//	�����蔻��p�̍��W�̍X�V����
	_UpdateHitPoint();
}

//-----------------------------------------------------------------------------
//	@brief	�ړ�����
//-----------------------------------------------------------------------------
void StayShot::_Move(SoundEffect& _soundEffect)
{
	//	SE
	if (!m_isMoveShotSeStart) { _soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_MOVE_SHOT); m_isMoveShotSeStart = true; }

	//	�ړ�
	VECTOR velocity = VScale(MOVE_DIR, MOVE_SPEED);
	m_pos = VAdd(m_pos, velocity);

	m_effectMove->SetPos(m_pos);
	m_effectMove->SetPlaySpeed(2.0f);
	m_effectMove->OnPlayEffect();

	//	�͈͊O�ɏo����A�G�t�F�N�g������
	const bool isArrivalRight = m_pos.x >= MAX_X_POS;
	if (isArrivalRight) { m_effectMove->OnEndEffect(); }

	m_effectMove->Update();
}

//-----------------------------------------------------------------------------
//	@brief	�؍ݏ���
//-----------------------------------------------------------------------------
void StayShot::_Stay(SoundEffect& _soundEffect)
{
	if (!m_isShotEnd)
	{
		//	SE
		if (!m_isStayShotSeStart)
		{
			_soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_STAY_SHOT);
			m_isStayShotSeStart = true;
		}

		m_stayTime++;

		//	���̏�ɑ؍݂���
		const bool isStay = m_stayTime <= MAX_STAY_TIME;
		if (isStay)
		{
			//	�����蔻���傫������
			const float lerpSpeed = 0.5f;
			m_hitCircle.m_radius = CommonFunction::Lerp(m_hitCircle.m_radius, STAY_HIT_RADIUS, lerpSpeed);

			//	�G�t�F�N�g
			m_effectScale += EFFECT_SCALE;
			m_effectStay->SetPos(m_pos);
			m_effectStay->SetPlaySpeed(1.5f);
			m_effectStay->SetScale(VGet(m_effectScale, m_effectScale, m_effectScale));
			m_effectStay->OnPlayEffect();
			m_effectMove->OnEndEffect();
		}

		//	�����蔻������񂾂񏬂�������
		const bool isStayEnd = m_stayTime >= MAX_STAY_TIME;
		if (isStayEnd)
		{
			//	�����蔻�������������
			const float lerpSpeed = 0.1f;
			m_hitCircle.m_radius = CommonFunction::Lerp(m_hitCircle.m_radius, 0.0f, lerpSpeed);

			//	�G�t�F�N�g
			m_effectScale -= EFFECT_SCALE;
			m_effectStay->SetScale(VGet(m_effectScale, m_effectScale, m_effectScale));
		}

		//	�����蔻�肪��萔��菬�����Ȃ�����A
		//	�V���b�g���I��������
		const bool isShotEnd = m_hitCircle.m_radius <= MIN_HIT_RADIUS;
		if (isShotEnd) { m_isShotEnd = true; m_effectStay->OnEndEffect(); }

		m_effectStay->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̓_�̍X�V
//-----------------------------------------------------------------------------
void StayShot::_UpdateHitPoint()
{
	//	�����蔻��p�̒��S���W�̍X�V
	m_hitCircle.m_centerPoint = m_pos;

	m_hitRect.m_vertexTop = VSub(m_pos, ADJUSTMENT_RECT);
	m_hitRect.m_vertexUnder = VAdd(m_pos, ADJUSTMENT_RECT);
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void StayShot::_FinalRelease()
{
	//	�G�t�F�N�g�̍폜
	CommonSafe::Delete(m_effectMove);
	CommonSafe::Delete(m_effectStay);
}
