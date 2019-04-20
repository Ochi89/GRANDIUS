
//=============================================================================
//	@file	ParticleEmitter.cpp
//	@brief	�p�[�e�B�N���̐���
//	@autor	���m ���
//	@date	2018/10/3
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEmitter.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
ParticleEmitter::ParticleEmitter(const int _spriteHandle, const int _size)
{
	//	�摜�̃R�s�[
	m_spriteHandle = _spriteHandle;
	CommonDebug::Assert((m_spriteHandle <= -1), "[ ParticleEmitter.cpp ] : error : model loading failed.");

	m_activeTime = 0.0f;			//	�`�掞��
	m_maxActiveTime = 0.0f;			//	�ő厞��

	//	�p�����[�^�̏��i�A��
	SetParameters(PARAMETER_KIND::MIN_PARAMETER, CommonConstant::ORIGIN, CommonConstant::ORIGIN, 0.0f, 0.0f, 0.0f);
	SetParameters(PARAMETER_KIND::MAX_PARAMETER, CommonConstant::ORIGIN, CommonConstant::ORIGIN, 0.0f, 0.0f, 0.0f);
	m_isEndParticle = false;
	m_red = 255.0f;					//	��
	m_green = 255.0f;				//	��
	m_blue = 255.0f;				//	��

	//	�T�C�Y���̐���
	m_pParticles = new Particle[_size];

	//	�p�[�e�B�N�����̕ۑ�
	m_particleNum = _size;
}

//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^
//-----------------------------------------------------------------------------
ParticleEmitter::~ParticleEmitter()
{
	//	�摜�̃A�����[�h
	DeleteGraph(m_spriteHandle);
}

//-----------------------------------------------------------------------------
// @brief  ������
//-----------------------------------------------------------------------------
void ParticleEmitter::Initialize()
{
	//	������
	for (int i = 0; i < m_particleNum; i++)
	{
		m_pParticles[i].m_pos = CommonConstant::ORIGIN;
		m_pParticles[i].m_dir = CommonConstant::ORIGIN;
		m_pParticles[i].m_size = 0.0f;
		m_pParticles[i].m_speed = 0.0f;
		m_pParticles[i].m_life = 0.0f;
		m_pParticles[i].m_red = m_red;
		m_pParticles[i].m_green = m_green;
		m_pParticles[i].m_blue = m_blue;
		m_pParticles[i].m_alpha = 0.0f;
		m_pParticles[i].m_isActive = false;
	}
}

//-----------------------------------------------------------------------------
// @brief  �X�V
//-----------------------------------------------------------------------------
void ParticleEmitter::Update()
{
	//	�������ԓ��Ȃ�
	const bool isNotActive = m_activeTime >= m_maxActiveTime;
	if (isNotActive)
	{
		//	�I������
		End();

		for (int i = 0; i < m_particleNum; i++)
		{
			//	�ǂꂩ��ł����s���Ȃ�
			//	�I�����Ȃ�
			if (m_pParticles[i].m_isActive == true) { return; }
			m_isEndParticle = true;
		}

		return;
	}

	//	�p�[�e�B�N���̍쐬����
	_Create();

	for (int i = 0; i < m_particleNum; i++)
	{
		//	�p�[�e�B�N���̏�Ԃ��A�N�e�B�u�Ȃ�
		if (m_pParticles[i].m_isActive)
		{
			//	�ړ�
			VECTOR velocity = VScale(m_pParticles[i].m_dir, m_pParticles[i].m_speed);
			m_pParticles[i].m_pos = VAdd(m_pParticles[i].m_pos, velocity);

			//	�T�C�Y�ύX
			m_pParticles[i].m_size -= 0.05f;

			//	�������ւ炷
			m_pParticles[i].m_life--;

			//	�������Ȃ��Ȃ�����A�p�[�e�B�N���̍폜
			if (m_pParticles[i].m_life <= 0) { m_pParticles[i].m_isActive = false; }

		}
	}

	m_activeTime++;
}

//-----------------------------------------------------------------------------
// @brief  ���݂̏o�Ă���̂݃G�t�F�N�g���X�V����
//-----------------------------------------------------------------------------
void ParticleEmitter::End()
{
	//	�`�悵�Ȃ��悤�ɂ���
	for (int i = 0; i < m_particleNum; i++)
	{
		//	�p�[�e�B�N���̏�Ԃ��A�N�e�B�u�Ȃ�
		if (m_pParticles[i].m_isActive)
		{
			//	�ړ�
			VECTOR velocity = VScale(m_pParticles[i].m_dir, m_pParticles[i].m_speed);
			m_pParticles[i].m_pos = VAdd(m_pParticles[i].m_pos, velocity);

			//	�T�C�Y�ύX
			m_pParticles[i].m_size -= 0.05f;

			//	�������ւ炷
			m_pParticles[i].m_life--;

			//	�������Ȃ��Ȃ�����A�p�[�e�B�N���̍폜
			if (m_pParticles[i].m_life <= 0) { m_pParticles[i].m_isActive = false; }
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  �`��
//-----------------------------------------------------------------------------
void ParticleEmitter::Draw()
{
	//	Z�o�b�t�@���g�p����ݒ�ɕύX
	SetUseZBufferFlag(TRUE);

	//	Z�o�b�t�@�ւ̏������݂͍s��Ȃ�
	SetWriteZBufferFlag(FALSE);

	for (int i = 0; i < m_particleNum; i++)
	{
		//	�`����x���W���ݒ�ɂ���
		SetDrawBright((int)m_pParticles[i].m_red, (int)m_pParticles[i].m_green, (int)m_pParticles[i].m_blue);
	}

	for (int i = 0; i < m_particleNum; i++)
	{
		//	�p�[�e�B�N���̏�Ԃ��A�N�e�B�u�Ȃ�
		if (m_pParticles[i].m_isActive)
		{
			if (m_pParticles[i].m_alpha <= 0.0f) { continue; }

			//	���Z�u�����h�Ńp�[�e�B�N���̕`��
			SetDrawBlendMode(DX_BLENDMODE_SUB, (int)(m_pParticles[i].m_alpha * 255.0f));
			DrawBillboard3D(m_pParticles[i].m_pos, 0.5f, 0.5f, m_pParticles[i].m_size * m_pParticles[i].m_alpha, 0.0f, m_spriteHandle, TRUE);
		}
	}

	for (int i = 0; i < m_particleNum; i++)
	{
		//	�p�[�e�B�N���̏�Ԃ��A�N�e�B�u�Ȃ�
		if (m_pParticles[i].m_isActive)
		{
			if (m_pParticles[i].m_alpha <= 0.0f) { continue; }

			//	���Z�u�����h�Ńp�[�e�B�N���̕`��
			SetDrawBlendMode(DX_BLENDMODE_ADD_X4, (int)(m_pParticles[i].m_alpha * 255.0f));
			DrawBillboard3D(m_pParticles[i].m_pos, 0.5f, 0.5f, m_pParticles[i].m_size * m_pParticles[i].m_alpha, 0.0f, m_spriteHandle, TRUE);
		}
	}

	//	�u�����h���[�h��W���ݒ�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	//	�`����x���W���ݒ�ɂ���
	SetDrawBright(255, 255, 255);

	//	Z�o�b�t�@���g�p���Ȃ��ݒ�ɕύX
	SetUseZBufferFlag(FALSE);
}

//-----------------------------------------------------------------------------
// @brief  �폜
//-----------------------------------------------------------------------------
void ParticleEmitter::Release()
{
	//  �ŏI�I�ȉ������
	_FinalRelease();
}

//-----------------------------------------------------------------------------
// @brief  �p�����[�^�̐ݒ�
//-----------------------------------------------------------------------------
void ParticleEmitter::SetParameters(const PARAMETER_KIND _paramKind, const VECTOR _pos, const VECTOR _dir, const float _speed, const float _size, const float _life)
{
	switch (_paramKind)
	{
	case PARAMETER_KIND::MIN_PARAMETER:
		m_minParam.m_pos = _pos;
		m_minParam.m_dir = _dir;
		m_minParam.m_speed = _speed;
		m_minParam.m_size = _size;
		m_minParam.m_life = _life;
		break;

	case PARAMETER_KIND::MAX_PARAMETER:
		m_maxParam.m_pos = _pos;
		m_maxParam.m_dir = _dir;
		m_maxParam.m_speed = _speed;
		m_maxParam.m_size = _size;
		m_maxParam.m_life = _life;
		break;
	}
}

//-----------------------------------------------------------------------------
// @brief  �p�[�e�B�N���̍쐬����
//-----------------------------------------------------------------------------
void ParticleEmitter::_Create()
{
	//	�쐬
	for (int i = 0; i < m_particleNum; i++)
	{
		if (!m_pParticles[i].m_isActive)
		{
			//	�|�W�V����
			m_pParticles[i].m_pos = CommonFunction::GetRand(m_minParam.m_pos, m_maxParam.m_pos);

			//	����
			m_pParticles[i].m_dir = CommonFunction::GetRand(m_minParam.m_dir, m_maxParam.m_dir);

			//	���x
			m_pParticles[i].m_speed = CommonFunction::GetRand(m_minParam.m_speed, m_maxParam.m_speed);

			//	�T�C�Y
			m_pParticles[i].m_size = CommonFunction::GetRand(m_minParam.m_size, m_maxParam.m_size);

			//	���C�t
			m_pParticles[i].m_life = CommonFunction::GetRand(m_minParam.m_life, m_maxParam.m_life);

			//	�F�̐ݒ�
			m_pParticles[i].m_red = m_red;
			m_pParticles[i].m_green = m_green;
			m_pParticles[i].m_blue = m_blue;

			//	�s�����x
			m_pParticles[i].m_alpha = 1.0f;

			//	�A�N�e�B�u��
			m_pParticles[i].m_isActive = true;
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  �ŏI�I�ȉ������
//-----------------------------------------------------------------------------
void ParticleEmitter::_FinalRelease()
{
	//	�摜�n���h���̉��
	DeleteGraph(m_spriteHandle);
}
