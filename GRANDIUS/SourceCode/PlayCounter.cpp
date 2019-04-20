
//=============================================================================
//	@file	PlayCounter.cpp
//	@brief	�v���C��
//	@autor	���m ���
//	@date	2018/1/9
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayCounter.h"
#include "LoadFile.h"

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
PlayCounter::PlayCounter()
{
	m_playCpunt = 0;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
PlayCounter::~PlayCounter()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�v���C�񐔂̉��Z
//-----------------------------------------------------------------------------
void PlayCounter::AddPlayCounter()
{
	//	�ǂݍ���
	_Load();

	//	�v���C�񐔂̉��Z
	m_playCpunt++;

	//	��������
	_Writing();
}

//-----------------------------------------------------------------------------
//	@brief	�ǂݍ���
//-----------------------------------------------------------------------------
void PlayCounter::_Load()
{
	//	�t�@�C���̓ǂݍ���
	LOAD_FILE->LoadCsvFile("Data/CSV/PlayCounter.csv");

	//	���e�̎擾
	m_playCpunt = LOAD_FILE->GetCsvFile();
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void PlayCounter::_Writing()
{
	//	��������
	LOAD_FILE->WritingCsvFile("Data/CSV/PlayCounter.csv", m_playCpunt);
}