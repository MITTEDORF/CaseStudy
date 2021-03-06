//=============================================================================
//
// road_managerクラス [road_manager.h]
// Author : Ken Matsuura
//
//=============================================================================

// インクルードガード
#ifndef __ROAD_MANAGER_H__
#define __ROAD_MANAGER_H__

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "scene2D.h"
#include "road.h"

//=============================================================================
// クラス定義
//=============================================================================
class CRoadManager
{
public:
	CRoadManager();
	~CRoadManager(){};
	HRESULT	Init(LPDIRECT3DDEVICE9 device,CImport::MAPS maps);
	void	Update(void);
	void	Scroll(float f);
	D3DXVECTOR2	CheckHit(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType);
	static	CRoadManager* Create(LPDIRECT3DDEVICE9 device,CImport::MAPS maps);
	// 道路タイプゲット
	ROAD_TYPE	GetHitRoadType(D3DXVECTOR2 pos, D3DXVECTOR2 size, CScene2D::POINT_TYPE pointType);
private:
	CRoad* m_list_top;		// 障害物リスト先頭
	CRoad* m_list_cur;		// 障害物リスト末尾
};

// インクルードガード終了
#endif // __ROAD_MANAGER_H__
// End of File