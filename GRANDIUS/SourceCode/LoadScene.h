
//=============================================================================
//	@file	LoadScene.h
//	@brief	���[�f�B���O
//	@autor	���m ���
//	@date	2018/12/30
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
//	@brief	���[�f�B���O�N���X
//-----------------------------------------------------------------------------
class Loading final
{
public:

//===================== �֐� ======================//

	//	�f�X�g���N�^
	~Loading();

	//	����
	static Loading* GetInstance()
	{
		static Loading m_instance;
		return &m_instance;
	}

	//	�`��
	void Draw();

private:

//================== �V���O���g�� ==================//

	//	�R���X�g���N�^
	Loading();

//=================== �����o�ϐ� ===================//

	int		m_spriteHendle;		//	�X�v���C�g�n���h��

};

#define LOADING Loading::GetInstance()