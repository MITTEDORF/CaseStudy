//=============================================================================
//
// stum_manager�N���X [stum_manager.h]
// Author : Ken Matsuura
//
//=============================================================================

// �C���N���[�h�K�[�h
#ifndef __STUM_MANAGER_H__
#define __STUM_MANAGER_H__

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
class CStumbler;

//=============================================================================
// �N���X��`
//=============================================================================
class CStumManager
{
public:
	CStumManager();
	~CStumManager();
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Update(void);
	void	Scroll(float f);
	static	CStumManager* Create(LPDIRECT3DDEVICE9 device);
private:
	CStumbler* m_list_top;		// ��Q�����X�g�擪
	CStumbler* m_list_cur;		// ��Q�����X�g����
};





// �C���N���[�h�K�[�h�I��
#endif // __STUM_MANAGER_H__

// End of File