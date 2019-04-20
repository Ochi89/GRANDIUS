
//=============================================================================
//	@file	BackGround.cpp
//	@brief	�w�i
//	@autor	���m ���
//	@date	2018/12/22
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BackGround.h"
#include "Common.h"
#include "MoveHelper.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float BackGround::SKYDOME_MOVE_SPEED = 0.0005f;			//	�X�J�C�h�[���̈ړ����x

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
BackGround::BackGround()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
BackGround::~BackGround()
{
	//	�ŏI�I�ȉ��
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬
//-----------------------------------------------------------------------------
void BackGround::Create()
{
	m_productionTime = 0.0f;

    //	���f���̓ǂݍ���
    m_modelHandle = MV1LoadModel("Data/Model/BackGround/Skydome.x");
    CommonDebug::Assert((m_modelHandle <= -1), " [ BackGround.cpp ] : error : model loading failed.");

    //	�e�ϐ��̏�����
    m_pos = CommonConstant::ORIGIN;
    m_dir = CommonConstant::ORIGIN;
    m_angle = CommonConstant::ORIGIN;
    m_size = VGet(1.0f, 1.0f, 1.0f);
}

//-----------------------------------------------------------------------------
//	@brief	���
//-----------------------------------------------------------------------------
void BackGround::Release()
{
	MV1DeleteModel(m_modelHandle);
}


//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void BackGround::Update()
{
	//	�K�E�Z�̂Ƃ��͍X�V���Ȃ�
	const bool isNotSpecialProduction = !PRODUCTION->GetIsSpecialProduction();
	if (isNotSpecialProduction)
	{
		//	�X�J�C�h�[������]
		m_angle.y -= SKYDOME_MOVE_SPEED;

		//	�X�J�C�h�[��
		MV1SetPosition(m_modelHandle, m_pos);
		MV1SetRotationXYZ(m_modelHandle, m_angle);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`��
//-----------------------------------------------------------------------------
void BackGround::Draw()
{
	//	�`��
	MV1DrawModel(m_modelHandle);
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ��
//-----------------------------------------------------------------------------
void BackGround::_FinalRelease()
{
	MV1DeleteModel(m_modelHandle);
}