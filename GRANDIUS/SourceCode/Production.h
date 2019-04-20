
//=============================================================================
//	@file	Production.h
//	@brief	���o�N���X
//	@autor	���m ���
//	@date	2018/12/24
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
struct Rect;

//-----------------------------------------------------------------------------
//	@brief	���o�N���X
//-----------------------------------------------------------------------------
class Production final
{
public:

//===================== �֐� ======================//

	//	�f�X�g���N�^
	~Production();

	//	�C���X�^���X�̐���
	static Production* GetInstance()
	{
		static Production s_instance;
		return &s_instance;
	}

	//	�X�V
	void Update();

	//	�`��
	void Draw();

	//	�K�E�Z�̃��Z�b�g
	void ResetSpecialProduction();

	//	���ׂẴ��Z�b�g
	void AllReset();

//==================== getter =====================//

	//	�Q�[�����̃V�[���ړ��̉��o�� getter
	const bool GetIsSceneProduction() const { return m_isSceneProduction; }

	//	�K�E�Z�g�p���̉��o�� getter
	const bool GetIsSpecialProduction() const { return m_isSpecialProduction; }

	//	�N���A���̉��o�� getter
	const bool GetIsClearProduction() const { return m_isClearProduction; }

	//	�^�C�g�����̉��o�� getter
	const bool GetIsTitleProduction() const { return m_isTitleProduction; }

//==================== setter =====================//

	//	�Q�[�����̃V�[���ړ��̉��o�� setter
	void SetIsSceneProduction(const bool _set) { m_isSceneProduction = _set; }

	//	�K�E�Z�g�p���̉��o�� setter
	void SetIsSpecialProduction(const bool _set) { m_isSpecialProduction = _set; }

	//	�N���A���̉��o�� setter
	void SetIsClearProduction(const bool _set) { m_isClearProduction = _set; }

	//	�^�C�g�����̉��o�� setter
	void SetIsTitleProduction(const bool _set) { m_isTitleProduction = _set; }

private:

//================== �V���O���g�� ==================//

	//	�R���X�g���N�^
	Production();

//================== ���������֐� ==================//

	//	�Q�[�W�̏o��
	void _EmergenceGauge();

	//	�Q�[�W�����ɖ߂�
	void _RestoreGauge();

//=================== �����o�ϐ� ===================//

	Rect	m_gaugeBar1;					//	���o���̃Q�[�W
	Rect	m_gaugeBar2;					//	���o���̃Q�[�W
	int		m_gaugeColor;					//	�Q�[�W�̐F
	bool	m_isSceneProduction;			//	�Q�[�����̃V�[���ړ��̉��o���t���O
	bool	m_isSpecialProduction;			//	�K�E�Z�g�p���̉��o���t���O
	bool	m_isClearProduction;			//	�N���A���̉��o���t���O
	bool	m_isTitleProduction;			//	�^�C�g�����̉��o
	float	m_specialProductionTime;		//	�K�E�Z�g�p���̎���

//===================== �ÓI�萔 ===================//

	static const VECTOR	GAUGE_START_VERTEX_1;		//	�Q�[�W�̊J�n���_�P
	static const VECTOR	GAUGE_START_VERTEX_2;		//	�Q�[�W�̊J�n���_�Q
	static const VECTOR	GAUGE_END_VERTEX_1;			//	�Q�[�W�̏I�����_�P
	static const VECTOR	GAUGE_END_VERTEX_2;			//	�Q�[�W�̏I�����_�Q
	static const float	MAX_Y_AXIS_1;				//	�Q�[�W�̍ő�l
	static const float	MAX_Y_AXIS_2;				//	�Q�[�W�̍ő�l
	static const float	GAUGE_ADD_SPEED;			//	�Q�[�W�̉��Z���x�P

};

#define PRODUCTION Production::GetInstance()