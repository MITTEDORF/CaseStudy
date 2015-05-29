//*****************************************************************************
//
// プレイヤー制御クラス [character_player.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_player.h"
#include "inputKeyboard.h"
#include "math_animation.h"
#include "player_config.h"

#include "game.h"
#include "debugproc.h"
#include "fade.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//変数のNULL埋め
	NullSetVariable();

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(LPDIRECT3DDEVICE9 device)
{
	
	Assy=CScene2D::Create(device,CImport::TEX_ASSY_ONE,POINT_CENTER);
	Assy->Init(device,CImport::TEX_ASSY_ONE,POINT_CENTER);

	//親の初期化
	CScene2D::Init(device,CImport::TEX_PLAYER_WAIT,POINT_CENTER);

	SetAnim(1,1,this);


	//成功を返す
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CPlayer::Uninit(void)
{
	//親の終了
	CScene2D::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CPlayer::Update(void)
{
	//フェード中ではないとき
	if(CPhase::GetFade()->GetState() == CFade::FADESTATE_NONE)
	{

		m_posOld = m_pos;
		
		//移動処理
		Move();

		//攻撃処理
		Attack();

	}

	//重力加算
	AddGravity();

	//スピードを考慮した座標の算出
	m_pos+=m_move_spd;

	//様々な当たり判定
	Collider();

	//アッシーのポジションをセット
	Assy->SetPos(m_pos);
	
	//座標の再計算
	SetVertexPolygon();
	//親の更新
	CScene2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CPlayer::Draw(void)
{
	//親の描画
	CScene2D::Draw();
}
//=============================================================================
// 生成
//=============================================================================
CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 device)
{
	CPlayer* scene = new CPlayer;
	scene->Init(device);

	return scene;
}
//=============================================================================
// 移動処理
//=============================================================================
void CPlayer::Move()
{
	//右移動
	if(m_keyboard->GetPress(DIK_A))
	{
		m_move_spd.x-=MOVE_SPD;
	}

	//左移動
	if(m_keyboard->GetPress(DIK_D))
	{
		m_move_spd.x+=MOVE_SPD;
	}

	//慣性
	m_move_spd.x*=MOVE_FRICTIONAL_FORCE;

	//ジャンプ処理
	moveJump();
}
//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::moveJump()
{
	//スペースキーを押したとき
	if(m_keyboard->GetTrigger(DIK_SPACE)&&canJump)
	{
		if(!isJump)
		{
			canJump=false;
			isJump=true;
			//スピードの設定
			m_move_spd.y=JUMP_SPD;
		}
	}
}
//=============================================================================
// 重力加算処理
//=============================================================================
void CPlayer::AddGravity()
{

	m_move_spd.y+=GRAVITY_SPD;

}
//=============================================================================
// 様々な当たり判定
//=============================================================================
void CPlayer::Collider()
{
	//地面とプレイヤの当たり判定
	if(m_pos.y>=625.0f)
	{
		canJump=true;
		isJump=false;
		m_pos.y=625.0f;
	}

	if(m_pos.x<=0.0f)
	{
		m_pos.x=0.0f;
	}

	if(m_pos.x>=((SCREEN_WIDTH>>1)+(SCREEN_WIDTH>>2)))
	{
		m_pos.x=((SCREEN_WIDTH>>1)+(SCREEN_WIDTH>>2));
	}

}
//=============================================================================
// 攻撃処理
//=============================================================================
void CPlayer::Attack()
{
	

	if(m_keyboard->GetTrigger(DIK_K)&&!isAttack)
	{
		cntAnim=0;
		nowAnim=1;
		isAttack=true;
		this->SetTex(CImport::TEX_PLAY_ATTACK);
		SetAnim(5,1,this);
	}

	if(isAttack)
	{
		switch (cntAnim)
		{
			case ATTACK_ANIM_SPD:
				SetAnim(5,2,this);
				break;

			case ATTACK_ANIM_SPD*2:
				SetAnim(5,3,this);
				break;

			case ATTACK_ANIM_SPD*3:
				SetAnim(5,4,this);
				break;

			case ATTACK_ANIM_SPD*4:
				SetAnim(5,5,this);
				break;

			case ATTACK_ANIM_SPD*5:
				cntAnim=0;
				nowAnim=1;
				isAttack=false;
				this->SetTex(CImport::TEX_PLAYER_WAIT);
				SetAnim(1,1,this);
				return;
				break;
		}

		cntAnim++;
	}
}