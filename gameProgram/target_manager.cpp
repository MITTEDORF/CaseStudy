//=============================================================================
//
// target_managerクラス [target_manager.cpp]
// Author : Ken Matsuura
//
//=============================================================================


//=============================================================================
// インクルード
//=============================================================================
#include "target_manager.h"
#include "target.h"

#include "mapData.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTargetManager::CTargetManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// クリエイト関数
//=============================================================================
CTargetManager* CTargetManager::Create(LPDIRECT3DDEVICE9 device)
{
	CTargetManager* manager = new CTargetManager;

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
HRESULT CTargetManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// データ取得
	//----------------------------------------
	CMapData*	 mapData = CImport::GetMap(CImport::STAGE_1_1);
	TARGET_DATA* data = mapData->GetTargetData();
	int			 size = mapData->GetTargetSize();

	// データの個数分生成処理
	for(int loop = 0; loop < size; loop++)
	{
		// 障害物リスト先頭が空の時
		if(m_list_top == NULL)
		{
			// 障害物リスト先頭に障害物生成
			m_list_top = CTarget::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// 障害物リスト末尾を障害物リスト先頭に
			m_list_cur = m_list_top;
		}
		else
		{
			// 障害物生成
			CTarget* p = CTarget::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// 障害物リスト末尾のnextに生成した障害物をセット
			m_list_cur->SetTargetNext(p);
			// 生成した障害物のprevに障害物リスト末尾をセット
			p->SetTargetPrev(m_list_cur);
			// 障害物リスト末尾を生成した障害物に
			m_list_cur = p;
		}
	}
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CTargetManager::Update(void)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		cur->Update();

		next = cur->GetTargetNext();

		cur = next;
	}
}

//=============================================================================
// スクロール
//=============================================================================
void CTargetManager::Scroll(float f)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		cur->Scroll(f);

		next = cur->GetTargetNext();

		cur = next;
	}
}

//=============================================================================
// パーティクル用衝突判定
//=============================================================================
CTarget* CTargetManager::CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		if(cur->CheckCollisionAABB(pos, size, pointType))
		{
			if(cur->GetTargetFrag() == true)
				return cur;
		}

		next = cur->GetTargetNext();

		cur = next;
	}
	return NULL;
}

//=============================================================================
// ゴール用衝突判定
//=============================================================================
bool CTargetManager::CheckHitGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		if(cur->CheckCollisionAABB(pos, size, pointType))
		{
			if(cur->GetTargetFrag() != true)
				return true;
		}

		next = cur->GetTargetNext();

		cur = next;
	}
	return false;
}

//=============================================================================
// リスト抹消
//=============================================================================
void CTargetManager::UnLinkTarget(CTarget* cur)
{
	// リスト先頭だった場合、次障害物をリスト先頭に
	if(cur == m_list_top)
		m_list_top = cur->GetTargetNext();
	// リスト末尾だった場合、前障害物をリスト末尾に
	if(cur == m_list_cur)
		m_list_cur = cur->GetTargetPrev();
}
// End of File