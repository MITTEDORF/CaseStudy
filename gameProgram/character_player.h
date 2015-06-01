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
//乗り物制御クラス
class CVehicle;
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
	//戻り値:プレイヤーの移動量
	D3DXVECTOR2 move_spd_()
	{
		return (m_move_spd);
	}

	//HPの取得処理
	//戻り値:プレイヤーのHP
	int HP_()
	{
		return (HP);
	}

	//HPの加算処理
	//第一引数:加算する値(減算したい場合は-の値を入れてください)
	void AddHP(int value)
	{
		HP+=value;
		//HPが0いかにならないように処理
		if(HP<=0)
		{
			HP=0;
		}
	}

private:

	//Y値オフセット
	D3DXVECTOR2 Offset;

	//プレイヤーのHP
	int HP;

	//キーボード情報格納変数
	CInputKeyboard*	m_keyboard;
	//プレイヤーの移動速度
	D3DXVECTOR2 m_move_spd;

	//ジャンプ中かどうか
	bool isJump;
	//ジャンプ可能かどうか
	bool canJump;
	//攻撃中かどうか
	bool isAttack;

	//現在のアニメーションモード
	int AnimMode;
	//アニメーションのループフラグ
	bool isRupeAnim;
	//アニメーションの1順終了フラグ
	bool isAnimEnd;

	//現在のアニメーション番号
	int nowAnim;
	//アニメーションのカウント用
	int cntAnim;
	//アニメーションの最大コマ数
	int maxAnim;

	CVehicle* Assy;

	//変数のNULL埋め処理
	void NullSetVariable(void)
	{
		Offset.x=0;
		Offset.y=0;
		HP=3;
		maxAnim=1;
		isAnimEnd=false;
		isRupeAnim=true;
		AnimMode=-1;
		m_keyboard=NULL;
		Assy=NULL;
		cntAnim=0;
		nowAnim=1;
		m_move_spd=D3DXVECTOR2(0.0f,0.0f);
		isJump=false;
		isAttack=false;
		canJump=true;
	}

	//移動処理
	void Move();
	//攻撃処理
	void Attack();
	//ジャンプ処理
	void moveJump();
	//重力をかける
	void AddGravity();
	//様々な当たり判定
	void Collider();
	//アニメーションの更新処理
	void UpdateAnim();
	//アニメーションのセット処理
	void SetAnimMode(int animID,bool Rupe);


};

#endif

