//*****************************************************************************
//
// �v���C���[����N���X [character_player.cpp]
// Author :YUKI SAKAMOTO
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "character_goal.h"

#include "import.h"


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
// ����������
//=============================================================================
HRESULT CCharacterGoal::Init(LPDIRECT3DDEVICE9 device)
{
	
	CharacterL=CScene2D::Create(device,CImport::GOAL_CHAR_RIGHT,CScene2D::POINT_CENTER);
	CharacterL->SetPos(0.0f-534.0f/4.0f,SCREEN_HEIGHT-128.0f-544.0f/8.0f);
	CharacterL->SetSize(534.0f/2.0f,544.0f/2.0f);

	CharacterR=CScene2D::Create(device,CImport::GOAL_CHAR_LEFT,CScene2D::POINT_CENTER);
	CharacterR->SetPos(SCREEN_WIDTH+576.0f/4.0f,SCREEN_HEIGHT-128.0f-522.0f/8.0f);
	CharacterR->SetSize(576.0f/2.0f,522.0f/2.0f);



	//������Ԃ�
	return S_OK;
}

void CCharacterGoal::Start(CScene* Target)
{
	if(!isStart)
	{
		if(Target)
		{
			target=Target;
			lenL = (target->GetPos().x-CharacterL->GetPos().x-534.0f/3.0f)/80.0f;
			lenR = (target->GetPos().x-CharacterR->GetPos().x+576.0f/2.0f)/80.0f;
		}

		else
		{
			lenL = (SCREEN_WIDTH/2.0f-CharacterL->GetPos().x-534.0f/3.0f)/80.0f;
			lenR = (SCREEN_WIDTH/2.0f-CharacterR->GetPos().x+576.0f/3.0f)/80.0f;
		}

		isStart=true;
	}
}

//=============================================================================
// �N���G�C�g
//=============================================================================
CCharacterGoal* CCharacterGoal::Create(LPDIRECT3DDEVICE9 device)
{
	CCharacterGoal* scene = new CCharacterGoal();
	//������
	scene->Init(device);

	return scene;
}
//=============================================================================
// �I��
//=============================================================================
void CCharacterGoal::Uninit(void)
{

	//�e�̏I��
	CScene2D::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CCharacterGoal::Update(void)
{
	if(isStart)
	{
		if(Cunt>=80)
		{
			isFade=true;
			return;
		}

		CharacterR->SetPosX(CharacterR->GetPos().x+lenR);
		CharacterL->SetPosX(CharacterL->GetPos().x+lenL);
		Cunt++;
	}
	//�e�̍X�V
	CScene2D::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CCharacterGoal::Draw(void)
{
	
}