//*****************************************************************************
//
// CDustManagerManagerクラス [dustManager.cpp]
// Author : YUJI MOMOI
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "dustManager.h"
#include "dust.h"
#include "import.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 敵の初期座標
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const D3DXVECTOR3 enemyPos[ENEMY_MAX] = {
	D3DXVECTOR3(-100.0f,0.0f,-200.0f),
	D3DXVECTOR3(-50.0f,0.0f,-200.0f),
	D3DXVECTOR3(0.0f,0.0f,-200.0f),
	D3DXVECTOR3(50.0f,0.0f,-200.0f),
	D3DXVECTOR3(100.0f,0.0f,-200.0f),
};

//=============================================================================
// コンストラクタ
//=============================================================================
CDustManager::CDustManager()
{
}

//=============================================================================
// 生成
//=============================================================================
CDustManager* CDustManager::Create(LPDIRECT3DDEVICE9 device)
{
	CDustManager* pointer = new CDustManager;

	pointer->Init(device);

	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CDustManager::Init(LPDIRECT3DDEVICE9 device)
{
	m_enemyMax = ENEMY_MAX;
	m_enemyNum = ENEMY_MAX;

	for(int cnt = 0; cnt < ENEMY_MAX; ++cnt)
	{
		m_DustArray[cnt] = CDust::Create(device,CImport::X_ENEMY);
		m_DustArray[cnt] -> SetPos(enemyPos[cnt]);
		m_DustArray[cnt]->SetSize(26.0f,30.0f,25.0f);
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CDustManager::Uninit(void)
{
}

//=============================================================================
// 更新
//=============================================================================
void CDustManager::Update(void)
{
}

CDust* CDustManager::GetDust(int index)
{
	if(index < 0 || index + 1 > ENEMY_MAX)
	{
		return NULL;
	}

	if(m_DustArray[index] ->GetHP() <= 0)
	{
		return NULL;
	}

	return m_DustArray[index];
}

//=============================================================================
// ダメージ処理
//=============================================================================
void CDustManager::Damage(int index)
{
	if(index >= 0 && index < ENEMY_MAX)
	{

	}
}
