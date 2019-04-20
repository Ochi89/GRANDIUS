
//=============================================================================
//	@file	ItemManager.h
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
#include "DxLib.h"
#include "Common.h"
#include <list>

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class Item;

//-----------------------------------------------------------------------------
//	@brief	�A�C�e���}�l�[�W���[
//-----------------------------------------------------------------------------
class ItemManager final
{
public:

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	ItemManager();
	~ItemManager();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	�X�V����
	void Update();

	//	�`�揈��
	void Draw();

	//	���X�g�ɓo�^
	void RegisterOnList(const VECTOR _startPos);

	//	���X�g����폜
	void RemoveFromList(const Item* _itemPtr);

//==================== getter =====================//

	//	�g�p���X�g�̃T�C�Y�� getter
	const int GetListSize() const { return (int)m_useList.size(); }

	//	�V���b�g�ւ̃|�C���^�� getter
	Item* GetItemPtr(const int _num);

private:

//================== ���������֐� ==================//

	//	���X�g�̍X�V
	void _UpdateList();

	//	���X�g�̕`��
	void _DrawList();

	//	���X�g����폜
	void _RemoveFromList();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	Item*						m_pItem[CommonConstant::MAX_ITEM_NUM];	//	�A�C�e��
	std::list<Item*>			m_useList;								//	�g�p�A�C�e�����X�g
	std::list<Item*>			m_unusedList;							//	���g�p�A�C�e�����X�g
	int							m_sourceItem1ModelHandle;				//	��{�̃��f���n���h��
	int							m_sourceItem2ModelHandle;				//	��{�̃��f���n���h��
	int							m_sourceItem3ModelHandle;				//	��{�̃��f���n���h��

//===================== �ÓI�萔 ===================//

	static const float MIN_X_POS;		//	X���W�̍ŏ�
};