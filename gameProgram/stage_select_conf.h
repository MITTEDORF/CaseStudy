//=============================================================================
//
// 選択画面の各種設定情報 [equipment_choice_config.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _STAGE_SELECT_CONFIG_H
#define _STAGE_SELECT_CONFIG_H
//=============================================================================
// 設定情報
//=============================================================================

//オブジェクトのポリゴンサイズ
const D3DXVECTOR2 POL_SIZE[5]={
								D3DXVECTOR2(350.0f,312.0f),
								D3DXVECTOR2(350.0f,312.0f),
								D3DXVECTOR2(350.0f,312.0f),
								D3DXVECTOR2(350.0f,312.0f),
								D3DXVECTOR2(350.0f,312.0f)};
//オブジェクトの各座標
const D3DXVECTOR2 POL_POS[5]={
								D3DXVECTOR2(672.0f,145.0f),
								D3DXVECTOR2(992.0f,302.0f),
								D3DXVECTOR2(855.0f,509.0f),
								D3DXVECTOR2(406.0f,509.0f),
								D3DXVECTOR2(312.0f,257.0f)};

//選択時のオブジェクトの揺れ幅
const float SHAKING_WIDTH   = D3DX_PI/16.0f;
//選択時のオブジェクトの揺れる速さ
const float SHAKING_SPD   = 0.16f;

//ステージ
typedef enum
{
	// 上に配置されるよ
	STAGE_DESERT = 0,
	// 右に配置されるよ
	STAGE_WATERSIDE,
	// 右下に配置されるよ
	STAGE_GLACIER,
	// 左下に配置されるよ
	STAGE_SAVANNAH,
	// 左に配置されるよ
	STAGE_FOREST,
	
	//ステージの数
	STAGE_MAX

} StageObject;

#endif
