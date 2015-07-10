//=============================================================================
//
// 乗り物の各種設定情報 [vehicle_config.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_CONFIG_H
#define _CHARACTER_CONFIG_H
//=============================================================================
// 設定情報
//=============================================================================

//コスチューム
typedef enum
{
	// なし
	COSTUME_NONE = 0,
	COSTUME_KNIGHT,
	COSTUME_SANTA,
	COSTUME_SWIMWEAR,
	COSTUME_NINJA,
	COSTUME_FAITER,

	COSTUME_MAX

} CostumeID;

//乗り物
typedef enum
{
	// なし
	VHEICLE_TRUCK=0,
	VHEICLE_DOLLY,
	VEHICLE_TRAM,
	VHEICLE_LOG,
	VEHICLE_BATHTUB,
	VEHICLE_SLEIGH,

	VEHICLE_MAX

} VehicleID;


#endif

