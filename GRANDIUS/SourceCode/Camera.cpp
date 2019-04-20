
//=============================================================================
//	@file	Camera.cpp
//	@brief	�J����
//	@autor	���m ���
//	@date	2018/9/29
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Camera.h"
#include "Common.h"
#include "PlayerManager.h"
#include "PlayerBase.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const float Camera::V_ANGLE_SPEED_MOUSE = 0.08f;		// �����p�x�̉�]���x
const float Camera::H_ANGLE_SPEED_MOUSE = 0.08f;		// �����p�x�̉�]���x
const float Camera::V_ANGLE_SPEED_PAD = 1.2f;			// �����p�x�̉�]���x
const float Camera::H_ANGLE_SPEED_PAD = 1.5f;			// �����p�x�̉�]���x
const int	Camera::MAX_H_ANGLE = 10;					// �����p�x�̍ő�
const int	Camera::MIN_H_ANGLE = -10;					// �����p�x�̍ŏ�
const int	Camera::MAX_V_ANGLE = 20;					// �����p�x�̍ő�
const int	Camera::MIN_V_ANGLE = -20;					// �����p�x�̍ŏ�
const float Camera::LERP_SPEED = 0.5f;					//	���`�ۊǂ̑��x
const float Camera::HEIGHT_LENGTH = 60.0f;				//	�����̒���
const float Camera::DEPTH_LENGTH = 100.0f;				//	���s���̒���

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^
//-----------------------------------------------------------------------------
Camera::Camera()
{
	// ���s0.1f�`1000.0f�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.0f, 10000.0f);

	m_pos = CommonConstant::ORIGIN;
	m_lookAtPos = CommonConstant::ORIGIN;
	m_lookAtPos.y = HEIGHT_LENGTH;

	m_verticalAngle = 0.0f;
	m_horizontalAngle = 0.0f;
	m_productionTime = 0.0f;
	m_isProduction = false;
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^
//-----------------------------------------------------------------------------
Camera::~Camera()
{
	// �����Ȃ�
}

//-----------------------------------------------------------------------------
// @brief	�^�C�g���p�̏�������
//-----------------------------------------------------------------------------
void Camera::InitializeForTitle()
{
	//	�^�C�g���p�̏�����
	m_pos = CommonConstant::ORIGIN;
	m_lookAtPos = CommonConstant::ORIGIN;

	m_verticalAngle = 20.0f;
	m_horizontalAngle = -45.0f;
	m_productionTime = 0.0f;
	m_isProduction = false;
}

//-----------------------------------------------------------------------------
// @brief	��������
//-----------------------------------------------------------------------------
void Camera::Initialize()
{
	m_pos = CommonConstant::ORIGIN;
	m_lookAtPos = CommonConstant::ORIGIN;
	m_lookAtPos.y = HEIGHT_LENGTH;

	m_verticalAngle = 0.0f;
	m_horizontalAngle = 0.0f;
	m_productionTime = 0.0f;
	m_isProduction = false;
}

//-----------------------------------------------------------------------------
// @brief	�^�C�g���p�̍X�V����
//-----------------------------------------------------------------------------
void Camera::UpdateForTitle(PlayerManager& _playerManager)
{
	if (!m_isProduction)
	{
		//	�^�C�g���p�̒����_�̐ݒ�
		_SetGazingPointForTitle(_playerManager);

		//	�J�����̊p�x�𔽉f�����ʒu�����߂�
		VECTOR tmpPos = _PosAccordingToAngle();

		//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
		VECTOR target = VAdd(tmpPos, m_lookAtPos);

		//	���`�ۊǂ��g���ǂ�
		m_pos = CommonFunction::Lerp(m_pos, target, LERP_SPEED);
	}

	//	�^�C�g���p�̉��o
	_ProductionForTitle(_playerManager);

	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(m_pos, m_lookAtPos);
}

//-----------------------------------------------------------------------------
// @brief	���U���g�p�̍X�V����
//-----------------------------------------------------------------------------
void Camera::UpdateForResult(PlayerManager & _playerManager)
{
	//	�����_�̐ݒ�
	_SetGazingPoint();

	//	�J�����̊p�x�𔽉f�����ʒu�����߂�
	VECTOR tmpPos = _PosAccordingToAngle();

	//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
	VECTOR target = VAdd(tmpPos, m_lookAtPos);

	//	���`�ۊǂ��g���ǂ�
	m_pos = CommonFunction::Lerp(m_pos, target, LERP_SPEED);

	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(m_pos, m_lookAtPos);
}

//-----------------------------------------------------------------------------
// @brief	�X�V����
//-----------------------------------------------------------------------------
void Camera::Update(PlayerManager& _playerManager)
{
	if (!m_isProduction)
	{
		//	�����_�̐ݒ�
		_SetGazingPoint();

		//	�J�����̊p�x�𔽉f�����ʒu�����߂�
		VECTOR tmpPos = _PosAccordingToAngle();

		//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
		VECTOR target = VAdd(tmpPos, m_lookAtPos);

		//	���`�ۊǂ��g���ǂ�
		m_pos = CommonFunction::Lerp(m_pos, target, LERP_SPEED);
	}

	//	�J�������o
	_Production(_playerManager);

	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(m_pos, m_lookAtPos);
}

//-----------------------------------------------------------------------------
// @brief	�^�C�g���p�̉��o
//-----------------------------------------------------------------------------
void Camera::_ProductionForTitle(PlayerManager& _playerManager)
{
	if (PRODUCTION->GetIsTitleProduction())
	{
		//	���o�J�n
		m_isProduction = true;
	}
}

//-----------------------------------------------------------------------------
// @brief	���o
//-----------------------------------------------------------------------------
void Camera::_Production(PlayerManager& _playerManager)
{
	//	�V�[�����o
	_SceneProduction(_playerManager);

	//	�K�E���o
	_SpecialProduction(_playerManager);

	//	�N���A���o
	_ClearProduction(_playerManager);
}

//-----------------------------------------------------------------------------
// @brief	�V�[�����o
//-----------------------------------------------------------------------------
void Camera::_SceneProduction(PlayerManager& _playerManager)
{
	//	�V�[���ύX
	if (PRODUCTION->GetIsSceneProduction())
	{
		m_productionTime++;
		const bool isProduction1 = m_productionTime >= 0.0f && m_productionTime <= 100.0f;
		const bool isProduction2 = m_productionTime >= 100.0f && m_productionTime <= 210.0f;
		const bool isProduction3 = m_productionTime >= 210.0f && m_productionTime <= 300.0f;
		const bool isProduction4 = m_productionTime >= 300.0f && m_productionTime <= 330.0f;
		const bool isProduction5 = m_productionTime >= 330.0f && m_productionTime <= 360.0f;

		const bool isProductionInit = m_productionTime == 100.0f;
		if (isProductionInit) { m_lookAtPos = CommonConstant::ORIGIN; }

		if (isProduction1)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�v���C���[�͈ړ���~
				player->SetIsStopMove(true);
				player->SetAngle(VGet(0.0f, 1.4f, 0.0f));

				//	�v���C���[�̃|�W�V�������������ʒu�ɂ��āA
				//	���o������
				VECTOR playerPos = player->GetPos();
				const float playerLerpSpeed = 0.05f;
				playerPos = CommonFunction::Lerp(playerPos, player->GetStartPos(), playerLerpSpeed);
				player->SetPos(playerPos);

				//	���o�J�n
				m_isProduction = true;

				//	�_�ł��Ă���ꍇ�A
				//	�ςȂ̂ŁA�_�ł�����
				player->SetIsInvincible(false);

				//	�J�����̉�]
				const float angleSpeed = 0.2f;
				m_verticalAngle += angleSpeed;

				//	�����_�����߂�
				const float cameraLerpSpeed = 0.8f;
				m_lookAtPos = CommonFunction::Lerp(m_lookAtPos, player->GetPos(), cameraLerpSpeed);
				m_lookAtPos.y = player->GetPos().y;
				m_lookAtPos.z = 0.0f;

				//	�J�����̊p�x�𔽉f�����ʒu�����߂�
				VECTOR tmpPos = _PosAccordingToAngle();

				//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
				VECTOR target = VAdd(tmpPos, m_lookAtPos);

				//	���`�ۊǂ��g���ǂ�
				m_pos = CommonFunction::Lerp(m_pos, target, cameraLerpSpeed);
			}
		}
		if (isProduction2)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�J�����̉�]
				const float angleSpeed = 3.0f;
				m_horizontalAngle -= angleSpeed;

				//	�����_�����߂�
				const float lerpSpeed = 0.2f;
				m_lookAtPos = CommonFunction::Lerp(m_lookAtPos, player->GetPos(), lerpSpeed);
				m_lookAtPos.y = player->GetPos().y;
				m_lookAtPos.z = 0.0f;

				//	�J�����̊p�x�𔽉f�����ʒu�����߂�
				VECTOR tmpPos = _PosAccordingToAngle();

				//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
				VECTOR target = VAdd(tmpPos, m_lookAtPos);

				//	���`�ۊǂ��g���ǂ�
				m_pos = CommonFunction::Lerp(m_pos, target, lerpSpeed);
			}
		}
		if (isProduction3)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�v���C���[�̉��o�J�n
				player->SetIsSceneProduction(true);
			}
		}
		if (isProduction4)
		{
			//	�����_�̐ݒ�
			_SetGazingPoint();

			//	�p�x�̏�����
			const float angleSpeed = 0.64f;
			m_verticalAngle -= angleSpeed;
			m_horizontalAngle--;

			//	�J�����̊p�x�𔽉f�����ʒu�����߂�
			VECTOR tmpPos = _PosAccordingToAngle();

			//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
			VECTOR target = VAdd(tmpPos, m_lookAtPos);

			//	���`�ۊǂ��g���ǂ�
			const float lerpSpeed = 0.2f;
			m_pos = CommonFunction::Lerp(m_pos, target, lerpSpeed);

		}
		if (isProduction5)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�v���C���[�͈ړ��\
				player->SetIsStopMove(false);

				//	�v���C���[�̉��o�I��
				player->SetIsSceneProduction(false);

				//	�v���C���[�̓o��
				player->SetIsEmerge(true);

				//	���o�I��
				m_isProduction = false;
				m_productionTime = 0.0f;
				m_verticalAngle = 0.0f;
				m_horizontalAngle = 0.0f;
				PRODUCTION->SetIsSceneProduction(false);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// @brief	�K�E���o
//-----------------------------------------------------------------------------
void Camera::_SpecialProduction(PlayerManager& _playerManager)
{
	//	�K�E��
	if (PRODUCTION->GetIsSpecialProduction())
	{
		m_productionTime++;
		const bool isProduction1 = m_productionTime >= 5.0f && m_productionTime <= 25.0f;
		const bool isProduction2 = m_productionTime >= 285.0f && m_productionTime <= 305.0f;
		const bool isProduction3 = m_productionTime >= 305.0f;

		if (isProduction1)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�v���C���[�͈ړ���~
				player->SetIsStopMove(true);
				player->SetAngle(VGet(0.0f, 1.4f, 0.0f));

				//	�J�����̊p�x��ύX
				const float horizontalAngleSpeed = 2.0f;
				const float verticalAngleSpeed = 1.0f;
				m_horizontalAngle -= horizontalAngleSpeed;
				m_verticalAngle += verticalAngleSpeed;

				//	�����_�����߂�
				VECTOR adjustment = VGet(60.0f, 10.0f, 0.0f);
				VECTOR targetPos = player->GetPos();
				targetPos.x += adjustment.x;
				targetPos.y -= adjustment.y;
				m_lookAtPos = targetPos;

				//	�J�����̊p�x�𔽉f�����ʒu�����߂�
				VECTOR tmpPos = _PosAccordingToAngle();

				//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
				VECTOR target = VAdd(tmpPos, m_lookAtPos);

				//	���`�ۊǂ��g���ǂ�
				const float lerpSpeed = 0.2f;
				m_pos = CommonFunction::Lerp(m_pos, target, lerpSpeed);

				//	�_�ł��Ă���ꍇ�A
				//	�ςȂ̂ŁA�_�ł�����
				player->SetIsInvincible(false);

				//	���o�J�n
				m_isProduction = true;
			};

		}
		if (isProduction2)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�J�����̊p�x��ύX����
				const float horizontalAngleSpeed = 2.0f;
				const float verticalAngleSpeed = 1.0f;
				m_horizontalAngle += horizontalAngleSpeed;
				m_verticalAngle -= verticalAngleSpeed;

				//	�����_�����߂�
				VECTOR adjustment = VGet(60.0f, 10.0f, 0.0f);
				VECTOR targetPos = player->GetPos();
				targetPos.x += adjustment.x;
				targetPos.y -= adjustment.y;
				m_lookAtPos = targetPos;

				//	�J�����̊p�x�𔽉f�����ʒu�����߂�
				VECTOR tmpPos = _PosAccordingToAngle();

				//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
				VECTOR target = VAdd(tmpPos, m_lookAtPos);

				//	���`�ۊǂ��g���ǂ�
				const float lerpSpeed = 0.2f;
				m_pos = CommonFunction::Lerp(m_pos, target, lerpSpeed);
			};
		}
		if (isProduction3)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�v���C���[���ړ��\�ɂ��A
				//	�����������G�ɂ���
				player->SetIsStopMove(false);
				player->SetIsInvincibleAfterLaser(true);

				//	���o�I��
				m_isProduction = false;
				m_productionTime = 0.0f;
				PRODUCTION->ResetSpecialProduction();
			}
		}
	}
}

//-----------------------------------------------------------------------------
// @brief	�N���A���o
//-----------------------------------------------------------------------------
void Camera::_ClearProduction(PlayerManager & _playerManager)
{
	//	�N���A��
	if (PRODUCTION->GetIsClearProduction())
	{
		m_productionTime++;
		const bool isProduction1 = m_productionTime >= 5.0f && m_productionTime <= 60.0f;
		const bool isProduction2 = m_productionTime >= 60.0f && m_productionTime <= 130.0f;
		const bool isProduction3 = m_productionTime >= 160.0f;

		if (isProduction1)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�v���C���[�͈ړ���~
				player->SetIsStopMove(true);
				player->SetAngle(VGet(0.0f, 1.4f, 0.0f));

				//	�v���C���[����ʂ̒��S�ֈړ�
				const float lerpSpeed = 0.1f;
				const VECTOR screenCenter = VGet(0.0f, 55.0f, 0.0f);
				VECTOR playerPos = player->GetPos();
				playerPos = CommonFunction::Lerp(playerPos, screenCenter, lerpSpeed);
				player->SetPos(playerPos);

				//	���o�J�n
				m_isProduction = true;

				//	�_�ł��Ă���ꍇ�A
				//	�ςȂ̂ŁA�_�ł�����
				player->SetIsInvincible(false);
			}
		}
		if (isProduction2)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�J�����̊p�x��ύX
				const float horizontalAngleSpeed = 4.0f;
				m_horizontalAngle += horizontalAngleSpeed;

				//	�����_�����߂�
				VECTOR targetPos = player->GetPos();
				m_lookAtPos = targetPos;

				//	�J�����̊p�x�𔽉f�����ʒu�����߂�
				VECTOR tmpPos = _PosAccordingToAngle();

				//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
				VECTOR target = VAdd(tmpPos, m_lookAtPos);

				//	���`�ۊǂ��g���ǂ�
				const float lerpSpeed = 0.2f;
				m_pos = CommonFunction::Lerp(m_pos, target, lerpSpeed);
			}
		}
		if (isProduction3)
		{
			PlayerBase* player = _playerManager.GetPlayerPtr();
			if (player)
			{
				//	�v���C���[�̉��o�J�n
				player->SetIsClearProduction(true);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// @brief	�^�C�g���p�̒����_�̐ݒ�
//-----------------------------------------------------------------------------
void Camera::_SetGazingPointForTitle(PlayerManager& _playerManager)
{
	PlayerBase* player = _playerManager.GetPlayerPtr();
	if (player)
	{
		//	�����_�����߂�
		m_lookAtPos = VGet(60.0f, 42.0f, 16.0f);

		//	�J�����̊p�x�𔽉f�����ʒu�����߂�
		VECTOR tmpPos = _PosAccordingToAngle();

		//	���߂����W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
		VECTOR target = VAdd(tmpPos, m_lookAtPos);

		//	���`�ۊǂ��g���ǂ�
		const float lerpSpeed = 0.2f;
		m_pos = CommonFunction::Lerp(m_pos, target, lerpSpeed);
	}
}

//-----------------------------------------------------------------------------
// @brief	�����_�̎擾
//-----------------------------------------------------------------------------
void Camera::_SetGazingPoint()
{
	//	���s���̂ݒǂ�
	VECTOR lookAtPos = CommonConstant::ORIGIN;
	lookAtPos.y = HEIGHT_LENGTH;

	m_lookAtPos = CommonFunction::Lerp(m_lookAtPos, lookAtPos, 0.05f);
}

//-----------------------------------------------------------------------------
// @brief	�p�x�ɉ������ʒu
//-----------------------------------------------------------------------------
VECTOR Camera::_PosAccordingToAngle()
{
	// �J�����̈ʒu�̒���
	VECTOR tmpPos1;
	VECTOR tmpPos2;

	// �����p�x�𔽉f�����ʒu
	float m_sinParam = sinf(CommonFunction::DegToRad(m_verticalAngle));
	float m_cosParam = cosf(CommonFunction::DegToRad(m_verticalAngle));
	tmpPos1.x = 0.0f;
	tmpPos1.y = m_sinParam * DEPTH_LENGTH;
	tmpPos1.z = -m_cosParam * DEPTH_LENGTH;

	// �����p�x�𔽉f�����ʒu
	m_sinParam = sinf(CommonFunction::DegToRad(m_horizontalAngle));
	m_cosParam = cosf(CommonFunction::DegToRad(m_horizontalAngle));
	tmpPos2.x = m_cosParam * tmpPos1.x - m_sinParam * tmpPos1.z;
	tmpPos2.y = tmpPos1.y;
	tmpPos2.z = m_sinParam * tmpPos1.x + m_cosParam * tmpPos1.z;

	return tmpPos2;
}
