
//=============================================================================
//	@file	UIScore.h
//	@brief	�X�R�AUI
//	@autor	���m ���
//	@date	2018/12/30
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�v���v���Z�b�T
//-----------------------------------------------------------------------------
#pragma once
#pragma warning(disable:4996)

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	�X�R�A�N���X
//-----------------------------------------------------------------------------
class UIScore final
{
public:

//==================== �񋓑� =====================//

	//	�X�R�A
	enum ADD_SCORE
	{
		ADD_SCORE_ENEMY = 500,
		ADD_SCORE_ITEM = 3000,
		ADD_SCORE_MEDIUM_BOSS = 5000,
		ADD_SCORE_LAST_BOSS_PART = 8000,
		ADD_SCORE_LAST_BOSS = 20000,
	};

//===================== �֐� ======================//

	//	�f�X�g���N�^
	~UIScore();

	//	����
	static UIScore* GetInstance()
	{
		static UIScore s_instance;
		return &s_instance;
	}

	//	�X�V
	void Update();

	//	�`��
	void Draw();

	//	�X�R�A�̉��Z
	void AddScore(const ADD_SCORE _score) { m_targetScore += (int)_score; }

	//	�X�R�A�̉��Z
	void AddScore(const float _score) { m_targetScore += (int)_score; }

	//	�X�R�A���Z�̃X�L�b�v
	void SkipScore() { m_score = m_targetScore; }

	//	�X�R�A�̃��Z�b�g
	void ScoreReset();

//==================== getter =====================//

	//	�X�R�A�̎擾
	const int GetScore() const { return (int)m_score; }

private:

//================== �V���O���g�� ==================//

	//	�R���X�g���N�^
	UIScore();

//=================== �����o�ϐ� ===================//

	VECTOR	m_pos;											//	�|�W�V����
	float	m_score;										//	�X�R�A
	float	m_targetScore;									//	�X�R�A�̃^�[�Q�b�g
	char	m_scoreText[CommonConstant::MAX_SCORE_NUM];		//	�X�R�A�̕�����

//===================== �ÓI�萔 ===================//

};

#define SCORE UIScore::GetInstance()