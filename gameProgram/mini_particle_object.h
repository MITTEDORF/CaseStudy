//=============================================================================
//
// パーティクル制御クラス [particle_object.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _MINI_PARTICLE_OBJECT_H
#define _MINI_PARTICLE_OBJECT_H
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "particle_manager.h"
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
class CMiniParticleObject: public CScene2D
{
public:
	//コンストラクタ
	//第一引数:プライオリティ(最大はPRIORITY_MAX、何も入力しないとPRIORITY_MAX - 2に設定)
	//第二引数:オブジェクトタイプ(何も入力しないとOBJTYPE_NONEに設定)
	CMiniParticleObject(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//デストラクタ
	~CMiniParticleObject(){};

	//クリエイト
	//第一引数:デバイス
	//戻り値  :インスタンスのポインタ
	static CMiniParticleObject* Create(LPDIRECT3DDEVICE9 device);

	//初期化処理
	//第一引数:デバイス
	//戻り値  :成功したかどうかをHRESULT型で返す
	HRESULT	Init(LPDIRECT3DDEVICE9 device);

	//終了処理
	void	Uninit(void);

	//更新処理
	void	Update(void);

	//描画処理
	void Draw(void);

	//パーティクル開始処理
	//第一引数:スタート座標
	//第二引数:目的の座標
	void Start(D3DXVECTOR2 pos);

	//パーティクル破壊処理
	void Destroy();

	//パーティクルが生きているかどうか
	//戻り値:パーティクルの生死
	bool isUse_()
	{
		return (isUse);
	}

	void Scrol(float value)
	{
		m_pos.x -=value;
		CScene2D::SetVertexPolygon();
	}
private:

	D3DXCOLOR m_color;

	float m_Rad;

	float Angle;

	bool isUse;

	float ColA;

	float Anglespd;



	//変数のNULL埋め処理
	void NullSetVariable(void)
	{
		Angle=0.0f;
		m_Rad=0;
		m_color=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		isUse=false;
		ColA=1.0f;
		Anglespd=0;
	}
};

#endif

