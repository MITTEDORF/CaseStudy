//=============================================================================
//
// ��蕨�̊e��ݒ��� [vehicle_config.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_CONFIG_H
#define _CHARACTER_CONFIG_H
//=============================================================================
// �ݒ���
//=============================================================================

//�R�X�`���[��
typedef enum
{
	// �Ȃ�
	COSTUME_NONE = 0,
	COSTUME_KNIGHT,
	COSTUME_SANTA,
	COSTUME_SWIMWEAR,
	COSTUME_NINJA,
	COSTUME_FAITER,

	COSTUME_MAX

} CostumeID;

//��蕨
typedef enum
{
	// �Ȃ�
	VHEICLE_TRUCK=0,
	VHEICLE_DOLLY,
	VEHICLE_TRAM,
	VHEICLE_LOG,
	VEHICLE_BATHTUB,
	VEHICLE_SLEIGH,

	VEHICLE_MAX

} VehicleID;


#endif

