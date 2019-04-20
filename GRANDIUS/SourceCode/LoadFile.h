
//=============================================================================
//	@file	LoadFile.h
//	@brief	�t�@�C���̓ǂݍ���
//	@autor	���m ���
//	@date	2018/10/28
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
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//-----------------------------------------------------------------------------
//	@brief	�t�@�C���̓ǂݍ��݃N���X
//-----------------------------------------------------------------------------
class LoadFile final
{
public:

//===================== �֐� ======================//

	~LoadFile();								//	�f�X�g���N�^
	
	//	����
	static LoadFile* GetInstance()
	{
		static LoadFile m_instance;
		return &m_instance;
	}

	//	CSV �Q�����t�@�C���̓ǂݍ���
	bool LoadCsvTwoDimensionsFile(const char* _fileName);

	//	�t�@�C���̓ǂݍ���
	bool LoadCsvFile(const char* _fileName);

	//	CSV �Q�����t�@�C���̎擾
	int GetCsvFile(const int _row, const int _col);

	//	CSV �t�@�C���̎擾
	int GetCsvFile(const int _row = 0);

	//	CSV �t�@�C���̏�������
	bool WritingCsvFile(const char* _fileName, const float _writingVal);

	//	CSV �t�@�C���̏�������
	bool WritingCsvFile(const char* _fileName, const int _writingVal);

	//	CSV �t�@�C���̏�������
	bool WritingCsvFile(const char* _fileName, const int _size, int* _writingVal);

private:

//================== �V���O���g�� ==================//

	//	�R���X�g���N�^
	LoadFile();

//================== ���������֐� ==================//
	
	//	�ǂݎ��̋�؂�
	std::vector<std::string> _Split(std::string& _input, char _split);

	//	�ǂݍ���
	bool _Load(const char* _fileName, std::vector<std::string>& _strvec, int* date);

	//	�ǂݍ���
	bool _Load(const char* _fileName, std::vector<std::string>& _strvec, float* date);

	//	�\�[�g
	void _Sort(std::vector<std::string>& _strvec, const float _writingVal, int* date);

	//	�\�[�g
	void _Sort(std::vector<std::string>& _strvec, const float _writingVal, float* date);

	//	��������
	bool _ToWrite(const char* _fileName, std::vector<std::string>& _strvec, int* date);

	//	��������
	bool _ToWrite(const char* _fileName, std::vector<std::string>& _strvec, float* date);

//=================== �����o�ϐ� ===================//

	int m_twoDimensionsData[CommonConstant::MAX_CSV_NUM][CommonConstant::MAX_CSV_NUM];	//	2�����t�@�C���ǂݍ��ݗp
	int m_data[CommonConstant::MAX_CSV_NUM];								//	�t�@�C���ǂݍ��ݗp

};

#define LOAD_FILE LoadFile::GetInstance()