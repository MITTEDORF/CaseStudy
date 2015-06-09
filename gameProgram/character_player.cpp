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
#include "character_vehicle.h"

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
	
	Assy=CVehicle::Create(device,CImport::ASSY_TRAM);
	Offset.x=-20.0f;
	Offset.y=0;

	//親の初期化
	CScene2D::Init(device,CImport::PLAYER_WAIT,POINT_CENTER);

	SetAnimMode(PLAYER_ANIM_WAIT,true);

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
	
	//アニメーションのアップデート
	UpdateAnim();

	//フェード中ではないとき
	if(CPhase::GetFade()->GetState() == CFade::FADESTATE_NONE)
	{
		m_posOld = m_pos;
		
		//移動処理
		Move();

		//攻撃処理
		Attack();

		//光アクション処理
		LightAction();
	}


	//乗り物破壊
	if(m_keyboard->GetTrigger(DIK_T))
	{
		AddHP(1);
	}

	//乗り物修復
	if(m_keyboard->GetTrigger(DIK_U))
	{
		AddHP(-1);
	}

	//重力加算
	AddGravity();

	//スピードを考慮した座標の算出
	m_pos+=m_move_spd;

	//様々な当たり判定
	Collider();

	//アッシーのポジションをセット
	Assy->SetPos(m_pos.x+(int)Offset.x,m_pos.y+(int)Offset.y);
	
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
	if(!isLighting)
	{
		//右移動
		if(m_keyboard->GetPress(DIK_A))
		{
			m_move_spd.x-=MOVE_SPD;
			Assy->SetAnimMode(1,true);
		}

		//左移動
		if(m_keyboard->GetPress(DIK_D))
		{
			m_move_spd.x+=MOVE_SPD;
			Assy->SetAnimMode(1,true);
		}
	}

	//慣性
	m_move_spd.x*=MOVE_FRICTIONAL_FORCE;

	if(m_keyboard->GetSetDelete(DIK_A)||m_keyboard->GetSetDelete(DIK_D))
	{
		Assy->SetAnimMode(0,true);
	}

	//ジャンプ処理
	moveJump();
}

//=============================================================================
// HP更新処理
//=============================================================================
void CPlayer::AddHP(int value)
{
	HP+=value;
	//HPが0いかにならないように処理
	if(HP<=0)
	{
		HP=0;
		isDeth=true;
	}

	//HPが0いかにならないように処理
	if(HP>=PLAYER_HP_MAX)
	{
		HP=PLAYER_HP_MAX;
	}

	if(value<0)
	{
		if(HP<AssyDamage*AssyHP)
		{
			AssyHP--;
			Assy->addRateOfDestruction(1);
		}
	}

	if(value>0)
	{
		if(HP>AssyDamage*AssyHP)
		{
			AssyHP++;
			Assy->addRateOfDestruction(-1);
		}
	}
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::moveJump()
{
	//スペースキーを押したとき
	if(m_keyboard->GetTrigger(DIK_SPACE)&&canJump&&!isLighting)
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
	if(!isLighting)
	{
		m_move_spd.y+=GRAVITY_SPD;
	}

}
//=============================================================================
// 様々な当たり判定
//=============================================================================
void CPlayer::Collider()
{
	//地面とプレイヤの当たり判定
	if(m_pos.y>=593.0f-Offset.y)
	{
		canJump=true;
		canLighting=true;
		isJump=false;
		m_pos.y=593.0f-Offset.y;
	}

	if(m_pos.x<=0.0f)
	{
		m_pos.x=0.0f;
	}

	if(m_pos.x>=((SCREEN_WIDTH>>1)+(SCREEN_WIDTH>>2)*2.f))
	{
		m_pos.x=((SCREEN_WIDTH>>1)+(SCREEN_WIDTH>>2)*2.f);
	}

}
//=============================================================================
// 攻撃処理
//=============================================================================
void CPlayer::Attack()
{
	if(m_keyboard->GetTrigger(DIK_K)&&!isAttack&&!isLighting)
	{
		SetAnimMode(PLAYER_ANIM_ATACK,false);
	}
}
//=============================================================================
// 光アクション処理
//=============================================================================
void CPlayer::LightAction()
{
	if(m_keyboard->GetTrigger(DIK_L)&&!isAttack&&!isLighting&&canLighting)
	{
		
		canLighting=false;
		m_move_spd.y=0.0f;
		SetAnimMode(PLAYER_ANIM_LIGHT,false);
	}

	if(isHoldLighting)
	{
		if(m_keyboard->GetSetDelete(DIK_L))
		{
			isHoldLighting=false;
		}
	}
}
//=============================================================================
//アニメーションの更新処理
//=============================================================================
void CPlayer::UpdateAnim()
{
	switch(AnimMode)
	{
	case PLAYER_ANIM_WAIT:
		if(cntAnim==PLAYER_ANIMSPD_WAIT*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				isAnimEnd=true;
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;

	case PLAYER_ANIM_MOVE:
		if(cntAnim==PLAYER_ANIMSPD_MOVE*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				isAnimEnd=true;
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;

	case PLAYER_ANIM_ATACK:
		if(cntAnim==PLAYER_ANIMSPD_ATACK*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				isAnimEnd=true;
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;

	case PLAYER_ANIM_DAMAGE:
		if(cntAnim==PLAYER_ANIMSPD_DAMAGE*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				isAnimEnd=true;
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;

	case PLAYER_ANIM_LIGHT:
		if(cntAnim==PLAYER_ANIMSPD_LIGHT*nowAnim)
		{
			if(nowAnim==maxAnim)
			{
				
				isAnimEnd=true;
				
			}

			else
			{
				nowAnim++;
				SetAnim(maxAnim,nowAnim,1,1,this);
			}
		}
		cntAnim++;
		break;
	}

	if(isAnimEnd&&!isHoldLighting)
	{
		if(isRupeAnim)
		{
			cntAnim=0;
			nowAnim=1;
			SetAnim(maxAnim,1,1,1,this);
		}

		else
		{
			isAttack=false;
			isLighting=false;
			SetAnimMode(PLAYER_ANIM_WAIT,true);
		}

		isAnimEnd=false;
	}
}
//=============================================================================
//アニメーションのセット処理
//=============================================================================
void CPlayer::SetAnimMode(int AnimID,bool Rupe)
{
	if(AnimMode==AnimID)
	{
		return;
	}

	switch (AnimID)
	{
	case PLAYER_ANIM_WAIT:
		cntAnim=0;
		nowAnim=1;
		maxAnim=PLAYER_MAXANIM_WAIT;
		this->SetTex(CImport::PLAYER_WAIT);
		SetAnim(maxAnim,1,1,1,this);
		break;

	case PLAYER_ANIM_MOVE:

		break;

	case PLAYER_ANIM_ATACK:
		cntAnim=0;
		nowAnim=1;
		maxAnim=PLAYER_MAXANIM_ATACK;
		isAttack=true;
		this->SetTex(CImport::PLAYER_ATTACK);
		SetAnim(maxAnim,1,1,1,this);
		break;

	case PLAYER_ANIM_DAMAGE:

		break;

	case PLAYER_ANIM_LIGHT:
		cntAnim=0;
		nowAnim=1;
		maxAnim=PLAYER_MAXANIM_LIGHT;
		isHoldLighting=true;
		isLighting=true;
		this->SetTex(CImport::PLAYER_LIGHT);
		SetAnim(maxAnim,1,1,1,this);
		break;
	}
	
	AnimMode=AnimID;

	isRupeAnim=Rupe;

}
