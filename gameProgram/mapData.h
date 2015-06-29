//*****************************************************************************
//
// CMapDataクラス [mapData.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_MAP_H
#define _MY_MAP_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

#include "background.h"
#include "road.h"
#include "stumbler.h"
#include "target.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CMapData
{
public:
	CMapData();
	~CMapData(){};

	static	CMapData* Create(const char* file);
	HRESULT	Init(const char* file);
	void	Uninit(void);

	BG_DATA*	 GetBgData(void){return m_bgData;}
	ROAD_DATA*	 GetRoadData(void){return m_roadData;}
	STUM_DATA*	 GetStumData(void){return m_stumData;}
	TARGET_DATA* GetTargetData(void){return m_targetData;}

	int GetBgSize(void){return m_bgSize;}
	int GetRoadSize(void){return m_roadSize;}
	int GetStumSize(void){return m_stumSize;}
	int GetTargetSize(void){return m_targetSize;}

private:
	int m_bgSize;
	int m_roadSize;
	int m_stumSize;
	int m_targetSize;

	BG_DATA*	 m_bgData;
	ROAD_DATA*	 m_roadData;
	STUM_DATA*	 m_stumData;
	TARGET_DATA* m_targetData;
};

//=============================================================================
#endif