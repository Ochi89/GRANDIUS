
//=============================================================================
//	@file	StayShotManager.h
//	@brief	�؍݃V���b�g�}�l�[�W���[
//	@autor	���m ���
//	@date	2018/12/25
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
#include <list>

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class StayShot;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�X�e�C�V���b�g�}�l�[�W���[
//-----------------------------------------------------------------------------
class StayShotManager final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	StayShotManager();
	~StayShotManager();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	��������
	void Initialize();

	//	�X�V����
	void Update(SoundEffect& _soundEffect);

	//	���X�g�ɓo�^
	void RegisterOnList(const VECTOR _startPos);

//==================== getter =====================//

	//	�g�p���X�g�̃T�C�Y�� getter
	const int GetListSize() const { return (int)m_useList.size(); }

	//	�V���b�g�ւ̃|�C���^�� getter
	StayShot* GetStayShotPtr(const int _num);

private:

	//================== ���������֐� ==================//

	//	���X�g�̍X�V
	void _UpdateList(SoundEffect& _soundEffect);

	//	���X�g������
	void _RemoveFromList();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

	//=================== �����o�ϐ� ===================//

	StayShot*				m_pStayShot[CommonConstant::MAX_STAY_SHOT_NUM];		//	�؍݃V���b�g
	std::list<StayShot*>	m_useList;											//	�g�p�V���b�g���X�g
	std::list<StayShot*>	m_unusedList;										//	���g�p�V���b�g���X�g

//===================== �ÓI�萔 ===================//

	static const float MAX_X_POS;		//	X���W�̍ő�

};