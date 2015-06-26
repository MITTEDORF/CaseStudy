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

#include "particle_manager.h"

#include "inputKeyboard.h"
#include "math_animation.h"

#include "game.h"
#include "debugproc.h"
#include "fade.h"

#include "listObject.h"

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
	particle=NULL;
	
	Assy=CVehicle::Create(device,ConsultationVehicleTexID());
	Offset.x=-20.0f;
	Offset.y=0;

	particle=new CParticleManager();
	particle->Init(device);

	//親の初期化
	CScene2D::Init(device,ConsultationPlayerTexID(PLAYER_STATE_WAIT),POINT_CENTER);

	SetAnimMode(PLAYER_ANIM_WAIT,true);

	//成功を返す
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CPlayer::Uninit(void)
{
	SAFE_DELETE(particle);
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

	if(isGame)
	{
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

		//重力加算
		AddGravity();

		//無敵処理の更新
		InvincibleUpdate();

		//スピードを考慮した座標の算出
		m_pos+=m_move_spd;

		//様々な当たり判定
		Collider();

		//無敵処理の更新
		InvincibleUpdate();

		

		particle->Setpos(m_pos);

	
	}

	//アッシーのポジションをセット
	Assy->SetPos(m_pos.x+(int)Offset.x,m_pos.y+(int)Offset.y);
	//座標の再計算
	SetVertexPolygon();
	// 当たり判定用座標の更新
	CScene2D::SetHitPos(m_pos);

	//親の更新
	CScene2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CPlayer::Draw(void)
{
	if(isDraw)
	{
		//親の描画
		CScene2D::Draw();
		CScene2D::DrawHitBox();
	}
}
//=============================================================================
// 生成
//=============================================================================
CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 device,CostumeID costume_id,VehicleID vehicle_id)
{
	CPlayer* scene = new CPlayer;
	//コスチュームと乗り物のIDのセット
	scene->SetCostumeID(costume_id);
	scene->SetVehicleID(vehicle_id);
	//初期化
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

	if(value<0&&!isinvincible)
	{
		isinvincible=true;
		isinvincibleCnt=0;
		isinvincibleDrawCnt=0;
	}

	else
	{
		return;
	}

	HP+=value;
	//HPが0いかにならないように処理
	if(HP<=0)
	{
		HP=0;
		isDeth=true;
		m_move_spd.x=0.0f;
		m_move_spd.y=JUMP_SPD/1.5f;
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
	if((m_pos.y>=593.0f-Offset.y)&&!isDeth)
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

	CheckCollisionAABB(D3DXVECTOR2(0,0),D3DXVECTOR2(0,0),POINT_LEFTTOP);

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
		this->SetTex(ConsultationPlayerTexID(PLAYER_STATE_WAIT));
		SetAnim(maxAnim,1,1,1,this);
		break;

	case PLAYER_ANIM_MOVE:

		break;

	case PLAYER_ANIM_ATACK:
		cntAnim=0;
		nowAnim=1;
		maxAnim=PLAYER_MAXANIM_ATACK;
		isAttack=true;
		this->SetTex(ConsultationPlayerTexID(PLAYER_STATE_ATTACK));
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
		this->SetTex(ConsultationPlayerTexID(PLAYER_STATE_LIGHTNING));
		SetAnim(maxAnim,1,1,1,this);
		break;
	}
	
	AnimMode=AnimID;

	isRupeAnim=Rupe;

}
//=============================================================================
// 無敵処理の更新
//=============================================================================
void CPlayer::InvincibleUpdate()
{
	if(isinvincible)
	{
		isinvincibleCnt++;
		isinvincibleDrawCnt++;

		if(isinvincibleDrawCnt>=INVISIBLE_DRAW_TIME)
		{
			isDraw=!isDraw;
			isinvincibleDrawCnt=0;
		}
		

		if(isinvincibleCnt>=INVISIBLE_TIME)
		{
			isinvincible=false;
			isDraw=true;
		}
	}
}
//=============================================================================
// パーティクル開始
//=============================================================================
void CPlayer::PaticleStart(CScene* target)
{
	particle->StartBurst(target);
}

//=============================================================================
// スクロール処理
//=============================================================================
void CPlayer::ParticleScrol(float value)
{
	if(particle)
	{
		particle->Scrol(value);
	}
}

//=============================================================================
// テクスチャIDの参照処理(プレイヤー)
//=============================================================================
CImport::TEXTURES CPlayer::ConsultationPlayerTexID(PlayerState state)
{
	switch (state)
	{
	case PLAYER_STATE_WAIT:
		switch (Costume_id)
		{
		case COSTUME_NONE:
			return (CImport::PLAYER_DEFAULT_WAIT);
			break;
		case COSTUME_KNIGHT:
			return (CImport::PLAYER_KNIGHT_WAIT);
			break;
		case COSTUME_SANTA:
			return (CImport::PLAYER_SANTA_WAIT);
			break;
		case COSTUME_SWIMWEAR:
			return (CImport::PLAYER_SWIMWEAR_WAIT);
			break;
		case COSTUME_NINJA:
			return (CImport::PLAYER_NINJA_WAIT);
			break;
		case COSTUME_FAITER:
			return (CImport::PLAYER_FAITER_WAIT);
			break;
		}
		break;
	case PLAYER_STATE_ATTACK:
		switch (Costume_id)
		{
		case COSTUME_NONE:
			return (CImport::PLAYER_DEFAULT_ATTACK);
			break;
		case COSTUME_KNIGHT:
			return (CImport::PLAYER_KNIGHT_ATTACK);
			break;
		case COSTUME_SANTA:
			return (CImport::PLAYER_SANTA_ATTACK);
			break;
		case COSTUME_SWIMWEAR:
			return (CImport::PLAYER_SWIMWEAR_ATTACK);
			break;
		case COSTUME_NINJA:
			return (CImport::PLAYER_NINJA_ATTACK);
			break;
		case COSTUME_FAITER:
			return (CImport::PLAYER_FAITER_ATTACK);
			break;
		}
		break;
	case PLAYER_STATE_LIGHTNING:
		switch (Costume_id)
		{
		case COSTUME_NONE:
			return (CImport::PLAYER_DEFAULT_LIGHT);
			break;
		case COSTUME_KNIGHT:
			return (CImport::PLAYER_KNIGHT_LIGHT);
			break;
		case COSTUME_SANTA:
			return (CImport::PLAYER_SANTA_LIGHT);
			break;
		case COSTUME_SWIMWEAR:
			return (CImport::PLAYER_SWIMWEAR_LIGHT);
			break;
		case COSTUME_NINJA:
			return (CImport::PLAYER_NINJA_LIGHT);
			break;
		case COSTUME_FAITER:
			return (CImport::PLAYER_FAITER_LIGHT);
			break;
		}

		break;
	}

	return (CImport::PLAYER_DEFAULT_WAIT);
}

//=============================================================================
// テクスチャIDの参照処理(乗り物)
//=============================================================================
CImport::TEXTURES CPlayer::ConsultationVehicleTexID()
{
	switch (Vehicle_id)
	{
	case VEHICLE_TRAM:
		return (CImport::ASSY_TRAM);
		break;
	case VHEICLE_LOG:
		return (CImport::ASSY_LOG);
		break;
	case VEHICLE_BATHTUB:
		return (CImport::ASSY_BATHTUB);
		break;
	case VHEICLE_DOLLY:
		return (CImport::ASSY_DOLLY);
		break;
	case VEHICLE_SLEIGH:
		return (CImport::ASSY_SLEIGH);
		break;
	case VHEICLE_TRUCK:
		return (CImport::ASSY_TRUCK);
		break;
	}

	return (CImport::ASSY_TRAM);
}

//=============================================================================
// 乗り物のテクスチャIDのセット(ゲームシーン以外で使う場合はアニメも勝手にセット)
//=============================================================================
void CPlayer::SetVehicleID(VehicleID value)
{
	if(Vehicle_id==value){return;}

	Vehicle_id=value;;
	if(!isGame)
	{
		Assy->SetTex(ConsultationVehicleTexID());
	}
}

//=============================================================================
// コスプレのテクスチャIDのセット(ゲームシーン以外で使う場合はアニメも勝手にセット)
//=============================================================================
void CPlayer::SetCostumeID(CostumeID value)
{
	if(Costume_id==value){return;}

	Costume_id=value;
	if(!isGame)
	{
		this->SetTex(ConsultationPlayerTexID(PLAYER_STATE_WAIT));
	}
}

//=============================================================================
//ゲーム中かどうかのセット
//=============================================================================
void CPlayer::Set_isGame(bool value)
{
	isGame=value;
}
