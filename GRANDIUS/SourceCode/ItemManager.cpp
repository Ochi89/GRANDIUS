
//=============================================================================
//	@file	ItemManager.cpp
//	@brief	�A�C�e���}�l�[�W���[
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
#include "ItemManager.h"
#include "Item.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float ItemManager::MIN_X_POS = -110.0f;	//	X���W�̍ŏ�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
ItemManager::ItemManager()
{
	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
	for (int i = 0; i < CommonConstant::MAX_ITEM_NUM; i++)
	{
		m_pItem[i] = NULL;
	}

	//	�e�ϐ��̏�����
	m_sourceItem1ModelHandle = -1;
	m_sourceItem2ModelHandle = -1;
	m_sourceItem3ModelHandle = -1;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
ItemManager::~ItemManager()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void ItemManager::Create()
{
	//	��{���f���̃��[�h
	m_sourceItem1ModelHandle = MV1LoadModel("Data/Model/Item/Item1.mqo");
	m_sourceItem2ModelHandle = MV1LoadModel("Data/Model/Item/Item2.mqo");
	m_sourceItem3ModelHandle = MV1LoadModel("Data/Model/Item/Item3.mqo");
	CommonDebug::Assert((m_sourceItem1ModelHandle <= -1), " [ Shooter.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_sourceItem2ModelHandle <= -1), " [ Shooter.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_sourceItem3ModelHandle <= -1), " [ Shooter.cpp ] : error : model loading failed.");

	//	��������
	for (int i = 0; i < CommonConstant::MAX_ITEM_NUM; i++)
	{
		//	�V���b�g�̍쐬
		m_pItem[i] = new Item(m_sourceItem1ModelHandle, m_sourceItem2ModelHandle, m_sourceItem3ModelHandle);

		//	���g�p���X�g�ɓo�^
		m_unusedList.push_back(m_pItem[i]);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void ItemManager::Release()
{
	//	��{���f���̃A�����[�h
	MV1DeleteModel(m_sourceItem1ModelHandle);
	MV1DeleteModel(m_sourceItem2ModelHandle);
	MV1DeleteModel(m_sourceItem3ModelHandle);

	//	���X�g�ɓo�^����Ă�����폜
	if (!m_unusedList.empty()) { m_unusedList.clear(); }
	if (!m_useList.empty()) { m_useList.clear(); }

	//	�V���b�g�̉��
	for (int i = 0; i < CommonConstant::MAX_ITEM_NUM; i++)
	{
		CommonSafe::Delete(m_pItem[i]);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void ItemManager::Update()
{
	//	�K�E�Z�̂Ƃ��͍X�V���Ȃ�
	const bool isNotSpecialProduction = !PRODUCTION->GetIsSpecialProduction();
	if (isNotSpecialProduction)
	{
		//	�������
		_RemoveFromList();

		//	���X�g�̍X�V
		_UpdateList();
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void ItemManager::Draw()
{
	_DrawList();
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�ɓo�^
//-----------------------------------------------------------------------------
void ItemManager::RegisterOnList(const VECTOR _startPos)
{
	//	���g�p���X�g����łȂ��Ƃ�
	if (!m_unusedList.empty())
	{
		//	���g�p���X�g�̐擪�̃C�e���[�^�[�����
		std::list<Item*>::iterator 	ite;
		ite = m_unusedList.begin();

		//	�܂�������ݒ肵�Ă��Ȃ��Ƃ��͐ݒ肷��
		if (!(*ite)->GetIsOneTime())
		{
			//	���e�̏�����
			(*ite)->SetStartPos(_startPos);
			(*ite)->SetIsOneTime(true);
			(*ite)->Update();
		}

		//	���g�p���X�g����g�p���X�g�ɓo�^
		m_useList.push_back(*ite);

		//	���g�p���X�g����폜
		m_unusedList.remove(*ite);
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void ItemManager::RemoveFromList(const Item* _itemPtr)
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!m_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Item*>::iterator 	ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	_num �ƈ�v�����|�C���^��Ԃ�
			const bool isSame = _itemPtr == (*ite);
			if (isSame)
			{
				//	�������ɂ���
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
//	@brief	�A�C�e���̃|�C���^�� getter
//-----------------------------------------------------------------------------
Item* ItemManager::GetItemPtr(const int _num)
{
	int counter = 0;

	//	�g�p���X�g����łȂ��Ƃ�
	if (!m_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Item*>::iterator 	ite;
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
void ItemManager::_UpdateList()
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!m_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Item*>::iterator 	ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	�X�V����
			(*ite)->Update();
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void ItemManager::_DrawList()
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!m_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Item*>::iterator 	ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			(*ite)->Draw();
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void ItemManager::_RemoveFromList()
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!m_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Item*>::iterator 	ite;
		for (ite = m_useList.begin(); ite != m_useList.end(); ite++)
		{
			//	�͈͊O�̂Ƃ��́A�폜����
			const bool isActive = (*ite)->GetPos().x <= MIN_X_POS;
			if (isActive)
			{
				//	�ݒ�\�ɂ���
				(*ite)->SetIsOneTime(false);

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
void ItemManager::_FinalRelease()
{
	//	��{���f���̃A�����[�h
	MV1DeleteModel(m_sourceItem1ModelHandle);
	MV1DeleteModel(m_sourceItem2ModelHandle);
	MV1DeleteModel(m_sourceItem3ModelHandle);

	//	���X�g�ɓo�^����Ă�����폜
	if (!m_unusedList.empty()) { m_unusedList.clear(); }
	if (!m_useList.empty()) { m_useList.clear(); }

	//	�V���b�g�̉��
	for (int i = 0; i < CommonConstant::MAX_ITEM_NUM; i++)
	{
		CommonSafe::Delete(m_pItem[i]);
	}
}
