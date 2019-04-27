﻿
//=============================================================================
//	@file	EffekseerManager.h
//	@brief	EffekseerManager
//	@autor	Takuya Ochi
//	@date	2018/12/31
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Common.h"

//-----------------------------------------------------------------------------
//	@brief	EffekseerManagerクラス
//-----------------------------------------------------------------------------
class EffekseerManager final
{
public:

//===================== 関数 ======================//

	//	コンストラクタ / デストラクタ
	EffekseerManager();
	~EffekseerManager();

	//	更新処理
	void Update();

	//	描画処理
	void Draw();

private:

};