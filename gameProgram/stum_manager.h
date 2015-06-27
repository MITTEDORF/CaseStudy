//=============================================================================
//
// stum_managerクラス [stum_manager.h]
// Author : Ken Matsuura
//
//=============================================================================

// インクルードガード
#ifndef __STUM_MANAGER_H__
#define __STUM_MANAGER_H__

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "scene2D.h"
class CStumbler;

//=============================================================================
// クラス定義
//=============================================================================
class CStumManager
{
public:
	CStumManager();
	~CStumManager(){};
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Update(void);
	void	Scroll(float f);
	bool	CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType);
	static	CStumManager* Create(LPDIRECT3DDEVICE9 device);
	// リスト抹消
	void	UnLinkStum(CStumbler* cur);
private:
	CStumbler* m_list_top;		// 障害物リスト先頭
	CStumbler* m_list_cur;		// 障害物リスト末尾
};





// インクルードガード終了
#endif // __STUM_MANAGER_H__

// End of File