//=============================================================================
//
// 乗り物制御クラス [character_vehicle.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_VEHICLE_H
#define _CHARACTER_VEHICLE_H
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

//=============================================================================
// クラス定義
//=============================================================================
class CVehicle : public CScene2D
{
public:
	//コンストラクタ
	//第一引数:プライオリティ(最大はPRIORITY_MAX、何も入力しないとPRIORITY_MAX - 2に設定)
	//第二引数:オブジェクトタイプ(何も入力しないとOBJTYPE_NONEに設定)
	CVehicle(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//デストラクタ
	~CVehicle(){};

	//クリエイト
	//第一引数:デバイス
	//第二引数:テクスチャ情報
	//戻り値  :インスタンスのポインタ
	static CVehicle* Create(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture);

	//初期化処理
	//第一引数:デバイス
	//第二引数:テクスチャ情報
	//戻り値  :成功したかどうかをHRESULT型で返す
	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture);

	//終了処理
	void	Uninit(void);

	//更新処理
	void	Update(void);

	//描画処理
	void	Draw(void);

	//乗り物の壊れ具合取得(大きくなるにつれて壊れていく)
	//戻り値:乗り物の破壊率
	int RateOfDestruction_()
	{
		return (RateOfDestruction);
	}
	
	//乗り物の破壊率加算
	//第一引数:加算したい値(減算したい場合は-の値を入れてください)
	void addRateOfDestruction(int value);
	//アニメーションのセット処理
	void SetAnimMode(int animID,bool Rupe);
	//描画のON,OFF切り替え
	//第一引数:描画するかしないか
	void SetisDraw(bool value)
	{
		isDraw=value;
	}

private:
	//現在のアニメーションモード
	int AnimMode;
	//アニメーションのループフラグ
	bool isRupeAnim;
	//アニメーションの1順終了フラグ
	bool isAnimEnd;
	//描画フラグ
	bool isDraw;

	//現在のアニメーション番号
	int nowAnim;
	//アニメーションのカウント用
	int cntAnim;
	//アニメーションの最大コマ数
	D3DXVECTOR2 maxAnim;
	//破壊率
	int RateOfDestruction;

	//変数のNULL埋め処理
	void NullSetVariable(void)
	{
		RateOfDestruction=1;
		isDraw=true;
		isAnimEnd=false;
		isRupeAnim=true;
		AnimMode=99;
		cntAnim=0;
		nowAnim=1;
		maxAnim.x=1;
		maxAnim.y=1;
	}

	//アニメーションの更新処理
	void UpdateAnim();
};

#endif

