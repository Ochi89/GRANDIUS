
//=============================================================================
//	@file	UIBackPixel.h
//	@brief	�w�i�s�N�Z��UI
//	@autor	���m ���
//	@date	2018/1/15
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "UIBackPixel.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float		UIBackPixel::MIN_RADIUS_SIZE = 0.1f;					//	���a�T�C�Y�̍ŏ�
const float		UIBackPixel::MAX_RADIUS_SIZE = 0.2f;					//	���a�T�C�Y�̍ő�
const float		UIBackPixel::MIN_SPEED = 0.1f;							//	X���W�̍ŏ�
const float		UIBackPixel::MAX_SPEED = 0.2f;							//	X���W�̍ő�
const VECTOR	UIBackPixel::START_POSTION = VGet(-120.0f, 0.0f, 0.0f);	//	X���W�̊J�n�ʒu
const VECTOR	UIBackPixel::MIN_POSTION = VGet(120.0f, 120.0f, 0.0f);	//	X���W�̍ŏ�
const VECTOR	UIBackPixel::MAX_POSTION = VGet(140.0f, 140.0f, 0.0f);	//	X���W�̍ő�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
UIBackPixel::UIBackPixel()
{
	//	�J�n���̐ݒ�
	for (int i = 0; i < CommonConstant::MAX_BACK_PIXEL_NUM; i++)
	{
		//	���S�ʒu
		m_backPixel[i].m_centerPoint.x = CommonFunction::GetRand(START_POSTION.x, MIN_POSTION.x);
		m_backPixel[i].m_centerPoint.y = CommonFunction::GetRand(START_POSTION.y, MIN_POSTION.y);
		m_backPixel[i].m_centerPoint.z = 0.0f;

		//	���a
		m_backPixel[i].m_radius = CommonFunction::GetRand(MIN_RADIUS_SIZE, MAX_RADIUS_SIZE);

		//	���x
		m_backPixel[i].m_speed = CommonFunction::GetRand(MIN_SPEED, MAX_SPEED);

		//	�g�p��
		m_backPixel[i].m_isInUse = true;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
UIBackPixel::~UIBackPixel()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void UIBackPixel::Update()
{
	//	�_�̍쐬����
	_CreateBackPixel();

	//	�_�̍X�V����
	_UpdateBackPixel();
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void UIBackPixel::Draw()
{
	//	�_�̕`�揈��
	_DrawBackPixel();
}

//-----------------------------------------------------------------------------
//	@brief	�_�̐�������
//-----------------------------------------------------------------------------
void UIBackPixel::_CreateBackPixel()
{
	for (int i = 0; i < CommonConstant::MAX_BACK_PIXEL_NUM; i++)
	{
		//	�_�̎g�p�󋵂͖��g�p�̂Ƃ�
		const bool isBackPixelUnused = !m_backPixel[i].m_isInUse;
		if (isBackPixelUnused)
		{
			//	��̓_�̐���

			//	���S�ʒu
			m_backPixel[i].m_centerPoint.x = CommonFunction::GetRand(MIN_POSTION.x, MAX_POSTION.x);
			m_backPixel[i].m_centerPoint.y = CommonFunction::GetRand(START_POSTION.y, MAX_POSTION.y);
			m_backPixel[i].m_centerPoint.z = 0.0f;

			//	���a
			m_backPixel[i].m_radius = CommonFunction::GetRand(MIN_RADIUS_SIZE, MAX_RADIUS_SIZE);

			//	���x
			m_backPixel[i].m_speed = CommonFunction::GetRand(MIN_SPEED, MAX_SPEED);

			//	�g�p��
			m_backPixel[i].m_isInUse = true;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�_�̍X�V����
//-----------------------------------------------------------------------------
void UIBackPixel::_UpdateBackPixel()
{
	//	���o���ȊO
	const bool isNotProduction = !PRODUCTION->GetIsSpecialProduction() || !PRODUCTION->GetIsSceneProduction() || !PRODUCTION->GetIsClearProduction();
	if (isNotProduction)
	{
		for (int i = 0; i < CommonConstant::MAX_BACK_PIXEL_NUM; i++)
		{
			//	�_�̎g�p�󋵂͎g�p���̂Ƃ�
			const bool isBackPixelUse = m_backPixel[i].m_isInUse;
			if (isBackPixelUse)
			{
				//	�ړ�����
				m_backPixel[i].m_centerPoint.x -= m_backPixel[i].m_speed;
				m_backPixel[i].m_centerPoint.z = 0.0f;

				//	�͈͊O����
				const bool isMinXVal = m_backPixel[i].m_centerPoint.x <= START_POSTION.x;
				const bool isMinYVal = m_backPixel[i].m_centerPoint.y <= START_POSTION.y;
				const bool isMinVal = isMinXVal || isMinYVal;
				if (isMinVal) { m_backPixel[i].m_isInUse = false; }
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�_�̕`�揈��
//-----------------------------------------------------------------------------
void UIBackPixel::_DrawBackPixel()
{
	//	���o���ȊO
	const bool isNotProduction = !PRODUCTION->GetIsSpecialProduction() && !PRODUCTION->GetIsSceneProduction() && !PRODUCTION->GetIsClearProduction();
	if (isNotProduction)
	{
		for (int i = 0; i < CommonConstant::MAX_BACK_PIXEL_NUM; i++)
		{
			//	�_�̎g�p�󋵂͎g�p���̂Ƃ�
			const bool isBackPixelUse = m_backPixel[i].m_isInUse;
			if (isBackPixelUse)
			{
				DrawSphere3D(m_backPixel[i].m_centerPoint, m_backPixel[i].m_radius, 5, 0xffffff, 0xffffff, TRUE);
			}
		}
	}
}
