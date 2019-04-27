﻿
//=============================================================================
//	@file	Mouse.h
//	@brief	マウス入力
//	@autor	Takuya Ochi
//	@date	2018/9/28
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "DxLib.h"

//-----------------------------------------------------------------------------
//	@brief	マウス入力クラス
//-----------------------------------------------------------------------------
class Mouse final
{
public:

//===================== 関数 ======================//

	//	デストラクタ
	~Mouse();

	//	更新処理
	void Update();

	//	押した瞬間
	bool Push(const char* _mode);

	//	押されている間
	bool Press(const char* _mode);

	//	インスタンスの生成
	static Mouse* GetInstance()
	{
		static Mouse s_instance;
		return &s_instance;
	}

//==================== getter =====================//

	//	ポジションの getter
	const VECTOR& GetPos() const { return m_pos; };	

private:

//================== シングルトン ==================//

	//	コンストラクタ
	Mouse();

//================== 内部処理関数 ==================//

	//	移動量を求める
	void _Velocity();

//=================== メンバ変数 ===================//

	VECTOR	m_pos;			//	ポジション
	int		m_newPosX;		//	新しいｘ座標
	int		m_newPosY;		//	新しいｙ座標
	int		m_prevLeft;		//	前フレームに左ボタン入力があるか
	int		m_prevRight;	//	前フレームに右ボタン入力があるか
};

//===================== マクロ =====================//

#define MOUSE Mouse::GetInstance()//	マウスのインスタンス