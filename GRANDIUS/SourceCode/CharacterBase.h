
//=============================================================================
//	@file	CharacterBase.h
//	@brief	�L�����N�^�[�x�[�X
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
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
struct Circle;
struct Rect;

//-----------------------------------------------------------------------------
//	@brief	�L�����N�^�[���N���X
//-----------------------------------------------------------------------------
class CharacterBase
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	CharacterBase();
	virtual ~CharacterBase();

	//	�쐬����gett
	virtual void Create() = 0;

	//	�������
	virtual void Release() = 0;

	//	��������
	virtual void Initialize() = 0;

	//	�`�揈��
    virtual void Draw() = 0;

//==================== getter =====================//

	//	���f���n���h���� getter
	const int& GetModelHandle() const { return m_modelHandle; }

	//	�|�W�V������ getter
	const VECTOR& GetPos() const { return m_pos; }

	//	�f�B���N�V������ getter
	const VECTOR& GetDir() const { return m_dir; }

	//	�A���O���� getter
	const VECTOR& GetAngle() const { return m_angle; }

	//	�T�C�Y�� getter
	const VECTOR& GetSize() const { return m_size; }

	//	�����蔻��p�̉~�`�́@getter
	const Circle& GetCircle() const { return m_hitCircle; };

	//	�����蔻��p�̒����`�́@getter
	const Rect& GetRect() const { return m_hitRect; };

//==================== setter =====================//

	//	�|�W�V������ setter
	const void SetPos(const VECTOR& _set) { m_pos = _set; }

	//	�f�B���N�V������ setter
	const void SetDir(const VECTOR& _set) { m_dir = _set; }

	//	�A���O���� setter
	const void SetAngle(const VECTOR& _set) { m_angle = _set; }

	//	�T�C�Y�� setter
	const void SetSize(const VECTOR& _set) { m_size = _set; }
	
protected:
	
//================== ���������֐� ==================//

	//	�ŏI�I�ȉ������
	virtual void _FinalRelease() = 0;

//=================== �����o�ϐ� ===================//
	
	int			m_modelHandle;		//	���f���n���h��
	VECTOR		m_pos;				//	�|�W�V����
	VECTOR		m_dir;				//	�f�B���N�V����
	VECTOR		m_angle;			//	�A���O��
	VECTOR		m_size;				//	�T�C�Y

	Circle		m_hitCircle;		//	�����蔻��p�̉~�̍\����
	Rect		m_hitRect;			//	�����蔻��p�̒����`�̍\����

	float		m_shotWaitTime;		//	�e�̒x������

};
