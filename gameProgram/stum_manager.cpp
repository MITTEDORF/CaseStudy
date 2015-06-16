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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStumManager::CStumManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStumManager::~CStumManager()
{

}

//=============================================================================
// �N���G�C�g�֐�
//=============================================================================
CStumManager* CStumManager::Create(LPDIRECT3DDEVICE9 device)
{
	CStumManager* manager = new CStumManager;

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
HRESULT CStumManager::Init(LPDIRECT3DDEVICE9 device)
{
	//----------------------------------------
	// ��Q���֘A�i�Ƃ肠�����ׂ��ł��A�G�f�B�^����̃f�[�^�ɂȂ�\��n
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

	// �f�[�^�̌�����������
	for(int loop = 0; loop < (int)(sizeof(data)/sizeof(STUM_DATA)); loop++)
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
// �X�V����
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
		if(cur->CheckCollisionAABB(pos, size, pointType) == true)
			return true;

		next = cur->GetStumNext();

		cur = next;
	}
	return false;
}

// End of File