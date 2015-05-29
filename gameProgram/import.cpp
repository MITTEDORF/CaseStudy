//*****************************************************************************
//
// CImport�N���X [import.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "import.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �e�N�X�`��
const char* TEX_PATH[] =
{
	NULL,

	// �V�X�e��
	"./data/TEXTURE/fade.jpg",

	// ���S
	"./data/TEXTURE/titleLogo.png",

	// ��
	"./data/TEXTURE/sky01.png",
	"./data/TEXTURE/sky02.png",
	"./data/TEXTURE/sky03.png",
	"./data/TEXTURE/sky04.png",
	"./data/TEXTURE/sky05.png",

	// �X
	"./data/TEXTURE/dirt.png",
	"./data/TEXTURE/forest_01.png",

	// ��
	"./data/TEXTURE/asphalt.png",
	"./data/TEXTURE/town_01.png",

	// �v���C���[
	"./data/TEXTURE/player_wait.png",
	"./data/TEXTURE/Assy_one.png",
	"./data/TEXTURE/player_attack.png",
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9	CImport::m_tex[TEX_MAX];

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CImport::CImport(void)
{
	// �e�N�X�`��
	for(int cnt = 0; cnt < TEX_MAX; ++cnt)
	{
		m_tex[cnt] = nullptr;
	}
}

//=============================================================================
// ����
//=============================================================================
CImport* CImport::Create(LPDIRECT3DDEVICE9 device)
{
	CImport* pointer = new CImport;
	pointer->Init(device);
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CImport::Init(LPDIRECT3DDEVICE9 device)
{
	HRESULT hr;

	//----------------------------
	// �e�N�X�`��
	//----------------------------
	for(int cnt = 1; cnt < TEX_MAX; ++cnt)
	{
		hr = D3DXCreateTextureFromFile(device, TEX_PATH[cnt], &m_tex[cnt]);
		if(FAILED(hr))
		{
			MessageBox(NULL, "�e�N�X�`������", "D3DXCreateTextureFromFile", MB_OK);
		}
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CImport::Uninit(void)
{
	//----------------------------
	// �e�N�X�`��
	//----------------------------
	for(int cnt = 1; cnt < TEX_MAX; cnt++)
	{
		// �e�N�X�`���̊J��
		SAFE_RELEASE(m_tex[cnt]);
	}
}
