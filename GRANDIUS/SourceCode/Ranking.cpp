
//=============================================================================
//	@file	Ranking.cpp
//	@brief	�����L���O
//	@autor	���m ���
//	@date	2018/1/3
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "Ranking.h"
#include "LoadFile.h"
#include "UIScore.h"
#include "Pad.h"
#include "SoundEffect.h"

//-----------------------------------------------------------------------------
//	@brief	�ÓI�萔
//-----------------------------------------------------------------------------
const int			Ranking::TEXT_START = 29;						//	�e�L�X�g�̏����ʒu
const int			Ranking::TEXT_INTERVAL = 91;					//	���܂ł̊Ԋu
const int			Ranking::AFTER_RANK = -1;						//	�����N�O
const float			Ranking::MAX_PRODUCTION_TIME = 120.0f;			//	���o���Ԃ̍ő�
const float			Ranking::MAX_WAITTIME = 60.0f;					//	�x�����Ԃ̍ő�
const float			Ranking::LIFE_BONUS_SCORE = 50000.0f;			//	���C�t�{�[�i�X
const float			Ranking::DESTRUCTION_BONUS_SCORE = 5000.0f;		//	�������{�[�i�X
const float			Ranking::MAX_SCENE_CHANGE_TIME = 3600.0f;		//	�V�[���؂�ւ����Ԃ̍ő�

//-----------------------------------------------------------------------------
//	@brief	�R���X�g���N�^
//-----------------------------------------------------------------------------
Ranking::Ranking()
{
	//	���e�̏�����
	for (int i = 0; i < CommonConstant::MAX_RANKING_NUM; i++)
	{
		m_score[i] = 0;
	}

	m_rank = AFTER_RANK;
	m_isLifeBonusScore = false;
	m_isDestructionBonusScore = false;
	m_isRankingStart = false;
	m_productionTime = 0.0f;
	m_waitTime = 0.0f;
	m_lifeBonusScoreVal = 0.0f;
	m_DestructionBonusScoreVal = 0.0f;
	m_flashingTime = 0.0f;
	m_sceneChangeTime = 0.0f;
	m_isSceneChange = false;

	m_bonusUI.m_spriteHendle = LoadGraph("Data/Sprite/Result/Bonus.png");
	CommonDebug::Assert((m_bonusUI.m_spriteHendle <= -1), " [ Ranking.cpp ] : error : sprite loading failed.");
	m_bonusUI.m_pos = VGet(10.0f, 10.0f, 0.0f);

	m_rankingUI.m_spriteHendle = LoadGraph("Data/Sprite/Result/Ranking.png");
	CommonDebug::Assert((m_rankingUI.m_spriteHendle <= -1), " [ Ranking.cpp ] : error : sprite loading failed.");
	m_rankingUI.m_pos = VGet(10.0f, 10.0f, 0.0f);
}

//-----------------------------------------------------------------------------
//	@brief	�f�X�g���N�^
//-----------------------------------------------------------------------------
Ranking::~Ranking()
{
	//	�X�v���C�g�̃A�����[�h
	DeleteGraph(m_bonusUI.m_spriteHendle);
	DeleteGraph(m_rankingUI.m_spriteHendle);
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void Ranking::Initialize()
{
	//	�ǂݍ���
	_Load();

	//	�N���A���Ă���Ƃ��A
	//	�{�[�i�X������
	const bool isClear = HAND_OVER_RESULT->GetIsClear();
	if (isClear) { m_isLifeBonusScore = true; }
	else { m_isRankingStart = true; }
}

//-----------------------------------------------------------------------------
//	@brief	�X�V����
//-----------------------------------------------------------------------------
void Ranking::Update(Pad& _pad, SoundEffect& _soundEffect)
{
	//	���C�t�{�[�i�X
	_LifeBonus(_pad, _soundEffect);

	//	�������{�[�i�X
	_DestructionBonus(_pad, _soundEffect);

	//	�����L���O
	_Ranking(_soundEffect);
}

//-----------------------------------------------------------------------------
//	@brief	�`�揈��
//-----------------------------------------------------------------------------
void Ranking::Draw()
{
	//	���C�t�{�[�i�X
	if (m_isLifeBonusScore)
	{
		FONT->Draw(700, 400, m_thisTimeScoreText);
		FONT->Draw(700, 500, m_bonusScoreText);
	}

	//	�����{�[�i�X
	if (m_isDestructionBonusScore)
	{
		FONT->Draw(700, 400, m_thisTimeScoreText);
		FONT->Draw(700, 500, m_bonusScoreText);
	}

	//	�{�[�i�X��
	const bool isBonus = m_isLifeBonusScore || m_isDestructionBonusScore;
	if (isBonus) { DrawGraph((int)m_bonusUI.m_pos.x, (int)m_bonusUI.m_pos.y, m_bonusUI.m_spriteHendle, TRUE); }

	//	�����L���O
	if (m_isRankingStart)
	{
		//	�X�R�A�̕\��
		for (int i = 0; i < CommonConstant::MAX_RANKING_NUM; i++)
		{
			_FlashingDraw(i, m_rank);
		}

		//	�����N�O�̕\��
		_AfterRankFlashingDraw();

		DrawGraph((int)m_rankingUI.m_pos.x, (int)m_rankingUI.m_pos.y, m_rankingUI.m_spriteHendle, TRUE);
	}
}

//-----------------------------------------------------------------------------
//	@brief	���C�t�{�[�i�X
//-----------------------------------------------------------------------------
void Ranking::_LifeBonus(Pad& _pad, SoundEffect& _soundEffect)
{
	if (m_isLifeBonusScore)
	{
		const bool isBonusStart = m_productionTime == 0.0f;
		const bool isBonusSE = m_productionTime == 30.0f;
		const bool isAddBonus = m_productionTime >= 30.0f;
		const bool isBonusEnd = m_lifeBonusScoreVal <= 0.0f;

		if (isBonusStart)
		{
			//	�{�[�i�X�l�����߂�
			m_lifeBonusScoreVal = LIFE_BONUS_SCORE * HAND_OVER_RESULT->GetLife();
			SCORE->AddScore(m_lifeBonusScoreVal);
		}

		//	SE�̍Đ�
		if (isBonusSE)
		{
			const bool isSE = m_lifeBonusScoreVal > 0.0f;
			if (isSE) { _soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_SCORE_UP); }
		}

		//	�{�[�i�X�̉��Z
		if (isAddBonus)
		{
			SCORE->Update();
			const float ignore = 1.0f;
			const float lerpSpeed = 0.2f;
			m_lifeBonusScoreVal = CommonFunction::Lerp(m_lifeBonusScoreVal, 0.0f, lerpSpeed, ignore);
		}

		//	�������{�[�i�X�ֈڍs����
		if (isBonusEnd)
		{
			const bool isActive = m_waitTime++ >= MAX_WAITTIME;
			if (isActive)
			{
				m_isLifeBonusScore = false;
				m_isDestructionBonusScore = true;
				m_productionTime = 0.0f;
				m_waitTime = 0.0f;
				return;
			}
		}

		m_productionTime++;

		//	���o�̃X�L�b�v
		const bool isKeyActive = KEY->Push(KEY_INPUT_RETURN) || KEY->Push(KEY_INPUT_SPACE) || KEY->Push(KEY_INPUT_X) || KEY->Push(KEY_INPUT_K) || KEY->Push(KEY_INPUT_A);
		const bool isNextActive = isKeyActive || _pad.GetXInputPushButton(PadInfo::PAD_BUTTON_KIND::BUTTON_A);
		if (isNextActive)
		{
			SCORE->SkipScore();
			m_lifeBonusScoreVal = 0.0f;
			m_isLifeBonusScore = false;
			m_isDestructionBonusScore = true;
			m_productionTime = 0.0f;
			m_waitTime = 0.0f;

			//	SE�̍Đ�
			_soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_MENU_DECISION);
		}

		sprintf(m_thisTimeScoreText, "%010d", SCORE->GetScore());
		sprintf(m_bonusScoreText, "%010d", (int)m_lifeBonusScoreVal);

	}
}

//-----------------------------------------------------------------------------
//	@brief	�������{�[�i�X
//-----------------------------------------------------------------------------
void Ranking::_DestructionBonus(Pad& _pad, SoundEffect& _soundEffect)
{
	if (m_isDestructionBonusScore)
	{
		const bool isBonusStart = m_productionTime == 0.0f;
		const bool isBonusSE = m_productionTime == 30.0f;
		const bool isAddBonus = m_productionTime >= 30.0f;
		const bool isBonusEnd = m_DestructionBonusScoreVal <= 0.0f;

		if (isBonusStart)
		{
			//	�{�[�i�X�l�����߂�
			m_DestructionBonusScoreVal = DESTRUCTION_BONUS_SCORE * HAND_OVER_RESULT->GetDestructionNum();
			SCORE->AddScore(m_DestructionBonusScoreVal);
		}

		if (isBonusSE)
		{
			//	SE�̍Đ�
			const bool isSE = m_DestructionBonusScoreVal > 0.0f;
			if (isSE) { _soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_SCORE_UP); }
		}

		//	�{�[�i�X�̉��Z
		if (isAddBonus)
		{
			SCORE->Update();

			const float ignore = 1.0f;
			const float lerpSpeed = 0.2f;
			m_DestructionBonusScoreVal = CommonFunction::Lerp(m_DestructionBonusScoreVal, 0.0f, lerpSpeed, ignore);
		}

		//	�����L���O�ֈڍs����
		if (isBonusEnd)
		{
			const bool isActive = m_waitTime++ >= MAX_WAITTIME;
			if (isActive)
			{
				m_isDestructionBonusScore = false;
				m_isRankingStart = true;
				m_productionTime = 0.0f;
				m_waitTime = 0.0f;
				return;
			}
		}

		m_productionTime++;

		//	���o�̃X�L�b�v
		const bool isKeyActive = KEY->Push(KEY_INPUT_RETURN) || KEY->Push(KEY_INPUT_SPACE) || KEY->Push(KEY_INPUT_X) || KEY->Push(KEY_INPUT_K) || KEY->Push(KEY_INPUT_A);
		const bool isNextActive = isKeyActive || _pad.GetXInputPushButton(PadInfo::PAD_BUTTON_KIND::BUTTON_A);
		if (isNextActive)
		{
			SCORE->SkipScore();
			m_DestructionBonusScoreVal = 0.0f;
			m_isDestructionBonusScore = false;
			m_isRankingStart = true;
			m_productionTime = 0.0f;
			m_waitTime = 0.0f;

			//	SE�̍Đ�
			_soundEffect.OnPlaySound(_soundEffect.ONE_SE_KIND::ONE_SE_MENU_DECISION);
		}

		sprintf(m_thisTimeScoreText, "%010d", (int)SCORE->GetScore());
		sprintf(m_bonusScoreText, "%010d", (int)m_DestructionBonusScoreVal);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�����L���O
//-----------------------------------------------------------------------------
void Ranking::_Ranking(SoundEffect& _soundEffect)
{
	if (m_isRankingStart)
	{
		const bool isRankingStart = m_productionTime == 0.0f;
		if (isRankingStart)
		{
			//	�\�[�g
			_Sort();

			//	��������
			_Writing();

			m_productionTime++;
		}

		//	���l�𕶎��ɂ���
		for (int i = 0; i < CommonConstant::MAX_RANKING_NUM; i++)
		{
			sprintf(m_scoreText[i], "%010d", (int)m_score[i]);
		}

		//	�V�[���؂�ւ�
		m_sceneChangeTime++;
		m_isSceneChange = m_sceneChangeTime >= MAX_SCENE_CHANGE_TIME;
	}
}

//-----------------------------------------------------------------------------
//	@brief	�ǂݍ���
//-----------------------------------------------------------------------------
void Ranking::_Load()
{
	//	�t�@�C���̓ǂݍ���
	LOAD_FILE->LoadCsvFile("Data/CSV/Score.csv");

	//	���e�̎擾
	for (int i = 0; i < CommonConstant::MAX_RANKING_NUM; i++)
	{
		m_score[i] = LOAD_FILE->GetCsvFile(i);
	}
}

//-----------------------------------------------------------------------------
//	@brief	�\�[�g
//-----------------------------------------------------------------------------
void Ranking::_Sort()
{
	//	����̃X�R�A�ƁA���܂ł̃X�R�A�̔�r
	for (int i = 0; i < CommonConstant::MAX_RANKING_NUM; i++)
	{
		//	�X�R�A�������L���O���X�R�A���傫����
		const bool isActive = m_score[i] <= SCORE->GetScore();
		if (isActive)
		{
			//	���̒n�_�ɑ������
			int tmp1 = m_score[i];
			m_score[i] = SCORE->GetScore();

			//	����
			m_rank = i;

			//	����ȍ~���A������炷
			for (int j = (i + 1); j < CommonConstant::MAX_RANKING_NUM; j++)
			{
				int tmp2 = m_score[j];
				m_score[j] = tmp1;
				tmp1 = tmp2;
			}

			//	�X�R�A�̑}���͏I������̂ŁA
			//	���[�v���甲����
			return;
		}
	}
}

//-----------------------------------------------------------------------------
//	@brief	��������
//-----------------------------------------------------------------------------
void Ranking::_Writing()
{
	//	��������
	LOAD_FILE->WritingCsvFile("Data/CSV/Score.csv", CommonConstant::MAX_RANKING_NUM, m_score);
}

//-----------------------------------------------------------------------------
//	@brief	�_�ŕ`��
//-----------------------------------------------------------------------------
void Ranking::_FlashingDraw(const int _num, const int _rank)
{
	
	//	�_�ŕ`��
	const bool isFlashing = _num == _rank;
	if (isFlashing)
	{
		const bool isDraw = m_flashingTime >= 0.0f && m_flashingTime <= 15.0f;
		const bool isReset = m_flashingTime >= 20.0f;

		if (isDraw) { FONT->Draw(782, TEXT_START + (TEXT_INTERVAL * _num), m_scoreText[_num]); }
		if (isReset) { m_flashingTime = 0.0f; return; }

		m_flashingTime++;
		return;
	}

	//	�_�łȂ��`��
	FONT->Draw(782, TEXT_START + (TEXT_INTERVAL * _num), m_scoreText[_num]);
}

//-----------------------------------------------------------------------------
//	@brief	�����N�O�̓_�ŕ`��
//-----------------------------------------------------------------------------
void Ranking::_AfterRankFlashingDraw()
{
	//	�_�ŕ`��
	const bool isAfterRank = m_rank == AFTER_RANK;
	if (isAfterRank)
	{
		const bool isDraw = m_flashingTime >= 0.0f && m_flashingTime <= 15.0f;
		const bool isReset = m_flashingTime >= 20.0f;

		if (isDraw) { FONT->Draw(782, 975, m_thisTimeScoreText); }
		if (isReset) { m_flashingTime = 0.0f; return; }

		m_flashingTime++;
		return;
	}
}
