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
								D3DXVECTOR2(327.0f,196.0f),
								D3DXVECTOR2(321.0f,190.0f),
								D3DXVECTOR2(343.0f,193.0f),
								D3DXVECTOR2(327.0f,196.0f),
								D3DXVECTOR2(327.0f,196.0f)};
//オブジェクトの各座標
const D3DXVECTOR2 POL_POS[5]={
								D3DXVECTOR2(517.0f,69.0f),
								D3DXVECTOR2(835.0f,270.0f),
								D3DXVECTOR2(697.0f,431.0f),
								D3DXVECTOR2(251.0f,431.0f),
								D3DXVECTOR2(159.0f,168.0f)};

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
