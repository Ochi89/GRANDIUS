
//=============================================================================
//	@file	EnemyBase.h
//	@brief	�G�l�~�[�x�[�X
//	@autor	���m ���
//	@date	2018/11/14
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
class PlayerManager;
class ShotManager;
class EffekseerEmitter;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�G�l�~�[���N���X
//-----------------------------------------------------------------------------
class EnemyBase : public CharacterBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	EnemyBase(const int _modelHandle);
	virtual ~EnemyBase();

	//	�쐬����
	virtual void Create() override = 0;

	//	�������
	virtual void Release() override = 0;

	//	��������
	virtual void Initialize() override = 0;

	//	�X�V����
	virtual void Update(PlayerManager& _playerManager, ShotManager& _shotManager, SoundEffect& _soundEffect) = 0;

	//	�`�揈��
	virtual void Draw() override final;

	//	�������Ԃ̉��Z
	void AddAliveTime() { m_aliveTime++; }

//==================== getter =====================//

	//	�GID�� getter
	const int GetFormationID() const { return m_formationID; }

	//	�GID�� getter
	const int GetEntryID() const { return m_entryID; }

	//	�G��� getter
	const int GetEntryKind() const { return m_entryKind; }

	//	�������Ԃ� getter
	const float GetAliveTime() const { return m_aliveTime; }

	//	�A�C�e���������Ă��邩�� getter
	const bool& GetIsHavingItems() const { return m_isHavingItems; }

	//	�q�b�g�t���O�� getter
	const bool& GetIsHIt() const { return m_isHit; }

	//	�폜�t���O�� getter
	const bool& GetIsDeleate() const { return m_isDeleate; }

//==================== setter =====================//

	//	�GID�� setter
	void SetFormationID(const int _set) { m_formationID = _set; }

	//	�GID�� setter
	void SetEntryID(const int _set) { m_entryID = _set; }

	//	�G��� setter
	void SetEntryKind(const int _set) { m_entryKind = _set; }
	
	//	�A�C�e���������Ă��邩�� setter
	void SetIsHavingItems(const bool _set) { m_isHavingItems = _set; }

	//	�V���b�g���g������ setter
	void SetIsUseShot(const bool _set) { m_isUseShot = _set; }

	//	�q�b�g�t���O�� setter
	void SetIsHit(const bool _set) { m_isHit = _set; }

protected:

//================== ���������֐� ==================//

	//	�����̐؂�ւ�����
	virtual void _ChangeDir() = 0;

	//	�F�̕ύX
	void _ChangeColor();

	//	�V���b�g�̓o�^
	void _ShotEntry(PlayerManager& _playerManager, ShotManager& _shotManager);

	//	�����G�t�F�N�g
	void _OnEffectExplosion(SoundEffect& _soundEffect);

	//	�����蔻��p�̓_�̍X�V
	virtual void _UpdateHitPoint() = 0;

	//	�ŏI�I�ȉ������
	virtual void _FinalRelease() = 0;

//=================== �����o�ϐ� ===================//

	float	m_behaviorTime;		//	�s������
	float	m_moveSpeed;		//	�ړ����x
	float	m_aliveTime;		//	�������Ă���̎���
	bool	m_isUseShot;		//	�V���b�g���g�����̃t���O
	bool	m_isHavingItems;	//	�A�C�e���������Ă��邩�̃t���O
	int		m_formationID;		//	����̔ԍ�
	int		m_entryID;			//	�g�p���Ă���GID
	int		m_entryKind;		//	�g�p���Ă���G��
	bool	m_isAttenuation;	//	�����t���O
	bool	m_isHit;			//	�q�b�g�t���O
	bool	m_isOffDraw;		//	�`�悵�Ȃ��t���O
	bool	m_isDeleate;		//	�폜�t���O

	//	�G�t�F�N�g�֌W
	EffekseerEmitter*	m_effectExplosion;	//	�����G�t�F�N�g

//===================== �ÓI�萔 ===================//

	static const VECTOR		RECT_CORRECTION;	//	�����`�̕␳
	static const float		SHOT_SPEED;			//	�V���b�g���x
	static const float		MAX_WAIT_TIME;		//	�V���b�g�̒x������
	static const float		HIT_RADIUS;			//	�����蔻��p�̔��a
	static const float		CENTER_CORRECTION;	//	���S���W�̕␳

private:

//================== ���������֐� ==================//

	//	���F�ݒ�
	void _AttenuationColor();

//=================== �����o�ϐ� ===================//

	COLOR_F		m_color;			//	���f���̐F

//===================== �ÓI�萔 ===================//

	static const COLOR_F	COLOR_NORMAL;		//	�f�t�H���g�F
	static const COLOR_F	COLOR_DECAY_NORMAL;	//	�f�t�H���g�F�̌���
	static const COLOR_F	COLOR_RED;			//	�ԐF
	static const COLOR_F	COLOR_DECAY_RED;	//	�ԐF�̌���

};