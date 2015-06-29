//=============================================================================
//
// target_managerクラス [target_manager.h]
// Author : Ken Matsuura
//
//=============================================================================

// インクルードガード
#ifndef __TARGET_MANAGER_H__
#define __TARGET_MANAGER_H__

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "scene2D.h"
class CTarget;

//=============================================================================
// クラス定義
//=============================================================================
class CTargetManager
{
public:
	CTargetManager();
	~CTargetManager(){};
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Update(void);
	void	Scroll(float f);
	CTarget*	CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType);
	bool	CheckHitGoal(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType);
	static	CTargetManager* Create(LPDIRECT3DDEVICE9 device);
	// リスト抹消
	void	UnLinkTarget(CTarget* cur);
private:
	CTarget* m_list_top;		// 障害物リスト先頭
	CTarget* m_list_cur;		// 障害物リスト末尾
};

// インクルードガード終了
#endif // __STUM_MANAGER_H__

// End of File