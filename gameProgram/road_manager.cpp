//=============================================================================
//
// road_managerクラス [road_manager.cpp]
// Author : Ken Matsuura
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "road_manager.h"
#include "road.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRoadManager::CRoadManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// クリエイト関数
//=============================================================================
CRoadManager* CRoadManager::Create(LPDIRECT3DDEVICE9 device)
{
	CRoadManager* manager = new CRoadManager;

	if(manager->Init(device) == E_FAIL)
	{
		// 初期化コケたよ
		return NULL;
	}
	return manager;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRoadManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// 道路関連（とりあえずべた打ち、エディタからのデータになる予定地
	ROAD_DATA data[] = {
		{TYPE_DIRT,
		D3DXVECTOR2(0,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(1,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(2,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(3,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(4,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(5,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(6,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(7,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(8,3)},
		{TYPE_DIRT,
		D3DXVECTOR2(9,3)},
		{TYPE_DIRT,
		D3DXVECTOR2(10,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(11,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(12,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(13,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(14,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(15,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(16,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(17,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(18,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(19,0)},
	};

	int a = (int)(sizeof(data)/sizeof(TYPE_DIRT));

	//// データの個数分生成処理
	//for(int loop = 0; loop < (int)(sizeof(data)/sizeof(ROAD_DATA)); loop++)
	//{
	//	// 道路リスト先頭が空の時
	//	if(m_list_top == NULL)
	//	{
	//		// 道路リスト先頭に道路生成
	//		m_list_top = CRoad::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
	//		// 道路リスト末尾を道路リスト先頭に
	//		m_list_cur = m_list_top;
	//	}
	//	else
	//	{
	//		// 道路生成
	//		CRoad* p = CRoad::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
	//		// 道路リスト末尾のnextに生成した道路をセット
	//		m_list_cur->SetRoadNext(p);
	//		// 生成した道路のprevに道路リスト末尾をセット
	//		p->SetRoadPrev(m_list_cur);
	//		// 道路リスト末尾を生成した道路に
	//		m_list_cur = p;
	//	}
	//}

	// データ出来るまでの繋ぎ、本物は上のコメント部
	for(int loop = 0; loop < 144; loop++)
	{
		ROAD_DATA a = {TYPE_DIRT, D3DXVECTOR2(loop,0)};
		if((loop > 4 && loop < 8) || (loop > 30 && loop < 35))
		{
			a.Index.y = 3;
		}
		// 道路リスト先頭が空の時
		if(m_list_top == NULL)
		{
			// 道路リスト先頭に道路生成
			m_list_top = CRoad::Create(device, a, CScene2D::POINT_LEFTTOP);
			// 道路リスト末尾を道路リスト先頭に
			m_list_cur = m_list_top;
		}
		else
		{
			// 道路生成
			CRoad* p = CRoad::Create(device, a, CScene2D::POINT_LEFTTOP);
			// 道路リスト末尾のnextに生成した道路をセット
			m_list_cur->SetRoadNext(p);
			// 生成した道路のprevに道路リスト末尾をセット
			p->SetRoadPrev(m_list_cur);
			// 道路リスト末尾を生成した道路に
			m_list_cur = p;
		}
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CRoadManager::Update(void)
{
	CRoad* cur = m_list_top;
	CRoad* next;

	while(cur)
	{
		cur->Update();

		next = cur->GetRoadNext();

		cur = next;
	}
}

//=============================================================================
// スクロール
//=============================================================================
void CRoadManager::Scroll(float f)
{
	CRoad* cur = m_list_top;
	CRoad* next;

	while(cur)
	{
		cur->Scroll(f);

		next = cur->GetRoadNext();

		cur = next;
	}
}

//=============================================================================
// 衝突判定
//=============================================================================
D3DXVECTOR2	CRoadManager::CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CRoad* cur = m_list_top;
	CRoad* next;

	while(cur)
	{
		// ぶつかっていた場合、めり込んでる数値分を返す
		if(cur->CheckCollisionAABB(pos, size, pointType) == true)
		{
			return cur->ReturnPush(pos, size, pointType);
		}

		next = cur->GetRoadNext();

		cur = next;
	}

	// ぶつかってない場合
	return D3DXVECTOR2(0.0f, 0.0f);
}


// End of File