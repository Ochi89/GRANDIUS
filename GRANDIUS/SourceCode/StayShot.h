
//=============================================================================
//	@file	StayShot.h
//	@brief	�؍ݒe�ЂƂ��̏���
//	@autor	���m ���
//	@date	2018/12/25
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
struct Circle;
struct Rect;
class EffekseerEmitter;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�X�e�C�V���b�g�N���X
//-----------------------------------------------------------------------------
class StayShot final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	StayShot();
	~StayShot();

	//	��������
	void Initialize();

	//	�X�V����
	void Update(SoundEffect& _soundEffect);

//==================== setter =====================//

	//	�J�n�ʒu�� setter
	void SetStartPos(const VECTOR _set) { m_pos = _set; }

	//	��x�݂̂� setter
	void SetIsOneTime(const bool _set) { m_isOneTime = _set; }

	//	�؍݂ɐ؂�ւ���t���O�� setter
	void SetIsChangeStay(const bool _set) { m_isChangeStay = _set; }

//==================== getter =====================//

	//	�|�W�V������ getter
	const VECTOR& GetPos() const { return m_pos; }

	//	��x�݂̂� getter
	const bool& GetIsOneTime() const { return m_isOneTime; }

	//	�����蔻��p�̉~�`�� getter
	const Circle& GetCircle() const { return m_hitCircle; }

	//	�����蔻��p�̒����`�� getter
	const Rect& GetRect() const { return m_hitRect; }

	//	�V���b�g�̏I���� getter
	const bool& GetIsShotEnd() const { return m_isShotEnd; }

private:

//================== ���������֐� ==================//

	//	�ړ�����
	void _Move(SoundEffect& _soundEffect);

	//	�؍ݏ���
	void _Stay(SoundEffect& _soundEffect);

	//	�����蔻��p�̓_�̍X�V
	void _UpdateHitPoint();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	VECTOR		m_pos;					//	�ʒu
	bool		m_isOneTime;			//	��x�̂ݏ����t���O
	bool		m_isChangeStay;			//	���[�h��؍݂ɐ؂�ւ���t���O
	float		m_stayTime;				//	�؍ݎ���
	bool		m_isShotEnd;			//	�V���b�g�̏I��
	bool		m_isMoveShotSeStart;	//	�ړ��V���b�gSE�J�n
	bool		m_isStayShotSeStart;	//	�؍݃V���b�gSE�J�n

	Circle		m_hitCircle;			//	�����蔻��p�̉~�`
	Rect		m_hitRect;				//	�����蔻��p�̒����`

	//	�G�t�F�N�g�֌W
	EffekseerEmitter*	m_effectMove;	//	�ړ��G�t�F�N�g
	EffekseerEmitter*	m_effectStay;	//	�؍݃G�t�F�N�g
	float				m_effectScale;	//	�G�t�F�N�g�̊g�嗦

//===================== �ÓI�萔 ===================//

	static const VECTOR		MOVE_DIR;			//	�ړ�����
	static const float		MOVE_SPEED;			//	�ړ����x
	static const float		MOVE_HIT_RADIUS;	//	�ړ����̓����蔻��p�̔��a
	static const float		STAY_HIT_RADIUS;	//	�؍ݒ��̓����蔻��p�̔��a
	static const float		MIN_HIT_RADIUS;		//	�����蔻��p�̍ŏ����a
	static const float		MAX_STAY_TIME;		//	�؍ݒ��̎��Ԃ̍ő�
	static const float		EFFECT_SCALE;		//	�G�t�F�N�g�̊g�呬�x
	static const float		MAX_X_POS;			//	X���W�̍ő�
	static const VECTOR		ADJUSTMENT_RECT;	//	�����蔻�蒲���p

};