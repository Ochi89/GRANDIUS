
//=============================================================================
//	@file	Shot.h
//	@brief	�e�ЂƂ��̏���
//	@autor	���m ���
//	@date	2018/12/12
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

//-----------------------------------------------------------------------------
//	@brief	�V���b�g�N���X
//-----------------------------------------------------------------------------
class Shot final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	Shot(const int _modelHandle);
	~Shot();
	
	//	�X�V����
	void Update();

	//	�`�揈��
	void Draw();

//==================== setter =====================//

	//	�J�n�ʒu�� setter
	void SetStartPos(const VECTOR _set) { m_pos = _set; }

	//	�J�n������ setter
	void SetStartDir(const VECTOR _set) { m_dir = VNorm(_set);}

	//	�ړ����x�� setter
	void SetSpeed(const float _set) { m_speed = _set; }

	//	��x�݂̂� setter
	void SetIsOneTime(const bool _set) { m_isOneTime = _set; }

//==================== getter =====================//

	//	�|�W�V������ getter
	const VECTOR& GetPos() const { return m_pos; }

	//	��x�݂̂� getter
	const bool& GetIsOneTime() const { return m_isOneTime; }

	//	�����蔻��p�̉~�`�� getter
	const Circle& GetCircle() const { return m_hitCircle; }

	//	�����蔻��p�̒����`�� getter
	const Rect& GetRect() const { return m_hitRect; }

private:

//================== ���������֐� ==================//

	//	�ړ�����
	void _Move();

	//	�����蔻��p�̓_�̍X�V
	void _UpdateHitPoint();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int			m_modelHandle;		//	���f���n���h��
	VECTOR		m_pos;				//	�ʒu
	VECTOR		m_dir;				//	����
	float		m_speed;			//	���x
	bool		m_isOneTime;		//	��x�̂ݏ���

	Circle		m_hitCircle;		//	�����蔻��p�̉~�`
	Rect		m_hitRect;			//	�����蔻��p�̒����`

//===================== �ÓI�萔 ===================//

	static const float HIT_RADIUS;			//	�����蔻��p�̔��a
	static const VECTOR		ADJUSTMENT_RECT;	//	�����蔻�蒲���p

};