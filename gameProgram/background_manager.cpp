//*****************************************************************************
//
// CBackgroundManagerクラス [background_manager.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルード
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "background_manager.h"
#include "background.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBackgroundManager::CBackgroundManager()
{
	m_top = nullptr;
	m_cur = nullptr;
}

//=============================================================================
// 生成
//=============================================================================
CBackgroundManager* CBackgroundManager::Create(LPDIRECT3DDEVICE9 device)
{
	CBackgroundManager* pointer = new CBackgroundManager;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CBackgroundManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// データ
	BG_DATA data[] =
	{
		{TYPE_FOREST_01, 0},
		{TYPE_FOREST_01, 1},
		{TYPE_FOREST_01, 2},
		{TYPE_FOREST_01, 3},
		{TYPE_FOREST_01, 4},
		{TYPE_FOREST_01, 5},
		{TYPE_FOREST_01, 6},
		{TYPE_FOREST_01, 7},
		{TYPE_FOREST_01, 8}
	};

	int size = (int)(sizeof(data)/sizeof(BG_DATA));

	// データの個数分生成処理
	for(int cnt = 0; cnt < size; cnt++)
	{
		if(m_top == NULL)
		{
			m_top = CBackground::Create(device, data[cnt]);
			m_cur = m_top;
		}
		else
		{
			CBackground* pointer = CBackground::Create(device, data[cnt]);
			m_cur->SetBgNext(pointer);
			pointer->SetBgPrev(m_cur);
			m_cur = pointer;
		}
	}
	return S_OK;
}

//=============================================================================
// スクロール
//=============================================================================
void CBackgroundManager::Scroll(float scroll)
{
	CBackground* cur = m_top;
	CBackground* next;

	while(cur)
	{
		cur->Scroll(scroll);

		next = cur->GetBgNext();

		cur = next;
	}
}
