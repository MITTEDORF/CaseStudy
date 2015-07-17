//=============================================================================
//
// プレイヤー制御クラス [character_player.h]
// Author :YUKI SAKAMOTO
//
//=============================================================================
#ifndef _CHARACTER_PLAYER_H
#define _CHARACTER_PLAYER_H
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2D.h"
#include "character_config.h"
#include "player_config.h"

#include "character_vehicle.h"
//=============================================================================
// マクロ
//============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
//キーボード入力制御クラス
class CInputKeyboard;
class CInputPadX;
class CParticleManager;
class CSound;
//=============================================================================
// クラス定義
//=============================================================================
class CPlayer : public CScene2D
{
public:
	
	//コンストラクタ
	//第一引数:プライオリティ(最大はPRIORITY_MAX、何も入力しないとPRIORITY_MAX - 2に設定)
	//第二引数:オブジェクトタイプ(何も入力しないとOBJTYPE_NONEに設定)
	CPlayer(int priority = PRIORITY_MAX - 2, OBJTYPE objType = OBJTYPE_NONE);

	//デストラクタ
	~CPlayer(){};

	//クリエイト
	//第一引数:デバイス
	//戻り値  :インスタンスのポインタ
	static CPlayer* Create(LPDIRECT3DDEVICE9 device,CostumeID costume_id=COSTUME_NONE,VehicleID vehicle_id=(VehicleID)0);

	//初期化処理
	//第一引数:デバイス
	//戻り値  :成功したかどうかをHRESULT型で返す
	HRESULT	Init(LPDIRECT3DDEVICE9 device);

	//終了処理
	void	Uninit(void);

	//更新処理
	void	Update(void);

	//描画処理
	void	Draw(void);

	//キーボード情報のセット
	void SetKeyboard(CInputKeyboard* keyboard){m_keyboard = keyboard;}
	//パッド情報のセット
	void SetPadX(CInputPadX* padX){m_padX = padX;}

	//移動速度の取得処理
	//戻り値:プレイヤーの移動量
	D3DXVECTOR2 move_spd_()
	{
		return (m_move_spd);
	}

	//HPの取得処理
	//戻り値:プレイヤーのHP
	int HP_()
	{
		return (HP);
	}

	//プレイヤーの生死確認
	//戻り値:死んでたらfalseが返ってくるよ
	bool isDeth_()
	{
		return (isDeth);
	}

	//無敵状態かどうかの取得
	//戻り値:無敵状態ならtrueが返ってくるよ
	bool isinvincible_()
	{
		return (isinvincible);
	}

	//パーティクル管理クラスの取得
	//戻り値:パーティクル管理クラスのポインタ
	CParticleManager* particle_()
	{
		return (particle);
	}

	//光アクション中かどうかのチェック
	//戻り値:trueなら光アクション中だよ
	bool isLitninng()
	{
		return(isAnimEnd&&isHoldLighting);
	}

	//パーティクルを放出
	//第一引数:パーティクルが向かう目標のポインタ(NULLをいれればほわ～っと消える)
	void PaticleStart(CScene* target);
	//パーティクルの画面スクロール処理(とりあえず毎フレーム呼んで)
	//第一引数:スクロールの値
	void ParticleScrol(float value);

	//HPの加算処理
	//第一引数:加算する値(減算したい場合は-の値を入れてください)
	void AddHP(int value);

	//コスチュームのセット
	//第一引数:ID入れてね(character_configにて定義)
	void SetCostumeID(CostumeID value);

	//乗り物のセット
	//第一引数:ID入れてね(character_configにて定義)
	void SetVehicleID(VehicleID value);
	
	//現在のシーンがゲーム中かどうか切り替える
	//第一引数:ゲーム中ならtrue、それ以外はfalse
	void Set_isGame(bool value);

	//プレイヤーの値をリフレッシュする
	//第一引数:死に際に小ジャンプをさせたい場合はtrueを入れる
	void PlayerReflash(bool value=true)
	{
		isLighting=false;
		if(value||isFall)
		{
			m_move_spd.y=0.0f;
		}

		else
		{
			m_move_spd.y=JUMP_SPD/1.5f;
		}
	}

	void PlayerGoal()
	{
		isLighting=false;
		isGoal=true;
		SetAnimMode(PLAYER_ANIM_LIGHT,false);
		m_move_spd.y=0.0f;
		m_move_spd.x=MOVE_FRICTIONAL_FORCE*50.0f;
	}

	
	//アッシーのポインタを渡す
	//戻り値:アッシーのポインター
	CVehicle* Assy_()
	{
		return (Assy);
	}
	
	//今現在地面に着地中かどうか調べる
	//戻り値:地面に着地中ならばtrueが返ってくる
	bool isGround_()
	{
		return (isGround);
	}

	//今現在地面に着地中かどうかをセット出来る(接地判定以外では呼ぶのNG)
	//第一引数:着地中ならばtrueを入れる
	void isGround_set(bool value)
	{
		if(isGround==value){return;}
		isGround=value;
	}

	//Y方向の高さを0にする
	void SpdKill()
	{
		m_move_spd.y=0.0f;
	}

	//ジャンプ可能状態にする
	void SetCanJump()
	{
		isJump=false;
		canJump=true;
	}

	bool isFadeStart_()
	{
		return (isFadeStart);
	}

	void SetSound(CSound* psound)
	{
		sound=psound;
	}
	
	//テクスチャIDの参照
	CImport::TEXTURES ConsultationPlayerTexID(PlayerState state,int offset=0);
	CImport::TEXTURES ConsultationVehicleTexID(int offset=0);

private:
	void DrawHitBox(void);

	CSound * sound;

	//テクスチャID
	CostumeID Costume_id;
	VehicleID Vehicle_id;

	//ゲーム中かどうか
	bool isGame;
	//今地面に接地しているかどうか
	bool isGround;
	//描画フラグ
	bool isDraw;
	//落ちているかどうか
	bool isFall;
	//ジャンプ中かどうか
	bool isJump;
	//ジャンプ可能かどうか
	bool canJump;
	//攻撃中かどうか
	bool isAttack;
	//光アクション中かどうか
	bool isLighting;
	//光アクションを継続するかどうか
	bool isHoldLighting;
	//光アクションが可能かどうか
	bool canLighting;
	//志望フラグ
	bool isDeth;
	//無敵フラグ
	bool isinvincible;
	//アニメーションのループフラグ
	bool isRupeAnim;
	//アニメーションの1順終了フラグ
	bool isAnimEnd;
	//ゴール中かどうかのフラグ
	bool isGoal;
	//バーストしたかフラグ
	bool isBurst;

	bool isFadeStart;

	//パーティクル管理クラス
	CParticleManager *particle;
	//キーボード情報格納変数
	CInputKeyboard* m_keyboard;
	//パッド情報格納変数
	CInputPadX* m_padX;
	//アッシー管理クラス
	CVehicle* Assy;

	//プレイヤーの移動速度
	D3DXVECTOR2 m_move_spd;
	//Y値オフセット
	D3DXVECTOR2 Offset;

	//プレイヤーのHP
	int HP;
	//ビークルダメージ値
	int AssyDamage;
	//ビークルの耐久(1～3)
	int AssyHP;
	//無敵カウンター
	int isinvincibleCnt;
	//無敵の見た目カウンター
	int isinvincibleDrawCnt;

	//現在のアニメーションモード
	int AnimMode;
	//現在のアニメーション番号
	int nowAnim;
	//アニメーションのカウント用
	int cntAnim;
	//アニメーションの最大コマ数
	int maxAnim;

	//無敵時間
	float InbisibleTime;
	//移動速度
	float MoveSpd;
	//ジャンプ力
	float JumpSpd;

	//重力値
	float localGravity;

	//変数のNULL埋め処理
	void NullSetVariable(void)
	{
		isFadeStart=false;
		isBurst=false;
		isGoal=false;
		particle=NULL;
		isGround=false;
		Offset.x=0;
		Offset.y=0;
		isGame=true;
		HP=PLAYER_HP_MAX;
		AssyDamage=HP/3;
		AssyHP=PLAYER_HP_MAX;
		isinvincible=false;
		isDraw=true;
		isDeth=false;
		isFall=false;
		InbisibleTime=INVISIBLE_TIME;
		isinvincibleDrawCnt=0;
		maxAnim=1;
		isAnimEnd=false;
		isRupeAnim=true;
		AnimMode=-1;
		m_keyboard=NULL;
		m_padX=NULL;
		Assy=NULL;
		cntAnim=0;
		nowAnim=1;
		m_move_spd=D3DXVECTOR2(0.0f,0.0f);
		isJump=false;
		canJump=true;
		isAttack=false;
		isLighting=false;
		isHoldLighting=false;
		canLighting=true;
		isinvincibleCnt=0;
		localGravity=GRAVITY_SPD;
		MoveSpd=MOVE_SPD;
		JumpSpd=JUMP_SPD;
	}

	//移動処理
	void Move();
	//攻撃処理
	void Attack();
	//ジャンプ処理
	void moveJump();
	//光アクション処理
	void LightAction();
	//重力をかける
	void AddGravity();
	//様々な当たり判定
	void Collider();
	//アニメーションの更新処理
	void UpdateAnim();
	//アニメーションのセット処理
	void SetAnimMode(int animID,bool Rupe);
	//HPの更新
	void HPUpdate();
	//無敵処理
	void InvincibleUpdate();
};

#endif

