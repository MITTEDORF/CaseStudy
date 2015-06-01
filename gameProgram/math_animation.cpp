//*****************************************************************************
//
// アニメーション関連の計算 [math_animation.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "math_animation.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//最大値、最小値を考慮した現在値の算出する
static float MapValues(float x,float inMin,float inMax,float outMin,float outMax);

//=============================================================================
// ポリゴンに指定したコマを貼り付ける処理(縦分割されたものには非対応)
//=============================================================================
void SetAnim(int maxTex_X,int nowTex_X,int maxTex_Y,int nowTex_Y,CScene2D* pol)
{
	
	D3DXVECTOR2 uvOffset;
	uvOffset.x=MapValues(1.0f,0,(float)maxTex_X,0,1.0f);
	uvOffset.y=MapValues(1.0f,0,(float)maxTex_Y,0,1.0f);

	D3DXVECTOR2 cord=D3DXVECTOR2(uvOffset.x*(float)(nowTex_X-1),uvOffset.y*(float)(nowTex_Y-1));
	pol->SetCord(0,cord);

	cord=D3DXVECTOR2(uvOffset.x*(float)(nowTex_X),uvOffset.y*(float)(nowTex_Y-1));
	pol->SetCord(1,cord);

	cord=D3DXVECTOR2(uvOffset.x*(float)(nowTex_X-1),uvOffset.y*(float)(nowTex_Y));
	pol->SetCord(2,cord);

	cord=D3DXVECTOR2(uvOffset.x*(float)(nowTex_X),uvOffset.y*(float)(nowTex_Y));
	pol->SetCord(3,cord);

}
//=============================================================================
// 最大値、最小値を考慮した現在値の算出
//=============================================================================
float MapValues(float x,float inMin,float inMax,float outMin,float outMax)
{
	return ((x-inMin)*(outMax-outMin)/(inMax-inMin)+outMin);
}