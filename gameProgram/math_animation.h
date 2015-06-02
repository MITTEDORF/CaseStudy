//=============================================================================
//
// アニメーション関連の計算 [math_animation.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _MATH_ANIM_H
#define _MATH_ANIM_H
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"

//=============================================================================
// マクロ
//=============================================================================

//=============================================================================
// 構造体宣言
//=============================================================================

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//ポリゴンに指定したコマを貼り付ける処理(縦分割されたものには非対応)
//第一引数:アニメーションの最大コマ数(x)
//第二引数:アニメーションの現在のコマ(x)
//第三引数:アニメーションの最大コマ数(y)
//第四引数:アニメーションの現在のコマ(y)
//第五引数:貼り付けるポリゴンのポインタ
void SetAnim(int maxTex_X,int nowTex_X,int maxTex_Y,int nowTex_Y,CScene2D* pol);

#endif

