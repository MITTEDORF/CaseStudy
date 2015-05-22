//=============================================================================
//
// プレイヤー制御クラス [character_player.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_PLAYER_H
#define _CHARACTER_PLAYER_H
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
// マクロ
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
//キーボード入力制御クラス
class CInputKeyboard;

//=============================================================================
// クラス定義
//=============================================================================
class CPlayer : public CScene2D
{
public:
	//コンストラクタ
	//第一引数:プライオリティ(最大はPRIORITY_MAX、何も入力しないとPRIORITY_MAX - 2に設定)
	//第二引数:オブジェクトタイプ(何も入力しないとOBJTYPE_NONEに設定)
	CPlayer(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//デストラクタ
	~CPlayer(){};

	//クリエイト
	//第一引数:デバイス
	//戻り値  :インスタンスのポインタ
	static CPlayer* Create(LPDIRECT3DDEVICE9 device);

	//初期化処理
	//第一引数:デバイス
	//戻り値  :成功したかどうかをHRESULT型で返す
	HRESULT	Init(LPDIRECT3DDEVICE9 device);

	//終了処理
	void	Uninit(void);

	//更新処理
	void	Update(void);

	//描画処理
	void	Draw(void);

	//キーボード情報のセット
	void SetKeyboard(CInputKeyboard* keyboard){m_keyboard = keyboard;}

	//移動速度の取得処理
	float move_spd_()
	{
		return (m_move_spd);
	}

private:
	//キーボード情報格納変数
	CInputKeyboard*	m_keyboard;
	//プレイヤーの移動速度
	float m_move_spd;
	//ジャンプ中かどうか
	bool isJump;
	//ジャンプ可能かどうか
	bool canJump;
	//ジャンプスピード
	float jump_spd;


	//変数のNULL埋め処理
	void NullSetVariable(void)
	{
		m_keyboard=NULL;
		m_move_spd=0.0f;
		isJump=false;
		canJump=true;
		jump_spd=0.0f;
	}
	//ジャンプ処理
	void moveJump();
	//重力をかける
	void AddGravity();

};

#endif

