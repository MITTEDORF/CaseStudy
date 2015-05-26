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

#include "game.h"
#include "debugproc.h"
#include "fade.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const float JUMP_SPD    = -40.0f;
const float MOVE_SPD    = 3.0f;
const float GRAVITY_SPD = 2.0f;

float MapValues(float x,float inMin,float inMax,float outMin,float outMax);

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

	Anim(1,1);


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
	m_move_spd.x*=0.8f;

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
}
//=============================================================================
// アニメーション処理
//=============================================================================
void CPlayer::Anim(int maxTex,int nowTex)
{
	
	float uvOffset;
	uvOffset=MapValues(1.0f,0,(float)maxTex,0,1.0f);

	D3DXVECTOR2 cord=D3DXVECTOR2(uvOffset*(float)(nowTex-1),0);
	this->SetCord(0,cord);

	cord=D3DXVECTOR2(uvOffset*(float)(nowTex),0);
	this->SetCord(1,cord);

	cord=D3DXVECTOR2(uvOffset*(float)(nowTex-1),1.0f);
	this->SetCord(2,cord);

	cord=D3DXVECTOR2(uvOffset*(float)(nowTex),1.0f);
	this->SetCord(3,cord);

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
		Anim(5,1);
	}

	if(isAttack)
	{
		switch (cntAnim)
		{
			case 10:
				Anim(5,2);
				break;

			case 10*2:
				Anim(5,3);
				break;

			case 10*3:
				Anim(5,4);
				break;

			case 10*4:
				Anim(5,5);
				break;

			case 10*5:
				cntAnim=0;
				nowAnim=1;
				isAttack=false;
				this->SetTex(CImport::TEX_PLAYER_WAIT);
				Anim(1,1);
				return;
				break;
		}

		cntAnim++;
	}
}

//=============================================================================
// 最大値、最小値を考慮した現在値の算出
//=============================================================================
float MapValues(float x,float inMin,float inMax,float outMin,float outMax)
{
	return ((x-inMin)*(outMax-outMin)/(inMax-inMin)+outMin);
}