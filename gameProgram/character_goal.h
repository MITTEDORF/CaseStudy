//=============================================================================
//
// プレイヤー制御クラス [character_player.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_GOAL_H
#define _CHARACTER_GOAL_H
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
// マクロ
//============================================================================

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// クラス定義
//=============================================================================
class CCharacterGoal : public CScene2D
{
public:
	//コンストラクタ
	CCharacterGoal(){NullSetValiable();};
	//デストラクタ
	~CCharacterGoal(){};

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

	bool isFade_()
	{
		return (isFade);
	}
	bool isStart_()
	{
		return (isStart);
	}

	void Start(CScene* Target);

	static CCharacterGoal* Create(LPDIRECT3DDEVICE9 device);

private:
	CScene2D* CharacterL;
	CScene2D* CharacterR;

	CScene* target;

	bool isFade;
	bool isStart;

	float lenL;
	float lenR;

	int Cunt;

	void NullSetValiable()
	{
		isStart=false;
		isFade=false;
		Cunt=0;
		lenL=0;
		lenR=0;
		CharacterL=NULL;
		CharacterR=NULL;
		target=NULL;
	}



};

#endif

