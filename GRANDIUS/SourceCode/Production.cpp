
//=============================================================================
//	@file	Production.h
//	@brief	�V���b�g�}�l�[�W���[
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
#include "Production.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const VECTOR	Production::GAUGE_START_VERTEX_1 = VGet(0.0f, 0.0f, 0.0f);			//	�Q�[�W�̊J�n���_�P
const VECTOR	Production::GAUGE_START_VERTEX_2 = VGet(0.0f, 1080.0f, 0.0f);		//	�Q�[�W�̊J�n���_�Q
const VECTOR	Production::GAUGE_END_VERTEX_1 = VGet(1920.0f, 0.0f, 0.0f);			//	�Q�[�W�̏I�����_�P
const VECTOR	Production::GAUGE_END_VERTEX_2 = VGet(1920.0f, 1080.0f, 0.0f);		//	�Q�[�W�̏I�����_�Q
const float		Production::MAX_Y_AXIS_1 = 120.0f;									//	�Q�[�W�̍ő�l
const float		Production::MAX_Y_AXIS_2 = 960.0f;									//	�Q�[�W�̍ő�l
const float		Production::GAUGE_ADD_SPEED = 10.0f;								//	�Q�[�W�̉��Z���x�P

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Production::Production()
{
	//	�e�ϐ��̏�����
	m_gaugeBar1.m_vertexTop = GAUGE_START_VERTEX_1;
	m_gaugeBar1.m_vertexUnder = GAUGE_END_VERTEX_1;
	m_gaugeBar2.m_vertexTop = GAUGE_START_VERTEX_2;
	m_gaugeBar2.m_vertexUnder = GAUGE_END_VERTEX_2;
	m_gaugeColor = GetColor(30, 30, 30);
	m_isSceneProduction = false;
	m_isSpecialProduction = false;
	m_isClearProduction = false;
	m_isTitleProduction = false;
	m_specialProductionTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Production::~Production()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void Production::Update()
{
	//	���o��
	const bool isActive = m_isSceneProduction || m_isSpecialProduction || m_isClearProduction;
	if (isActive)
	{
		//	���o���Ȃ̂ŁA
		//	�Q�[�W���o��������
		_EmergenceGauge();
		return;
	}

	//	���o���ł͂Ȃ��̂ŁA
	//	�Q�[�W�����̏�Ԃɖ߂�
	_RestoreGauge();
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void Production::Draw()
{
	//	�Q�[�W�̕`��
	DrawBox((int)m_gaugeBar1.m_vertexTop.x, (int)m_gaugeBar1.m_vertexTop.y, (int)m_gaugeBar1.m_vertexUnder.x, (int)m_gaugeBar1.m_vertexUnder.y, m_gaugeColor, TRUE);
	DrawBox((int)m_gaugeBar2.m_vertexTop.x, (int)m_gaugeBar2.m_vertexTop.y, (int)m_gaugeBar2.m_vertexUnder.x, (int)m_gaugeBar2.m_vertexUnder.y, m_gaugeColor, TRUE);
}

//-----------------------------------------------------------------------------
//	@brief	�K�E�Z�̃��Z�b�g
//-----------------------------------------------------------------------------
void Production::ResetSpecialProduction()
{
	m_specialProductionTime = 0.0f; 
	m_isSpecialProduction = false; 
}

//-----------------------------------------------------------------------------
//	@brief	���ׂẴ��Z�b�g
//-----------------------------------------------------------------------------
void Production::AllReset()
{
	//	�e�ϐ��̏�����
	m_gaugeBar1.m_vertexTop = GAUGE_START_VERTEX_1;
	m_gaugeBar1.m_vertexUnder = GAUGE_END_VERTEX_1;
	m_gaugeBar2.m_vertexTop = GAUGE_START_VERTEX_2;
	m_gaugeBar2.m_vertexUnder = GAUGE_END_VERTEX_2;
	m_gaugeColor = GetColor(30, 30, 30);
	m_isSceneProduction = false;
	m_isSpecialProduction = false;
	m_isClearProduction = false;
	m_isTitleProduction = false;
	m_specialProductionTime = 0.0f;
}

//-----------------------------------------------------------------------------
//	@brief	�Q�[�W�̏o��
//-----------------------------------------------------------------------------
void Production::_EmergenceGauge()
{
	m_gaugeBar1.m_vertexUnder.y += GAUGE_ADD_SPEED;
	m_gaugeBar2.m_vertexTop.y -= GAUGE_ADD_SPEED;

	//	�Q�[�W�̍ő�ŏ�����
	const bool isMaxGauge1 = m_gaugeBar1.m_vertexUnder.y >= MAX_Y_AXIS_1;
	const bool isMaxGauge2 = m_gaugeBar2.m_vertexTop.y <= MAX_Y_AXIS_2;
	const bool isMax = isMaxGauge1 || isMaxGauge2;
	if (isMax)
	{
		m_gaugeBar1.m_vertexUnder.y = MAX_Y_AXIS_1;
		m_gaugeBar2.m_vertexTop.y = MAX_Y_AXIS_2;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�Q�[�W�����ɖ߂�
//-----------------------------------------------------------------------------
void Production::_RestoreGauge()
{
	m_gaugeBar1.m_vertexUnder.y -= GAUGE_ADD_SPEED;
	m_gaugeBar2.m_vertexTop.y += GAUGE_ADD_SPEED;

	//	�Q�[�W�̍ő�ŏ�����
	const bool isMaxGauge1 = m_gaugeBar1.m_vertexUnder.y <= GAUGE_END_VERTEX_1.y;
	const bool isMaxGauge2 = m_gaugeBar2.m_vertexTop.y >= GAUGE_START_VERTEX_2.y;
	const bool isMax = isMaxGauge1 || isMaxGauge2;
	if (isMax)
	{
		m_gaugeBar1.m_vertexUnder.y = GAUGE_END_VERTEX_1.y;
		m_gaugeBar2.m_vertexTop.y = GAUGE_START_VERTEX_2.y;
	}
}
