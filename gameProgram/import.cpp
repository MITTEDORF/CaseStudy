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
	"./data/TEXTURE/version/beta.png",

	// �^�C�g��
	"./data/TEXTURE/title/titleLogo.png",
	"./data/TEXTURE/title/title_bg.png",

	// ��
	"./data/TEXTURE/sky/sky_back.png",
	"./data/TEXTURE/sky/sky_01.png",
	"./data/TEXTURE/sky/sky_02.png",
	"./data/TEXTURE/sky/sky_03.png",
	"./data/TEXTURE/sky/sky_04.png",
	"./data/TEXTURE/sky/sky_05.png",

	// �X
	"./data/TEXTURE/forest/forest_01.png",

	// ��
	"./data/TEXTURE/town/town_01.png",

	// ��
	"./data/TEXTURE/forest/dirt.png",
	"./data/TEXTURE/town/asphalt.png",

	// ��Q��
	"./data/TEXTURE/stumbler/signboard.png",
	"./data/TEXTURE/stumbler/lion.png",
	"./data/TEXTURE/stumbler/rock.png",
	"./data/TEXTURE/stumbler/log_left.png",
	"./data/TEXTURE/stumbler/log_center.png",
	"./data/TEXTURE/stumbler/log_right.png",
	"./data/TEXTURE/stumbler/bird.png",
	"./data/TEXTURE/stumbler/dustbox.png",
	"./data/TEXTURE/stumbler/barricade.png",

	// �^�[�Q�b�g
	"./data/TEXTURE/goal/tv_on.png",
	"./data/TEXTURE/goal/tv_on.png",
	"./data/TEXTURE/goal/tv_off.png",
	"./data/TEXTURE/goal/tv_clear.png",

	// �v���C���[
	"./data/TEXTURE/player/default/player_wait.png",
	"./data/TEXTURE/player/default/player_attack.png",
	"./data/TEXTURE/player/default/player_light.png",

	"./data/TEXTURE/player/knight/player_wait.png",
	"./data/TEXTURE/player/knight/player_attack.png",
	"./data/TEXTURE/player/knight/player_light.png",

	"./data/TEXTURE/player/santa/player_wait.png",
	"./data/TEXTURE/player/santa/player_attack.png",
	"./data/TEXTURE/player/santa/player_light.png",

	"./data/TEXTURE/player/swimwear/player_wait.png",
	"./data/TEXTURE/player/swimwear/player_attack.png",
	"./data/TEXTURE/player/swimwear/player_light.png",
	
	"./data/TEXTURE/player/ninja/player_wait.png",
	"./data/TEXTURE/player/ninja/player_attack.png",
	"./data/TEXTURE/player/ninja/player_light.png",

	"./data/TEXTURE/player/faiter/player_wait.png",
	"./data/TEXTURE/player/faiter/player_attack.png",
	"./data/TEXTURE/player/faiter/player_light.png",


	"./data/TEXTURE/player/player_goodmood.png",
	"./data/TEXTURE/player/player_badmood.png",

	//�p�[�e�B�N��
	"./data/TEXTURE/particle/particle_yellow_small.png",
	"./data/TEXTURE/particle/particle_daidai_small.png",
	"./data/TEXTURE/particle/particle_white_small.png",

	// ��蕨
	"./data/TEXTURE/assy/tram.png",
	"./data/TEXTURE/assy/log.png",
	"./data/TEXTURE/assy/bathtub.png",
	"./data/TEXTURE/assy/dolly.png",
	"./data/TEXTURE/assy/sleigh.png",
	"./data/TEXTURE/assy/truck.png",

	//�L�������C�N���UI
	"./data/TEXTURE/select/assy_option.png",
	"./data/TEXTURE/select/costume_option.png",
	"./data/TEXTURE/select/option_details.png",
	"./data/TEXTURE/select/select_cursor.png",
	"./data/TEXTURE/select/select_frame.png"


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
