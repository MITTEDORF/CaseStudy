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

#include "mapData.h"

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
	// データ取得
	//----------------------------------------
	CMapData*	mapData = CImport::GetMap(CImport::STAGE_1_1);
	ROAD_DATA*	data = mapData->GetRoadData();
	int			size = mapData->GetRoadSize();

	// データの個数分生成処理
	for(int loop = 0; loop < size; loop++)
	{
		// 道路リスト先頭が空の時
		if(m_list_top == NULL)
		{
			// 道路リスト先頭に道路生成
			m_list_top = CRoad::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// 道路リスト末尾を道路リスト先頭に
			m_list_cur = m_list_top;
		}
		else
		{
			// 道路生成
			CRoad* p = CRoad::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
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

	D3DXVECTOR2 rtn = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 max = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 min = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 value;

	while(cur)
	{
		// ぶつかっていた場合、めり込んでる数値分を返す
		if(cur->CheckCollisionAABB(pos, size, pointType) == true)
		{
			value=cur->ReturnPush(pos, size, pointType);


				if(max.y<=value.y)
				{
					max.y=value.y;
				}
				if(min.y>=value.y)
				{
					min.y=value.y;
				}

			if(value.y<=0)
			{
				if(max.x<=value.x)
				{
					max.x=value.x;
				}
				if(min.x>=value.x)
				{
					min.x=value.x;
				}
			}

		}

		next = cur->GetRoadNext();

		cur = next;
	}

	if((max.x*max.x)>=(min.x*min.x))
	{
		rtn.x=max.x;
	}

	else
	{
		rtn.x=min.x;
	}

	if((max.y*max.y)>=(min.y*min.y))
	{
		rtn.y=max.y;
	}

	else
	{
		rtn.y=min.y;
	}

	return rtn;
}

// End of File