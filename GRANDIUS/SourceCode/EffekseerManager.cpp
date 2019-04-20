
//=============================================================================
//	@file	EffekseerManager.cpp
//	@brief	EffekseerManager
//	@autor	���m ���
//	@date	2018/12/31
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EffekseerManager.h"

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
EffekseerManager::EffekseerManager()
{
	//	Effekseer����������
	const int maxParticleNum = 8000;
	CommonDebug::Assert((Effkseer_Init(maxParticleNum) == -1), " [ EffekseerManager.cpp ] : error : failed to initialize the effkseer .");
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
EffekseerManager::~EffekseerManager()
{
	//	Effekseer�̏I������
	Effkseer_End();
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void EffekseerManager::Update()
{
	//	DX���C�u�����̃J������EffekseerEmitter�̃J�����𓯊�
	Effekseer_Sync3DSetting();

	//	EffekseerEmitter�ɂ��Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void EffekseerManager::Draw()
{
	//	Z�o�b�t�@���g�p����ݒ�ɕύX
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	//	EffekseerEmitter�ɂ��Đ����̃G�t�F�N�g��`��
	DrawEffekseer3D();

	//	Z�o�b�t�@���g�p���Ȃ��ݒ�ɕύX
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);
}
