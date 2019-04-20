
//=============================================================================
//	@file	UIGauge.h
//	@brief	�Q�[�WUI
//	@autor	���m ���
//	@date	2018/12/23
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

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
struct Rect;
struct Color;
struct UI;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	UIGauge�N���X
//-----------------------------------------------------------------------------
class UIGauge final
{
public:

//==================== �񋓑� =====================//

	//	�Q�[���̉��Z���
	enum ADD_GAUGE_KIND
	{
		ENEMY,
		BOSS,
		ITEM,
	};

//===================== �֐� ======================//

	//	�R���X�g���N�^/�f�X�g���N�^
	UIGauge();
	~UIGauge();

	//	�쐬����
	void Create();

	//	�������
	void Release();

	//	�X�V����
	void Update(SoundEffect& _soundEffect);

	//	�`�揈��
	void Draw();

	//	�Q�[�W�̉��Z
	void AddGauge(const ADD_GAUGE_KIND _addGaugeKind);

	//	�Q�[�W�̏�����
	void ResetGauge();

//==================== getter =====================//

	//	�Q�[�W�̍ő�t���O�́@getter
	const bool GetIsGaugeMax() const { return m_isGaugeMax; }

private:

//================== ���������֐� ==================//

	//	�ŏI�I�ȉ������
	void _FinalRelease();

//=================== �����o�ϐ� ===================//

	UI		m_buttonUI;				//	�{�^��UI
	Rect	m_gaugeFlame;			//	�Q�[�W�g
	Rect	m_gauge;				//	�Q�[�W
	Color	m_gaugeFlameColor;		//	�Q�[�W�g�̐F
	Color	m_gaugeColor;			//	�Q�[�W�̐F
	float	m_targetGauge;			//	�Q�[�W�̖ړI�n
	bool	m_isGaugeMax;			//	�Q�[�W�̍ő�t���O
	bool	m_isChangeButtonScale;	//	�{�^���T�C�Y�؂�ւ�

//===================== �ÓI�萔 ===================//

	static const VECTOR		START_POS;			//	�J�n�ʒu
	static const VECTOR		END_POS;			//	�I���ʒu
	static const float		FLAME_INTERVAL;		//	�t���[���Ԋu
	static const float		ADD_GAUGE_ENEMY;	//	�G�l�~�[�������̉��Z��
	static const float		ADD_GAUGE_BOSS;		//	�{�X�������̉��Z��
	static const float		ADD_GAUGE_ITEM;		//	�A�C�e���擾���̉��Z��
	static const float		MIN_BUTTON_SCALE;	//	�{�^���̊g�嗦�̍ŏ�
	static const float		MAX_BUTTON_SCALE;	//	�{�^���̊g�嗦�̍ő�
	static const float		BUTTON_SCALE_SPEED;	//	�{�^���̊g�嗦�̑��x
	static const int		MAX_COLOR;			//	�F�̍ő�
	static const int		MIN_COLOR;			//	�F�̍ŏ�
	static const int		COLOR_SPEED;		//	�F�̑��x
};