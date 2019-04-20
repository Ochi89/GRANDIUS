
//=============================================================================
//	@file	UIBackPixel.h
//	@brief	�w�i�s�N�Z��UI
//	@autor	���m ���
//	@date	2018/1/15
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
//	@brief	UIGameOver�N���X
//-----------------------------------------------------------------------------
class UIBackPixel final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^/�f�X�g���N�^
	UIBackPixel();
	~UIBackPixel();

	//	�`�揈��
	void Update();

	//	�`�揈��
	void Draw();

private:

//===================== �\���� =====================//
	
	//	�s�N�Z��
	struct BackPixel
	{
		VECTOR		m_centerPoint;		//	���S�_
		float		m_radius;			//	���a
		float		m_speed;			//	���x
		bool		m_isInUse;			//	�g�p��
	};

//================== ���������֐� ==================//

	//	�_�̍쐬����
	void _CreateBackPixel();

	//	�_�̍X�V����
	void _UpdateBackPixel();

	//	�_�̕`�揈��
	void _DrawBackPixel();

//=================== �����o�ϐ� ===================//

	BackPixel	m_backPixel[CommonConstant::MAX_BACK_PIXEL_NUM];	//	�w�i�s�N�Z��

//===================== �ÓI�萔 ===================//

	static const float		MIN_RADIUS_SIZE;	//	���a�T�C�Y�̍ŏ�
	static const float		MAX_RADIUS_SIZE;	//	���a�T�C�Y�̍ő�
	static const float		MIN_SPEED;			//	���x�̍ŏ�
	static const float		MAX_SPEED;			//	���x�̍ő�
	static const VECTOR		START_POSTION;		//	���W�̊J�n�ʒu
	static const VECTOR		MIN_POSTION;		//	���W�̍ŏ�
	static const VECTOR		MAX_POSTION;		//	���W�̍ő�

};