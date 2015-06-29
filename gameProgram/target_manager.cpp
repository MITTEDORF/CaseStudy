//=============================================================================
//
// target_manager�N���X [target_manager.cpp]
// Author : Ken Matsuura
//
//=============================================================================


//=============================================================================
// �C���N���[�h
//=============================================================================
#include "target_manager.h"
#include "target.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTargetManager::CTargetManager()
{
	m_list_top = NULL;
	m_list_cur = NULL;
}

//=============================================================================
// �N���G�C�g�֐�
//=============================================================================
CTargetManager* CTargetManager::Create(LPDIRECT3DDEVICE9 device)
{
	CTargetManager* manager = new CTargetManager;

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
HRESULT CTargetManager::Init(LPDIRECT3DDEVICE9 device)
{
	TARGET_DATA data[] =
	{
		{TYPE_GOAL_OFF,
		D3DXVECTOR2(130, 1)},
		{TYPE_TARGET_OFF,
		D3DXVECTOR2(145, 1)},
	};
	int a = (int)(sizeof(data)/sizeof(TARGET_DATA));

	// �f�[�^�̌�����������
	for(int loop = 0; loop < (int)(sizeof(data)/sizeof(TARGET_DATA)); loop++)
	{
		// ��Q�����X�g�擪����̎�
		if(m_list_top == NULL)
		{
			// ��Q�����X�g�擪�ɏ�Q������
			m_list_top = CTarget::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ��Q�����X�g��������Q�����X�g�擪��
			m_list_cur = m_list_top;
		}
		else
		{
			// ��Q������
			CTarget* p = CTarget::Create(device, data[loop], CScene2D::POINT_LEFTTOP);
			// ��Q�����X�g������next�ɐ���������Q�����Z�b�g
			m_list_cur->SetTargetNext(p);
			// ����������Q����prev�ɏ�Q�����X�g�������Z�b�g
			p->SetTargetPrev(m_list_cur);
			// ��Q�����X�g�����𐶐�������Q����
			m_list_cur = p;
		}
	}
	return S_OK;
}

//=============================================================================
// �X�V����
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
// �X�N���[��
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
// �Փ˔���
//=============================================================================
CTarget* CTargetManager::CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		if(cur->CheckCollisionAABB(pos, size, pointType) == true)
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
// �Փ˔���(goal)
//=============================================================================
bool CTargetManager::CheckHitGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType)
{
	CTarget* cur = m_list_top;
	CTarget* next;

	while(cur)
	{
		if(cur->CheckCollisionAABB(pos, size, pointType) == false)
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
// ���X�g����
//=============================================================================
void CTargetManager::UnLinkTarget(CTarget* cur)
{
	// ���X�g�擪�������ꍇ�A����Q�������X�g�擪��
	if(cur == m_list_top)
		m_list_top = cur->GetTargetNext();
	// ���X�g�����������ꍇ�A�O��Q�������X�g������
	if(cur == m_list_cur)
		m_list_cur = cur->GetTargetPrev();
}
// End of File