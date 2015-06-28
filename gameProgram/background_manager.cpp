//*****************************************************************************
//
// CBackgroundManager�N���X [background_manager.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "background_manager.h"
#include "background.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackgroundManager::CBackgroundManager()
{
	m_top = nullptr;
	m_cur = nullptr;
}

//=============================================================================
// ����
//=============================================================================
CBackgroundManager* CBackgroundManager::Create(LPDIRECT3DDEVICE9 device)
{
	CBackgroundManager* pointer = new CBackgroundManager;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CBackgroundManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// �f�[�^
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

	// �f�[�^�̌�����������
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
// �X�N���[��
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
