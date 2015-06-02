//=============================================================================
//
// �v���C���[�̊e��ݒ��� [player_config.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _PLAYER_CONFIG_H
#define _PLAYER_CONFIG_H
//=============================================================================
// �ݒ���
//=============================================================================

//�W�����v��
const float JUMP_SPD              = -40.0f;
//�ړ��X�s�[�h
const float MOVE_SPD              = 3.0f;
//�d��
const float GRAVITY_SPD           = 2.0f;

//�A�j���[�V�����X�s�[�h
const int   PLAYER_ANIMSPD_WAIT       = 10;
const int   PLAYER_ANIMSPD_MOVE       = 10;
const int   PLAYER_ANIMSPD_ATACK      = 10;
const int   PLAYER_ANIMSPD_DAMAGE     = 10;


//�ړ����̖��C��
const float MOVE_FRICTIONAL_FORCE = 0.8f;

const int   PLAYER_ANIM_WAIT      = 0;
const int   PLAYER_ANIM_MOVE      = 1;
const int   PLAYER_ANIM_ATACK     = 2;
const int   PLAYER_ANIM_DAMAGE    = 3;


#endif

