//=============================================================================
//
// プレイヤーの各種設定情報 [player_config.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _PLAYER_CONFIG_H
#define _PLAYER_CONFIG_H
//=============================================================================
// 設定情報
//=============================================================================

//ジャンプ力
const float JUMP_SPD              = -40.0f;
//移動スピード
const float MOVE_SPD              = 3.0f;
//重力
const float GRAVITY_SPD           = 2.0f;

//アニメーションスピード
const int   PLAYER_ANIMSPD_WAIT       = 10;
const int   PLAYER_ANIMSPD_MOVE       = 10;
const int   PLAYER_ANIMSPD_ATACK      = 10;
const int   PLAYER_ANIMSPD_DAMAGE     = 10;


//移動時の摩擦力
const float MOVE_FRICTIONAL_FORCE = 0.8f;

const int   PLAYER_ANIM_WAIT      = 0;
const int   PLAYER_ANIM_MOVE      = 1;
const int   PLAYER_ANIM_ATACK     = 2;
const int   PLAYER_ANIM_DAMAGE    = 3;


#endif

