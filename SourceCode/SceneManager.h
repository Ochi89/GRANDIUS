﻿
//=============================================================================
//	@file	SceneManager.h
//	@brief	シーンマネージャー
//	@autor	相知 拓弥
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
//	@brief	前方宣言
//-----------------------------------------------------------------------------
class SceneBase;
class Pad;
class BackGround;
class Camera;
class Sound;
class SoundEffect;

//-----------------------------------------------------------------------------
//	@brief	シーン管理クラス
//-----------------------------------------------------------------------------
class SceneManager final
{
public:

//==================== 列挙体 =====================//

	//	シーンの種類
	enum SCENE_KIND
	{
		TITLE_SCENE,			//	タイトルシーン
		GAME_SCENE,				//	ゲームシーン
		RESULT_SCENE,			//	リザルトシーン
		DEMO_SCENE,				//	デモシーン
	};

//===================== 関数 ======================//

	//	コンストラクタ/デストラクタ
	SceneManager();
	~SceneManager();

	//	作成処理
	void Create();

	//	解放処理
	void Release();

	//	初期処理
	void Initialize();

	//	シーンの切り替え
	void ChangeScene(SCENE_KIND _sceneKind);

	//	メインループ
	void Ran();


private:

//================== 内部処理関数 ==================//

	//	更新
	void _Update();

	//	描画
	void _Draw();

	//	パッドの入力
	void _PadInput();

	//	パッドの解放
	void _PadRelease();

	//	最終的な解放
	void _FinalRelease();

//=================== メンバ変数 ===================//

	SceneBase*			m_pScene;			//	現在のシーン
	Pad*				m_pPad1;			//	パッド1
	Pad*				m_pPad2;			//	パッド2
	Pad*				m_pPad3;			//	パッド3
	Pad*				m_pPad4;			//	パッド4
	Camera*				m_pCamera;			//	カメラ
	BackGround*			m_pBackGround;		//	背景
	SoundEffect*		m_pSoundEffect;		//	SE
};