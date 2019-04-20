
//=============================================================================
//	@file	MediumBoss.h
//	@brief	�ŏI�{�X
//	@autor	���m ���
//	@date	2018/12/21
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "CharacterBase.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
struct Circle;
struct Rect;
struct ColorF;
class ShotManager;
class EffekseerEmitter;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�ŏI�{�X�N���X
//-----------------------------------------------------------------------------
class LastBoss : public CharacterBase
{
public:

//===================== �񋓑� =====================//

	//	�p�[�c�̎��
	enum BOSS_PARTS_KIND
	{
		BOSS_PARTS_KIND_BODY,				//	�{�f�B�[
		BOSS_PARTS_KIND_CORE,				//	�R�A
		BOSS_PARTS_KIND_SIDE_BARREL,		//	�T�C�h�o���b�g
		BOSS_PARTS_KIND_ARM,				//	�A�[��
	};

//===================== �֐� ======================//
	
	//	�R���X�g���N�^ / �f�X�g���N�^
	LastBoss(const int _bodyModelHandle, const int _sideBarrelModelHandle, const int _armModelHandle, const int _coreModelHandle);
	~LastBoss();

	//	�쐬����
	void Create() override final;

	//	�������
	void Release() override final;

	//	��������
	void Initialize() override final;

	//	�X�V����
	void Update(ShotManager& _shot, SoundEffect& _soundEffect);

	//	�`�揈��
	void Draw() override final;

	//	�R�A�̃_���[�W����
	void OnHitCoreDamage(const int _num);

	//	�R�A�̃_���[�W����
	void OnHitCoreDamage(const int _num, const int _damage);

	//	�T�C�h�o�����̃_���[�W����
	void OnHitSideBarrelDamage(const int _num);

	//	�T�C�h�o�����̃_���[�W����
	void OnHitSideBarrelDamage(const int _num, const int _damage);

	//	�j���
	void DestructionSituation();


//==================== getter =====================//

	//	���C�t�� getter
	const int& GetLife() const { return m_life; }

	//	�����Ă��邩�� getter
	const bool GetIsAlive() const { return m_life > 0; }

	//	�o���t���O�� getter
	const bool& GetIsEmerge() const { return m_isEmerge; }

	//	�o��t���O�� getter
	const bool& GetIsAppearance() const { return m_isAppearance; }

	//	�s���J�n�t���O�� getter
	const bool& GetIsStarted() const { return m_isStarted; }

	//	�����蔻��p�̉~�`�́@getter
	const Circle& GetCircle(const BOSS_PARTS_KIND _partsNum, const int _num = 0) const;

	//	�����蔻��p�̃A�[���̒����`�́@getter
	const Rect& GetArmRect(const int _num = 0) const;

	//	�����蔻��p�̃R�A�̒����`�́@getter
	const Rect& GetCoreRect(const int _num = 0) const;

	//	�����蔻��p�̃T�C�h�o�����̒����`�́@getter
	const Rect& GetSideBarrelRect(const int _num = 0) const;

	//	�����蔻��p�̃��[�U�[�̒����`�́@getter
	const Rect& GetLaserRect(const int _num = 0) const;

	//	�����蔻��p�̃Z���^�[�o�����̒����`�́@getter
	const Rect& GetCenterBarrelRect() { return m_centerBarrel; }

	//	�E�R�A�������Ă��邩�� getter
	const bool& GetIsRightCoreAlive() const { return m_isRightCoreAlive; }

	//	���R�A�������Ă��邩�� getter
	const bool& GetIsLeftCoreAlive() const { return m_isLeftCoreAlive; }

	//	�E�T�C�h�o�����������Ă��邩�� getter
	const bool& GetIsRightSideBarrelAlive() const { return m_isRightSideBarrelAlive; }

	//	���T�C�h�o�����������Ă��邩�� getter
	const bool& GetIsLeftSideBarrelAlive() const { return m_isLeftSideBarrelAlive; }

	//	���ׂĔj�󂵂����� getter
	const bool& GetIsAllDestruction() const { return m_isAllDestruction; }

	//	�R�A�̃_���[�W����� getter
	const bool& GetIsCoreDamage(const int _num) { return m_bossPartsCore[_num].m_isDamage; }

	//	�T�C�h�o�����̃_���[�W����� getter
	const bool& GetIsSideBarrelDamage(const int _num) { return m_bossPartsSideBarrel[_num].m_isDamage; }

	//	�{�X���S�t���O�� getter
	const bool GetIsDeath() { return (!m_isLeftCoreAlive && !m_isRightCoreAlive); }

//==================== setter =====================//

	//	�o���t���O�� setter
	void SetIsEmerge(const bool _set) { m_isEmerge = _set; m_isStart = _set; }

	//	���C�t�� setter
	void SetLife(const int _set) { m_life = _set; };

private:

//===================== �񋓑� =====================//

	//	�p�[�c�̏��
	enum BOSS_PARTS_INFO
	{
		BOSS_PARTS_RIGHT,
		BOSS_PARTS_LEFT,
		BOSS_PARTS_NUM,
	};

	//	�{�X�̍s�����
	enum BEHAVIOR_KIND
	{
		BEHAVIOR_NONE,		//	�Ȃ�
		BEHAVIOR_SHOT,		//	�V���b�g
		BEHAVIOR_ROCKET,	//	���P�b�g
		BEHAVIOR_LASER		//	���[�U�[
	};

	//	�����G�t�F�N�g�̎��
	enum EXPLOSION_EFFECT_KIND
	{
		EXPLOSION_EFFECT_LEFT_BARREL,		//	���̃T�C�h�o����
		EXPLOSION_EFFECT_RIGHT_BARREL,		//	�E�̃T�C�h�o����
		EXPLOSION_EFFECT_LEFT_CORE,			//	���̃R�A
		EXPLOSION_EFFECT_RIGHT_CORE,		//	�E�̃R�A
		EXPLOSION_EFFECT_LAST,				//	�Ō�
		EXPLOSION_EFFECT_NUM,				//	��
	};

//===================== �\���� =====================//

	//	�p�[�c�̍\����
	struct BossParts
	{
		int			m_modelHandle;		//	���f���n���h��
		VECTOR		m_pos;				//	�|�W�V����
		VECTOR		m_dir;				//	�f�B���N�V����
		VECTOR		m_angle;			//	�A���O��
		VECTOR		m_size;				//	�T�C�Y
		int			m_life;				//	���C�t
		bool		m_isDamage;			//	�_���[�W�t���O
		Circle		m_hitCircle;		//	�����蔻��p�̉~�̍\����
		Rect		m_hitRect;			//	�����蔻��p�̒����`�̍\����
	};

//================== ���������֐� ==================//

	//	�p�[�c�̏�����
	void _InitializeBossParts(BossParts& _bossParts, const BOSS_PARTS_INFO _bossPartsInfo, const float _hitRadius = 0.0f, const int _liffe = 1);

	//	�J�n���̈ړ�
	void _EmergeMove();

	//	�ړ�����
	void _Move();

	//	�ˌ�����
	void _Shot(ShotManager& _shot);
	
	//	���P�b�g����
	void _Rocket();

	//	���[�U�[
	void _Laser();

	//	�p�[�c�̏�
	void _PartsSituation();

	//	�A�[���̉�]
	void _ArmRota(BossParts& _bossParts, const float _targetAngle);

	//	���[�v���g�������΍��W
	void _LerpRelativeCoordinates(BossParts& _bossParts, const BOSS_PARTS_INFO _bossInfo, const VECTOR _target);

	//	���`�ۊǂ��g�p�����ړ�
	void _LerpMove(bool _isConditions, VECTOR _targetPos, float _lerpSpeed);

	//	�q�b�g�G�t�F�N�g
	void _OnHitEffect(BossParts& _bossParts, SoundEffect& _soundEffect, const VECTOR _pos);

	//	�����G�t�F�N�g
	void _OnEffectExplosion(SoundEffect& _soundEffect);

	//	�����G�t�F�N�g���
	void _OneEffectExplosion(const  bool _isConditions, EffekseerEmitter& _effect, SoundEffect& _soundEffect, const VECTOR _pos, bool& _isUsedFlag);

	//	�ŏI�����G�t�F�N�g
	void _LastEffectExplosion(const  bool _isConditions, SoundEffect& _soundEffect);

	//	�����_�������G�t�F�N�g
	void _RandamEffectExplosion(EffekseerEmitter& _effect, SoundEffect& _soundEffect);

	//	���[�U�[�G�t�F�N�g
	void _OnEffectLaser(EffekseerEmitter& _effect, SoundEffect& _soundEffect, const VECTOR _startPos, const BOSS_PARTS_INFO _partsInfo);

	//	���P�b�g�G�t�F�N�g
	void _OnEffectRocket(EffekseerEmitter& _effect, SoundEffect& _soundEffect, const VECTOR _startPos, const BOSS_PARTS_INFO _partsInfo);

	//	�����蔻��p�̍X�V
	void _UpdateHitJudgment();

	//	�A�[���̓����蔻��p�̍X�V
	void _UpdateHitArm();

	//	�R�A�̓����蔻��p�̍X�V
	void _UpdateHitCore();

	//	�T�C�h�o�����̓����蔻��p�̍X�V
	void _UpdateHitSideBarrel();

	//	���[�U�[�̓����蔻��p�̍X�V
	void _UpdateHitLaser();

	//	�{�f�B�[�̓����蔻��p�̍X�V
	void _UpdateHitBody();

	//	�Z���^�[�o�����̓����蔻��p�̍X�V
	void _UpdateHitCenterBarrel();

	//	���΍��W�����蓖�Ă�
	void _AllocationRelativeCoordinates();

	//	���΍��W�����߂�
	VECTOR _AskRelativeCoordinates(const VECTOR _basePos, const VECTOR _relativePos, const BOSS_PARTS_INFO _bossPartsInfo);

	//	���f���̐F��ύX����
	void _ChangeModelColor(const int _modelHandle, const int _life, const int _maxLife, const ColorF _normalColor);

	//	�_�ŕ`�揈��
	void _FlashingDraw(BossParts& _bossParts);

	//	�ŏI�I�ȉ������
	void _FinalRelease() override final;

//=================== �����o�ϐ� ===================//

	int				m_life;																	//	���C�t
	float			m_emergeMoveTaim;														//	���o����
	float			m_behaviorTime;															//	�s������
	float			m_rocketTime;															//	���P�b�g����
	float			m_laserTime;															//	���[�U�[����
	float			m_moveSpeed;															//	�ړ����x
	bool			m_isEmerge;																//	�o���t���O
	bool			m_isAppearance;															//	�o��t���O
	bool			m_isStart;																//	�J�n�t���O
	bool			m_isStarted;															//	�s���J�n�t���O
	bool			m_isRightCoreAlive;														//	�E�R�A�������Ă���
	bool			m_isLeftCoreAlive;														//	���R�A�������Ă���
	bool			m_isRightSideBarrelAlive;												//	�E�T�C�h�o�����������Ă���
	bool			m_isLeftSideBarrelAlive;												//	���T�C�h�o�����������Ă���
	bool			m_isAllDestruction;														//	���ׂĔj�󂵂�
	float			m_flashingTime;															//	�_�Ŏ���
	bool			m_isUsedEffectExplosion[EXPLOSION_EFFECT_KIND::EXPLOSION_EFFECT_NUM];	//	�����G�t�F�N�g�̎g�p��
	bool			m_isOffDraw;															//	�`��I�t
	bool			m_isStartRocket;														//	���P�b�g�̊J�n
	bool			m_isStartLaser;															//	���[�U�[�̊J�n
	Circle			m_hitCircle;															//	�����蔻��p�̉~�̍\����
	Rect			m_laser;																//	���[�U�[
	Rect			m_centerBarrel;															//	�Z���^�[�o����
	Rect			m_laserHitRect[BOSS_PARTS_INFO::BOSS_PARTS_NUM];						//	���[�U�[�̓����蔻��
	Rect			m_coreHitRect[BOSS_PARTS_INFO::BOSS_PARTS_NUM];							//	�R�A�̓����蔻��
	Rect			m_sideBarrelHitRect[BOSS_PARTS_INFO::BOSS_PARTS_NUM];					//	�T�C�h�o�����̓����蔻��
	BEHAVIOR_KIND	m_behaviorKind;															//	�{�X�̍s�����

	BossParts		m_bossPartsCore[BOSS_PARTS_INFO::BOSS_PARTS_NUM];						//	�R�A
	BossParts		m_bossPartsSideBarrel[BOSS_PARTS_INFO::BOSS_PARTS_NUM];					//	�T�C�h�o����
	BossParts		m_bossPartsArm[BOSS_PARTS_INFO::BOSS_PARTS_NUM];						//	�A�[��

	ColorF			m_lifeNormalColorFYellow;												//	���C�t�f�t�H���g�F ���F
	ColorF			m_lifeNormalColorFBlack;												//	���C�t�f�t�H���g�F ��
	ColorF			m_lifeMiddleColorF;														//	���C�t���ԐF
	ColorF			m_lifeDangerColorF;														//	���C�t�댯�F

	//	�G�t�F�N�g�֌W
	EffekseerEmitter*	m_effectHit;												//	�q�b�g�G�t�F�N�g
	EffekseerEmitter*	m_effectExplosion[CommonConstant::MAX_BOSS_EXPLOSION_NUM];	//	�����G�t�F�N�g
	EffekseerEmitter*	m_effectLastExplosion;										//	�ŏI�����G�t�F�N�g
	EffekseerEmitter*	m_effectLaser[BOSS_PARTS_INFO::BOSS_PARTS_NUM];				//	���[�U�[�G�t�F�N�g
	EffekseerEmitter*	m_effectInjection[BOSS_PARTS_INFO::BOSS_PARTS_NUM];			//	���˃G�t�F�N�g

//===================== �ÓI�萔 ===================//

	static const VECTOR		EMERGE_POS;						//	�o�����̍��W
	static const VECTOR		EMERGE_RIGHT_ARM_POS;			//	�o�����̉E�A�[���̍��W
	static const VECTOR		EMERGE_LEFT_ARM_POS;			//	�o�����̍��A�[���̍��W
	static const VECTOR		RELATIVE_CORE_POS;				//	�R�A�̑��΍��W
	static const VECTOR		RELATIVE_SIDE_BARREL_POS;		//	�T�C�h�o�����̑��΍��W
	static const VECTOR		RELATIVE_ARM_POS;				//	�A�[���̑��΍��p
	static const VECTOR		OPEN_RELATIVE_CORE_POS;			//	�R�A�̑��΍��W
	static const VECTOR		OPEN_RELATIVE_SIDE_BARREL_POS;	//	�T�C�h�o�����̑��΍��W
	static const VECTOR		OPEN_RELATIVE_ARM_POS;			//	�A�[���̑��΍��p
	static const VECTOR		START_POS;						//	�J�n���̍��W

	static const VECTOR		MOVE_PATTERN_1;					//	�s���p�^�[���P
	static const VECTOR		MOVE_PATTERN_2;					//	�s���p�^�[���Q
	static const VECTOR		MOVE_PATTERN_3;					//	�s���p�^�[���R
	static const VECTOR		MOVE_PATTERN_4;					//	�s���p�^�[���S
	static const VECTOR		MOVE_PATTERN_5;					//	�s���p�^�[���T
	static const VECTOR		MOVE_PATTERN_6;					//	�s���p�^�[���U

	static const VECTOR		SHOT_START_POS_CORRECTION_1;	//	�V���b�g�J�n�ʒu���W�̕␳
	static const VECTOR		SHOT_START_POS_CORRECTION_2;	//	�V���b�g�J�n�ʒu���W�̕␳
	static const VECTOR		SHOT_START_POS_CORRECTION_3;	//	�V���b�g�J�n�ʒu���W�̕␳
	static const float		SHOT_SPEED;						//	�V���b�g���x
	static const float		MAX_START_WAIT_TIME;			//	�V���b�g�̊J�n���̒x������
	static const float		MAX_WAIT_TIME;					//	�V���b�g�̒x������
	static const float		LASER_LENGTH;					//	���[�U�[�̒���

	static const VECTOR		ADJUSTMENT_BODY_POS;			//	�����蔻�蒲���p�̃|�C���g �{�f�B�[
	static const VECTOR		ADJUSTMENT_SIDE_BARREL_POS;		//	�����蔻�蒲���p�̃|�C���g �T�C�h�o����
	static const VECTOR		ADJUSTMENT_ARM_CIRCLE_POS;		//	�����蔻�蒲���p�̃|�C���g �A�[��
	static const VECTOR		ADJUSTMENT_ARM_RECT_POS;		//	�����蔻�蒲���p�̃|�C���g �A�[��
	static const VECTOR		ADJUSTMENT_LASER_POS;			//	�����蔻�蒲���p�̃|�C���g ���[�U�[
	static const VECTOR		ADJUSTMENT_CENTER_BARRE_POS;	//	�����蔻�蒲���p�̃|�C���g �Z���^�[�o����
	static const VECTOR		ARM_CORRECTION;					//	�����蔻��p�̕␳ �A�[��
	static const VECTOR		CENTER_BARRE_CORRECTION;		//	�����蔻��p�̕␳ �Z���^�[�o����
	static const float		LASER_EFFECT_CORRECTION;		//	�G�t�F�N�g�̕␳ ���[�U�[
	static const float		ROCKET_EFFECT_CORRECTION;		//	�G�t�F�N�g�̕␳ ���P�b�g
	static const float		HIT_BODY_RADIUS;				//	�����蔻��p�̔��a �{�f�B�[
	static const float		HIT_SIDE_BARREL_RADIUS;			//	�����蔻��p�̔��a �T�C�h�o����
	static const float		HIT_CORE_RADIUS;				//	�����蔻��p�̔��a �R�A
	static const float		HIT_ARM_RADIUS;					//	�����蔻��p�̔��a �A�[��
	static const int		MAX_SIDE_BARREL_LIFE;			//	���C�t�̍ő� �T�C�h�o����
	static const int		MAX_CORE_LIFE;					//	���C�t�̍ő� �R�A
	static const VECTOR		BOSS_RADIUS;					//	�{�X�̔��a
	static const int		LIFE_ZERO;						//	���C�t�Ȃ�
};
