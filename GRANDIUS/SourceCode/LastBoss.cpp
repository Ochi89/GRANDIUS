
//=============================================================================
//	@file	LastBoss.cpp
//	@brief	�ŏI�{�X
//	@autor	���m ���
//	@date	2018/12/21
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "LastBoss.h"
#include "Common.h"
#include "MoveHelper.h"
#include "AngleHelper.h"
#include "PlayerManager.h"
#include "ShotManager.h"
#include "EffekseerEmitter.h"
#include "SoundEffect.h"
#include "Pad.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const VECTOR	LastBoss::EMERGE_POS = VGet(206.0f, 50.0f, 0.0f);						//	�o�����̍��W
const VECTOR	LastBoss::EMERGE_RIGHT_ARM_POS = VGet(60.0f, 150.0f, 0.0f);				//	�o�����̉E�A�[���̍��W
const VECTOR	LastBoss::EMERGE_LEFT_ARM_POS = VGet(60.0f, -150.0f, 0.0f);				//	�o�����̍��A�[���̍��W
const VECTOR	LastBoss::RELATIVE_CORE_POS = VGet(-9.5f, 5.0f, 0.0f);					//	�R�A�̑��΍��W
const VECTOR	LastBoss::RELATIVE_SIDE_BARREL_POS = VGet(-10.0f, 8.0f, 0.0f);			//	�T�C�h�o�����̑��΍��W
const VECTOR	LastBoss::RELATIVE_ARM_POS = VGet(0.9f, 28.0f, 0.0f);					//	�A�[���̑��΍��p
const VECTOR	LastBoss::OPEN_RELATIVE_CORE_POS = VGet(-9.5f, 8.0f, 0.0f);				//	�R�A�̑��΍��W
const VECTOR	LastBoss::OPEN_RELATIVE_SIDE_BARREL_POS = VGet(-10.0f, 20.0f, 0.0f);	//	�T�C�h�o�����̑��΍��W
const VECTOR	LastBoss::OPEN_RELATIVE_ARM_POS = VGet(0.9f, 35.0f, 0.0f);				//	�A�[���̑��΍��p
const VECTOR	LastBoss::START_POS = VGet(60.0f, 50.0f, 0.0f);							//	�J�n���̍��W
const VECTOR	LastBoss::MOVE_PATTERN_1 = VGet(60.0f, 90.0f, 0.0f);					//	�s���p�^�[���P
const VECTOR	LastBoss::MOVE_PATTERN_2 = VGet(60.0f, 55.0f, 0.0f);					//	�s���p�^�[���Q
const VECTOR	LastBoss::MOVE_PATTERN_3 = VGet(60.0f, 20.0f, 0.0f);					//	�s���p�^�[���R
const VECTOR	LastBoss::MOVE_PATTERN_4 = VGet(40.0f, 55.0f, 0.0f);					//	�s���p�^�[���S
const VECTOR	LastBoss::MOVE_PATTERN_5 = VGet(40.0f, 20.0f, 0.0f);					//	�s���p�^�[���T
const VECTOR	LastBoss::MOVE_PATTERN_6 = VGet(40.0f, 90.0f, 0.0f);					//	�s���p�^�[���U
const VECTOR	LastBoss::SHOT_START_POS_CORRECTION_1 = VGet(14.0f, 12.0f, 0.0f);		//	�V���b�g�J�n�ʒu���W�̕␳
const VECTOR	LastBoss::SHOT_START_POS_CORRECTION_2 = VGet(21.5f, 6.5f, 0.0f);		//	�V���b�g�J�n�ʒu���W�̕␳
const VECTOR	LastBoss::SHOT_START_POS_CORRECTION_3 = VGet(35.0f, 1.0f, 0.0f);		//	�V���b�g�J�n�ʒu���W�̕␳
const float		LastBoss::SHOT_SPEED = 1.5f;											//	�V���b�g�̑��x
const float		LastBoss::MAX_START_WAIT_TIME = 35.0f;									//	�V���b�g�̊J�n���̒x������
const float		LastBoss::MAX_WAIT_TIME = 100.0f;										//	�V���b�g�̒x������
const float		LastBoss::LASER_LENGTH = -200.0f;										//	���[�U�[�̒���
const VECTOR	LastBoss::ADJUSTMENT_BODY_POS = VGet(15.0f, 0.0f, 0.0f);				//	�����蔻�蒲���p�̃|�W�V���� �{�f�B�[
const VECTOR	LastBoss::ADJUSTMENT_SIDE_BARREL_POS = VGet(-10.0f, 1.0f, 0.0f);		//	�����蔻�蒲���p�̃|�W�V���� �T�C�h�o����
const VECTOR	LastBoss::ADJUSTMENT_ARM_CIRCLE_POS = VGet(-15.0f, 2.0f, 0.0f);			//	�����蔻�蒲���p�̃|�W�V���� �A�[��
const VECTOR	LastBoss::ADJUSTMENT_ARM_RECT_POS = VGet(18.0f, 8.0f, 5.0f);			//	�����蔻�蒲���p�̃|�W�V���� �A�[��
const VECTOR	LastBoss::ADJUSTMENT_LASER_POS = VGet(-25.0f, 4.0f, 5.0f);				//	�����蔻�蒲���p�̃|�C���g ���[�U�[
const VECTOR	LastBoss::ADJUSTMENT_CENTER_BARRE_POS = VGet(30.0f, 2.0f, 5.0f);		//	�����蔻�蒲���p�̃|�C���g �Z���^�[�o����
const VECTOR	LastBoss::ARM_CORRECTION = VGet(10.0f, 3.0f, 0.0f);						//	�����蔻��p�̕␳ �A�[��
const VECTOR	LastBoss::CENTER_BARRE_CORRECTION = VGet(10.0f, 0.0f, 0.0f);			//	�����蔻��p�̕␳ �Z���^�[�o����
const float		LastBoss::LASER_EFFECT_CORRECTION = -28.0f;								//	�G�t�F�N�g�̕␳ ���[�U�[
const float		LastBoss::ROCKET_EFFECT_CORRECTION = 25.0f;								//	�G�t�F�N�g�̕␳ ���P�b�g
const float		LastBoss::HIT_BODY_RADIUS = 15.0f;										//	�����蔻��p�̔��a �{�f�B�[
const float		LastBoss::HIT_SIDE_BARREL_RADIUS = 7.0f;								//	�����蔻��p�̔��a �T�C�h�o����
const float		LastBoss::HIT_CORE_RADIUS = 3.0f;										//	�����蔻��p�̔��a �R�A
const float		LastBoss::HIT_ARM_RADIUS = 10.0f;										//	�����蔻��p�̔��a �A�[��
const int		LastBoss::MAX_SIDE_BARREL_LIFE = 40;									//	���C�t�̍ő� �T�C�h�o����
const int		LastBoss::MAX_CORE_LIFE = 30;											//	���C�t�̍ő� �R�A
const VECTOR	LastBoss::BOSS_RADIUS = VGet(20.0f, 15.0f, 0.0f);						//	�{�X�̔��a
const int		LastBoss::LIFE_ZERO = 0;												//	���C�t�Ȃ�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
LastBoss::LastBoss(const int _bodyModelHandle, const int _sideBarrelModelHandle, const int _armModelHandle, const int _coreModelHandle)
{
	//	�e�ϐ���������
	m_pos = CommonConstant::ORIGIN;
	m_dir = CommonConstant::ORIGIN;
	m_angle = CommonConstant::ORIGIN;

	//	���f���̕���
	m_modelHandle = MV1DuplicateModel(_bodyModelHandle);
	CommonDebug::Assert((m_modelHandle <= -1), " [ LastBoss.cpp ] : error : model loading failed.");

	for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
	{
		m_bossPartsSideBarrel[i].m_modelHandle = MV1DuplicateModel(_sideBarrelModelHandle);
		m_bossPartsArm[i].m_modelHandle = MV1DuplicateModel(_armModelHandle);
		m_bossPartsCore[i].m_modelHandle = MV1DuplicateModel(_coreModelHandle);
		CommonDebug::Assert((m_bossPartsSideBarrel[i].m_modelHandle <= -1), " [ LastBoss.cpp ] : error : model loading failed.");
		CommonDebug::Assert((m_bossPartsArm[i].m_modelHandle <= -1), " [ LastBoss.cpp ] : error : model loading failed.");
		CommonDebug::Assert((m_bossPartsCore[i].m_modelHandle <= -1), " [ LastBoss.cpp ] : error : model loading failed.");

		//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
		m_effectLaser[i] = NULL;
		m_effectInjection[i] = NULL;
	}

	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
	m_effectHit = NULL;

	for (int i = 0; i < CommonConstant::MAX_BOSS_EXPLOSION_NUM; i++)
	{
		m_effectExplosion[i] = NULL;
	}

	m_effectLastExplosion = NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
LastBoss::~LastBoss()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void LastBoss::Create()
{
	//	�G�t�F�N�g�̓ǂݍ���
	m_effectHit = new EffekseerEmitter("Data/Effect/Hit/Hit.efk");
	m_effectHit->OnEndEffect();

	for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
	{
		m_effectInjection[i] = new EffekseerEmitter("Data/Effect/Injection/Injection.efk");
		m_effectLaser[i] = new EffekseerEmitter("Data/Effect/Boss/Laser/Laser.efk");
		m_effectInjection[i]->OnEndEffect();
		m_effectLaser[i]->OnEndEffect();
	}

	for (int i = 0; i < CommonConstant::MAX_BOSS_EXPLOSION_NUM; i++)
	{
		m_effectExplosion[i] = new EffekseerEmitter("Data/Effect/Explosion/Explosion.efk");
		m_effectExplosion[i]->OnEndEffect();
	}

	m_effectLastExplosion = new EffekseerEmitter("Data/Effect/Explosion/Explosion.efk");
	m_effectLastExplosion->OnEndEffect();
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void LastBoss::Release()
{
	//	���f���̃A�����[�h
	MV1DeleteModel(m_modelHandle);

	for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
	{
		MV1DeleteModel(m_bossPartsSideBarrel[i].m_modelHandle);
		MV1DeleteModel(m_bossPartsArm[i].m_modelHandle);
		MV1DeleteModel(m_bossPartsCore[i].m_modelHandle);
	}

	//	�G�t�F�N�g�̍폜
	CommonSafe::Delete(m_effectHit);

	for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
	{
		CommonSafe::Delete(m_effectInjection[i]);
		CommonSafe::Delete(m_effectLaser[i]);
	}

	for (int i = 0; i < CommonConstant::MAX_BOSS_EXPLOSION_NUM; i++)
	{
		CommonSafe::Delete(m_effectExplosion[i]);
	}

	CommonSafe::Delete(m_effectLastExplosion);
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void LastBoss::Initialize()
{
	//	�e�ϐ���������Ԃɐݒ�
	m_pos = EMERGE_POS;
	m_dir = CommonConstant::ORIGIN;
	m_angle = CommonConstant::ORIGIN;
	m_emergeMoveTaim = 0.0f;
	m_behaviorTime = 0.0f;
	m_rocketTime = 0.0f;
	m_laserTime = 0.0f;
	m_moveSpeed = 1.0f;
	m_shotWaitTime = MAX_START_WAIT_TIME;
	m_isEmerge = false;
	m_isStarted = false;
	m_isRightCoreAlive = true;
	m_isLeftCoreAlive = true;
	m_isRightSideBarrelAlive = true;
	m_isLeftSideBarrelAlive = true;
	m_isStartRocket = false;
	m_isStartLaser = false;
	m_life = 1;
	m_behaviorKind = BEHAVIOR_KIND::BEHAVIOR_NONE;
	m_laser.m_vertexTop = CommonConstant::ORIGIN;
	m_laser.m_vertexUnder = CommonConstant::ORIGIN;
	m_isOffDraw = false;
	m_isAllDestruction = false;

	//	���C�t�ɉ��������f���̐F
	m_lifeNormalColorFYellow = CommonFunction::GetColor(0.0f, 0.0f, 0.8f, 1.0f);	//	�F
	m_lifeNormalColorFBlack = CommonFunction::GetColor(0.4f, 0.4f, 0.4f, 1.0f);		//	�O���[
	m_lifeMiddleColorF = CommonFunction::GetColor(1.0f, 1.0f, 0.0f, 1.0f);			//	���F
	m_lifeDangerColorF = CommonFunction::GetColor(1.0f, 0.0f, 0.8f, 1.0f);			//	��

	//	�F�̊��蓖��
	MV1SetDifColorScale(m_modelHandle, m_lifeNormalColorFBlack.m_color);

	for (int i = 0; i < EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_NUM; i++)
	{
		m_isUsedEffectExplosion[i] = false;
	}

	//	�p�[�c�̏�����
	for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
	{
		//	�R�A�̏�����
		_InitializeBossParts(m_bossPartsCore[i], (BOSS_PARTS_INFO)i, HIT_CORE_RADIUS, MAX_CORE_LIFE);

		//	�T�C�h�o�����̏�����
		_InitializeBossParts(m_bossPartsSideBarrel[i], (BOSS_PARTS_INFO)i, HIT_SIDE_BARREL_RADIUS, MAX_SIDE_BARREL_LIFE );

		//	�A�[���̏�����
		_InitializeBossParts(m_bossPartsArm[i], (BOSS_PARTS_INFO)i, HIT_ARM_RADIUS);
		
		//	�F�̊��蓖��
		MV1SetDifColorScale(m_bossPartsArm[i].m_modelHandle, m_lifeNormalColorFBlack.m_color);

		//	���[�U�[�̓����蔻��̏�����
		m_laserHitRect[i].m_vertexTop = CommonConstant::ORIGIN;
		m_laserHitRect[i].m_vertexUnder = CommonConstant::ORIGIN;

		//	�R�A�̓����蔻��̏�����
		m_coreHitRect[i].m_vertexTop = CommonConstant::ORIGIN;
		m_coreHitRect[i].m_vertexUnder = CommonConstant::ORIGIN;

		//	�T�C�h�o�����̓����蔻��̏�����
		m_sideBarrelHitRect[i].m_vertexTop = CommonConstant::ORIGIN;
		m_sideBarrelHitRect[i].m_vertexUnder = CommonConstant::ORIGIN;
	}

	//	�p�x�����蓖�Ă�
	MV1SetRotationXYZ(m_modelHandle, m_angle);
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void LastBoss::Update(ShotManager& _shot, SoundEffect& _soundEffect)
{
	//	�K�E�Z�̂Ƃ��͍X�V���Ȃ�
	const bool isNotSpecialProduction = !PRODUCTION->GetIsSpecialProduction();
	if (isNotSpecialProduction)
	{
		//	�o�����̉��o
		_EmergeMove();

		//	�J�n���Ă��āA
		//	����ł��Ȃ��Ƃ�
		const bool isActive = m_isStarted && (m_isLeftCoreAlive || m_isRightCoreAlive);
		if (isActive)
		{
			//	�R�A�̏��
			_PartsSituation();

			//	���΍��W�̐ݒ�
			_AllocationRelativeCoordinates();

			const bool isNotSpecialProduction = !PRODUCTION->GetIsSpecialProduction();
			if (isNotSpecialProduction)
			{
				//	�ړ�����
				_Move();

				//	�ˌ�����
				_Shot(_shot);
			}

			//	���P�b�g����
			_Rocket();

			//	���[�U�[����
			_Laser();
		}

		//	���f���Ƀ|�W�V���������蓖�Ă�
		MV1SetPosition(m_modelHandle, m_pos);

		//	���f���Ɋp�x�����蓖�Ă�
		MV1SetRotationXYZ(m_modelHandle, m_angle);

		//	�p�[�c�̃��f���Ƀ|�W�V�����Ɗp�x�����蓖�Ă�
		for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
		{
			//	�|�W�V�����̊��蓖��
			MV1SetPosition(m_bossPartsCore[i].m_modelHandle, m_bossPartsCore[i].m_pos);					//	�R�A
			MV1SetPosition(m_bossPartsSideBarrel[i].m_modelHandle, m_bossPartsSideBarrel[i].m_pos);		//	�T�C�h�o����
			MV1SetPosition(m_bossPartsArm[i].m_modelHandle, m_bossPartsArm[i].m_pos);					//	�A�[��

			//	�p�x�̊��蓖��
			MV1SetRotationXYZ(m_bossPartsCore[i].m_modelHandle, m_bossPartsCore[i].m_angle);				//	�R�A
			MV1SetRotationXYZ(m_bossPartsSideBarrel[i].m_modelHandle, m_bossPartsSideBarrel[i].m_angle);	//	�T�C�h�o����
			MV1SetRotationXYZ(m_bossPartsArm[i].m_modelHandle, m_bossPartsArm[i].m_angle);					//	�A�[��

			//	���[�U�[�G�t�F�N�g
			_OnEffectLaser((*m_effectLaser[i]), _soundEffect, m_bossPartsArm[i].m_pos, (BOSS_PARTS_INFO)i);

			//	���P�b�g�G�t�F�N�g
			_OnEffectRocket((*m_effectInjection[i]), _soundEffect, m_bossPartsArm[i].m_pos, (BOSS_PARTS_INFO)i);

			//	���f���̐F�ύX
			_ChangeModelColor(m_bossPartsCore[i].m_modelHandle, m_bossPartsCore[i].m_life, MAX_CORE_LIFE, m_lifeNormalColorFYellow);
			_ChangeModelColor(m_bossPartsSideBarrel[i].m_modelHandle, m_bossPartsSideBarrel[i].m_life, MAX_SIDE_BARREL_LIFE, m_lifeNormalColorFBlack);
		}

		//	�����G�t�F�N�g
		_OnEffectExplosion(_soundEffect);

		//	�����蔻��̍X�V
		_UpdateHitJudgment();
	}

	//	�p�[�c�̃��f���Ƀ|�W�V�����Ɗp�x�����蓖�Ă�
	for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
	{
		//	�q�b�g�G�t�F�N�g
		_OnHitEffect(m_bossPartsCore[i], _soundEffect, m_bossPartsCore[i].m_pos);
		_OnHitEffect(m_bossPartsSideBarrel[i], _soundEffect, m_bossPartsSideBarrel[i].m_pos);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void LastBoss::Draw()
{
	const bool isActive = m_isStart && !m_isOffDraw;
	if (isActive)
	{
		//	���f���̕`��
		MV1DrawModel(m_modelHandle);

		//	�A�[���̕`��
		if (m_isLeftCoreAlive)
		{
			MV1DrawModel(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_modelHandle);
		}
		if (m_isRightCoreAlive)
		{
			MV1DrawModel(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_modelHandle);
		}

		//	�p�[�c�̃��f���̓_�ŕ`��
		if (m_isLeftCoreAlive) { _FlashingDraw(m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_LEFT]); }
		if (m_isRightCoreAlive) { _FlashingDraw(m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT]); }
		if (m_isLeftSideBarrelAlive) { _FlashingDraw(m_bossPartsSideBarrel[BOSS_PARTS_INFO::BOSS_PARTS_LEFT]); }
		if (m_isRightSideBarrelAlive) { _FlashingDraw(m_bossPartsSideBarrel[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT]); }
	}
}

//-----------------------------------------------------------------------------
//	@brief	�R�A�̃_���[�W����
//-----------------------------------------------------------------------------
void LastBoss::OnHitCoreDamage(const int _num)
{
	const bool isNotDamage = !m_bossPartsCore[_num].m_isDamage;
	if (isNotDamage)
	{
		m_bossPartsCore[_num].m_life--;
		m_bossPartsCore[_num].m_isDamage = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�T�C�h�o�����̃_���[�W����
//-----------------------------------------------------------------------------
void LastBoss::OnHitSideBarrelDamage(const int _num)
{
	const bool isNotDamage = !m_bossPartsSideBarrel[_num].m_isDamage;
	if (isNotDamage)
	{
		m_bossPartsSideBarrel[_num].m_life--;
		m_bossPartsSideBarrel[_num].m_isDamage = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�R�A�̃_���[�W����
//-----------------------------------------------------------------------------
void LastBoss::OnHitCoreDamage(const int _num, const int _damage)
{
	const bool isNotDamage = !m_bossPartsCore[_num].m_isDamage;
	if (isNotDamage)
	{
		m_bossPartsCore[_num].m_life -= _damage;
		m_bossPartsCore[_num].m_isDamage = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�T�C�h�o�����̃_���[�W����
//-----------------------------------------------------------------------------
void LastBoss::OnHitSideBarrelDamage(const int _num, const int _damage)
{
	const bool isNotDamage = !m_bossPartsSideBarrel[_num].m_isDamage;
	if (isNotDamage)
	{
		m_bossPartsSideBarrel[_num].m_life -= _damage;
		m_bossPartsSideBarrel[_num].m_isDamage = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�j���
//-----------------------------------------------------------------------------
void LastBoss::DestructionSituation()
{
	//	�R�A�����ׂĔj�󂵂�
	const bool isAllDestruction = !m_isLeftCoreAlive && !m_isRightCoreAlive;
	if (isAllDestruction) { m_isAllDestruction = true; m_isAppearance = false; }
}

//-----------------------------------------------------------------------------
//	@brief	�p�[�c�̓����蔻��p�̉~�`�� getter
//-----------------------------------------------------------------------------
const Circle& LastBoss::GetCircle(const BOSS_PARTS_KIND _partsNum, const int _num) const
{
	//	�����蔻��̎擾
	switch (_partsNum)
	{
	case BOSS_PARTS_KIND::BOSS_PARTS_KIND_BODY:
		return m_hitCircle;
		break;

	case BOSS_PARTS_KIND::BOSS_PARTS_KIND_CORE:
		return m_bossPartsCore[_num].m_hitCircle;
		break;

	case BOSS_PARTS_KIND::BOSS_PARTS_KIND_SIDE_BARREL:
		return m_bossPartsSideBarrel[_num].m_hitCircle;
		break;

	case BOSS_PARTS_KIND::BOSS_PARTS_KIND_ARM:
		return m_bossPartsArm[_num].m_hitCircle;
		break;
	}

	return m_hitCircle;
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̃A�[���̒����`�́@getter
//-----------------------------------------------------------------------------
const Rect& LastBoss::GetArmRect(const int _num) const
{
	return  m_bossPartsArm[_num].m_hitRect;
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̃R�A�̒����`�́@getter
//-----------------------------------------------------------------------------
const Rect& LastBoss::GetCoreRect(const int _num) const
{
	return m_coreHitRect[_num];
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̃T�C�h�o�����̒����`�́@getter
//-----------------------------------------------------------------------------
const Rect& LastBoss::GetSideBarrelRect(const int _num) const
{
	return m_sideBarrelHitRect[_num];
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̃��[�U�[�̒����`�́@getter
//-----------------------------------------------------------------------------
const Rect& LastBoss::GetLaserRect(const int _num) const
{
	return m_laserHitRect[_num];
}

//-----------------------------------------------------------------------------
//	@brief	�p�[�c�̏�����
//-----------------------------------------------------------------------------
void LastBoss::_InitializeBossParts(BossParts& _bossParts, const BOSS_PARTS_INFO _bossPartsInfo, const float _hitRadius, const int _liffe)
{
	//	�p�[�c�̏�����
	_bossParts.m_pos = EMERGE_POS;											//	�|�W�V����
	_bossParts.m_dir = CommonConstant::ORIGIN;								//	����
	_bossParts.m_size = VGet(1.0f, 1.0f, 1.0f);								//	�T�C�Y
	_bossParts.m_angle = CommonConstant::ORIGIN;							//	�p�x
	_bossParts.m_life = _liffe;												//	���C�t
	_bossParts.m_hitCircle.m_radius = _hitRadius;							//	�����蔻��̔��a
	_bossParts.m_hitCircle.m_centerPoint = CommonConstant::ORIGIN;			//	�����蔻��̒��S���W
	_bossParts.m_isDamage = false;

	//	�p�[�c�̈ʒu�����Ȃ�p�x�𔽓]����
	const bool isLeft = _bossPartsInfo == BOSS_PARTS_INFO::BOSS_PARTS_LEFT;
	if (isLeft) { _bossParts.m_angle.x = CommonConstant::PI; }
}

//-----------------------------------------------------------------------------
//	@brief	�J�n���̈ړ�
//-----------------------------------------------------------------------------
void LastBoss::_EmergeMove()
{
	//	�o�����̉��o
	if (m_isEmerge)
	{
		//	�o��
		m_isAppearance = true;

		//	�o�����̉��o
		m_emergeMoveTaim++;
		const bool isEmergeMoveStart = m_emergeMoveTaim <= 5.0f;
		const bool isEmergeMove1 = m_emergeMoveTaim >= 5.0f && m_emergeMoveTaim <= 150.0f;
		const bool isEmergeMove2 = m_emergeMoveTaim >= 150.0f && m_emergeMoveTaim <= 210.0f;
		const bool isEmergeMove3 = m_emergeMoveTaim >= 210.0f && m_emergeMoveTaim <= 320.0f;
		const bool isEmergeMoveEnd = m_emergeMoveTaim == 320.0f;

		//	���o�J�n
		if (isEmergeMoveStart) 
		{
			m_pos = EMERGE_POS; 
			m_bossPartsArm[(int)BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos = EMERGE_RIGHT_ARM_POS;	//	�E�A�[��
			m_bossPartsArm[(int)BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos = EMERGE_LEFT_ARM_POS;		//	���A�[��
		}

		//	�{�̂̏o��
		if (isEmergeMove1)
		{
			//	�O�i
			m_dir = VGet(-1.0f, 0.0f, 0.0f);
			VECTOR moving = MoveHelper::AskMoveAmount(m_dir, m_moveSpeed);
			m_pos = VAdd(m_pos, moving);
		}

		//	�E�A�[���̏o��
		if (isEmergeMove2) 
		{
			const float lerpSpeed = 0.1f;
			VECTOR pos = m_bossPartsArm[(int)BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos;
			VECTOR targetPos = _AskRelativeCoordinates(m_pos, RELATIVE_ARM_POS, BOSS_PARTS_INFO::BOSS_PARTS_RIGHT);
			pos = CommonFunction::Lerp(pos, targetPos, lerpSpeed);
			m_bossPartsArm[(int)BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos = pos;
		}

		//	���A�[���̏o��
		if (isEmergeMove3)
		{
			const float lerpSpeed = 0.1f;
			VECTOR pos = m_bossPartsArm[(int)BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos;
			VECTOR targetPos = _AskRelativeCoordinates(m_pos, RELATIVE_ARM_POS, BOSS_PARTS_INFO::BOSS_PARTS_LEFT);
			pos = CommonFunction::Lerp(pos, targetPos, lerpSpeed);
			m_bossPartsArm[(int)BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos = pos;
		}

		//	���o�I��
		if (isEmergeMoveEnd)
		{
			m_pos = START_POS;
			m_angle = CommonConstant::ORIGIN;
			m_dir = CommonConstant::ORIGIN;

			for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
			{
				//	�A�[���̏�����
				m_bossPartsArm[i].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_ARM_POS, (BOSS_PARTS_INFO)i);
			}

			m_isStarted = true;
			m_isEmerge = false;
		}

		//	���΍��W�̐ݒ�
		for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
		{
			m_bossPartsCore[i].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_CORE_POS, (BOSS_PARTS_INFO)i);					//	�R�A
			m_bossPartsSideBarrel[i].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_SIDE_BARREL_POS, (BOSS_PARTS_INFO)i);		//	�T�C�h�o����
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ړ�����
//-----------------------------------------------------------------------------
void LastBoss::_Move()
{
	m_behaviorTime++;
	const bool isMovePattern1 = m_behaviorTime >= 0.0f && m_behaviorTime <= 100.0f;
	const bool isMovePattern2 = m_behaviorTime >= 200.0f && m_behaviorTime <= 300.0f;
	const bool isMovePattern3 = m_behaviorTime >= 400.0f && m_behaviorTime <= 500.0f;
	const bool isMovePattern4 = m_behaviorTime >= 600.0f && m_behaviorTime <= 700.0f;
	const bool isMovePattern5 = m_behaviorTime >= 800.0f && m_behaviorTime <= 900.0f;
	const bool isMovePattern6 = m_behaviorTime >= 1000.0f && m_behaviorTime <= 1400.0f;
	const bool isMovePattern7 = m_behaviorTime >= 1400.0f && m_behaviorTime <= 1500.0f;

	const bool isMovePattern8 = m_behaviorTime >= 1600.0f && m_behaviorTime <= 1700.0f;
	const bool isMovePattern9 = m_behaviorTime >= 1820.0f && m_behaviorTime <= 1950.0f;
	const bool isMovePattern10 = m_behaviorTime >= 1950.0f && m_behaviorTime <= 2100.0f;
	const bool isMovePattern11 = m_behaviorTime >= 2200.0f && m_behaviorTime <= 2300.0f;

	const bool isMovePattern12 = m_behaviorTime >= 2400.0f && m_behaviorTime <= 2500.0f;
	const bool isMovePattern13 = m_behaviorTime >= 2600.0f && m_behaviorTime <= 2700.0f;
	const bool isMovePattern14 = m_behaviorTime >= 2800.0f && m_behaviorTime <= 2900.0f;
	const bool isMovePattern15 = m_behaviorTime >= 3020.0f && m_behaviorTime <= 3150.0f;
	const bool isMovePattern16 = m_behaviorTime >= 3150.0f && m_behaviorTime <= 3300.0f;
	const bool isMovePattern17 = m_behaviorTime >= 3400.0f && m_behaviorTime <= 3500.0f;
	const bool isMovePattern18= m_behaviorTime >= 3600.0f && m_behaviorTime <= 3700.0f;
	if (m_behaviorTime >= 3800.0f) { m_behaviorTime = 0.0f;	m_behaviorKind = BEHAVIOR_KIND::BEHAVIOR_NONE; }

	//	���[�v���g�����ړ���
	_LerpMove(isMovePattern1, MOVE_PATTERN_3, 0.05f);
	_LerpMove(isMovePattern2, MOVE_PATTERN_2, 0.05f);
	_LerpMove(isMovePattern3, MOVE_PATTERN_1, 0.05f);
	_LerpMove(isMovePattern4, MOVE_PATTERN_2, 0.05f);
	_LerpMove(isMovePattern5, MOVE_PATTERN_1, 0.05f);
	_LerpMove(isMovePattern6, MOVE_PATTERN_4, 0.05f);
	_LerpMove(isMovePattern7, MOVE_PATTERN_3, 0.05f);

	_LerpMove(isMovePattern8, MOVE_PATTERN_5, 0.05f);
	_LerpMove(isMovePattern11, MOVE_PATTERN_3, 0.05f);

	_LerpMove(isMovePattern12, MOVE_PATTERN_2, 0.05f);
	_LerpMove(isMovePattern13, MOVE_PATTERN_1, 0.05f);
	_LerpMove(isMovePattern14, MOVE_PATTERN_6, 0.05f);

	_LerpMove(isMovePattern17, MOVE_PATTERN_1, 0.05f);
	_LerpMove(isMovePattern18, MOVE_PATTERN_2, 0.05f);

	//	���[�v���g��Ȃ��ړ�����
	if (isMovePattern9)
	{
		m_pos = VAdd(m_pos, VGet(0.0f, 0.6f, 0.0f));

		const bool isOutRange = m_pos.y >= MOVE_PATTERN_6.y;
		if(isOutRange) { m_pos.y = MOVE_PATTERN_6.y; }
	}
	if (isMovePattern10)
	{
		m_pos = VAdd(m_pos, VGet(0.0f, -0.6f, 0.0f));

		const bool isOutRange = m_pos.y <= MOVE_PATTERN_5.y;
		if (isOutRange) { m_pos.y = MOVE_PATTERN_5.y; }
	}
	if (isMovePattern15)
	{
		m_pos = VAdd(m_pos, VGet(0.0f, -0.6f, 0.0f));

		const bool isOutRange = m_pos.y <= MOVE_PATTERN_5.y;
		if (isOutRange) { m_pos.y = MOVE_PATTERN_5.y; }
	}
	if (isMovePattern16)
	{
		m_pos = VAdd(m_pos, VGet(0.0f, 0.6f, 0.0f));

		const bool isOutRange = m_pos.y >= MOVE_PATTERN_6.y;
		if (isOutRange) { m_pos.y = MOVE_PATTERN_6.y; }
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ˌ�����
//-----------------------------------------------------------------------------
void LastBoss::_Shot(ShotManager& _shot)
{
	//	�s�����Ԃ͈͓̔��ŁA�V���b�g�x�����Ȃ��Ȃ�����A
	//	�ˌ�����������
	const bool isShot1 = (m_behaviorTime == 110.0f) || (m_behaviorTime == 120.0f) || (m_behaviorTime == 130.0f);
	const bool isShot2 = (m_behaviorTime == 310.0f) || (m_behaviorTime == 320.0f) || (m_behaviorTime == 330.0f);
	const bool isShot3 = (m_behaviorTime == 510.0f) || (m_behaviorTime == 520.0f) || (m_behaviorTime == 530.0f);
	const bool isShot4 = (m_behaviorTime == 710.0f) || (m_behaviorTime == 720.0f) || (m_behaviorTime == 730.0f);
	const bool isShot5 = (m_behaviorTime == 910.0f) || (m_behaviorTime == 920.0f) || (m_behaviorTime == 930.0f);
	const bool isShot6 = (m_behaviorTime == 1140.0f) || (m_behaviorTime == 1160.0f) || (m_behaviorTime == 1180.0f) ||
						 (m_behaviorTime == 1240.0f) || (m_behaviorTime == 1260.0f) || (m_behaviorTime == 1280.0f) ||
						 (m_behaviorTime == 1340.0f) || (m_behaviorTime == 1360.0f) || (m_behaviorTime == 1380.0f);
	const bool isShot7 = (m_behaviorTime == 1510.0f) || (m_behaviorTime == 1520.0f) || (m_behaviorTime == 1530.0f);
	const bool isShot8 = (m_behaviorTime == 2110.0f) || (m_behaviorTime == 2120.0f) || (m_behaviorTime == 2130.0f);
	const bool isShot9 = (m_behaviorTime == 2310.0f) || (m_behaviorTime == 2320.0f) || (m_behaviorTime == 2330.0f);
	const bool isShot10 = (m_behaviorTime == 2510.0f) || (m_behaviorTime == 2520.0f) || (m_behaviorTime == 2530.0f);
	const bool isShot11 = (m_behaviorTime == 2710.0f) || (m_behaviorTime == 2720.0f) || (m_behaviorTime == 2730.0f);
	const bool isShot12 = (m_behaviorTime == 3310.0f) || (m_behaviorTime == 3320.0f) || (m_behaviorTime == 3330.0f);
	const bool isShot13 = (m_behaviorTime == 3510.0f) || (m_behaviorTime == 3520.0f) || (m_behaviorTime == 3530.0f);
	const bool isShot14 = (m_behaviorTime == 3710.0f) || (m_behaviorTime == 3720.0f) || (m_behaviorTime == 3730.0f);
	const bool isActiveShot = isShot1 || isShot2 || isShot3 || isShot4 || isShot5 || isShot6 || isShot7 || 
							  isShot8 || isShot9 || isShot10 || isShot11 || isShot12 || isShot13 || isShot14;
	if (isActiveShot)
	{
		//	��Ԃ����P�b�g�̂Ƃ��͖���
		const bool isIgnore = m_behaviorKind == BEHAVIOR_KIND::BEHAVIOR_ROCKET;
		if (!isIgnore)
		{
			//	��Ԃ��V���b�g�ɂ���
			m_behaviorKind = BEHAVIOR_KIND::BEHAVIOR_SHOT;
		}

		const VECTOR shotDir = VGet(-1.0f, 0.0f, 0.0f);

		//	�E�o�����������Ă���Ȃ�A
		//	�e�𐶐�����
		const bool isRightBarrelAlive = m_bossPartsSideBarrel[(int)BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_life > LIFE_ZERO;
		if (isRightBarrelAlive)
		{
			const VECTOR shotPos1 = VGet(m_pos.x - SHOT_START_POS_CORRECTION_1.x, m_pos.y + SHOT_START_POS_CORRECTION_1.y, m_pos.z);
			_shot.RegisterOnList(_shot.SHOT_KIND::ENEMY_SHOT, shotPos1, shotDir, SHOT_SPEED);

			const VECTOR shotPos2 = VGet(m_pos.x - SHOT_START_POS_CORRECTION_2.x, m_pos.y + SHOT_START_POS_CORRECTION_2.y, m_pos.z);
			_shot.RegisterOnList(_shot.SHOT_KIND::ENEMY_SHOT, shotPos2, shotDir, SHOT_SPEED);
		}

		//	���o�����������Ă���Ȃ�A
		//	�e�𐶐�����
		const bool isLeftBarrelAlive = m_bossPartsSideBarrel[(int)BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_life > LIFE_ZERO;
		if (isLeftBarrelAlive)
		{
			const VECTOR shotPos3 = VGet(m_pos.x - SHOT_START_POS_CORRECTION_2.x, m_pos.y - SHOT_START_POS_CORRECTION_2.y, m_pos.z);
			_shot.RegisterOnList(_shot.SHOT_KIND::ENEMY_SHOT, shotPos3, shotDir, SHOT_SPEED);

			const VECTOR shotPos4 = VGet(m_pos.x - SHOT_START_POS_CORRECTION_1.x, m_pos.y - SHOT_START_POS_CORRECTION_1.y, m_pos.z);
			_shot.RegisterOnList(_shot.SHOT_KIND::ENEMY_SHOT, shotPos4, shotDir, SHOT_SPEED);
		}

		//	�Z���^�[�o����
		const VECTOR shotPos5 = VGet(m_pos.x - SHOT_START_POS_CORRECTION_3.x, m_pos.y + SHOT_START_POS_CORRECTION_3.y, m_pos.z);
		_shot.RegisterOnList(_shot.SHOT_KIND::ENEMY_SHOT, shotPos5, shotDir, SHOT_SPEED);

		const VECTOR shotPos6 = VGet(m_pos.x - SHOT_START_POS_CORRECTION_3.x, m_pos.y - SHOT_START_POS_CORRECTION_3.y, m_pos.z);
		_shot.RegisterOnList(_shot.SHOT_KIND::ENEMY_SHOT, shotPos6, shotDir, SHOT_SPEED);
	}
}

//-----------------------------------------------------------------------------
//	@brief	���P�b�g����
//-----------------------------------------------------------------------------
void LastBoss::_Rocket()
{
	const bool isRocketActive1 = m_behaviorTime == 1100.0f;
	if (isRocketActive1) { m_isStartRocket = true; }

	if(m_isStartRocket)
	{
		m_rocketTime++;
		const bool isRocketStart = m_rocketTime >= 0.0f && m_rocketTime <= 60.0f;
		const bool isRocket1 = m_rocketTime >= 160.0f && m_rocketTime <= 200.0f;
		const bool isRocket2 = m_rocketTime == 200.0f;
		const bool isRocket3 = m_rocketTime >= 220.0f && m_rocketTime <= 300.0f;
		const bool isRocketEnd = m_rocketTime == 300.0f;

		if (isRocketStart)
		{
			//	��Ԃ����b�N�I���ɂ���
			m_behaviorKind = BEHAVIOR_KIND::BEHAVIOR_ROCKET;

			//	�R�A�������Ă���Ȃ�A�A�[�����J��
			if (m_isLeftCoreAlive) { _LerpRelativeCoordinates(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT], BOSS_PARTS_INFO::BOSS_PARTS_LEFT, OPEN_RELATIVE_ARM_POS); }
			if (m_isRightCoreAlive) { _LerpRelativeCoordinates(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT], BOSS_PARTS_INFO::BOSS_PARTS_RIGHT, OPEN_RELATIVE_ARM_POS); }

			//	�p�b�h�̐U���@�\
			const int vibrationPower = 500;
			PadInfo::Function::VibrationFunction(PadInfo::PAD_KIND::PAD_1, vibrationPower);
		}
		if (isRocket1)
		{
			//	�p�b�h�̐U���@�\�̏I��
			PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);
			
			//	�ړ�����
			const float speed = 5.0f;
			VECTOR velocity = VScale(VGet(-1.0f, 0.0f, 0.0f), speed);
			if (m_isLeftCoreAlive) { m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos = VAdd(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos, velocity); }
			if (m_isRightCoreAlive) { m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos = VAdd(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos, velocity); }

			//	�p�b�h�̐U���@�\
			PadInfo::Function::VibrationFunction(PadInfo::PAD_KIND::PAD_1);
		}
		if (isRocket2)
		{
			if (m_isLeftCoreAlive) { m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos = EMERGE_LEFT_ARM_POS;}
			if (m_isRightCoreAlive) { m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos = EMERGE_RIGHT_ARM_POS;}
		}
		if (isRocket3)
		{
			//	�{�X�ɂ�������
			_LerpRelativeCoordinates(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT], BOSS_PARTS_INFO::BOSS_PARTS_LEFT, RELATIVE_ARM_POS);
			_LerpRelativeCoordinates(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT], BOSS_PARTS_INFO::BOSS_PARTS_RIGHT, RELATIVE_ARM_POS);

			//	�p�b�h�̐U���@�\�̏I��
			PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);
		}
		if (isRocketEnd)
		{
			//	������
			m_rocketTime = 0.0f;
			m_behaviorKind = BEHAVIOR_KIND::BEHAVIOR_NONE;
			m_isStartRocket = false;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	���[�U�[����
//-----------------------------------------------------------------------------
void LastBoss::_Laser()
{
	const bool isLaserActive1 = m_behaviorTime == 1700.0f;
	const bool isLaserActive2 = m_behaviorTime == 2900.0f;
	const bool isLaserActive = isLaserActive1 || isLaserActive2;
	if (isLaserActive) { m_isStartLaser = true; }

	if (m_isStartLaser)
	{
		m_laserTime++;
		const bool isLaserStart = m_laserTime >= 0.0f && m_laserTime <= 60.0f;
		const bool isLaser1 = m_laserTime == 130.0f;
		const bool isLaser2 = m_laserTime == 370.0f;
		const bool isLaser3 = m_laserTime >= 380.0f && m_laserTime <= 400.0f;
		const bool isLaserEnd = m_laserTime == 400.0f;

		if (isLaserStart)
		{
			//	��Ԃ����[�U�[�ɂ���
			m_behaviorKind = BEHAVIOR_KIND::BEHAVIOR_LASER;
			m_laser.m_vertexTop = CommonConstant::ORIGIN;
			m_laser.m_vertexUnder = CommonConstant::ORIGIN;

			//	�R�A�������Ă���Ȃ�A�A�[������]
			if (m_isLeftCoreAlive) { _ArmRota(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT], CommonConstant::PI); }
			if (m_isRightCoreAlive) { _ArmRota(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT], CommonConstant::PI); }

			//	�p�b�h�̐U���@�\
			const int vibrationPower = 500;
			PadInfo::Function::VibrationFunction(PadInfo::PAD_KIND::PAD_1, vibrationPower);
		}
		if (isLaser1)
		{
			//	�p�b�h�̐U���@�\�̏I��
			PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);

			m_laser.m_vertexTop.x = LASER_LENGTH;

			//	�p�b�h�̐U���@�\
			PadInfo::Function::VibrationFunction(PadInfo::PAD_KIND::PAD_1);
		}
		if (isLaser2)
		{
			m_laser.m_vertexTop = CommonConstant::ORIGIN;

			//	�p�b�h�̐U���@�\�̏I��
			PadInfo::Function::EndVibrationFunction(PadInfo::PAD_KIND::PAD_1);

		}
		if (isLaser3)
		{
			//	�A�[������]
			_ArmRota(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT], 0.0f);
			_ArmRota(m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT], 0.0f);
		}
		if (isLaserEnd)
		{
			m_behaviorKind = BEHAVIOR_KIND::BEHAVIOR_NONE;
			m_laserTime = 0.0f;
			m_isStartLaser = false;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�p�[�c�̏�
//-----------------------------------------------------------------------------
void LastBoss::_PartsSituation()
{
	//	�R�A�������Ă���Ԃ́Atrue
	m_isLeftCoreAlive = m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_life > LIFE_ZERO;
	m_isRightCoreAlive = m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_life > LIFE_ZERO;

	//	�T�C�h�o�����������Ă���Ԃ́Atrue
	m_isLeftSideBarrelAlive = m_bossPartsSideBarrel[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_life > LIFE_ZERO;
	m_isRightSideBarrelAlive = m_bossPartsSideBarrel[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_life > LIFE_ZERO;
}

//-----------------------------------------------------------------------------
//	@brief	�A�[���̉�]
//-----------------------------------------------------------------------------
void LastBoss::_ArmRota(BossParts& _bossParts, const float _targetAngle)
{
	const float lerpSpeed = 0.2f;
	VECTOR angle = _bossParts.m_angle;
	angle.y = CommonFunction::Lerp(angle.y, _targetAngle, lerpSpeed);
	_bossParts.m_angle = angle;
}

//-----------------------------------------------------------------------------
//	@brief	���[�v���g�������΍��W
//-----------------------------------------------------------------------------
void LastBoss::_LerpRelativeCoordinates(BossParts& _bossParts, const BOSS_PARTS_INFO _bossInfo, const VECTOR _target)
{
	const float lerpSpeed = 0.1f;
	VECTOR pos = _bossParts.m_pos;
	VECTOR targetPos = _AskRelativeCoordinates(m_pos, _target, _bossInfo);
	pos = CommonFunction::Lerp(pos, targetPos, lerpSpeed);
	_bossParts.m_pos = pos;
}

//-----------------------------------------------------------------------------
//	@brief	���`�ۊǂ��g�����ړ�����
//-----------------------------------------------------------------------------
void LastBoss::_LerpMove(bool _isConditions, VECTOR _targetPos, float _lerpSpeed)
{
	if (_isConditions) { m_pos = CommonFunction::Lerp(m_pos, _targetPos, _lerpSpeed); }
}

//-----------------------------------------------------------------------------
//	@brief	�q�b�g�G�t�F�N�g
//-----------------------------------------------------------------------------
void LastBoss::_OnHitEffect(BossParts& _bossParts, SoundEffect& _soundEffect, const VECTOR _pos)
{
	//	�_���[�W���������Ƃ�
	if (_bossParts.m_isDamage)
	{
		const bool isHitStart = m_effectHit->GetPlayTime() == 0.0f;
		const bool isHitEnd = m_effectHit->GetPlayTime() == 18.0f;

		m_effectHit->SetPos(_pos);

		if (isHitStart)
		{
			m_effectHit->SetPlaySpeed(2.0f);

			if (PRODUCTION->GetIsSpecialProduction()) { m_effectHit->SetScale(VGet(30.0f, 30.0f, 30.0f)); }
			else { m_effectHit->SetScale(VGet(15.0f, 15.0f, 15.0f)); }

			m_effectHit->OnPlayEffect();
			_soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_HIT);
		}
		if (isHitEnd)
		{
			m_effectHit->OnEndEffect();
			_bossParts.m_isDamage = false;
			return;
		}

		m_effectHit->AddPlayTime();
		m_effectHit->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����G�t�F�N�g
//-----------------------------------------------------------------------------
void LastBoss::_OnEffectExplosion(SoundEffect& _soundEffect)
{
	const bool isLeftSideBarrelExplosion = !m_isLeftSideBarrelAlive && !m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_LEFT_BARREL];
	const bool isRightSideBarrelExplosion = !m_isRightSideBarrelAlive && !m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_RIGHT_BARREL];
	const bool isLeftCoreExplosion = !m_isLeftCoreAlive && !m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_LEFT_CORE];
	const bool isRightCoreExplosion = !m_isRightCoreAlive && !m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_RIGHT_CORE];
	const bool isLastExplosion = !m_isLeftCoreAlive && !m_isRightCoreAlive;

	const int right = 0;
	const int left = 1;
	_OneEffectExplosion(isLeftSideBarrelExplosion, (*m_effectExplosion[0]), _soundEffect, m_bossPartsSideBarrel[left].m_pos, m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_LEFT_BARREL]);
	_OneEffectExplosion(isRightSideBarrelExplosion, (*m_effectExplosion[1]), _soundEffect, m_bossPartsSideBarrel[right].m_pos, m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_RIGHT_BARREL]);
	_OneEffectExplosion(isLeftCoreExplosion, (*m_effectExplosion[2]), _soundEffect, m_bossPartsCore[left].m_pos, m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_LEFT_CORE]);
	_OneEffectExplosion(isRightCoreExplosion, (*m_effectExplosion[3]), _soundEffect, m_bossPartsCore[right].m_pos, m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_RIGHT_CORE]);
	_LastEffectExplosion(isLastExplosion, _soundEffect);
}

//-----------------------------------------------------------------------------
//	@brief	�����G�t�F�N�g���
//-----------------------------------------------------------------------------
void LastBoss::_OneEffectExplosion(const bool _isConditions, EffekseerEmitter& _effect, SoundEffect& _soundEffect, const VECTOR _pos, bool& _isUsedFlag)
{
	if (_isConditions)
	{
		const bool isExplosionStart = _effect.GetPlayTime() == 0.0f;
		const bool isExplosion1 = _effect.GetPlayTime() == 50.0f;
		const bool isExplosionEnd = _effect.GetPlayTime() == 100.0f;

		//	�|�W�V�����͏�ɒǂ�
		_effect.SetPos(_pos);

		//	�����G�t�F�N�g�̊J�n
		if (isExplosionStart)
		{
			_effect.SetPlaySpeed(3.0f);
			_effect.SetScale(VGet(2.0f, 8.0f, 2.0f));
			_effect.OnPlayEffect();
		}

		if (isExplosion1)
		{
			_soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_EXPLOSION);
		}

		//	�����G�t�F�N�g�̏I��
		if (isExplosionEnd)
		{
			_effect.OnEndEffect();
			_isUsedFlag = true;
			return;
		}

		_effect.AddPlayTime();
		_effect.Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�����G�t�F�N�g
//-----------------------------------------------------------------------------
void LastBoss::_LastEffectExplosion(const bool _isConditions, SoundEffect& _soundEffect)
{
	if (_isConditions)
	{
		const bool isRandamExplosion = m_effectLastExplosion->GetPlayTime() < 150.0f;
		if (isRandamExplosion)
		{
			//	�����ŃG�t�F�N�g���o��������
			const bool isActive = CommonFunction::GetRand(0, 5) == 0;
			if (isActive)
			{
				for (int i = 0; i < CommonConstant::MAX_BOSS_EXPLOSION_NUM; i++)
				{
					//	�܂��Đ����Ă��Ȃ����
					const bool isNotPlay = !m_effectExplosion[i]->GetIsStartEffect();
					if (isNotPlay) { m_effectExplosion[i]->SetIsStartEffect(true); break; }
				}
			}

			//	�����_���Ȉʒu�ɔ��j�G�t�F�N�g���o��
			for (int i = 0; i < CommonConstant::MAX_BOSS_EXPLOSION_NUM; i++)
			{
				_RandamEffectExplosion((*m_effectExplosion[i]), _soundEffect);
			}
		}

		//	�ŏI�I�Ȕ����G�t�F�N�g
		m_effectLastExplosion->SetPos(m_pos);

		//	�ŏI�I�Ȕ��������G�t�F�N�g�̊J�n
		const bool isLastExplosionStart = m_effectLastExplosion->GetPlayTime() == 150.0f;
		if (isLastExplosionStart)
		{
			m_effectLastExplosion->SetScale(VGet(5.0f, 10.0f, 5.0f));
			m_effectLastExplosion->SetPlaySpeed(1.5f);
			m_effectLastExplosion->OnPlayEffect();
		}

		const bool isLastExplosion1 = m_effectLastExplosion->GetPlayTime() == 230.0f;
		if (isLastExplosion1) { _soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_EXPLOSION); }

		//	�ŏI�I�Ȕ��������G�t�F�N�g�̏I��
		const bool isLastExplosion2 = m_effectLastExplosion->GetPlayTime() == 250.0f;
		if(isLastExplosion2) { m_isOffDraw = true; }

		//	�N���A���̉��o�J�n
		const bool isClear = m_effectLastExplosion->GetPlayTime() == 300.0f;
		if (isClear) { PRODUCTION->SetIsClearProduction(true); }

		m_effectLastExplosion->AddPlayTime();
		m_effectLastExplosion->Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����_�������G�t�F�N�g
//-----------------------------------------------------------------------------
void LastBoss::_RandamEffectExplosion(EffekseerEmitter& _effect, SoundEffect& _soundEffect)
{
	const bool isStart = _effect.GetIsStartEffect();
	if (isStart)
	{
		const bool isExplosionStart = _effect.GetPlayTime() == 0.0f;
		const bool isExplosion = _effect.GetPlayTime() == 50.0f;
		const bool isExplosionEnd = _effect.GetPlayTime() == 100.0f;

		if (isExplosionStart)
		{
			VECTOR minPos = VSub(m_pos, BOSS_RADIUS);
			VECTOR maxPos = VAdd(m_pos, BOSS_RADIUS);
			VECTOR pos = CommonFunction::GetRand(minPos, maxPos);

			VECTOR minScale = VGet(2.0f, 4.0f, 2.0f);
			VECTOR maxScale = VGet(4.0f, 8.0f, 4.0f);
			VECTOR scale = CommonFunction::GetRand(minScale, maxScale);

			_effect.SetPos(pos);
			_effect.SetScale(scale);
			_effect.SetPlaySpeed(3.0f);
			_effect.OnPlayEffect();
		}

		if (isExplosion) { _soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_EXPLOSION); }

		//	�����G�t�F�N�g�̏I��
		if (isExplosionEnd)
		{
			_effect.OnEndEffect();
			return;
		}

		_effect.AddPlayTime();
		_effect.Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	���[�U�[�G�t�F�N�g
//-----------------------------------------------------------------------------
void LastBoss::_OnEffectLaser(EffekseerEmitter& _effect, SoundEffect& _soundEffect, const VECTOR _startPos, const BOSS_PARTS_INFO _partsInfo)
{
	//	���[�U�[�G�t�F�N�g
	if(m_isStartLaser)
	{
		//	�G�t�F�N�g�̎���
		static const float startTime = 0.0f;
		static const float endTime = 400.0f;

		//	���̃R�A���j�󂳂ꂽ
		const bool isLeftCoreAlive = !m_isLeftCoreAlive && _partsInfo == BOSS_PARTS_INFO::BOSS_PARTS_LEFT;
		if (isLeftCoreAlive) { _effect.SetPlayTime(endTime); }

		//	�E�̃R�A���j�󂳂ꂽ
		const bool isRightCoreAlive = !m_isRightCoreAlive && _partsInfo == BOSS_PARTS_INFO::BOSS_PARTS_RIGHT;
		if (isRightCoreAlive) { _effect.SetPlayTime(endTime); }

		const bool isLaserStart = _effect.GetPlayTime() == startTime;
		const bool isLaserEnd = _effect.GetPlayTime() == 400.0f;
		
		//	�|�W�V�����̍X�V
		_effect.SetPos(VGet(_startPos.x + LASER_EFFECT_CORRECTION, _startPos.y, _startPos.z));

		//	���[�U�[�G�t�F�N�g�̊J�n
		if (isLaserStart)
		{
			_effect.SetPlaySpeed(1.2f);
			_effect.SetScale(VGet(3.0f, 3.0f, 10.0f));
			_effect.SetAngle(VGet(0.0f, 90.0f, 0.0f));
			_effect.OnPlayEffect();
			_soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_ENEMY_LASER);
		}

		//	���[�U�[�G�t�F�N�g�̏I��
		if (isLaserEnd)
		{
			_effect.OnEndEffect();
			return;
		}

		_effect.AddPlayTime();
		_effect.Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	���P�b�g�G�t�F�N�g
//-----------------------------------------------------------------------------
void LastBoss::_OnEffectRocket(EffekseerEmitter& _effect, SoundEffect& _soundEffect, const VECTOR _startPos, const BOSS_PARTS_INFO _partsInfo)
{
	//	�G�t�F�N�g�̊J�n
	const bool isRocketActive = m_behaviorTime == 1000.0f;
	if (isRocketActive) { _effect.SetIsStartEffect(true); }

	const bool isStart = _effect.GetIsStartEffect();
	if (isStart)
	{
		//	�G�t�F�N�g�̎���
		static const float startTime = 100.0f;
		static const float endTime = 300.0f;

		//	���̃R�A���j�󂳂ꂽ
		const bool isLeftCoreAlive = !m_isLeftCoreAlive && _partsInfo == BOSS_PARTS_INFO::BOSS_PARTS_LEFT;
		if (isLeftCoreAlive) { _effect.SetPlayTime(endTime); }

		//	�E�̃R�A���j�󂳂ꂽ
		const bool isRightCoreAlive = !m_isRightCoreAlive && _partsInfo == BOSS_PARTS_INFO::BOSS_PARTS_RIGHT;
		if (isRightCoreAlive) { _effect.SetPlayTime(endTime); }

		//	�G�t�F�N�g�̊J�n
		const bool isRocketStart = _effect.GetPlayTime() == startTime;
		const bool isRocketEnd = _effect.GetPlayTime() == endTime;

		//	�|�W�V�����̍X�V
		_effect.SetPos(VGet(_startPos.x + ROCKET_EFFECT_CORRECTION, _startPos.y, _startPos.z));

		//	���[�U�[�G�t�F�N�g�̊J�n
		if (isRocketStart)
		{
			_effect.SetScale(VGet(5.0f, 5.0f, 5.0f));
			_effect.OnPlayEffect();
			_soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_ROCKET);
		}

		//	���[�U�[�G�t�F�N�g�̏I��
		if (isRocketEnd)
		{
			_effect.OnEndEffect();
			return;
		}

		_effect.AddPlayTime();
		_effect.Update();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����蔻��p�̓_�̍X�V
//-----------------------------------------------------------------------------
void LastBoss::_UpdateHitJudgment()
{
	//	�A�[���̓����蔻��p�̍X�V
	_UpdateHitArm();

	//	�R�A�̓����蔻��p�̍X�V
	_UpdateHitCore();

	//	�T�C�h�o�����̓����蔻��p�̍X�V
	_UpdateHitSideBarrel();

	//	���[�U�[�̓����蔻��p�̍X�V
	_UpdateHitLaser();

	//	�{�f�B�[�̓����蔻��p�̍X�V
	_UpdateHitBody();

	//	�Z���^�[�o�����̓����蔻��p�̍X�V
	_UpdateHitCenterBarrel();
}

//-----------------------------------------------------------------------------
//	@brief	�A�[���̓����蔻��p�̍X�V
//-----------------------------------------------------------------------------
void LastBoss::_UpdateHitArm()
{
	const int left = BOSS_PARTS_INFO::BOSS_PARTS_LEFT;
	const int right = BOSS_PARTS_INFO::BOSS_PARTS_RIGHT;

	//	���A�[���̉~�̓_�̍X�V
	m_bossPartsArm[left].m_hitCircle.m_centerPoint =
	VGet(
			m_bossPartsArm[left].m_pos.x + ADJUSTMENT_ARM_CIRCLE_POS.x,
			m_bossPartsArm[left].m_pos.y + ADJUSTMENT_ARM_CIRCLE_POS.y,
			m_bossPartsArm[left].m_pos.z
		);

	//	���A�[���̉~�̃T�C�Y�̍X�V
	m_bossPartsArm[left].m_hitCircle.m_radius = HIT_ARM_RADIUS;

	//	�E�A�[���̉~�̓_�̍X�V
	m_bossPartsArm[right].m_hitCircle.m_centerPoint =
	VGet(
		m_bossPartsArm[right].m_pos.x + ADJUSTMENT_ARM_CIRCLE_POS.x,
		m_bossPartsArm[right].m_pos.y - ADJUSTMENT_ARM_CIRCLE_POS.y,
		m_bossPartsArm[right].m_pos.z
	);

	//	���A�[���̉~�̃T�C�Y�̍X�V
	m_bossPartsArm[right].m_hitCircle.m_radius = HIT_ARM_RADIUS;


//-----------------------------------------------------------------------------//

	//	���A�[���̒����`�̒��_�P�̍X�V
	m_bossPartsArm[left].m_hitRect.m_vertexTop =
	VGet(
		m_bossPartsArm[left].m_pos.x - ADJUSTMENT_ARM_RECT_POS.x + ARM_CORRECTION.x,
		m_bossPartsArm[left].m_pos.y - ADJUSTMENT_ARM_RECT_POS.y + ARM_CORRECTION.y,
		m_bossPartsArm[left].m_pos.z - ADJUSTMENT_ARM_RECT_POS.z
	);

	//	���A�[���̒����`�̒��_�Q�̍X�V
	m_bossPartsArm[left].m_hitRect.m_vertexUnder =
	VGet(
		m_bossPartsArm[left].m_pos.x + ADJUSTMENT_ARM_RECT_POS.x + ARM_CORRECTION.x,
		m_bossPartsArm[left].m_pos.y + ADJUSTMENT_ARM_RECT_POS.y + ARM_CORRECTION.y,
		m_bossPartsArm[left].m_pos.z + ADJUSTMENT_ARM_RECT_POS.z
	);

	//	�E�A�[���̒����`�̒��_�P�̍X�V
	m_bossPartsArm[right].m_hitRect.m_vertexTop =
	VGet(
		m_bossPartsArm[right].m_pos.x - ADJUSTMENT_ARM_RECT_POS.x + ARM_CORRECTION.x,
		m_bossPartsArm[right].m_pos.y - ADJUSTMENT_ARM_RECT_POS.y - ARM_CORRECTION.y,
		m_bossPartsArm[right].m_pos.z - ADJUSTMENT_ARM_RECT_POS.z
	);

	//	�E�A�[���̒����`�̒��_�Q�̍X�V
	m_bossPartsArm[right].m_hitRect.m_vertexUnder =
	VGet(
		m_bossPartsArm[right].m_pos.x + ADJUSTMENT_ARM_RECT_POS.x + ARM_CORRECTION.x,
		m_bossPartsArm[right].m_pos.y + ADJUSTMENT_ARM_RECT_POS.y - ARM_CORRECTION.y,
		m_bossPartsArm[right].m_pos.z + ADJUSTMENT_ARM_RECT_POS.z
	);

}

//-----------------------------------------------------------------------------
//	@brief	�R�A�̓����蔻��p�̍X�V
//-----------------------------------------------------------------------------
void LastBoss::_UpdateHitCore()
{
	const int left = BOSS_PARTS_INFO::BOSS_PARTS_LEFT;
	const int right = BOSS_PARTS_INFO::BOSS_PARTS_RIGHT;

	//	���R�A�̉~�̓_�̍X�V
	m_bossPartsCore[left].m_hitCircle.m_centerPoint = m_bossPartsCore[left].m_pos;

	//	���R�A�̉~�̃T�C�Y�̍X�V
	m_bossPartsCore[left].m_hitCircle.m_radius = HIT_CORE_RADIUS;

	//	�E�R�A�̉~�̓_�̍X�V
	m_bossPartsCore[right].m_hitCircle.m_centerPoint = m_bossPartsCore[right].m_pos;

	//	���R�A�̉~�̃T�C�Y�̍X�V
	m_bossPartsCore[right].m_hitCircle.m_radius = HIT_CORE_RADIUS;


//-----------------------------------------------------------------------------//

	//	���R�A�̒����`�̒��_�P�̍X�V
	m_coreHitRect[left].m_vertexTop =
	VGet(
		m_bossPartsSideBarrel[left].m_pos.x + HIT_CORE_RADIUS,
		m_bossPartsSideBarrel[left].m_pos.y + HIT_CORE_RADIUS,
		m_bossPartsSideBarrel[left].m_pos.z + HIT_CORE_RADIUS
	);

	//	���R�A�̒����`�̒��_�Q�̍X�V
	m_coreHitRect[left].m_vertexUnder = 
	VGet(
		m_bossPartsSideBarrel[left].m_pos.x - HIT_CORE_RADIUS,
		m_bossPartsSideBarrel[left].m_pos.y - HIT_CORE_RADIUS,
		m_bossPartsSideBarrel[left].m_pos.z - HIT_CORE_RADIUS
	);

	//	�E�R�A�̒����`�̒��_�P�̍X�V
	m_coreHitRect[right].m_vertexTop = 
	VGet(
		m_bossPartsSideBarrel[right].m_pos.x + HIT_CORE_RADIUS,
		m_bossPartsSideBarrel[right].m_pos.y + HIT_CORE_RADIUS,
		m_bossPartsSideBarrel[right].m_pos.z + HIT_CORE_RADIUS
	);

	//	�E�R�A�̒����`�̒��_�Q�̍X�V
	m_coreHitRect[right].m_vertexUnder = 
	VGet(
		m_bossPartsSideBarrel[right].m_pos.x - HIT_CORE_RADIUS,
		m_bossPartsSideBarrel[right].m_pos.y - HIT_CORE_RADIUS,
		m_bossPartsSideBarrel[right].m_pos.z - HIT_CORE_RADIUS
	);
}

//-----------------------------------------------------------------------------
//	@brief	�T�C�h�o�����̓����蔻��p�̍X�V
//-----------------------------------------------------------------------------
void LastBoss::_UpdateHitSideBarrel()
{
	const int left = BOSS_PARTS_INFO::BOSS_PARTS_LEFT;
	const int right = BOSS_PARTS_INFO::BOSS_PARTS_RIGHT;

	//	���T�C�h�o�����̉~�̓_�̍X�V
	m_bossPartsSideBarrel[left].m_hitCircle.m_centerPoint =
	VGet(
		m_bossPartsSideBarrel[left].m_pos.x + ADJUSTMENT_SIDE_BARREL_POS.x,
		m_bossPartsSideBarrel[left].m_pos.y + ADJUSTMENT_SIDE_BARREL_POS.y,
		m_bossPartsSideBarrel[left].m_pos.z
	);

	//	���T�C�h�o�����̉~�̃T�C�Y�̍X�V
	m_bossPartsSideBarrel[left].m_hitCircle.m_radius = HIT_SIDE_BARREL_RADIUS;

	//	�E�T�C�h�o�����̉~�̓_�̍X�V
	m_bossPartsSideBarrel[right].m_hitCircle.m_centerPoint =
	VGet(
		m_bossPartsSideBarrel[right].m_pos.x + ADJUSTMENT_SIDE_BARREL_POS.x,
		m_bossPartsSideBarrel[right].m_pos.y - ADJUSTMENT_SIDE_BARREL_POS.y,
		m_bossPartsSideBarrel[right].m_pos.z
	);

	//	���T�C�h�o�����̉~�̃T�C�Y�̍X�V
	m_bossPartsSideBarrel[right].m_hitCircle.m_radius = HIT_SIDE_BARREL_RADIUS;

//-----------------------------------------------------------------------------//

	//	���T�C�h�o�����̒����`�̒��_�P�̍X�V
	m_sideBarrelHitRect[left].m_vertexTop =
	VGet(
		m_bossPartsSideBarrel[left].m_pos.x + ADJUSTMENT_SIDE_BARREL_POS.x + HIT_SIDE_BARREL_RADIUS,
		m_bossPartsSideBarrel[left].m_pos.y + ADJUSTMENT_SIDE_BARREL_POS.y + HIT_SIDE_BARREL_RADIUS,
		m_bossPartsSideBarrel[left].m_pos.z + HIT_SIDE_BARREL_RADIUS
	);

	//	���T�C�h�o�����̒����`�̒��_�Q�̍X�V
	m_sideBarrelHitRect[left].m_vertexUnder = 
	VGet(
		m_bossPartsSideBarrel[left].m_pos.x + ADJUSTMENT_SIDE_BARREL_POS.x - HIT_SIDE_BARREL_RADIUS,
		m_bossPartsSideBarrel[left].m_pos.y - ADJUSTMENT_SIDE_BARREL_POS.y - HIT_SIDE_BARREL_RADIUS,
		m_bossPartsSideBarrel[left].m_pos.z - HIT_SIDE_BARREL_RADIUS
	);

	//	�E�T�C�h�o�����̒����`�̒��_�P�̍X�V
	m_sideBarrelHitRect[right].m_vertexTop = 
	VGet(
		m_bossPartsSideBarrel[right].m_pos.x + ADJUSTMENT_SIDE_BARREL_POS.x + HIT_SIDE_BARREL_RADIUS,
		m_bossPartsSideBarrel[right].m_pos.y + ADJUSTMENT_SIDE_BARREL_POS.y + HIT_SIDE_BARREL_RADIUS,
		m_bossPartsSideBarrel[right].m_pos.z + HIT_SIDE_BARREL_RADIUS
	);

	//	�E�T�C�h�o�����̒����`�̒��_�Q�̍X�V
	m_sideBarrelHitRect[right].m_vertexUnder = 
	VGet(
		m_bossPartsSideBarrel[right].m_pos.x + ADJUSTMENT_SIDE_BARREL_POS.x - HIT_SIDE_BARREL_RADIUS,
		m_bossPartsSideBarrel[right].m_pos.y - ADJUSTMENT_SIDE_BARREL_POS.y - HIT_SIDE_BARREL_RADIUS,
		m_bossPartsSideBarrel[right].m_pos.z - HIT_SIDE_BARREL_RADIUS
	);
}

//-----------------------------------------------------------------------------
//	@brief	���[�U�[�̓����蔻��p�̍X�V
//-----------------------------------------------------------------------------
void LastBoss::_UpdateHitLaser()
{
	const int left = BOSS_PARTS_INFO::BOSS_PARTS_LEFT;
	const int right = BOSS_PARTS_INFO::BOSS_PARTS_RIGHT;

	//	�����[�U�[�̒����`�̒��_�P�̍X�V
	m_laserHitRect[left].m_vertexTop =
	VGet(
		m_bossPartsArm[left].m_pos.x + ADJUSTMENT_LASER_POS.x + m_laser.m_vertexTop.x,
		m_bossPartsArm[left].m_pos.y - ADJUSTMENT_LASER_POS.y,
		m_bossPartsArm[left].m_pos.z - ADJUSTMENT_LASER_POS.z
	);

	//	�����[�U�[�̒����`�̒��_�Q�̍X�V
	m_laserHitRect[left].m_vertexUnder =
	VGet(
		m_bossPartsArm[left].m_pos.x + ADJUSTMENT_LASER_POS.x + m_laser.m_vertexUnder.x,
		m_bossPartsArm[left].m_pos.y + ADJUSTMENT_LASER_POS.y,
		m_bossPartsArm[left].m_pos.z + ADJUSTMENT_LASER_POS.z
	);

	//	�E���[�U�[�̒����`�̒��_�P�̍X�V
	m_laserHitRect[right].m_vertexTop =
	VGet(
		m_bossPartsArm[right].m_pos.x + ADJUSTMENT_LASER_POS.x + m_laser.m_vertexTop.x,
		m_bossPartsArm[right].m_pos.y - ADJUSTMENT_LASER_POS.y,
		m_bossPartsArm[right].m_pos.z - ADJUSTMENT_LASER_POS.z
	);

	//	�E���[�U�[�̒����`�̒��_�Q�̍X�V
	m_laserHitRect[right].m_vertexUnder =
	VGet(
		m_bossPartsArm[right].m_pos.x + ADJUSTMENT_LASER_POS.x + m_laser.m_vertexUnder.x,
		m_bossPartsArm[right].m_pos.y + ADJUSTMENT_LASER_POS.y,
		m_bossPartsArm[right].m_pos.z + ADJUSTMENT_LASER_POS.z
	);
}

//-----------------------------------------------------------------------------
//	@brief		�{�f�B�[�̓����蔻��p�̍X�V
//-----------------------------------------------------------------------------
void LastBoss::_UpdateHitBody()
{
	//	�{�f�B�[�̉~�̓_�̍X�V
	m_hitCircle.m_centerPoint = VGet(m_pos.x + ADJUSTMENT_BODY_POS.x, m_pos.y, m_pos.z);
	
	//	�{�f�B�[�̉~�̃T�C�Y�̍X�V
	m_hitCircle.m_radius = HIT_BODY_RADIUS;
}

//-----------------------------------------------------------------------------
//	@brief	�Z���^�[�o�����̓����蔻��p�̍X�V
//-----------------------------------------------------------------------------
void LastBoss::_UpdateHitCenterBarrel()
{
	//	�Z���^�[�o�����̒����`�̒��_�P�̍X�V
	m_centerBarrel.m_vertexTop =
	VGet(
		m_pos.x - ADJUSTMENT_CENTER_BARRE_POS.x - CENTER_BARRE_CORRECTION.x,
		m_pos.y - ADJUSTMENT_CENTER_BARRE_POS.y,
		m_pos.z - ADJUSTMENT_CENTER_BARRE_POS.z
	);

	//	�Z���^�[�o�����̒����`�̒��_�Q�̍X�V
	m_centerBarrel.m_vertexUnder =
	VGet(
		m_pos.x + ADJUSTMENT_CENTER_BARRE_POS.x - CENTER_BARRE_CORRECTION.x,
		m_pos.y + ADJUSTMENT_CENTER_BARRE_POS.y,
		m_pos.z + ADJUSTMENT_CENTER_BARRE_POS.z
	);
}

//-----------------------------------------------------------------------------
//	@brief	���΍��W�����蓖�Ă�
//-----------------------------------------------------------------------------
void LastBoss::_AllocationRelativeCoordinates()
{
	//	�E�o�����������Ă���Ȃ�A
	//	�{�X�ɂ�������
	if (m_isRightSideBarrelAlive) { m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_CORE_POS, BOSS_PARTS_INFO::BOSS_PARTS_RIGHT); }
	else { m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos = _AskRelativeCoordinates(m_pos, OPEN_RELATIVE_CORE_POS, BOSS_PARTS_INFO::BOSS_PARTS_RIGHT); }

	//	���o�����������Ă���Ȃ�A
	//	�{�X�ɂ�������
	if (m_isLeftSideBarrelAlive) { m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_CORE_POS, BOSS_PARTS_INFO::BOSS_PARTS_LEFT); }
	else { m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos = _AskRelativeCoordinates(m_pos, OPEN_RELATIVE_CORE_POS, BOSS_PARTS_INFO::BOSS_PARTS_LEFT); }

	m_bossPartsSideBarrel[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_SIDE_BARREL_POS, BOSS_PARTS_INFO::BOSS_PARTS_RIGHT);
	m_bossPartsSideBarrel[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_SIDE_BARREL_POS, BOSS_PARTS_INFO::BOSS_PARTS_LEFT);

	const bool isActive = m_behaviorKind != BEHAVIOR_KIND::BEHAVIOR_ROCKET;
	if (isActive)
	{
		m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_RIGHT].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_ARM_POS, BOSS_PARTS_INFO::BOSS_PARTS_RIGHT);
		m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_LEFT].m_pos = _AskRelativeCoordinates(m_pos, RELATIVE_ARM_POS, BOSS_PARTS_INFO::BOSS_PARTS_LEFT);
	}
}

//-----------------------------------------------------------------------------
//	@brief	���΍��W�����蓖�Ă�
//-----------------------------------------------------------------------------
VECTOR LastBoss::_AskRelativeCoordinates(const VECTOR _basePos, const VECTOR _relativePos, const BOSS_PARTS_INFO _bossPartsInfo)
{
	VECTOR tmpPos;

	tmpPos = VAdd(_basePos, _relativePos);

	//	�p�[�c�̈ʒu�����Ȃ炙���̂ݔ��]����
	const bool isLeft = _bossPartsInfo == BOSS_PARTS_INFO::BOSS_PARTS_LEFT;
	if (isLeft) { tmpPos.y = _basePos.y - _relativePos.y; }

	return tmpPos;
}

//-----------------------------------------------------------------------------
//	@brief	���f���̐F��ύX����
//-----------------------------------------------------------------------------
void LastBoss::_ChangeModelColor(const int _modelHandle, const int _life, const int _maxLife, const ColorF _normalColor)
{
	const int midleLife = _maxLife / 2;
	const int dangerLife = _maxLife / 5;

	//	���C�t�͒��Ԃ��傫���̂ŁA
	//	���f���̐F�̓f�t�H���g�F
	const bool isNormalColor = _life > midleLife;
	if(isNormalColor) { MV1SetDifColorScale(_modelHandle, _normalColor.m_color); }

	//	���C�t�͒��ԂȂ̂ŁA
	//	���f���̐F�����F�ɕϊ�
	const bool isLifeMidle = _life > dangerLife && _life <= midleLife;
	if (isLifeMidle) { MV1SetDifColorScale(_modelHandle, m_lifeMiddleColorF.m_color); }

	//	���C�t�͒��ԂȂ̂ŁA
	//	���f���̐F��ԐF�ɕϊ�
	const bool isLifeDanger = _life > LIFE_ZERO && _life <= dangerLife;
	if (isLifeDanger) { MV1SetDifColorScale(_modelHandle, m_lifeDangerColorF.m_color); }
}

//-----------------------------------------------------------------------------
//	@brief	�_�ŕ`�揈��
//-----------------------------------------------------------------------------
void LastBoss::_FlashingDraw(BossParts& _bossParts)
{
	//	�_���[�W���������Ƃ�
	if (_bossParts.m_isDamage)
	{
		m_flashingTime++;

		//	�_��
		const bool isDraw = (m_flashingTime >= 0.0f && m_flashingTime <= 3.0f) ||
			(m_flashingTime >= 6.0f && m_flashingTime <= 9.0f) ||
			(m_flashingTime >= 12.0f && m_flashingTime <= 15.0f);
		if (isDraw) { MV1DrawModel(_bossParts.m_modelHandle); }

		const bool isReset = m_flashingTime >= 18.0f;
		if (isReset) { m_flashingTime = 0.0f;}
	}
	else
	{
		MV1DrawModel(_bossParts.m_modelHandle);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void LastBoss::_FinalRelease()
{
	//	���f���̃A�����[�h
	MV1DeleteModel(m_modelHandle);

	for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
	{
		MV1DeleteModel(m_bossPartsSideBarrel[i].m_modelHandle);
		MV1DeleteModel(m_bossPartsArm[i].m_modelHandle);
		MV1DeleteModel(m_bossPartsCore[i].m_modelHandle);
	}

	//	�G�t�F�N�g�̍폜
	CommonSafe::Delete(m_effectHit);

	for (int i = 0; i < BOSS_PARTS_INFO::BOSS_PARTS_NUM; i++)
	{
		CommonSafe::Delete(m_effectInjection[i]);
		CommonSafe::Delete(m_effectLaser[i]);
	}

	for (int i = 0; i < CommonConstant::MAX_BOSS_EXPLOSION_NUM; i++)
	{
		CommonSafe::Delete(m_effectExplosion[i]);
	}

	CommonSafe::Delete(m_effectLastExplosion);
}

