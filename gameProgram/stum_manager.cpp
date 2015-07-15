//=============================================================================
//
// stum_managerクラス [stum_manager.cpp]
// Author : Ken Matsuura
//
//=============================================================================


//=============================================================================
// インクルード
//=============================================================================
#include "stum_manager.h"
#include "stumbler.h"

#include "mapData.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CStumManager::CStumManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// クリエイト関数
//=============================================================================
CStumManager* CStumManager::Create(LPDIRECT3DDEVICE9 device,CImport::MAPS maps)
{
	CStumManager* manager = new CStumManager;

	if(manager->Init(device,maps) == E_FAIL)
	{
		// 初期化コケたよ
		return NULL;
	}
	return manager;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStumManager::Init(LPDIRECT3DDEVICE9 device,CImport::MAPS maps)
{
	//----------------------------------------
	// データ取得
	//----------------------------------------
	CMapData*	mapData = CImport::GetMap(maps);
	STUM_DATA*	data = mapData->GetStumData();
	int			size = mapData->GetStumSize();

	// データの個数分生成処理
	for(int loop = 0; loop < size; loop++)
	{
		// 障害物リスト先頭が空の時
		if(m_list_top == NULL)
		{
			// 障害物リスト先頭に障害物生成
			m_list_top = CStumbler::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// 障害物リスト末尾を障害物リスト先頭に
			m_list_cur = m_list_top;
		}
		else
		{
			// 障害物生成
			CStumbler* p = CStumbler::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// 障害物リスト末尾のnextに生成した障害物をセット
			m_list_cur->SetStumNext(p);
			// 生成した障害物のprevに障害物リスト末尾をセット
			p->SetStumPrev(m_list_cur);
			// 障害物リスト末尾を生成した障害物に
			m_list_cur = p;
		}
	}
	return S_OK;
}

//=============================================================================
// スクロール
//=============================================================================
void CStumManager::Scroll(float f)
{
	CStumbler* cur = m_list_top;
	CStumbler* next;

	while(cur)
	{
		cur->Scroll(f);

		next = cur->GetStumNext();

		cur = next;
	}
}

//=============================================================================
// 衝突判定
//=============================================================================
bool CStumManager::CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CStumbler* cur = m_list_top;
	CStumbler* next;

	while(cur)
	{
		cur->CheckFall(pos);

		next = cur->GetStumNext();

		cur = next;
	}

	cur = m_list_top;

	while(cur)
	{
		if(cur->CheckCollisionAABB(pos, size, pointType) == true)
		{
			// ぶつかってる障害物にダメージ
			cur->Attack(1);
			return true;
		}

		next = cur->GetStumNext();

		cur = next;
	}
	return false;
}

//=============================================================================
// リスト抹消
//=============================================================================
void CStumManager::UnLinkStum(void)
{
	CStumbler* cur = m_list_top;
	CStumbler* next;

	while(cur)
	{
		next = cur->GetStumNext();
		if(cur->GetStumDelete() == true)
		{
			if(m_list_top == cur && m_list_cur == cur)
			{
				m_list_top = NULL;
				m_list_cur = NULL;
			}
			else
			{
				if(m_list_top != cur)
				{
					cur->GetStumPrev()->SetStumNext(cur->GetStumNext());
				}
				else
				{
					cur->GetStumNext()->SetStumPrev(NULL);
					m_list_top = cur->GetStumNext();
				}

				if(m_list_cur != cur)
				{
					cur->GetStumNext()->SetStumPrev(cur->GetStumPrev());
				}
				else
				{
					cur->GetStumPrev()->SetStumNext(NULL);
					m_list_cur = cur->GetStumPrev();
				}
			}
			cur->Delete();
		}
		cur = next;
	}
}
// End of File