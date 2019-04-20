
//=============================================================================
//	@file	PlayerBase.cpp
//	@brief	�v���C���[�x�[�X
//	@autor	���m ���
//	@date	2018/11/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerBase.h"
#include "ShotManager.h"
#include "StayShotManager.h"
#include "EffekseerEmitter.h"
#include "UIGauge.h"
#include "Pad.h"
#include "Common.h"
#include "SoundEffect.h"
#include "EnemyManager.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const VECTOR	PlayerBase::TITLE_POS = VGet(10.0f, 25.0f, 40.0f);			//	�^�C�g�����̍��W
const VECTOR	PlayerBase::RESULT_POS = VGet(-50.0f, 50.0f, 0.0f);			//	���U���g���̍��W
const VECTOR	PlayerBase::EMERGE_POS = VGet(-70.0f, 50.0f, -40.0f);		//	�o�����̍��W
const VECTOR	PlayerBase::START_POS = VGet(-30.0f, 50.0f, 0.0f);			//	�J�n���̍��W
const VECTOR	PlayerBase::RECT_CORRECTION = VGet(0.5f, 0.5f, 1.0f);		//	���W�̕␳
const VECTOR	PlayerBase::ITEM_RECT_CORRECTION = VGet(7.0f, 2.0f, 1.0f);	//	�A�C�e�����W�̕␳
const float		PlayerBase::EMERGE_MOVE_SPEED = 4.0f;						//	�o�����̈ړ����x
const float		PlayerBase::SHOT_SPEED = 7.0f;								//	�V���b�g���x
const float		PlayerBase::MAX_SHOT_WAIT_TIME = 8.0f;						//	�V���b�g�̒x������
const float		PlayerBase::MAX_STAY_SHOT_WAIT_TIME = 70.0f;				//	�؍݃V���b�g�̒x������
const float		PlayerBase::CENTER_CORRECTION = 5.0f;						//	���S���W�̕␳
const float		PlayerBase::HIT_RADIUS = 0.5f;								//	�����蔻��p�̔��a
const float		PlayerBase::MAX_INVINCIBLE_TIME_1 = 120.0f;					//	�����蔻��̖������Ԃ̍ő�
const float		PlayerBase::MAX_INVINCIBLE_TIME_2 = 30.0f;					//	�����蔻��̖������Ԃ̍ő�
const float		PlayerBase::MOVE_SPEED = 1.2f;								//	�ړ����x
const float		PlayerBase::MIN_POS_X = -90.0f;								//	�����W�̍ŏ�
const float		PlayerBase::MAX_POS_X = 95.0f;								//	�����W�̍ő�
const float		PlayerBase::MIN_POS_Y = 5.0f;								//	�����W�̍ŏ�
const float		PlayerBase::MAX_POS_Y = 105.0f;								//	�����W�̍ő�
const float		PlayerBase::LASER_SIZE = 40.0f;								//	���[�U�[�T�C�Y
const float		PlayerBase::LASER_SIZE_DEPTH = 60.0f;						//	���[�U�[�T�C�Y�̉��s��
const float		PlayerBase::LASER_SPEED = 20.0f;							//	���[�U�[���x
const float		PlayerBase::ADD_RADIAN_SPEED = 0.1f;						//	���W�A���p�̉��Z���x
const float		PlayerBase::MAX_DEMO_SHOT_FIRING_TIME = -3.0f;				//	�V���b�g�̔��ˎ���
const float		PlayerBase::MAX_DEMO_STAY_SHOT_FIRING_TIME = -10.0f;		//	�؍݃V���b�g�̔��ˎ���
const float		PlayerBase::MAX_DEMO_CHANGE_DIR_WAIT_TIME = 180.0f;			//	�f���p�̌����؂�ւ��x������
const float		PlayerBase::MAX_DEMO_DISTANCE_TO_ENEMY = 80.0f;				//	�f���p�̓G�Ƃ̋����̊Ԋu
const int		PlayerBase::START_LIFE = 5;									//	�J�n���̎c�@
const int		PlayerBase::ZERO_LIFE = 0;									//	�c�@�Ȃ�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
PlayerBase::PlayerBase(const int _modelHandle)
{
	//	���f���̕���
	m_modelHandle = MV1DuplicateModel(_modelHandle);
	CommonDebug::Assert((m_modelHandle <= -1), " [ PlayerBase.cpp ] : error : missing duplicat model.");
	m_flashingTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
PlayerBase::~PlayerBase()
{
	//	���f���̃A�����[�h
	MV1DeleteModel(m_modelHandle);
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void PlayerBase::Draw()
{
	//	���G��Ԃ̂Ƃ�
	const bool isInvincible = m_isInvincible && !m_isEmerge;
	if (isInvincible)
	{
		m_flashingTime++;
		const bool isFlashingEnd = m_flashingTime > 10.0f;
		if (isFlashingEnd) { m_flashingTime = 0.0f; }

		const bool isFlashing = m_flashingTime >= 5.0f && m_flashingTime <= 10.0f;
		if (isFlashing) { return; }
	}

	//	�`�斳�����Ȃ��Ƃ��́A
	//	���f����`��
	const bool isDraw = !m_offDraw && m_life > ZERO_LIFE;
	if (isDraw)
	{
		//	���f���̕`��
		MV1DrawModel(m_modelHandle);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����ʒu�� getter
//-----------------------------------------------------------------------------
const VECTOR PlayerBase::GetStartPos() const
{
	return START_POS;
}

//-----------------------------------------------------------------------------
//	@brief	sin�J�[�u�ɂ����������߂�
//-----------------------------------------------------------------------------
void PlayerBase::_AskSinCurveDirection()
{
    //	���W�A���p�̉��Z
    m_radian += ADD_RADIAN_SPEED;

    //	���������߂�
    //	sin�J�[�u���g���A���V����悤�ȃJ�[�u
    m_dir.y = sinf(m_radian);
}
