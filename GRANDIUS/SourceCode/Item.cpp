
//=============================================================================
//	@file	Item.
//	@brief	�A�C�e���ЂƂ��̏���
//	@autor	���m ���
//	@date	2018/12/14
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Item.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const VECTOR	Item::RECT_CORRECTION = VGet(4.0f, 4.0f, 1.0f);		//	���W�̕␳
const float		Item::MOVE_SPEED = 0.5f;							//	�ړ����x
const float		Item::HIT_RADIUS = 4.0f;							//	�����蔻��p�̔��a
const float		Item::ANGLE_SPEED_1 = 0.05f;						//	��]���x�P
const float		Item::ANGLE_SPEED_2 = 0.03f;						//	��]���x�Q

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Item::Item(const int _modelHandle1, const int _modelHandle2, const int _modelHandle3)
{
	//	���f���̕�������
	m_modelHandle1 = MV1DuplicateModel(_modelHandle1);
	m_modelHandle2 = MV1DuplicateModel(_modelHandle2);
	m_modelHandle3 = MV1DuplicateModel(_modelHandle3);
	CommonDebug::Assert((m_modelHandle1 <= -1), " [ Item.cpp ] : error : missing duplicat model.");
	CommonDebug::Assert((m_modelHandle2 <= -1), " [ Item.cpp ] : error : missing duplicat model.");
	CommonDebug::Assert((m_modelHandle3 <= -1), " [ Item.cpp ] : error : missing duplicat model.");

	m_pos = CommonConstant::ORIGIN;
	m_dir = VGet(-1.0f, 0.0f, 0.0f);
	m_isOneTime = false;
	m_radian = 0.0f;
	m_angle1 = CommonConstant::ORIGIN;
	m_angle2 = CommonConstant::ORIGIN;

	//	�����蔻��p�̍\���̂̏�����
	m_hitCircle.m_radius = HIT_RADIUS;
	m_hitCircle.m_centerPoint = CommonConstant::ORIGIN;
	m_hitRect.m_vertexTop = CommonConstant::ORIGIN;
	m_hitRect.m_vertexUnder = CommonConstant::ORIGIN;
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Item::~Item()
{
	//	�ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void Item::Initialize()
{
	m_pos = CommonConstant::ORIGIN;
	m_dir = VGet(-1.0f, 0.0f, 0.0f);
	m_isOneTime = false;
	m_radian = 0.0f;
	m_angle1 = CommonConstant::ORIGIN;
	m_angle2 = CommonConstant::ORIGIN;

	//	�����蔻��p�̍\���̂̏�����
	m_hitCircle.m_radius = HIT_RADIUS;
	m_hitCircle.m_centerPoint = CommonConstant::ORIGIN;
	m_hitRect.m_vertexTop = CommonConstant::ORIGIN;
	m_hitRect.m_vertexUnder = CommonConstant::ORIGIN;
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void Item::Update()
{
	//	�����蔻��p�̒��S���W�̍X�V
	m_hitCircle.m_centerPoint = m_pos;

	//	�����蔻��p�̍��W�̍X�V
	m_hitRect.m_vertexTop = VSub(m_pos, RECT_CORRECTION);
	m_hitRect.m_vertexUnder = VAdd(m_pos, RECT_CORRECTION);

	//	�ړ�����
	_Move();

	//	��]����
	_Rotation();
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void Item::Draw()
{
	//	���f���̕`��
	MV1DrawModel(m_modelHandle1);
	MV1DrawModel(m_modelHandle2);
	MV1DrawModel(m_modelHandle3);
}

//-----------------------------------------------------------------------------
//	@brief	�V���b�g�N���X
//-----------------------------------------------------------------------------
void Item::_Move()
{
	//	�ړ�
	VECTOR velocity = VScale(m_dir, MOVE_SPEED);
	m_pos = VAdd(m_pos, velocity);

	//	���f���̃|�W�V���������蓖��
	MV1SetPosition(m_modelHandle1, m_pos);
	MV1SetPosition(m_modelHandle2, m_pos);
	MV1SetPosition(m_modelHandle3, m_pos);
}

//-----------------------------------------------------------------------------
//	@brief	��]����
//-----------------------------------------------------------------------------
void Item::_Rotation()
{
	m_angle1.x += ANGLE_SPEED_1;
	m_angle2.x += ANGLE_SPEED_2;

	//	���f���̉�]�̊��蓖��
	MV1SetRotationXYZ(m_modelHandle2, m_angle1);
	MV1SetRotationXYZ(m_modelHandle3, m_angle2);
}

//-----------------------------------------------------------------------------
//	@brief	�ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void Item::_FinalRelease()
{
	//	���f���̃A�����[�h
	MV1DeleteModel(m_modelHandle1);
	MV1DeleteModel(m_modelHandle2);
	MV1DeleteModel(m_modelHandle3);
}
