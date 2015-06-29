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

#include "mapData.h"

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
	// データ取得
	//----------------------------------------
	CMapData*	mapData = CImport::GetMap(CImport::STAGE_1_1);
	BG_DATA*	data = mapData->GetBgData();
	int			size = mapData->GetBgSize();

	//----------------------------------------
	// データの個数分生成処理
	//----------------------------------------
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
