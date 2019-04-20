
//=============================================================================
//	@file	Player.cpp
//	@brief	�v���C���[
//	@autor	���m ���
//	@date	2018/11/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayer.h"
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
TitlePlayer::TitlePlayer(const int _modelHandle)
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
TitlePlayer::~TitlePlayer()
{
    //	�ŏI�I�ȉ������
    _FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void TitlePlayer::Create()
{
    //  �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void TitlePlayer::Release()
{
    //  �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void TitlePlayer::Initialize()
{
    //	�e�ϐ���������Ԃɐݒ�
    m_pos = TITLE_POS;
    m_dir = CommonConstant::ORIGIN;
    m_angle = VGet(0.0f, 1.4f, 0.0f);
    m_size = VGet(1.0f, 1.0f, 1.0f);
    m_life = START_LIFE;
    m_invincibleTime = 0.0f;
    m_isInvincible = false;
    m_isStopMove = false;
    m_offDraw = false;

    //	�p�x�ƃT�C�Y�����蓖�Ă�
    MV1SetRotationXYZ(m_modelHandle, m_angle);
    MV1SetScale(m_modelHandle, m_size);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void TitlePlayer::Update()
{
    //  �J�n���̉��o
    _StartProdoction();

    //  ���V���o
    _FloatingProdoction();
}

//-----------------------------------------------------------------------------
//	@brief	�J�n���̉��o
//-----------------------------------------------------------------------------
void TitlePlayer::_StartProdoction()
{
    //  �J�n���Ă��Ȃ�������A�������X�L�b�v
    bool isNotStart = !PRODUCTION->GetIsTitleProduction();
    if (isNotStart) { return; }

    //  �^�������ɐi��
    VECTOR tmpDir = VGet(1.0f, 0.0f, 0.0f);
    const float tmpSpeed = 10.0f;
    VECTOR moving = MoveHelper::AskMoveAmount(tmpDir, tmpSpeed);
    m_pos = VAdd(m_pos, moving);

    //	���f���Ƀ|�W�V���������蓖�Ă�
    MV1SetPosition(m_modelHandle, m_pos);
}

//-----------------------------------------------------------------------------
//	@brief	���V���o
//-----------------------------------------------------------------------------
void TitlePlayer::_FloatingProdoction()
{
    //  �J�n������A�������X�L�b�v
    bool isStart = PRODUCTION->GetIsTitleProduction();
    if (isStart) { return; }

    //  sin�J�[�u�ɂ����������߂�
    _AskSinCurveDirection();
    
    //	���V
    const float tmpSpeed = 0.1f;
    VECTOR velocity = VScale(m_dir, tmpSpeed);
    m_pos = VAdd(m_pos, velocity);

    //	���f���Ƀ|�W�V���������蓖�Ă�
    MV1SetPosition(m_modelHandle, m_pos);
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void TitlePlayer::_FinalRelease()
{
    //  �����Ȃ�
}
