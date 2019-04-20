﻿
//=============================================================================
//	@file	Title.h
//	@brief	タイトル
//	@autor	相知 拓弥
//	@date	2018/1/6
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	前方宣言
//-----------------------------------------------------------------------------
struct UI;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	タイトルクラス
//-----------------------------------------------------------------------------
class Title final
{
public:

//===================== 関数 ======================//

	// コンストラクタ / デストラクタ
	Title();
	~Title();

	//	作成処理
	void Create();

	//	解放処理
	void Release();

	//	更新処理
	void Update(SoundEffect& _soundEffect);

	//	描画処理
	void Draw();

private:

//================== 内部処理関数 ==================//

	//	タイトルの拡縮率を求める
	void _AskTitleScale(SoundEffect& _soundEffect);

	//	点滅描画
	void _FlashingDraw(UI& _ui);

	//	最終的な解放処理
	void _FinalRelease();

//=================== メンバ変数 ===================//

	UI		m_titleLogo;		//	タイトルロゴ
	UI		m_title;			//	タイトル
	UI		m_start;			//	スタート
	bool	m_isSeStart;		//	SEの開始

//===================== 静的定数 ===================//

	static const float EQUAL;				//	等倍
	static const float SUB_SCALE_SPEED;		//	拡大率の速度

};
