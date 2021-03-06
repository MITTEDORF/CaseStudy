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
const float JUMP_SPD                    = -40.0f;
//移動スピード
const float MOVE_SPD                    = 3.0f;
//重力
const float GRAVITY_SPD                 = 2.0f;

//無敵時間
const int  INVISIBLE_TIME               = 120;
//無敵時の描画感覚
const int  INVISIBLE_DRAW_TIME          = 5;

const int PLAYER_MAXANIM_WAIT           = 4;
const int PLAYER_MAXANIM_MOVE           = 1;
const int PLAYER_MAXANIM_ATACK          = 5;
const int PLAYER_MAXANIM_DAMAGE         = 10;
const int PLAYER_MAXANIM_LIGHT          = 6;

//アニメーションスピード
const int   PLAYER_ANIMSPD_WAIT         = 10;
const int   PLAYER_ANIMSPD_MOVE         = 10;
const int   PLAYER_ANIMSPD_ATACK        = 10;
const int   PLAYER_ANIMSPD_DAMAGE       = 10;
const int   PLAYER_ANIMSPD_LIGHT        = 7;

//移動時の摩擦力
const float MOVE_FRICTIONAL_FORCE       = 0.8f;

const int   PLAYER_ANIM_WAIT            = 0;
const int   PLAYER_ANIM_MOVE            = 1;
const int   PLAYER_ANIM_ATACK           = 2;
const int   PLAYER_ANIM_DAMAGE          = 3;
const int   PLAYER_ANIM_LIGHT           = 4;

//プレイヤのHPの最大値(3の倍数が好ましい)
const int PLAYER_HP_MAX                 = 4;



//乗り物ごとの高さオフセット
const float PLAYER_HEGHIT_OFFSET_MARUTA = 25.0f;

//プレイヤーの状態
typedef enum
{
	// 待機
	PLAYER_STATE_WAIT = 0,
	//攻撃
	PLAYER_STATE_ATTACK,
	//光アクション
	PLAYER_STATE_LIGHTNING,
	//ダメージ
	PLAYER_STATE_DAMAGE,

	//状態の数
	PLAYER_STATE_MAX

} PlayerState;

#endif

