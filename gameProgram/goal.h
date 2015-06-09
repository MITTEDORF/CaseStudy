//*****************************************************************************
//
// goalクラス [goal.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

#ifndef _GOAL_H
#define _GOAL_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CGoal : public CScene2D
{
public:
	CGoal( int priority , OBJTYPE objtype );
	~CGoal(){};
	static	CGoal* Create( LPDIRECT3DDEVICE9 device , CImport::TEXTURES texture , POINT_TYPE pointType , int priority , D3DXVECTOR2 pos );
	static	CGoal* Create(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType , int priority , D3DXVECTOR2 pos );
	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	void		SetPos(D3DXVECTOR2 pos){m_pos = pos; SetVertexPolygon();}
	void		SetPos(float x, float y){m_pos = D3DXVECTOR2(x, y); SetVertexPolygon();}
	D3DXVECTOR2	GetPos(void){return m_pos;}
	void		SetRot(float rot){m_rot = rot; SetVertexPolygon();}
	float		GetRot(void){return m_rot;}
	void		SetSize(D3DXVECTOR2 size){m_size = size; SetVertexPolygon();}
	void		SetSize(float x, float y){m_size = D3DXVECTOR2(x, y); SetVertexPolygon();}
	D3DXVECTOR2	GetSize(void){return m_size;}
	void		SetColor(D3DXCOLOR color){m_color = color; SetVertexPolygon();}
	void		SetColor(float r, float g, float b, float a){m_color = D3DXCOLOR(r, g, b, a); SetVertexPolygon();}
	D3DXCOLOR	GetColor(void){return m_color;}
	BOOL GetFlag( void ){ return m_Flag ;}
	void Scroll( float scroll );
	BOOL CheckCollisionAABB(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType);
	CGoal *GetGoal( void ){ return m_Goal; }
	void SetGoal( CGoal *goalpointer ){ m_Goal = goalpointer; }
private:
	CGoal *m_Goal;
	BOOL m_Flag;
};
#endif