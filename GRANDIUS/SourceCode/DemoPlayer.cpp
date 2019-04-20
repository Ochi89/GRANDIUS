
//=============================================================================
//	@file	Player.cpp
//	@brief	�v���C���[
//	@autor	���m ���
//	@date	2018/11/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DemoPlayer.h"
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
DemoPlayer::DemoPlayer(const int _modelHandle)
    : GamePlayer(_modelHandle)
{
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
DemoPlayer::~DemoPlayer()
{
    //	�ŏI�I�ȉ������
    _FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void DemoPlayer::Create()
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
void DemoPlayer::Release()
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
void DemoPlayer::Initialize()
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
void DemoPlayer::Update(ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect, UIGauge& _gaugeUI, EnemyManager& _enemyManager)
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
            //	�����̐؂�ւ�
            _ChangeDir(_enemyManager);

            //	�ړ�����
            //	moving �̃m������0�ȊO�̂Ƃ��́A�ړ���
            VECTOR moving = MoveHelper::AskMoveAmount(m_dir, m_speed);
            m_isMove = VSize(moving) != 0;

            //	�|�W�V�����̍X�V
            m_pos = VAdd(m_pos, moving);

            //	�͈͊O�w��
            _OutOfRange();

            //	�ˌ�����
            _Shot(_shot, _stayShot, _soundEffect);

            //	�p�x����
            AngleHelper::AskAngle(m_angle, m_dir);
        }
    }

    //	�q�b�g�G�t�F�N�g
    _OnHitEffect(_soundEffect);

    //	�����G�t�F�N�g
    _OnEffectExplosion(_soundEffect);

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
}

//-----------------------------------------------------------------------------
//	@brief	�ړ������̐؂�ւ�
//-----------------------------------------------------------------------------
void DemoPlayer::_ChangeDir(EnemyManager& _enemyManager)
{
    //	�����̐؂�ւ�
    const float startTime = 0.0f;
    const bool isStart = m_demoDirChangeTime == startTime;
    if (isStart)
    {
        //	�G���X�g�̐擪���擾
        const int beginningOfEnemyList = 0;
        EnemyBase* enemy = _enemyManager.GetEnemyPtr(beginningOfEnemyList);

        if (enemy)
        {
            //	�ړI�n�����߂�
            m_demoTargetPos = enemy->GetPos();
            m_demoTargetPos.x -= MAX_DEMO_DISTANCE_TO_ENEMY;
        }

        //	���������߂�
        m_dir = VSub(m_demoTargetPos, m_pos);

        //	���K��
        m_dir = VNorm(m_dir);
    }

    //	�����̏�����
    const float endTime = 60.0f;
    const bool isInitDir = m_demoDirChangeTime == endTime;
    if (isInitDir) { m_dir = CommonConstant::ORIGIN; }

    m_demoDirChangeTime++;

    //	�ő又��
    const float resetTime = 100.0f;
    const bool isMaxVal = m_demoDirChangeTime > resetTime;
    if (isMaxVal) { m_demoDirChangeTime = 0.0f; }
}

//-----------------------------------------------------------------------------
//	@brief	�e�̏���
//-----------------------------------------------------------------------------
void DemoPlayer::_Shot(ShotManager& _shot, StayShotManager& _stayShot, SoundEffect& _soundEffect)
{
    //	�x�����Ԃ��Ȃ��Ȃ�����A�e�𐶐�����
    m_shotWaitTime--;
    const bool isActiveShot = m_shotWaitTime <= MAX_DEMO_SHOT_FIRING_TIME;
    if (isActiveShot)
    {
        //	�e���X�g�ɒǉ�����
        _shot.RegisterOnList(ShotManager::SHOT_KIND::PLAYER_SHOT, m_pos, VGet(1.0f, 0.0f, 0.0f), SHOT_SPEED, _soundEffect);
        m_shotWaitTime = MAX_SHOT_WAIT_TIME;
    }

    //	�؍݃V���b�g�̎g�p��
    m_stayShotWaitTime--;
    m_isUseStayShot = (m_stayShotWaitTime <= 0.0f);

    //	���˒x�����Ԃ����ˎ��Ԃ�菬�����Ȃ�����A�؍ݒe�𐶐�����
    const bool isActiveStayShot = m_stayShotWaitTime <= MAX_DEMO_STAY_SHOT_FIRING_TIME;
    if (isActiveStayShot)
    {
        _stayShot.RegisterOnList(m_pos);
        m_stayShotWaitTime = MAX_STAY_SHOT_WAIT_TIME;
    }
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void DemoPlayer::_FinalRelease()
{
    //	�G�t�F�N�g�̍폜
    CommonSafe::Delete(m_effectLaser);
    CommonSafe::Delete(m_effectHit);
    CommonSafe::Delete(m_effectExplosion);
    CommonSafe::Delete(m_effectSpeedUp);
    CommonSafe::Delete(m_effectGetItem);
}
