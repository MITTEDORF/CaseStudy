//=============================================================================
//
// road_manager�N���X [road_manager.cpp]
// Author : Ken Matsuura
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "road_manager.h"
#include "road.h"

#include "mapData.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRoadManager::CRoadManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// �N���G�C�g�֐�
//=============================================================================
CRoadManager* CRoadManager::Create(LPDIRECT3DDEVICE9 device)
{
	CRoadManager* manager = new CRoadManager;

	if(manager->Init(device) == E_FAIL)
	{
		// �������R�P����
		return NULL;
	}
	return manager;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRoadManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// �f�[�^�擾
	//----------------------------------------
	CMapData*	mapData = CImport::GetMap(CImport::STAGE_1_1);
	ROAD_DATA*	data = mapData->GetRoadData();
	int			size = mapData->GetRoadSize();

	// �f�[�^�̌�����������
	for(int loop = 0; loop < size; loop++)
	{
		// ���H���X�g�擪����̎�
		if(m_list_top == NULL)
		{
			// ���H���X�g�擪�ɓ��H����
			m_list_top = CRoad::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ���H���X�g�����𓹘H���X�g�擪��
			m_list_cur = m_list_top;
		}
		else
		{
			// ���H����
			CRoad* p = CRoad::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ���H���X�g������next�ɐ����������H���Z�b�g
			m_list_cur->SetRoadNext(p);
			// �����������H��prev�ɓ��H���X�g�������Z�b�g
			p->SetRoadPrev(m_list_cur);
			// ���H���X�g�����𐶐��������H��
			m_list_cur = p;
		}
	}

	return S_OK;
}

//=============================================================================
// �X�V����
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
// �X�N���[��
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
// �Փ˔���
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
		// �Ԃ����Ă����ꍇ�A�߂荞��ł鐔�l����Ԃ�
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