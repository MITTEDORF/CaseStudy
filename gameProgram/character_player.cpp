//*****************************************************************************
//
// �v���C���[����N���X [character_player.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_player.h"

#include "particle_manager.h"

#include "inputKeyboard.h"
#include "math_animation.h"

#include "game.h"
#include "debugproc.h"
#include "fade.h"

#include "listObject.h"

#include "inputPadX.h"

#include "road_manager.h"

#include "sound.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ���̒�`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	//�ϐ���NULL����
	NullSetVariable();

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(LPDIRECT3DDEVICE9 device)
{

	//�A�b�V�[�̐���
	Assy=CVehicle::Create(device,ConsultationVehicleTexID());

	//�I�t�Z�b�g�̏�����
	Offset.x=0.0f;
	Offset.y=0.0f;

	//�p�[�e�B�N���̐���/������
	particle=new CParticleManager();
	particle->Init(device);

	// ���͊֌W
	m_keyboard = nullptr;
	m_padX = nullptr;

	//�e�̏�����
	CScene2D::Init(device,ConsultationPlayerTexID(PLAYER_STATE_WAIT),POINT_CENTER);

	//���݂̃A�j���[�V������ҋ@�ɂ���
	SetAnimMode(PLAYER_ANIM_WAIT,true);

	//������Ԃ�
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CPlayer::Uninit(void)
{
	//�p�[�e�B�N������Ȃ�
	SAFE_DELETE(particle);
	//�e�̏I��
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{
	
	//�A�j���[�V�����̃A�b�v�f�[�g
	UpdateAnim();

	if(isGame)
	{
		//�t�F�[�h���ł͂Ȃ��Ƃ�
		if(((CPhase::GetFade()->GetState() == CFade::FADESTATE_NONE)&&!isGoal))
		{
			m_posOld = m_pos;
		
			//�ړ�����
			Move();
		}

		//����
		m_move_spd.x*=MOVE_FRICTIONAL_FORCE;

		if(isBurst&&!particle->IsUsing())
		{
			isFadeStart=true;
		}

		//�d�͉��Z
		AddGravity();

		//���G�����̍X�V
		InvincibleUpdate();

		//�X�s�[�h���l���������W�̎Z�o
		m_pos+=m_move_spd;

		//�l�X�ȓ����蔻��
		Collider();

		//���G�����̍X�V
		InvincibleUpdate();
		particle->Setpos(m_pos);
	}

	//�A�b�V�[�̃|�W�V�������Z�b�g
	Assy->SetPos(m_pos.x+(int)Offset.x,m_pos.y+(int)Offset.y);
	//���W�̍Čv�Z
	SetVertexPolygon();
	// �����蔻��p���W�̍X�V
	CScene2D::SetHitPos(D3DXVECTOR2(Assy->GetPos().x,Assy->GetPos().y));

	//�e�̍X�V
	CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CPlayer::Draw(void)
{
	if(isDraw)
	{
		//�e�̕`��
		CScene2D::Draw();
		DrawHitBox();
	}
}
//=============================================================================
// ����
//=============================================================================
CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 device,CostumeID costume_id,VehicleID vehicle_id)
{
	CPlayer* scene = new CPlayer;
	//�R�X�`���[���Ə�蕨��ID�̃Z�b�g
	scene->SetCostumeID(costume_id);
	scene->SetVehicleID(vehicle_id);
	//������
	scene->Init(device);

	return scene;
}
//=============================================================================
// �ړ�����
//=============================================================================
void CPlayer::Move()
{
	if(!isLighting)
	{
		//�E�ړ�
		if(m_keyboard->GetPress(DIK_A))
		{
			m_move_spd.x-=MoveSpd;
			Assy->SetAnimMode(1,true);
		}

		//���ړ�
		if(m_keyboard->GetPress(DIK_D))
		{
			m_move_spd.x+=MoveSpd;
			Assy->SetAnimMode(1,true);
		}

		if(m_padX != NULL)
		{
			//�E�ړ�
			if(m_padX->GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT))
			{
				m_move_spd.x-=MoveSpd;
				Assy->SetAnimMode(1,true);
			}

			//���ړ�
			if(m_padX->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT))
			{
				m_move_spd.x+=MoveSpd;
				Assy->SetAnimMode(1,true);
			}
		}
	}

	if(m_keyboard->GetSetDelete(DIK_A)||m_keyboard->GetSetDelete(DIK_D))
	{
		Assy->SetAnimMode(0,true);
	}

	if(m_padX != NULL)
	{
		if(m_padX->GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT)||m_padX->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			Assy->SetAnimMode(0,true);
		}
	}

	//�W�����v����
	moveJump();
}
//=============================================================================
// HP�X�V����
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
	//HP��0�����ɂȂ�Ȃ��悤�ɏ���
	if(HP<=0)
	{
		HP=0;
		isDeth=true;
		m_move_spd.x=0.0f;
		m_move_spd.y=JUMP_SPD/1.5f;
	}

	//HP��0�����ɂȂ�Ȃ��悤�ɏ���
	if(HP>=PLAYER_HP_MAX)
	{
		HP=PLAYER_HP_MAX;
	}

	if(value<0)
	{
		sound->Play(CSound::SOUND_LABEL_DAMAGE);
		if(HP==2.0f||HP==1.0f)
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
// �W�����v����
//=============================================================================
void CPlayer::moveJump()
{
	//�X�y�[�X�L�[���������Ƃ�
	if(m_keyboard->GetTrigger(DIK_SPACE)&&canJump&&!isLighting)
	{
		if(!isJump)
		{
			sound->Play(CSound::SOUND_LABEL_JUMPSE);
			canJump=false;
			isJump=true;
			//�X�s�[�h�̐ݒ�
			m_move_spd.y=JumpSpd;
		}
	}

	if(m_padX != NULL)
	{
		if(m_padX->GetButtonTrigger(XINPUT_GAMEPAD_A))
		{
			if(!isJump)
			{
				sound->Play(CSound::SOUND_LABEL_JUMPSE);
				//isGravity=true;
				canJump=false;
				isJump=true;
				//�X�s�[�h�̐ݒ�
				m_move_spd.y=JumpSpd;
				CDebugproc::PrintDebugProc("�W�����v\n");
			}
		}
	}

}
//=============================================================================
// �d�͉��Z����
//=============================================================================
void CPlayer::AddGravity()
{
	if(!isLighting)
	{
		if(m_move_spd.y<0||isinvincible)
		{
			m_move_spd.y+=GRAVITY_SPD;
		}

		else
		{
			m_move_spd.y+=localGravity;
		}
	}

}
//=============================================================================
// �l�X�ȓ����蔻��
//=============================================================================
void CPlayer::Collider()
{
	//�n�ʂƃv���C���̓����蔻��
	if((m_pos.y>=SCREEN_HEIGHT)&&!isDeth)
	{
		AddHP(-5);
		isFall=true;
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
// �U������
//=============================================================================
void CPlayer::Attack()
{
	if(m_keyboard->GetTrigger(DIK_K)&&!isAttack&&!isLighting)
	{
		SetAnimMode(PLAYER_ANIM_ATACK,false);
	}
}
//=============================================================================
// ���A�N�V��������
//=============================================================================
void CPlayer::LightAction()
{
	if(m_keyboard->GetTrigger(DIK_L)&&!isAttack&&!isLighting&&canLighting)
	{
		
		canLighting=false;
		m_move_spd.y=0.0f;
		SetAnimMode(PLAYER_ANIM_LIGHT,false);
	}

	if(m_padX != NULL)
	{
		if(m_padX->GetButtonTrigger(XINPUT_GAMEPAD_B))
		{
			canLighting=false;
			m_move_spd.y=0.0f;
			SetAnimMode(PLAYER_ANIM_LIGHT,false);
		}
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
//�A�j���[�V�����̍X�V����
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
//�A�j���[�V�����̃Z�b�g����
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
// ���G�����̍X�V
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
		

		if(isinvincibleCnt>=InbisibleTime)
		{
			isinvincible=false;
			isDraw=true;
		}
	}
}
//=============================================================================
// �p�[�e�B�N���J�n
//=============================================================================
void CPlayer::PaticleStart(CScene* target)
{
	if(!isBurst)
	{
		particle->StartBurst(target);
		isBurst=true;
	}
}
//=============================================================================
// �X�N���[������
//=============================================================================
void CPlayer::ParticleScrol(float value)
{
	if(particle)
	{
		particle->Scrol(value);
	}
}
//=============================================================================
// �e�N�X�`��ID�̎Q�Ə���(�v���C���[)
//=============================================================================
CImport::TEXTURES CPlayer::ConsultationPlayerTexID(PlayerState state,int offset)
{
	int lid = (int)Costume_id+offset;

	if(lid<0||lid>=COSTUME_MAX)
	{
		return (CImport::TEX_MAX);
	}

	switch (state)
	{
	case PLAYER_STATE_WAIT:
		switch (lid)
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
		switch (lid)
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
		switch (lid)
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
// �e�N�X�`��ID�̎Q�Ə���(��蕨)
//=============================================================================
CImport::TEXTURES CPlayer::ConsultationVehicleTexID(int offset)
{
	int lid = (int)Vehicle_id+offset;

	if(lid<0||lid>=VEHICLE_MAX)
	{
		return (CImport::TEX_MAX);
	}

	switch (lid)
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

	return (CImport::ASSY_DOLLY);
}
//=============================================================================
// ��蕨�̃e�N�X�`��ID�̃Z�b�g(�Q�[���V�[���ȊO�Ŏg���ꍇ�̓A�j��������ɃZ�b�g)
//=============================================================================
void CPlayer::SetVehicleID(VehicleID value)
{
	if(Vehicle_id==value){return;}

	Vehicle_id=value;
	switch (Vehicle_id)
	{
	case VEHICLE_TRAM:
		HP=HP+2;
		break;

	case VHEICLE_LOG:
		InbisibleTime=InbisibleTime*1.3f;
		break;

	case VEHICLE_BATHTUB:

		break;

	case VEHICLE_SLEIGH:
		localGravity=localGravity/5.0f;
		break;

	case VHEICLE_TRUCK:
		break;

	case VHEICLE_DOLLY:
		HP--;
		break;

	}

	if(!isGame)
	{
		Assy->SetTex(ConsultationVehicleTexID());
	}
}
//=============================================================================
// �R�X�v���̃e�N�X�`��ID�̃Z�b�g(�Q�[���V�[���ȊO�Ŏg���ꍇ�̓A�j��������ɃZ�b�g)
//=============================================================================
void CPlayer::SetCostumeID(CostumeID value)
{
	if(Costume_id==value){return;}

	Costume_id=value;
	
	switch (Costume_id)
	{
	case COSTUME_NONE:
		break;

	case COSTUME_KNIGHT:
		InbisibleTime=InbisibleTime*1.6f;
		break;

	case COSTUME_SANTA:
		localGravity=localGravity/5.0f;
		break;

	case COSTUME_SWIMWEAR:

		break;

	case COSTUME_NINJA:
		MoveSpd=MoveSpd*1.3f;
		break;

	case COSTUME_FAITER:
		InbisibleTime=InbisibleTime*1.3f;
		break;

	}
	if(!isGame)
	{
		this->SetTex(ConsultationPlayerTexID(PLAYER_STATE_WAIT));
	}
}
//=============================================================================
//�Q�[�������ǂ����̃Z�b�g
//=============================================================================
void CPlayer::Set_isGame(bool value)
{
	isGame=value;
}

//=============================================================================
// �����蔻��{�b�N�X�̕`��
//=============================================================================
void CPlayer::DrawHitBox(void)
{
	if(CDebugproc::GetDrawFrag())
	{
		// �����̒��_�����v�Z
		D3DXVECTOR2 self[4], temp;
		D3DXVECTOR3 pos = Assy->GetPos();

		temp = (m_size - m_hitSize)/2;

		if(m_pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
		{
			self[0].x = pos.x + m_hitOffset.x + temp.x;				self[0].y = pos.y + m_hitOffset.y + temp.y;
			self[1].x = pos.x + m_hitOffset.x + m_size.x - temp.x;	self[1].y = pos.y + m_hitOffset.y + temp.y;
			self[2].x = pos.x + m_hitOffset.x + m_size.x - temp.x;	self[2].y = pos.y + m_hitOffset.y + m_size.y - temp.y;
			self[3].x = pos.x + m_hitOffset.x + temp.x;				self[3].y = pos.y + m_hitOffset.y + m_size.y - temp.y;
		}
		else if(m_pointType == POINT_CENTER)	// ���S���_�̏ꍇ
		{
			self[0].x = pos.x + m_hitOffset.x - m_hitSize.x/2;	self[0].y = pos.y + m_hitOffset.y - m_hitSize.y/2;
			self[1].x = pos.x + m_hitOffset.x + m_hitSize.x/2;	self[1].y = pos.y + m_hitOffset.y - m_hitSize.y/2;
			self[2].x = pos.x + m_hitOffset.x + m_hitSize.x/2;	self[2].y = pos.y + m_hitOffset.y + m_hitSize.y/2;
			self[3].x = pos.x + m_hitOffset.x - m_hitSize.x/2;	self[3].y = pos.y + m_hitOffset.y + m_hitSize.y/2;
		}

		// ���_���W
		m_hitBox[0].vtx = D3DXVECTOR3(self[0].x, self[0].y, 0);
		m_hitBox[1].vtx = D3DXVECTOR3(self[1].x, self[1].y, 0);
		m_hitBox[2].vtx = D3DXVECTOR3(self[3].x, self[3].y, 0);
		m_hitBox[3].vtx = D3DXVECTOR3(self[2].x, self[2].y, 0);

		// �e�N�X�`�����W
		m_hitBox[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_hitBox[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		m_hitBox[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_hitBox[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// �F���
		for(int cnt = 0; cnt < 4; cnt++)
		{
			m_hitBox[cnt].diffuse	= D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.4f);
			m_hitBox[cnt].rhw		= 1.0f;
		}

		//���_�t�H�[�}�b�g�̐ݒ�
		m_device->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		m_device->SetTexture(0, NULL);

		//�`��ݒ�
		m_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
									2,
									m_hitBox,
									sizeof(VERTEX_2D));
	}
}