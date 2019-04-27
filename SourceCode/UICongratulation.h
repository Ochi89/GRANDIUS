﻿
//=============================================================================
//	@file	UICongratulation.h
//	@brief	ゲームオーバーUI
//	@autor	相知 拓弥
//	@date	2018/12/30
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
class PlayerManager;

//-----------------------------------------------------------------------------
//	@brief	UICongratulationクラス
//-----------------------------------------------------------------------------
class UICongratulation final
{
public:

//===================== 関数 ======================//

	//	コンストラクタ/デストラクタ
	UICongratulation();
	~UICongratulation();

	//	作成処理
	void Create();

	//	解放処理
	void Release();

	//	描画処理
	void Update(PlayerManager& _playerManager);

	//	描画処理
	void Draw();

private:

//================== 内部処理関数 ==================//

	//	最終的な解放処理
	void _FinalRelease();

//=================== メンバ変数 ===================//

	UI		m_congratulationUI;		//	ゲームオーバーUI
	int		m_alpha;				//	アルファ値
	bool	m_isClear;				//	クリアフラグ
	float	m_clearWaitTime;		//	クリア時の遅延時間

//===================== 静的定数 ===================//

	static const float		MAAX_CLEAR_WAIT_TIME;	//	クリア時の遅延時間の最大
	static const int		MIN_ALPHA;				//	アルファ値の最小
	static const int		MAX_ALPHA;				//	アルファ値の最大
	static const int		ALPHA_SPEED;			//	アルファ値の速度

};