
//=============================================================================
//	@file	LoadFile.cpp
//	@brief	�t�@�C���̓ǂݍ���
//	@autor	���m ���
//	@_date	2018/10/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "LoadFile.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
LoadFile::LoadFile()
{
	for (int i = 0; i < CommonConstant::MAX_CSV_NUM; i++)
	{
		for (int j = 0; j < CommonConstant::MAX_CSV_NUM; j++)
		{
			//	�񎟌��z��̏�����
			m_twoDimensionsData[i][j] = 0;
		}

		//	�z��̏�����
		m_data[i] = 0;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
LoadFile::~LoadFile()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	CSV�t�@�C���̓ǂݍ���
//-----------------------------------------------------------------------------
bool LoadFile::LoadCsvTwoDimensionsFile(const char* _fileName)
{
	//	�t�@�C�����J��
	std::ifstream ifs(_fileName);
	if (!ifs) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	���ۑ�����
	std::string line;

	//	�s��ۑ�����
	int row = 0;

	//	�t�@�C���̍Ō�܂Ń��[�v
	while (getline(ifs, line))
	{
		//	�J���}��؂�œǂݍ���
		std::vector<std::string> strvec = _Split(line, ',');

		//	��̍Ō�܂Ń��[�v
		for (int col = 0; col < (int)strvec.size(); col++)
		{
			m_twoDimensionsData[row][col] = stoi(strvec.at(col));
		}

		//	�s�𑝂₷
		row++;
	}

	return true;
}

//-----------------------------------------------------------------------------
//	@brief	�t�@�C���̓ǂݍ���
//-----------------------------------------------------------------------------
bool LoadFile::LoadCsvFile(const char* _fileName)
{
	//	�t�@�C�����J��
	std::ifstream ifs(_fileName);
	if (!ifs) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	���ۑ�����
	std::string line;

	//	�t�@�C���̍Ō�܂Ń��[�v
	while (getline(ifs, line))
	{
		//	�J���}��؂�œǂݍ���
		std::vector<std::string> strvec = _Split(line, ',');

		//	��̍Ō�܂Ń��[�v
		for (int row = 0; row < (int)strvec.size(); row++)
		{
			m_data[row] = stoi(strvec.at(row));
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
//	@brief	���e�̎擾
//-----------------------------------------------------------------------------
int LoadFile::GetCsvFile(const int _row, const int _col)
{
	return m_twoDimensionsData[_row][_col];
}

//-----------------------------------------------------------------------------
//	@brief	���e�̎擾
//-----------------------------------------------------------------------------
int LoadFile::GetCsvFile(const int _row)
{
	return m_data[_row];
}

//-----------------------------------------------------------------------------
//	@brief	CSV�t�@�C���̏�������
//-----------------------------------------------------------------------------
bool LoadFile::WritingCsvFile(const char* _fileName, const float _writingVal)
{
	//	�t�@�C���ɒǉ��ŏ�������
	std::ofstream fout(_fileName);
	if (!fout) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	�J���}��؂�ŏ�������
	fout << _writingVal << "," << std::flush;
	return true;
}

//-----------------------------------------------------------------------------
//	@brief	CSV�t�@�C���̏�������
//-----------------------------------------------------------------------------
bool LoadFile::WritingCsvFile(const char* _fileName, const int _writingVal)
{
	//	�t�@�C���ɒǉ��ŏ�������
	std::ofstream fout(_fileName);
	if (!fout) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	�J���}��؂�ŏ�������
	fout << _writingVal << "," << std::flush;
	return true;
}

//-----------------------------------------------------------------------------
//	@brief	CSV�t�@�C���̏�������
//-----------------------------------------------------------------------------
bool LoadFile::WritingCsvFile(const char* _fileName, const int _size, int* _writingVal)
{
	//	�t�@�C���ɒǉ��ŏ�������
	std::ofstream fout(_fileName);
	if (!fout) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	��������
	for (int i = 0; i < _size; i++)
	{
		//	�J���}��؂�ŏ�������
		fout << _writingVal[i] << "," << std::flush;
	}

	return true;
}

//-----------------------------------------------------------------------------
//	@brief	��s�ǂݍ���
//-----------------------------------------------------------------------------
std::vector<std::string> LoadFile::_Split(std::string& _input, char _split)
{
	//	��̕ۑ�
	std::istringstream stream(_input);

	//	�ꕶ�����ۑ�
	std::string field;

	//	�����ۑ�
	std::vector<std::string> result;

	//	�������Ō�܂œǂݍ���
	while (getline(stream, field, _split))
	{
		//	���������ɒǉ����Ă���
		result.push_back(field);
	}

	return result;
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
bool LoadFile::_Load(const char* _fileName, std::vector<std::string>& _strvec, int* _date)
{
	//	�t�@�C�����J��
	std::ifstream ifs(_fileName);
	if (!ifs) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	���ۑ�����
	std::string line;

	//	�t�@�C���̓ǂݍ���
	getline(ifs, line);
	_strvec = _Split(line, ',');

	//	�Ō�܂Ń��[�v
	for (int i = 0; i < (int)_strvec.size(); i++)
	{
		_date[i] = std::stoi(_strvec.at(i));
	}

	return true;
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
bool LoadFile::_Load(const char* _fileName, std::vector<std::string>& _strvec, float* _date)
{
	//	�t�@�C�����J��
	std::ifstream ifs(_fileName);
	if (!ifs) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	���ۑ�����
	std::string line;

	//	�t�@�C���̓ǂݍ���
	getline(ifs, line);
	_strvec = _Split(line, ',');

	//	�Ō�܂Ń��[�v
	for (int i = 0; i < (int)_strvec.size(); i++)
	{
		if (i > 10) { break; }
		_date[i] = std::stof(_strvec.at(i));
	}

	return true;
}


//-----------------------------------------------------------------------------
//	@brief	�\�[�g
//-----------------------------------------------------------------------------
void LoadFile::_Sort(std::vector<std::string>& _strvec, const float _writingVal, int* _date)
{
	//	��������ł���f�[�^�ƍ���̃f�[�^�̔�r
	int val = (int)_writingVal;
	for (int i = 0; i < (int)_strvec.size(); i++)
	{
		//	���_���Ȃ��Ƃ��́A�������Ȃ�
		if (val <= 0.0f) { break; }

		//	�f�[�^�̓���ւ�
		if (val >= _date[i])
		{
			int tmp = _date[i];
			_date[i] = val;
			val = tmp;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	�\�[�g
//-----------------------------------------------------------------------------
void LoadFile::_Sort(std::vector<std::string>& _strvec, const float _writingVal, float* _date)
{
	//	��������ł���f�[�^�ƍ���̃f�[�^�̔�r
	float val = _writingVal;
	for (int i = 0; i < (int)_strvec.size(); i++)
	{
		//	���_���Ȃ��Ƃ��́A�������Ȃ�
		if (val <= 0.0f) { break; }

		//	�f�[�^�̓���ւ�
		if (val >= _date[i])
		{
			float tmp = _date[i];
			_date[i] = val;
			val = tmp;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
bool LoadFile::_ToWrite(const char* _fileName, std::vector<std::string>& _strvec, int* _date)
{
	//	�t�@�C���ɒǉ��ŏ�������
	std::ofstream fout(_fileName);
	if (!fout) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	��������
	for (int i = 0; i < (int)_strvec.size(); i++)
	{
		//	�J���}��؂�ŏ�������
		fout << _date[i] << "," << std::flush;
	}

	return true;
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
bool LoadFile::_ToWrite(const char * _fileName, std::vector<std::string>& _strvec, float* _date)
{
	//	�t�@�C���ɒǉ��ŏ�������
	std::ofstream fout(_fileName);
	if (!fout) { CommonDebug::Log("�t�@�C�����J���܂���"); return false; }

	//	��������
	for (int i = 0; i < (int)_strvec.size(); i++)
	{
		//	�J���}��؂�ŏ�������
		fout << _date[i] << "," << std::flush;
	}

	return true;
}