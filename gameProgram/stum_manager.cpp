//=============================================================================
//
// stum_manager�N���X [stum_manager.cpp]
// Author : Ken Matsuura
//
//=============================================================================


//=============================================================================
// �C���N���[�h
//=============================================================================
#include "stum_manager.h"
#include "stumbler.h"

#include "mapData.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStumManager::CStumManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// �N���G�C�g�֐�
//=============================================================================
CStumManager* CStumManager::Create(LPDIRECT3DDEVICE9 device,CImport::MAPS maps)
{
	CStumManager* manager = new CStumManager;

	if(manager->Init(device,maps) == E_FAIL)
	{
		// �������R�P����
		return NULL;
	}
	return manager;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStumManager::Init(LPDIRECT3DDEVICE9 device,CImport::MAPS maps)
{
	//----------------------------------------
	// �f�[�^�擾
	//----------------------------------------
	CMapData*	mapData = CImport::GetMap(maps);
	STUM_DATA*	data = mapData->GetStumData();
	int			size = mapData->GetStumSize();

	// �f�[�^�̌�����������
	for(int loop = 0; loop < size; loop++)
	{
		// ��Q�����X�g�擪����̎�
		if(m_list_top == NULL)
		{
			// ��Q�����X�g�擪�ɏ�Q������
			m_list_top = CStumbler::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ��Q�����X�g��������Q�����X�g�擪��
			m_list_cur = m_list_top;
		}
		else
		{
			// ��Q������
			CStumbler* p = CStumbler::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ��Q�����X�g������next�ɐ���������Q�����Z�b�g
			m_list_cur->SetStumNext(p);
			// ����������Q����prev�ɏ�Q�����X�g�������Z�b�g
			p->SetStumPrev(m_list_cur);
			// ��Q�����X�g�����𐶐�������Q����
			m_list_cur = p;
		}
	}
	return S_OK;
}

//=============================================================================
// �X�N���[��
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
// �Փ˔���
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
			// �Ԃ����Ă��Q���Ƀ_���[�W
			cur->Attack(1);
			return true;
		}

		next = cur->GetStumNext();

		cur = next;
	}
	return false;
}

//=============================================================================
// ���X�g����
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