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
								D3DXVECTOR2(672.0f,105.0f),
								D3DXVECTOR2(992.0f,262.0f),
								D3DXVECTOR2(855.0f,469.0f),
								D3DXVECTOR2(406.0f,469.0f),
								D3DXVECTOR2(312.0f,217.0f)};

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
