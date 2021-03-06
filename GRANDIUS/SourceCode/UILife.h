﻿
//=============================================================================
//	@file	UILife.h
//	@brief	ライフUI
//	@autor	Takuya Ochi
//	@date	2018/12/15
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
class PlayerManager;
struct UI;

//-----------------------------------------------------------------------------
//	@brief	UILifeクラス
//-----------------------------------------------------------------------------
class UILife final
{
public:

//===================== 関数 ======================//

	//	コンストラクタ/デストラクタ
	UILife();
	~UILife();

	//	作成処理
	void Create();

	//	解放処理
	void Release();

	//	描画処理
	void Draw(PlayerManager& _playerManager);

private:

//================== 内部処理関数 ==================//

	//	最終的な解放処理
	void _FinalRelease();

//=================== メンバ変数 ===================//

	UI		m_lifeUI;			//	ライフUI

//===================== 静的定数 ===================//

	static const float LEFT_UI_INTEVAL;					//	ライフUIの間隔

};