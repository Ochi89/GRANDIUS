﻿
//=============================================================================
//	@file	PlayCounter.cpp
//	@brief	プレイ回数
//	@autor	Takuya Ochi
//	@date	2018/1/9
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayCounter.h"
#include "LoadFile.h"

//-----------------------------------------------------------------------------
//	@brief	コンストラクタ
//-----------------------------------------------------------------------------
PlayCounter::PlayCounter()
{
	m_playCpunt = 0;
}

//-----------------------------------------------------------------------------
//	@brief	デストラクタ
//-----------------------------------------------------------------------------
PlayCounter::~PlayCounter()
{
	//	処理なし
}

//-----------------------------------------------------------------------------
//	@brief	プレイ回数の加算
//-----------------------------------------------------------------------------
void PlayCounter::AddPlayCounter()
{
	//	読み込み
	_Load();

	//	プレイ回数の加算
	m_playCpunt++;

	//	書き込み
	_Writing();
}

//-----------------------------------------------------------------------------
//	@brief	読み込み
//-----------------------------------------------------------------------------
void PlayCounter::_Load()
{
	//	ファイルの読み込み
	LOAD_FILE->LoadCsvFile("Data/CSV/PlayCounter.csv");

	//	内容の取得
	m_playCpunt = LOAD_FILE->GetCsvFile();
}

//-----------------------------------------------------------------------------
//	@brief	書き込み
//-----------------------------------------------------------------------------
void PlayCounter::_Writing()
{
	//	書き込み
	LOAD_FILE->WritingCsvFile("Data/CSV/PlayCounter.csv", m_playCpunt);
}
