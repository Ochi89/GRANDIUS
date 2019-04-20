
//=============================================================================
//	@file	ParticleEmitter.h
//	@brief	�p�[�e�B�N���̐���
//	@autor	���m ���
//	@date	2018/10/3
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"

//-----------------------------------------------------------------------------
//	@brief	�p�[�e�B�N���̐����N���X
//-----------------------------------------------------------------------------
class ParticleEmitter final
{
public:

//==================== �\���� =====================//

	//	�p�����[�^�̎��
	enum PARAMETER_KIND
	{
		MIN_PARAMETER,
		MAX_PARAMETER,
	};

//===================== �֐� ======================//

	//	�R���X�g���N�^ / �f�X�g���N�^
	ParticleEmitter(const int _spriteHandle, const int _size);
	~ParticleEmitter();

	//	������
	void Initialize();

	//	�X�V
	void Update();

	//	���݂̏o�Ă���̂݃G�t�F�N�g���X�V����
	void End();

	//	�`��
	void Draw();

	//	�폜
	void Release();

//==================== getter =====================//

	//	�p�[�e�B�N������ getter
	const int& GetParticleNum() const { return m_particleNum; }

	//	�p�[�e�B�N���̏I���� getter
	const bool& GetIsEndParticle() const { return m_isEndParticle; }

//==================== setter =====================//

	//	�p�����[�^�̐ݒ�
	void SetParameters(const PARAMETER_KIND _paramKind, const VECTOR _pos, const VECTOR _dir, const float _speed, const float _size, const float _life);

	//	�F�� setter
	void SetColor(const float _red, const float _green, const float _blue) { m_red = _red; m_green = _green; m_blue = _blue; }

	//	�ғ����Ԃ� setter
	void SetActiveTime(const float _set) { m_maxActiveTime = _set; }

	//	�p�[�e�B�N���̏I���� setter
	void SetIsEndParticle(const bool _set) { m_isEndParticle = _set; }

private:

//==================== �\���� =====================//

	//	�p�[�e�B�N��
	struct Particle
	{
		VECTOR	m_pos;			//	�ʒu
		VECTOR	m_dir;			//	����
		float	m_speed;		//	���x
		float	m_size;			//	�傫��
		float	m_life;			//	�����t���[����
		float	m_red;			//	�ԐF
		float	m_green;		//	�F
		float	m_blue;			//	�ΐF
		float	m_alpha;		//	�s�����x
		bool	m_isActive;		//	�ғ������ǂ���
	};

	//	�p�[�e�B�N���̏��
	struct ParticleInfo
	{
		VECTOR	m_pos;			//	�ʒu
		VECTOR	m_dir;			//	����
		float	m_size;			//	�傫��
		float	m_speed;		//	���x
		float	m_life;			//	�����t���[����
	};

//================== ���������֐� ==================//

	//	����
	void _Create();

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//
	
	Particle*		m_pParticles;			//	�p�[�e�B�N��
	int				m_particleNum;			//	�p�[�e�B�N���̐�
	int				m_spriteHandle;			//	�X�v���C�g�n���h��
	float			m_activeTime;			//	�`�掞��
	float			m_maxActiveTime;		//	�ő厞��
	ParticleInfo	m_minParam;				//	�ŏ��l�̏��
	ParticleInfo	m_maxParam;				//	�ő�l�̏��
	float			m_red;					//	��
	float			m_green;				//	��
	float			m_blue;					//	��
	bool			m_isEndParticle;		//	�p�[�e�B�N���̏I��
};
