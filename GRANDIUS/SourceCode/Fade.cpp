
//=============================================================================
//	@file	Fade.cpp
//	@brief	フェード
//	@autor	相知 拓弥
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Fade.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	コンストラクタ
//-----------------------------------------------------------------------------
Fade::Fade()
{
	m_alpha = 0;
	m_isOneTime = false;
	m_isFadeIn = false;
	m_isFadeOut = false;
	m_isEndFade = false;
}

//-----------------------------------------------------------------------------
//	@brief	デストラクタ
//-----------------------------------------------------------------------------
Fade::~Fade()
{
	// 処理なし
}

//-----------------------------------------------------------------------------
//	@brief	更新
//-----------------------------------------------------------------------------
void Fade::Update()
{
	//	フェード開始時の一度のみ実行
	if (!m_isOneTime)
	{
		m_alpha = 0;
		m_isFadeIn = true;
		m_isFadeOut = false;
		m_isEndFade = false;
		m_isOneTime = true;
	}

	//	フェードイン
	_FadeIn();

	//	フェードアウト
	_FadeOut();

	//	描画
	_Draw();
}

//-----------------------------------------------------------------------------
//	@brief	フェードの開始
//-----------------------------------------------------------------------------
void Fade::IsFadeStart()
{
	m_isOneTime = false;
	m_isFadeIn = false;
	m_isFadeOut = false;
	m_isEndFade = false;
}

//-----------------------------------------------------------------------------
//	@brief	フェードイン
//-----------------------------------------------------------------------------
void Fade::_FadeIn()
{
	if (m_isFadeIn)
	{
		m_alpha += 5;
		if (m_alpha >= 255) { m_alpha = 255; m_isFadeIn = false; m_isFadeOut = true; }
	}
}

//-----------------------------------------------------------------------------
//	@brief	フェードアウト
//-----------------------------------------------------------------------------
void Fade::_FadeOut()
{
	if (m_isFadeOut)
	{
		m_alpha -= 5;
		if (m_alpha <= 0) { m_alpha = 0; m_isFadeOut = false; m_isEndFade = true; }
	}
}

//-----------------------------------------------------------------------------
//	@brief	描画
//-----------------------------------------------------------------------------
void Fade::_Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawBox(0, 0, CommonConstant::WINDOW_WIDTH, CommonConstant::WINDOW_HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
