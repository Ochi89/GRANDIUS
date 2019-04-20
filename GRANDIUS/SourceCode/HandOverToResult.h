
//=============================================================================
//	@file	HandOverToResult.h
//	@brief	���U���g�ֈ����n��
//	@autor	���m ���
//	@date	2018/1/03
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
//	@brief	�����n���N���X
//-----------------------------------------------------------------------------
class HandOverToResult final
{
public:

//===================== �֐� ======================//

	//	�f�X�g���N�^
	~HandOverToResult();

	//	����
	static HandOverToResult* GetInstance()
	{
		static HandOverToResult s_instance;
		return &s_instance;
	}

	//	���Z�b�g
	void Reset();

	//	�������̉��Z
	void AddDestructionNum() { m_destructionNum++; }

//==================== getter =====================//

	//	���C�t�� getter
	const int& GetLife() const { return m_life; }

	//	�������� getter
	const int& GetDestructionNum() const { return m_destructionNum; }

	//	�N���A�������� getter
	const bool& GetIsClear() const { return m_isClear; }

//==================== setter =====================//

	//	���C�t�� setter
	void SetLife(const int _set) { m_life = _set; }

	//	�������� setter
	void SetDestructionNum(const int _set) { m_destructionNum = _set; }

	//	�N���A�������� setter
	void SetIsClear(const bool _set) { m_isClear = _set; }

private:

//================== �V���O���g�� ==================//

	// �R���X�g���N�^
	HandOverToResult();

//=================== �����o�ϐ� ===================//

	int		m_life;					//	���C�t
	int		m_destructionNum;		//	������
	bool	m_isClear;				//	�N���A������

};

#define HAND_OVER_RESULT HandOverToResult::GetInstance()