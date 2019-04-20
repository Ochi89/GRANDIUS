
//=============================================================================
//	@file	Item.h
//	@brief	�A�C�e���ЂƂ��̏���
//	@autor	���m ���
//	@date	2018/12/14
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
//	@brief	�A�C�e���N���X
//-----------------------------------------------------------------------------
class Item final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	Item(const int _modelHandle1, const int _modelHandle2, const int _modelHandle3);
	~Item();

	//	��������
	void Initialize();

	//	�X�V����
	void Update();

	//	�`�揈��
	void Draw();

//==================== setter =====================//

	//	�J�n�ʒu�� setter
	void SetStartPos(const VECTOR _set) { m_pos = VGet(_set.x, _set.y, 0.0f); }

	//	��x�݂̂� setter
	void SetIsOneTime(const bool _set) { m_isOneTime = _set; }

//==================== getter =====================//

	//	�|�W�V������ getter
	const VECTOR& GetPos() const { return m_pos; }

	//	��x�݂̂� getter
	const bool& GetIsOneTime() const { return m_isOneTime; }

	//	�����蔻��p�̉~�`�� getter
	const Circle& GetCircle() const { return m_hitCircle; }

	//	�����蔻��p�̒����`�́@setter
	const Rect& GetRect() const { return m_hitRect; };

private:

//================== ���������֐� ==================//

	//	�ړ�����
	void _Move();

	//	��]����
	void _Rotation();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	int			m_modelHandle1;		//	���f���n���h��
	int			m_modelHandle2;		//	���f���n���h��
	int			m_modelHandle3;		//	���f���n���h��
	VECTOR		m_pos;				//	�ʒu
	VECTOR		m_dir;				//	����
	bool		m_isOneTime;		//	��x�̂ݏ���
	float		m_radian;			//	�p�x
	VECTOR		m_angle1;			//	�p�x�P
	VECTOR		m_angle2;			//	�p�x�Q

	Circle		m_hitCircle;		//	�����蔻��p�̉~�`�̍\����
	Rect		m_hitRect;			//	�����蔻��p�̒����`�̍\����

//===================== �ÓI�萔 ===================//

	static const VECTOR		RECT_CORRECTION;	//	���W�̕␳
	static const float		MOVE_SPEED;			//	�ړ����x
	static const float		HIT_RADIUS;			//	�����蔻��p�̔��a
	static const float		ANGLE_SPEED_1;		//	��]���x�P
	static const float		ANGLE_SPEED_2;		//	��]���x�Q

};