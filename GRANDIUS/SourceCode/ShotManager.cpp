
//=============================================================================
//	@file	ShotManager.h
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
#include "ShotManager.h"
#include "Shot.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float ShotManager::MAX_X_POS = 110.0f;	//	X���W�̍ő�
const float ShotManager::MIN_X_POS = -110.0f;	//	X���W�̍ŏ�
const float ShotManager::MAX_Y_POS = 120.0f;	//	Y���W�̍ő�
const float ShotManager::MIN_Y_POS = 0.0f;		//	Y���W�̍ŏ�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
ShotManager::ShotManager()
{
	//	�܂��ǂ����w���Ă��Ȃ��̂ŁANULL�ŏ�����
	for (int i = 0; i < CommonConstant::MAX_SHOT_NUM; i++)
	{
		m_pPlayerShot[i] = NULL;
		m_pEnemyShot[i] = NULL;
	}

	//	�e�ϐ��̏�����
	m_sourcePlayerShotModelHandle = -1;
	m_sourceEnemyShotModelHandle = -1;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
ShotManager::~ShotManager()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	�쐬����
//-----------------------------------------------------------------------------
void ShotManager::Create()
{
	//	��{���f���̃��[�h
	m_sourcePlayerShotModelHandle = MV1LoadModel("Data/Model/Player/PlayerShot.mqo");
	m_sourceEnemyShotModelHandle = MV1LoadModel("Data/Model/Enemy/EnemyShot.mqo");

	CommonDebug::Assert((m_sourcePlayerShotModelHandle <= -1), " [ ShotManager.cpp ] : error : model loading failed.");
	CommonDebug::Assert((m_sourceEnemyShotModelHandle <= -1), " [ ShotManager.cpp ] : error : model loading failed.");

	//	��������
	for (int i = 0; i < CommonConstant::MAX_SHOT_NUM; i++)
	{
		//	�V���b�g�̍쐬
		m_pPlayerShot[i] = new Shot(m_sourcePlayerShotModelHandle);
		m_pEnemyShot[i] = new Shot(m_sourceEnemyShotModelHandle);

		//	���g�p���X�g�ɓo�^
		m_unusedPlayerShotList.push_back(m_pPlayerShot[i]);
		m_unusedEnemyShotList.push_back(m_pEnemyShot[i]);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�������
//-----------------------------------------------------------------------------
void ShotManager::Release()
{
	//	��{���f���̃A�����[�h
	MV1DeleteModel(m_sourcePlayerShotModelHandle);
	MV1DeleteModel(m_sourceEnemyShotModelHandle);

	//	���X�g�ɓo�^����Ă�����폜
	if (!m_unusedPlayerShotList.empty()) { m_unusedPlayerShotList.clear(); }
	if (!m_unusedEnemyShotList.empty()) { m_unusedEnemyShotList.clear(); }
	if (!m_usePlayerShotList.empty()) { m_usePlayerShotList.clear(); }
	if (!m_useEnemyShotList.empty()) { m_useEnemyShotList.clear(); }

	//	�V���b�g�̉��
	for (int i = 0; i < CommonConstant::MAX_SHOT_NUM; i++)
	{
		CommonSafe::Delete(m_pPlayerShot[i]);
		CommonSafe::Delete(m_pEnemyShot[i]);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void ShotManager::Update()
{
	//	�K�E�Z�̂Ƃ��͍X�V���Ȃ�
	const bool isNotSpecialProduction = !PRODUCTION->GetIsSpecialProduction();
	if (isNotSpecialProduction)
	{
		//	���X�g�̍X�V
		_UpdateList(SHOT_KIND::PLAYER_SHOT);
		_UpdateList(SHOT_KIND::ENEMY_SHOT);

		//	�������
		_RemoveFromList(SHOT_KIND::PLAYER_SHOT);
		_RemoveFromList(SHOT_KIND::ENEMY_SHOT);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void ShotManager::Draw()
{
	_DrawList(SHOT_KIND::PLAYER_SHOT);
	_DrawList(SHOT_KIND::ENEMY_SHOT);
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�ɓo�^
//-----------------------------------------------------------------------------
void ShotManager::RegisterOnList(const SHOT_KIND _shotKind, const VECTOR _startPos, const VECTOR _startDir, const float _speed, SoundEffect& _soundEffect)
{
	//	���g�p���X�g����g�p���X�g�ɓo�^
	switch (_shotKind)
	{
	case SHOT_KIND::PLAYER_SHOT:
		_RegisterOnList(m_usePlayerShotList, m_unusedPlayerShotList, _startPos, _startDir, _speed, _soundEffect);
		break;

	case SHOT_KIND::ENEMY_SHOT:
		_RegisterOnList(m_useEnemyShotList, m_unusedEnemyShotList, _startPos, _startDir, _speed, _soundEffect);
		break;
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�ɓo�^
//-----------------------------------------------------------------------------
void ShotManager::RegisterOnList(const SHOT_KIND _shotKind, const VECTOR _startPos, const VECTOR _startDir, const float _speed)
{
	//	���g�p���X�g����g�p���X�g�ɓo�^
	switch (_shotKind)
	{
	case SHOT_KIND::PLAYER_SHOT:
		_RegisterOnList(m_usePlayerShotList, m_unusedPlayerShotList, _startPos, _startDir, _speed);
		break;

	case SHOT_KIND::ENEMY_SHOT:
		_RegisterOnList(m_useEnemyShotList, m_unusedEnemyShotList, _startPos, _startDir, _speed);
		break;
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void ShotManager::RemoveFromList(const SHOT_KIND _shotKind, const Shot* _shotPtr)
{
	//	�g�p���X�g����폜
	switch (_shotKind)
	{
	case SHOT_KIND::PLAYER_SHOT:
		_RemoveFromList(m_usePlayerShotList, m_unusedPlayerShotList, _shotPtr);
		break;

	case SHOT_KIND::ENEMY_SHOT:
		_RemoveFromList(m_useEnemyShotList, m_unusedEnemyShotList, _shotPtr);
		break;
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�̃T�C�Y�̎擾
//-----------------------------------------------------------------------------
const int ShotManager::GetListSize(const SHOT_KIND _shotKind) const
{
	//	���X�g�̃T�C�Y�̎擾
	switch (_shotKind)
	{
	case SHOT_KIND::PLAYER_SHOT:
		return m_usePlayerShotList.size();

	case SHOT_KIND::ENEMY_SHOT:
		return m_useEnemyShotList.size();
	}

	return 0;
}

//-----------------------------------------------------------------------------
//	@brief	�V���b�g�ւ̃|�C���^�̎擾
//-----------------------------------------------------------------------------
Shot* ShotManager::GetShotPtr(const SHOT_KIND _shotKind, const int _num)
{
	//	�V���b�g�ւ̃|�C���^�̎擾
	switch (_shotKind)
	{
	case SHOT_KIND::PLAYER_SHOT:
		return _GetShotPtr(m_usePlayerShotList, _num);

	case SHOT_KIND::ENEMY_SHOT:
		return _GetShotPtr(m_useEnemyShotList, _num);
	}

	return NULL;
}

//-----------------------------------------------------------------------------
//	@brief	�V���b�g�ւ̃|�C���^�̎擾
//-----------------------------------------------------------------------------
Shot* ShotManager::_GetShotPtr(std::list<Shot*>& _useList, const int _num)
{
	int counter = 0;

	//	�g�p���X�g����łȂ��Ƃ�
	if (!_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Shot*>::iterator 	ite;
		for (ite = _useList.begin(); ite != _useList.end(); ite++)
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
//	@brief	���X�g�ɓo�^
//-----------------------------------------------------------------------------
void ShotManager::_RegisterOnList(std::list<Shot*>& _useList, std::list<Shot*>& _unusedList, const VECTOR _startPos, const VECTOR _startDir, const float _speed, SoundEffect& _soundEffect)
{
	//	���g�p���X�g����łȂ��Ƃ�
	if (!_unusedList.empty())
	{
		//	���g�p���X�g�̐擪�̃C�e���[�^�[�����
		std::list<Shot*>::iterator 	ite;
		ite = _unusedList.begin();

		//	�܂�������ݒ肵�Ă��Ȃ��Ƃ��͐ݒ肷��
		if (!(*ite)->GetIsOneTime())
		{
			//	���e�̏�����
			(*ite)->SetStartPos(_startPos);
			(*ite)->SetStartDir(_startDir);
			(*ite)->SetSpeed(_speed);
			(*ite)->SetIsOneTime(true);
			_soundEffect.OnPlaySound(_soundEffect.SE_KIND::SE_SHOT);
		}

		//	���g�p���X�g����g�p���X�g�ɓo�^
		_useList.push_back(*ite);

		//	���g�p���X�g����폜
		_unusedList.remove(*ite);
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�ɓo�^
//-----------------------------------------------------------------------------
void ShotManager::_RegisterOnList(std::list<Shot*>& _useList, std::list<Shot*>& _unusedList, const VECTOR _startPos, const VECTOR _startDir, const float _speed)
{
	//	���g�p���X�g����łȂ��Ƃ�
	if (!_unusedList.empty())
	{
		//	���g�p���X�g�̐擪�̃C�e���[�^�[�����
		std::list<Shot*>::iterator 	ite;
		ite = _unusedList.begin();

		//	�܂�������ݒ肵�Ă��Ȃ��Ƃ��͐ݒ肷��
		if (!(*ite)->GetIsOneTime())
		{
			//	���e�̏�����
			(*ite)->SetStartPos(_startPos);
			(*ite)->SetStartDir(_startDir);
			(*ite)->SetSpeed(_speed);
			(*ite)->SetIsOneTime(true);
		}

		//	���g�p���X�g����g�p���X�g�ɓo�^
		_useList.push_back(*ite);

		//	���g�p���X�g����폜
		_unusedList.remove(*ite);
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�̍X�V
//-----------------------------------------------------------------------------
void ShotManager::_UpdateList(const SHOT_KIND _shotKind)
{
	//	�g�p���X�g�̍X�V
	switch (_shotKind)
	{
	case SHOT_KIND::PLAYER_SHOT:
		_UpdateList(m_usePlayerShotList);
		break;

	case SHOT_KIND::ENEMY_SHOT:
		_UpdateList(m_useEnemyShotList);
		break;
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g�̍X�V
//-----------------------------------------------------------------------------
void ShotManager::_UpdateList(std::list<Shot*>& _useList)
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Shot*>::iterator 	ite;
		for (ite = _useList.begin(); ite != _useList.end(); ite++)
		{
			//	�X�V����
			(*ite)->Update();
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void ShotManager::_DrawList(const SHOT_KIND _shotKind)
{
	//	�g�p���X�g�̕`��
	switch (_shotKind)
	{
	case SHOT_KIND::PLAYER_SHOT:
		_DrawList(m_usePlayerShotList);
		break;

	case SHOT_KIND::ENEMY_SHOT:
		_DrawList(m_useEnemyShotList);
		break;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void ShotManager::_DrawList(std::list<Shot*>& _useList)
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Shot*>::iterator 	ite;
		for (ite = _useList.begin(); ite != _useList.end(); ite++)
		{
			(*ite)->Draw();
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void ShotManager::_RemoveFromList(const SHOT_KIND _shotKind)
{
	//	�g�p���X�g����폜
	switch (_shotKind)
	{
	case SHOT_KIND::PLAYER_SHOT:
		_RemoveFromList(m_usePlayerShotList, m_unusedPlayerShotList);
		break;

	case SHOT_KIND::ENEMY_SHOT:
		_RemoveFromList(m_useEnemyShotList, m_unusedEnemyShotList);
		break;
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void ShotManager::_RemoveFromList(std::list<Shot*>& _useList, std::list<Shot*>& _unusedList)
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Shot*>::iterator 	ite;
		for (ite = _useList.begin(); ite != _useList.end(); ite++)
		{
			//	�͈͊O�̂Ƃ��́A�폜����
			const bool isArrivalTop = (*ite)->GetPos().y >= MAX_Y_POS;
			const bool isArrivalButtom = (*ite)->GetPos().y <= MIN_Y_POS;
			const bool isArrivalRight = (*ite)->GetPos().x >= MAX_X_POS;
			const bool isArrivalLeft = (*ite)->GetPos().x <= MIN_X_POS;
			const bool isActive = isArrivalTop || isArrivalButtom || isArrivalRight || isArrivalLeft;
			if (isActive)
			{
				//	�ݒ�\�ɂ���
				(*ite)->SetIsOneTime(false);

				//	�g�p���X�g���疢�g�p���X�g�ɓo�^
				_unusedList.push_back(*ite);

				//	�g�p���X�g����폜
				_useList.remove(*ite);

				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	���X�g����폜
//-----------------------------------------------------------------------------
void ShotManager::_RemoveFromList(std::list<Shot*>& _useList, std::list<Shot*>& _unusedList, const Shot* _shotPtr)
{
	//	�g�p���X�g����łȂ��Ƃ�
	if (!_useList.empty())
	{
		//	���X�g�̉񐔕���
		std::list<Shot*>::iterator 	ite;
		for (ite = _useList.begin(); ite != _useList.end(); ite++)
		{
			//	_num �ƈ�v�����|�C���^��Ԃ�
			const bool isSame = _shotPtr == (*ite);
			if (isSame)
			{
				//	�ݒ�\�ɂ���
				(*ite)->SetIsOneTime(false);

				//	�g�p���X�g���疢�g�p���X�g�ɓo�^
				_unusedList.push_back(*ite);

				//	�g�p���X�g����폜
				_useList.remove(*ite);

				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void ShotManager::_FinalRelease()
{
	//	��{���f���̃A�����[�h
	MV1DeleteModel(m_sourcePlayerShotModelHandle);
	MV1DeleteModel(m_sourceEnemyShotModelHandle);

	//	���X�g�ɓo�^����Ă�����폜
	if (!m_unusedPlayerShotList.empty()) { m_unusedPlayerShotList.clear(); }
	if (!m_unusedEnemyShotList.empty()) { m_unusedEnemyShotList.clear(); }
	if (!m_usePlayerShotList.empty()) { m_usePlayerShotList.clear(); }
	if (!m_useEnemyShotList.empty()) { m_useEnemyShotList.clear(); }

	//	�V���b�g�̉��
	for (int i = 0; i < CommonConstant::MAX_SHOT_NUM; i++)
	{
		CommonSafe::Delete(m_pPlayerShot[i]);
		CommonSafe::Delete(m_pEnemyShot[i]);
	}
}
