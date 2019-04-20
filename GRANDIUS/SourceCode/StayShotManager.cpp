
//=============================================================================
//	@file	StayShotManager.h
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
#include "StayShotManager.h"
#include "StayShot.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float StayShotManager::MAX_X_POS = 110.0f;	//	X���W�̍ő�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
StayShotManager::StayShotManager()
{
	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
	for (int i = 0; i < CommonConstant::MAX_STAY_SHOT_NUM; i++)
	{
		m_pStayShot[i] = NULL;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
StayShotManager::~StayShotManager()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void StayShotManager::Create()
{
	//	��������
	for (int i = 0; i < CommonConstant::MAX_STAY_SHOT_NUM; i++)
	{
		//	�V���b�g�̍쐬
		m_pStayShot[i] = new StayShot();

		//	���g�p���X�g�ɓo�^
		m_unusedList.push_back(m_pStayShot[i]);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void StayShotManager::Release()
{
	//	���X�g�ɓo�^����Ă�����폜
	if (!m_unusedList.empty()) { m_unusedList.clear(); }
	if (!m_useList.empty()) { m_useList.clear(); }

	//	�V���b�g�̉��
	for (int i = 0; i < CommonConstant::MAX_STAY_SHOT_NUM; i++)
	{
		CommonSafe::Delete(m_pStayShot[i]);
	}
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void StayShotManager::Initialize()
{
	//	���g�p���X�g����łȂ��Ƃ�
	if (!m_unusedList.empty())
	{
		//	������
		std::list<StayShot*>::iterator 	ite;
		for (ite = m_unusedList.begin(); ite != m_unusedList.end(); ite++)
		{
			(*ite)->Initialize();
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void StayShotManager::Update(SoundEffect& _soundEffect)
{
	//	�K�E�Z�̂Ƃ��͍X�V���Ȃ�
	const bool isNotSpecialProduction = !PRODUCTION->GetIsSpecialProduction();
	if (isNotSpecialProduction)
	{
		//	���X�g�̍X�V
		_UpdateList(_soundEffect);

		//	���X�g������
		_RemoveFromList();
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�ɓo�^
//-----------------------------------------------------------------------------
void StayShotManager::RegisterOnList(const VECTOR _startPos)
{
	//	���g�p���X�g����łȂ��Ƃ�
	const bool isAlreadyEntry = !m_unusedList.empty();
	if (isAlreadyEntry)
	{
		//	���g�p���X�g�̐擪�̃C�e���[�^�[�����
		std::list<StayShot*>::iterator 	ite;
		ite = m_unusedList.begin();

		//	�܂�������ݒ肵�Ă��Ȃ��Ƃ��͐ݒ肷��
		const bool isNotSet = !(*ite)->GetIsOneTime();
		if (isNotSet)
		{
			//	���e�̏�����
			(*ite)->SetStartPos(_startPos);
			(*ite)->SetIsOneTime(true);
		}

		//	���g�p���X�g����g�p���X�g�ɓo�^
		m_useList.push_back(*ite);

		//	���g�p���X�g����폜
		m_unusedList.remove(*ite);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�V���b�g�ւ̃|�C���^�̎擾
//-----------------------------------------------------------------------------
StayShot* StayShotManager::GetStayShotPtr(const int _num)
{
	int counter = 0;

	//	�g�p���X�g����łȂ��Ƃ�
	if (!m_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<StayShot*>::iterator 	ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	_num �ƈ�v�����|�C���^��Ԃ�
			const bool isSame = counter == _num;
			if (isSame) { return (*ite); }
			counter++;
		}
	}

	return NULL;
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�̍X�V
//-----------------------------------------------------------------------------
void StayShotManager::_UpdateList(SoundEffect& _soundEffect)
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!m_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<StayShot*>::iterator 	ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	�X�V����
			(*ite)->Update(_soundEffect);
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void StayShotManager::_RemoveFromList()
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!m_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<StayShot*>::iterator 	ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	�͈͊O���A�V���b�g���I�����Ă�����A
			//	���X�g����폜����
			const bool isArrivalRight = (*ite)->GetPos().x >= MAX_X_POS;
			const bool isActive = isArrivalRight || (*ite)->GetIsShotEnd();
			if (isActive)
			{
				//	������
				(*ite)->Initialize();

				//	�g�p���X�g���疢�g�p���X�g�ɓo�^
				m_unusedList.push_back(*ite);

				//	�g�p���X�g����폜
				m_useList.remove(*ite);

				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void StayShotManager::_FinalRelease()
{
	//	���X�g�ɓo�^����Ă�����폜
	if (!m_unusedList.empty()) { m_unusedList.clear(); }
	if (!m_useList.empty()) { m_useList.clear(); }

	//	�V���b�g�̉��
	for (int i = 0; i < CommonConstant::MAX_STAY_SHOT_NUM; i++)
	{
		CommonSafe::Delete(m_pStayShot[i]);
	}
}
