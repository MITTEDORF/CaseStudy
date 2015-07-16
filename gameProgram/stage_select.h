//*****************************************************************************
//
// ステージ選択画面制御クラス [stage_selrect.h]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************
#ifndef _STAGE_SELECT_H
#define _STAGE_SELECT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"
#include "phase.h"
#include "character_config.h"
#include "stage_select_conf.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CScene2D;

class CStageSelect : CPhase
{
public:

	CStageSelect(void){};
	~CStageSelect(){};

	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	//背景に使う2Dポリゴン
	CScene2D* select_bg;
	CScene2D* select_object[STAGE_MAX];
	CScene2D* mesPol;
	CScene2D* backTitle;

	//現在選んでいるオブジェクト
	int nowSelectObject;
	bool backFrag;

	// 傾き
	float move;

	//デバッグ用

private:
	void InitObject(LPDIRECT3DDEVICE9 device);

	void SelectObjectUpdate();

	void ObjectUpdate();

	void NullSetVariable(void)
	{
		nowSelectObject=0;
		move = -0.025f;
		select_bg=NULL;
		backFrag=false;

		m_time=0;

		for(int i=0;i<STAGE_MAX;i++)
		{
			select_object[i]=NULL;
		}
	}

	float m_time;

};

#endif