
//=============================================================================
//	@file	MediumBoss.h
//	@brief	���{�X
//	@autor	���m ���
//	@date	2018/12/18
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
class ShotManager;
class EffekseerEmitter;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	���{�X�N���X
//-----------------------------------------------------------------------------
class MediumBoss : public CharacterBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	MediumBoss(const int _modelHandle);
	~MediumBoss();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	��������
	void Initialize();

	//	�X�V����
	void Update(ShotManager& _shot, SoundEffect& _soundEffect);

	//	�`�揈��
	virtual void Draw() override final;

	//	�_���[�W����
	void OnHitDamage()
	{
		if (!m_isDamage)
		{
			m_life--;
			m_isDamage = true;
		}
	}

	//	�_���[�W����
	void OnHitDamage(const int _damage)
	{
		if (!m_isDamage)
		{
			m_life -= _damage;
			m_isDamage = true;
		}
	}

//==================== getter =====================//

	//	���C�t�� getter
	const int& GetLife() const { return m_life; }

	//	�����Ă��邩�� getter
	const bool GetIsAlive() const { return m_life > 0; }

	//	�_���[�W����� getter
	const bool& GetIsDamage() const { return m_isDamage; }

	//	�o���t���O�� getter
	const bool& GetIsEmerge() const { return m_isEmerge; }

	//	�s���J�n�t���O�� getter
	const bool& GetIsStarted() const { return m_isStarted; }

	//	�폜�t���O�� getter
	const bool& GetIsDeleate() const { return m_isDeleate; }

//==================== setter =====================//

	//	�o���t���O�� setter
	void SetIsEmerge(const bool _set) { m_isEmerge = _set; m_isStart = _set; }

	//	���C�t�� setter
	void SetLife(const int _set) { m_life = _set; };

private:

//================== ���������֐� ==================//

	//	�J�n���̈ړ�
	void _EmergeMove();

	//	�ړ�����
	void _Move();

	//	���`�ۊǂ��g�p�����ړ�
	void _LerpMove(bool _isConditions, VECTOR _targetPos, float _lerpSpeed);

	//	�ˌ�����
	void _Shot(ShotManager& _shot);

	//	�q�b�g�G�t�F�N�g
	void _OnHitEffect(SoundEffect& _soundEffect);

	//	�����G�t�F�N�g
	void _OnEffectExplosion(SoundEffect& _soundEffect);

	//	�����蔻��p�̓_�̍X�V
	void _UpdateHitPoint();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int		m_life;				//	���C�t
	float	m_emergeMoveTaim;	//	���o����
	float	m_behaviorTime;		//	�s������
	float	m_moveSpeed;		//	�ړ����x
	bool	m_isEmerge;			//	�o���t���O
	bool	m_isStart;			//	�J�n�t���O
	bool	m_isDamage;			//	�_���[�W�t���O
	bool	m_isDeleate;		//	�폜�t���O
	bool	m_isStarted;		//	�s���J�n�t���O
	bool	m_isOffDraw;		//	�`��I�t�t���O
	float	m_flashingTime;		//	�_�Ŏ���

	//	�G�t�F�N�g�֌W
	EffekseerEmitter*	m_effectHit;			//	�q�b�g�G�t�F�N�g
	EffekseerEmitter*	m_effectExplosion;		//	�����G�t�F�N�g

//===================== �ÓI�萔 ===================//

	static const VECTOR		EMERGE_POS;						//	�o�����̍��W
	static const VECTOR		END_POS;						//	�ދp���̍��W
	static const VECTOR		START_POS;						//	�J�n���̍��W
	static const VECTOR		MOVE_PATTERN_1;					//	�s���p�^�[���P
	static const VECTOR		MOVE_PATTERN_2;					//	�s���p�^�[���Q
	static const VECTOR		MOVE_PATTERN_3;					//	�s���p�^�[���R
	static const VECTOR		MOVE_PATTERN_4;					//	�s���p�^�[���S
	static const VECTOR		SHOT_START_POS_CORRECTION_1;	//	�V���b�g�J�n�ʒu���W�̕␳
	static const VECTOR		SHOT_START_POS_CORRECTION_2;	//	�V���b�g�J�n�ʒu���W�̕␳
	static const VECTOR		SHOT_START_POS_CORRECTION_3;	//	�V���b�g�J�n�ʒu���W�̕␳
	static const VECTOR		SHOT_START_POS_CORRECTION_4;	//	�V���b�g�J�n�ʒu���W�̕␳
	static const VECTOR		RECT_CORRECTION;				//	���W�̕␳
	static const float		SHOT_SPEED;						//	�V���b�g���x
	static const float		MAX_START_WAIT_TIME;			//	�V���b�g�̊J�n���̒x������
	static const float		MAX_WAIT_TIME;					//	�V���b�g�̒x������
	static const float		HIT_RADIUS;						//	�����蔻��p�̔��a
	static const int		MAX_LIFE;						//	���C�t�̍ő�
	static const int		MIN_LIFE;						//	���C�t�̍ŏ�

};
