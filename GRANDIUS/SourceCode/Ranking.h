
//=============================================================================
//	@file	Ranking.h
//	@brief	�����L���O
//	@autor	���m ���
//	@date	2018/1/3
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once
#pragma warning(disable:4996)

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
struct UI;
class Pad;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	�����L���O�N���X
//-----------------------------------------------------------------------------
class Ranking final
{
public:

//===================== �֐� ======================//

	// �R���X�g���N�^ / �f�X�g���N�^
	Ranking();
	~Ranking();

	//	��������
	void Initialize();

	//	�X�V����
	void Update(Pad& _pad, SoundEffect& _soundEffect);

	//	�`�揈��
	void Draw();

//==================== getter =====================//

	//	�����L���O�J�n�t���O�� getter
	const bool& GetIsRankingStart() const { return m_isRankingStart; }

	//	�V�[���؂�ւ��t���O�� getter
	const bool& GetIsSceneChange() const { return m_isSceneChange; }

private:

//================== ���������֐� ==================//

	//	���C�t�{�[�i�X
	void _LifeBonus(Pad& _pad, SoundEffect& _soundEffect);

	//	�������{�[�i�X
	void _DestructionBonus(Pad& _pad, SoundEffect& _soundEffect);

	//	�����L���O
	void _Ranking(SoundEffect& _soundEffect);

	//	�ǂݍ���
	void _Load();

	//	�\�[�g
	void _Sort();

	//	��������
	void _Writing();

	//	�_�ŕ`��
	void _FlashingDraw(const int _num, const int _rank);

	//	�����N�O�̓_�ŕ`��
	void _AfterRankFlashingDraw();

//=================== �����o�ϐ� ===================//

	int		m_score[CommonConstant::MAX_RANKING_NUM];										//	�X�R�A
	int		m_rank;																			//	�����N
	char	m_thisTimeScoreText[CommonConstant::MAX_SCORE_NUM];								//	����̃X�R�A�̕�����
	char	m_bonusScoreText[CommonConstant::MAX_SCORE_NUM];								//	�{�[�i�X�̕�����
	char	m_scoreText[CommonConstant::MAX_RANKING_NUM][CommonConstant::MAX_SCORE_NUM];	//	�X�R�A�̕�����
	bool	m_isLifeBonusScore;																//	�c�@�{�[�i�X
	bool	m_isDestructionBonusScore;														//	�������{�[�i�X
	bool	m_isRankingStart;																//	�����L���O�̊J�n
	float	m_productionTime;																//	���o����
	float	m_waitTime;																		//	�x������
	float	m_lifeBonusScoreVal;															//	���C�t�{�[�i�X�l
	float	m_DestructionBonusScoreVal;														//	�������{�[�i�X�l
	float	m_flashingTime;																	//	�_�Ŏ���
	float	m_sceneChangeTime;																//	�V�[���؂�ւ�����
	bool	m_isSceneChange;																//	�V�[���؂�ւ�
	UI		m_bonusUI;																		//	�{�[�i�XUI
	UI		m_rankingUI;																	//	�����L���OUI

//===================== �ÓI�萔 ===================//

	static const int		TEXT_START;					//	�e�L�X�g�̏����ʒu
	static const int		TEXT_INTERVAL;				//	�e�L�X�g�̊Ԋu
	static const int		AFTER_RANK;					//	�����N�O
	static const float		MAX_PRODUCTION_TIME;		//	���o���Ԃ̍ő�
	static const float		MAX_WAITTIME;				//	�x�����Ԃ̍ő�
	static const float		LIFE_BONUS_SCORE;			//	���C�t�{�[�i�X
	static const float		DESTRUCTION_BONUS_SCORE;	//	�������{�[�i�X
	static const float		MAX_SCENE_CHANGE_TIME;		//	�V�[���؂�ւ����Ԃ̍ő�
};
