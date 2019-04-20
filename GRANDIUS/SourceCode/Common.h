
//=============================================================================
//	@file	Common.h
//	@brief	����
//	@autor	���m ���
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include <random>

//-----------------------------------------------------------------------------
//	@brief	�O���錾
//-----------------------------------------------------------------------------
class Camera;
class Pad;

//-----------------------------------------------------------------------------
//	@brief	�����`�̍\����
//-----------------------------------------------------------------------------
struct Rect
{
	VECTOR	m_vertexTop;		//	��̒��_
	VECTOR	m_vertexUnder;		//	���̒��_
};

//-----------------------------------------------------------------------------
//	@brief	�~�`�̍\����
//-----------------------------------------------------------------------------
struct Circle
{
	float	m_radius;			//	���a
	VECTOR	m_centerPoint;		//	���S�_
};

//-----------------------------------------------------------------------------
//	@brief	UI�̍\����
//-----------------------------------------------------------------------------
struct UI
{
	int		m_spriteHendle;		//	�X�v���C�g�n���h��
	VECTOR	m_pos;				//	�|�W�V����
	float	m_scale;			//	�X�P�[��
	float	m_angle;			//	�A���O��
	float	m_radian;			//	���W�A��
	float	m_flashingTime;		//	�_�ŕ`��p�̎���
};

//-----------------------------------------------------------------------------
//	@brief	�F�̍\����
//-----------------------------------------------------------------------------
struct Color
{
	int m_red;			//	�ԐF
	int m_green;		//	�ΐF
	int m_blue;			//	�F
	int m_color;		//	�F
};

//-----------------------------------------------------------------------------
//	@brief	�F�̍\����
//-----------------------------------------------------------------------------
struct ColorF
{
	float m_red;			//	�ԐF
	float m_green;			//	�ΐF
	float m_blue;			//	�F
	float m_alpha;			//	�A���t�@
	COLOR_F m_color;		//	�F
};

//-----------------------------------------------------------------------------
//	@brief	�A�j���[�V�����̍\����
//-----------------------------------------------------------------------------
struct Animation
{
	int		m_count;		//	�J�E���g
	float	m_time;			//	�^�C��
	float	m_maxTime;		//	�^�C���̍ő�
	int		m_maxCount;		//	�J�E���g�̍ő�
};

//-----------------------------------------------------------------------------
//	@brief	���O���	[�֐�]
//-----------------------------------------------------------------------------
namespace CommonFunction
{

//===================== �֐� ======================//

	//	���W�A����x�ɕϊ�����
	float RadToDeg(float _rad);

	//	���W�A����x�ɕϊ�����
	VECTOR RadToDeg(VECTOR _rad);

	//	�x�����W�A���ɕϊ�����
	float DegToRad(float _deg);

	//	�x�����W�A���ɕϊ�����
	VECTOR DegToRad(VECTOR _rad);

	//	�O���b�h�̍쐬
	void CreateGrid();

	//	�w��͈̗͂�������
	int GetRand(const int _min, const int _max);

	//	�w��͈̗͂�������
	float GetRand(const float _min, const float _max);

	//	�w��͈̗͂�������
	VECTOR GetRand(const VECTOR _min, const VECTOR _max);

	//	���`���
	float Lerp(const float _a, const float _b, const float _t, const float _ignoreVal = 0.0f);

	//	���`���
	VECTOR Lerp(const VECTOR _a, const VECTOR _b, const float _t, const float _ignoreVal = 0.0f);

	//	�F�̉��Z
	COLOR_F AddColor(COLOR_F _a, COLOR_F _b, float _t);

	//	���`��ԂŊp�x�����߂�
	float LerpRadian(float _a, float _b, float _t);

	//	��̃x�N�g���̊p�x��Ԃ�
	float Vec2Radian(const VECTOR _base, const VECTOR _dir);

	//  �J�����ɂ�钲��
	VECTOR AdjustmentByCamera(const VECTOR& _velocity, const Camera& _camera);

	//	�x�N�g���͔͈͓���
	bool VectorWithinRange(const VECTOR _vec1, const VECTOR _vec2, const float _range);

	//	�x�N�g���͓�������
	bool VectorSame(const VECTOR _vec1, const VECTOR _vec2);

	//	�p�x������������
	VECTOR AskDirFromAngle(const float _angle);

	//	��������p�x�����
	float AskAngleFromDir(const VECTOR _dir);

	//	�������烉�W�A���x�����
	float AskRadianFromDir(const VECTOR _dir);

	//	�F�̎擾
	int GetColor(const Color _color);

	//	�F�̎擾
	Color GetColor(const int _red, const int _green, const int _blue);

	//	�F�̎擾
	COLOR_F GetColor(const ColorF _colorf);

	//	�F�̎擾
	ColorF GetColor(const float _red, const float _green, const float _blue, const float _alpha);

	//	�A�j���[�V���������߂�
	void AskAnimationCount(Animation& _animation);

	//	�A�j���[�V�����̃��Z�b�g
	void ResetAnimationCount(Animation& _animation);

	//	�z��̃T�C�Y�̎擾
	template<typename Template>
	int GetArraySize(const Template& _array)
	{
		const int array = sizeof(_array);
		const int oneArray = sizeof(_array[0]);
		return (array / oneArray);
	}
}

//-----------------------------------------------------------------------------
//	@brief	���O���	[�萔]
//-----------------------------------------------------------------------------
namespace CommonConstant
{
//===================== �ÓI�萔 ===================//

	static const int		WINDOW_WIDTH = 1920;							//	�E�B���h�E�̕�
	static const int		WINDOW_HEIGHT = 1080;							//	�E�B���h�E�̍���
	static const int		COLOR_BIT = 16;									//	�J���[�r�b�g��
	static const VECTOR		ORIGIN = VGet(0.0f, 0.0f, 0.0f);				//	���_
	static const float		LINE_AREA_SIZE = 1000.0f;						//	���C����`���͈�
	static const int		LINE_NUM = 100;									//	���C���̐�
	static const float		PI = 3.14159265359f;							//	��
	static const float		PI2 = 6.28318530718f;							//	2��
	static const int		MAX_KEY_INPUT_NUM = 256;						//	�L�[�̐�
	static const int		MAX_CSV_NUM = 256;								//	CSV�̓ǂݍ��ݔ͈͂̍ő�
	static const int		MAX_ENEMY_ENTRY_NUM = 50;						//	�G�l�~�[�̓o�^��
	static const int		MAX_ITEM_NUM = 10;								//	�A�C�e���̓o�^��
	static const int		MAX_SHOT_NUM = 50;								//	�e�̓o�^��
	static const int		MAX_STAY_SHOT_NUM = 10;							//	�؍ݒe�̓o�^��
	static const int		MAX_PLAYER_LIFE = 5;							//	���C�t
	static const int		MAX_EFFECT_NUM = 50;							//	�G�t�F�N�g�̓o�^��
	static const int		MAX_BOSS_EXPLOSION_NUM = 5;						//	�{�X�����G�t�F�N�g��
	static const int		MAX_SCORE_NUM = 128;							//	�X�R�A�̐�
	static const int		FONT_NUM = 255;									//	�t�H���g�̍ő吔
	static const int		MAX_RANKING_NUM = 10;							//	�����L���O�̍ő吔
	static const int		MAX_ENEMY_SE_NUM = 20;							//	SE�̓o�^��
	static const int		STAY_SHOT_UI_ANIM_NUM = 10;						//	�X�e�C�V���b�gUI�̃A�j���[�V������
	static const int		MAX_BACK_PIXEL_NUM = 150;						//	�w�i�s�N�Z����
}

//-----------------------------------------------------------------------------
//	@brief	���O���	[�f�o�b�O]
//-----------------------------------------------------------------------------
namespace CommonDebug
{

//===================== �֐� ======================//

	//	���O
	void Log();
	void Log(const char* _log);
	void Log(const int _value);
	void Log(const float _value);
	void Log(const VECTOR _value);
	void Log(const int _value1, const int _value2);
	void Log(const float _value1, const float _value2);
	void Log(const VECTOR _value1, const VECTOR _value2);
	void Log(const int _value1, const int _value2, const int _value3);
	void Log(const float _value1, const float _value2, const float _value3);
	void Log(const VECTOR _value1, const VECTOR _value2, const VECTOR _value3);
	void Log(const char* _log, const int _value);
	void Log(const char* _log, const float _value);
	void Log(const char* _log, const VECTOR _value);
	void Log(const char* _log, const int _value1, const int _value2);
	void Log(const char* _log, const float _value1, const float _value2);
	void Log(const char* _log, const VECTOR _value1, const VECTOR _value2);
	void Log(const char* _log, const int _value1, const int _value2, const int _value3);
	void Log(const char* _log, const float _value1, const float _value2, const float _value3);
	void Log(const char* _log, const VECTOR _value1, const VECTOR _value2, const VECTOR _value3);
	
	//	�A�T�[�g
	bool Assert(const bool _isConditions, const char* _assate);

	//	�p�b�h���̓e�X�g [�������u��]
	void PadInputPushTest(Pad& _pad);

	//	�p�b�h���̓e�X�g [�������u��]
	void PadInputDisuniteTest(Pad& _pad);

	//	�p�b�h���̓e�X�g [�����Ă����]
	void PadInputTest(Pad& _pad);
}

//-----------------------------------------------------------------------------
//	@brief	���O���	[���S����]
//  TODO :: null�`�F�b�N���K�v�ȏ������܂Ƃ߂����O��ԁA�������̉���Ȃǂ����Ă���
//  TODO :: CommonSafe�ł͖��O���s�K���Ȃ̂ŁA�ύX�����ق����ǂ�����
//-----------------------------------------------------------------------------
namespace CommonSafe
{
    //-----------------------------------------------------------------------------
    //	@brief	�폜����
    //-----------------------------------------------------------------------------
    template<class Template>
    void Delete(Template*& _pointer)
    {
		if (_pointer)
		{
			delete _pointer;
			_pointer = NULL;
			return;
		}
    }

    //-----------------------------------------------------------------------------
    //	@brief	�������
    //-----------------------------------------------------------------------------
    template<class Template>
    void Release(Template*& _pointer)
    {
        if (_pointer)
        {
            _pointer->Release();
            delete _pointer;
            _pointer = NULL;
			return;
		}
    }
}

//-----------------------------------------------------------------------------
//	@brief	���ʃC���N���[�h
//-----------------------------------------------------------------------------
#include "Key.h"
#include "Production.h"
#include "Menu.h"
#include "HandOverToResult.h"
#include "LoadScene.h"
#include "Font.h"
