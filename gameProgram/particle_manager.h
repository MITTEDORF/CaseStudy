//=============================================================================
//
// パーティクル管理クラス [particle_manager.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _PARTICLE_MANAGER_H
#define _PARTICLE_MANAGER_H
//=============================================================================
// インクルード
//============================================================================
#include "particle_object.h"
//=============================================================================
// マクロ
//============================================================================
//パーティクル数
const int PARTICLE_MAX            = 40;
//ディレイ
const int PARTICLE_COOL_DOWN_TIME = 10;
//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// クラス定義
//=============================================================================
class CParticleManager
{
public:
	CParticleManager();
	~CParticleManager();

	//初期化
	void Init(LPDIRECT3DDEVICE9 device);

	//パーティクルオブジェクトの取得
	//第一引数:取得したいパーティクルのID
	CParticleObject* object_(int id)
	{
		return (object[id]);
	}

	//パーティクルの生成開始(シュンシュンシュンと飛ばす)
	//第一引数:目的地の座標(自分に飛ばしたい場合は自分の座標を入れる)
	void Start(CScene* target);

	//パーティクルの生成開始(ドバーッと飛ばす)
	//第一引数:目的地の座標(自分に飛ばしたい場合は自分の座標を入れる)
	void StartBurst(CScene* target);

	//全パーティクルの停止
	void StopALL();

	bool IsUsing()
	{
		return (object[0]->isLive());
	}

	//プレイヤーの座標のセット
	void Setpos(D3DXVECTOR2 pos);

	void Scrol(float value)
	{
		for(int i=0;i<PARTICLE_MAX-1;i++)
		{
			object[i]->Scrol(value);
		}
	}

private:
	//パーティクルオブジェクト
	CParticleObject* object[PARTICLE_MAX];
	//生成位置
	D3DXVECTOR2 m_pos;
	//ディレイ
	int coolDownTinme;
};

#endif

