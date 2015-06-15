//=============================================================================
//
// パーティクル制御クラス [particle_object.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _PARTICLE_OBJECT_H
#define _PARTICLE_OBJECT_H
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
// マクロ
//============================================================================
struct LASER
{
	float Time;

	D3DXVECTOR2 Position;

	D3DXVECTOR2 ControlVector0;
	D3DXVECTOR2 ControlVector1;

	bool Use;
};
//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// クラス定義
//=============================================================================
class CParticleObject: public CScene2D
{
public:
	//コンストラクタ
	//第一引数:プライオリティ(最大はPRIORITY_MAX、何も入力しないとPRIORITY_MAX - 2に設定)
	//第二引数:オブジェクトタイプ(何も入力しないとOBJTYPE_NONEに設定)
	CParticleObject(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//デストラクタ
	~CParticleObject(){};

	//クリエイト
	//第一引数:デバイス
	//戻り値  :インスタンスのポインタ
	static CParticleObject* Create(LPDIRECT3DDEVICE9 device);

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

	//パーティクル開始処理
	void Start(D3DXVECTOR2 pos,D3DXVECTOR2 spd,int LiveTime);
	//パーティクル破壊処理
	void Destroy();

private:
	//移動スピード
	D3DXVECTOR2 m_spd;
	//生存時間
	int LiveTime;
	//生きているかどうか
	bool isDeth;
	//存在した時間
	int LiveCnt;

	//レーザーの動きに必要な変数群
	LASER m_Laser;

	D3DXVECTOR2 targetPos;


	//変数のNULL埋め処理
	void NullSetVariable(void)
	{
		LiveCnt=0;
		m_spd=D3DXVECTOR2(0.0f,0.0f);
		LiveTime=100;
		isDeth=true;
		m_Laser.ControlVector0=D3DXVECTOR2(0.0f,0.0f);
		m_Laser.ControlVector1=D3DXVECTOR2(0.0f,0.0f);
		m_Laser.Position=D3DXVECTOR2(0.0f,0.0f);
		m_Laser.Time=0.0f;
		m_Laser.Use=false;
		targetPos=D3DXVECTOR2(0.0f,0.f);
	}
};

#endif

