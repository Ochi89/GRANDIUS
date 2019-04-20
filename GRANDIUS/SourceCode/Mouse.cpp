
//=============================================================================
//	@file	Mouse.h
//	@brief	�}�E�X����
//	@autor	���m ���
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Mouse.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Mouse::Mouse()
{
	m_pos = CommonConstant::ORIGIN;
	m_newPosX = 0;
	m_newPosY = 0;

	m_prevLeft = 0;
	m_prevRight = 0;

	//	�}�E�X�̕\��������
	SetMouseDispFlag(FALSE);
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Mouse::~Mouse()
{
	//	�����Ȃ�
}

//-----------------------------------------------------------------------------
//	@brief	�X�V
//-----------------------------------------------------------------------------
void Mouse::Update()
{
	_Velocity();
}

//-----------------------------------------------------------------------------
//	@brief	�������u��
//-----------------------------------------------------------------------------
bool Mouse::Push(const char* _mode)
{
	if (_mode == "LEFT")
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			if (m_prevLeft == 0)
			{
				//	�����ꂽ
				m_prevLeft = 1;
				return true;
			}

			return false;
		}
		else
		{
			//	������Ă��Ȃ�
			m_prevLeft = 0;
			return false;
		}
	}
	else if (_mode == "RIGHT")
	{
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
		{
			if (m_prevRight == 0)
			{
				//	�����ꂽ
				m_prevRight = 1;
				return true;
			}

			return false;
		}
		else
		{
			//	������Ă��Ȃ�
			m_prevRight = 0;
			return false;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	������Ă���
//-----------------------------------------------------------------------------
bool Mouse::Press(const char * _mode)
{
	if (_mode == "LEFT")
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) { return true; }
	}
	else if (_mode == "RIGHT")
	{
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) { return true; }
	}

	return false;
}

//-----------------------------------------------------------------------------
//	@brief	�ړ���
//-----------------------------------------------------------------------------
void Mouse::_Velocity()
{
	//	�}�E�X�̈ʒu���擾
	GetMousePoint(&m_newPosX, &m_newPosY);

	//	�}�E�X�̍��W�̍X�V
	m_pos.x = (float)(m_newPosX - CommonConstant::WINDOW_WIDTH / 2);
	m_pos.y = (float)(m_newPosY - CommonConstant::WINDOW_HEIGHT / 2);

	//	�}�E�X�̍��W�̏�����
	SetMousePoint(CommonConstant::WINDOW_WIDTH / 2, CommonConstant::WINDOW_HEIGHT / 2);
}
