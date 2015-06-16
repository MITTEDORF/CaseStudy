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

//=============================================================================
// コンストラクタ
//=============================================================================
CStumManager::CStumManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CStumManager::~CStumManager()
{

}

//=============================================================================
// クリエイト関数
//=============================================================================
CStumManager* CStumManager::Create(LPDIRECT3DDEVICE9 device)
{
	CStumManager* manager = new CStumManager;

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
HRESULT CStumManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// 障害物関連（とりあえずべた打ち、エディタからのデータになる予定地
	STUM_DATA data[] = {
		{TYPE_BARRICADE,
		D3DXVECTOR2(13,1)},
		{TYPE_ROCK,
		D3DXVECTOR2(27,1)},
		{TYPE_DUSTBOX,
		D3DXVECTOR2(40,1)},
		{TYPE_LION,
		D3DXVECTOR2(55,1)},
		{TYPE_ROCK,
		D3DXVECTOR2(67,1)},
		{TYPE_BIRD,
		D3DXVECTOR2(74,6)},
		{TYPE_SIGNBOARD,
		D3DXVECTOR2(89,1)},
		{TYPE_DUSTBOX,
		D3DXVECTOR2(99,1)},
		{TYPE_DUSTBOX,
		D3DXVECTOR2(124,1)},
		{TYPE_BIRD,
		D3DXVECTOR2(32,6)},
	};

	int a = (int)(sizeof(data)/sizeof(STUM_DATA));

	// データの個数分生成処理
	for(int loop = 0; loop < (int)(sizeof(data)/sizeof(STUM_DATA)); loop++)
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
// 更新処理
//=============================================================================
void CStumManager::Update(void)
{
	CStumbler* cur = m_list_top;
	CStumbler* next;

	while(cur)
	{
		cur->Update();

		next = cur->GetStumNext();

		cur = next;
	}
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
		if(cur->CheckCollisionAABB(pos, size, pointType) == true)
			return true;

		next = cur->GetStumNext();

		cur = next;
	}
	return false;
}

// End of File