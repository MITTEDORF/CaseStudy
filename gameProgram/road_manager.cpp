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
	// ���H�֘A�i�Ƃ肠�����ׂ��ł��A�G�f�B�^����̃f�[�^�ɂȂ�\��n
	ROAD_DATA data[] = {
		{TYPE_DIRT,
		D3DXVECTOR2(0,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(1,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(2,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(3,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(4,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(5,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(6,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(7,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(8,3)},
		{TYPE_DIRT,
		D3DXVECTOR2(9,3)},
		{TYPE_DIRT,
		D3DXVECTOR2(10,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(11,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(12,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(13,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(14,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(15,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(16,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(17,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(18,0)},
		{TYPE_DIRT,
		D3DXVECTOR2(19,0)},
	};

	int a = (int)(sizeof(data)/sizeof(TYPE_DIRT));

	//// �f�[�^�̌�����������
	//for(int loop = 0; loop < (int)(sizeof(data)/sizeof(ROAD_DATA)); loop++)
	//{
	//	// ���H���X�g�擪����̎�
	//	if(m_list_top == NULL)
	//	{
	//		// ���H���X�g�擪�ɓ��H����
	//		m_list_top = CRoad::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
	//		// ���H���X�g�����𓹘H���X�g�擪��
	//		m_list_cur = m_list_top;
	//	}
	//	else
	//	{
	//		// ���H����
	//		CRoad* p = CRoad::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
	//		// ���H���X�g������next�ɐ����������H���Z�b�g
	//		m_list_cur->SetRoadNext(p);
	//		// �����������H��prev�ɓ��H���X�g�������Z�b�g
	//		p->SetRoadPrev(m_list_cur);
	//		// ���H���X�g�����𐶐��������H��
	//		m_list_cur = p;
	//	}
	//}

	// �f�[�^�o����܂ł̌q���A�{���͏�̃R�����g��
	for(int loop = 0; loop < 144; loop++)
	{
		ROAD_DATA a = {TYPE_DIRT, D3DXVECTOR2(loop,0)};
		if((loop > 4 && loop < 8) || (loop > 30 && loop < 35))
		{
			a.Index.y = 3;
		}
		// ���H���X�g�擪����̎�
		if(m_list_top == NULL)
		{
			// ���H���X�g�擪�ɓ��H����
			m_list_top = CRoad::Create(device, a, CScene2D::POINT_LEFTTOP);
			// ���H���X�g�����𓹘H���X�g�擪��
			m_list_cur = m_list_top;
		}
		else
		{
			// ���H����
			CRoad* p = CRoad::Create(device, a, CScene2D::POINT_LEFTTOP);
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

	while(cur)
	{
		// �Ԃ����Ă����ꍇ�A�߂荞��ł鐔�l����Ԃ�
		if(cur->CheckCollisionAABB(pos, size, pointType) == true)
		{
			return cur->ReturnPush(pos, size, pointType);
		}

		next = cur->GetRoadNext();

		cur = next;
	}

	// �Ԃ����ĂȂ��ꍇ
	return D3DXVECTOR2(0.0f, 0.0f);
}


// End of File