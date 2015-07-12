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

#include "mapData.h"

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

	// ����
	"./data/TEXTURE/waterside/waterside_01.png",

	// ����
	"./data/TEXTURE/desert/desert_01.png",
	"./data/TEXTURE/desert/desert_02.png",
	"./data/TEXTURE/desert/desert_03.png",

	// �X��
	"./data/TEXTURE/glacier/glacier_01.png",
	"./data/TEXTURE/glacier/glacier_02.png",
	"./data/TEXTURE/glacier/glacier_03.png",
	"./data/TEXTURE/glacier/glacier_04.png",
	"./data/TEXTURE/glacier/glacier_05.png",

	// �T�o���i
	"./data/TEXTURE/savannah/savannah_01.png",
	"./data/TEXTURE/savannah/savannah_02.png",
	"./data/TEXTURE/savannah/savannah_03.png",
	"./data/TEXTURE/savannah/savannah_04.png",
	"./data/TEXTURE/savannah/savannah_05.png",

	// ��
	"./data/TEXTURE/town/town_01.png",

	// ��
	"./data/TEXTURE/forest/dirt.png",
	"./data/TEXTURE/town/asphalt.png",
	"./data/TEXTURE/desert/sand.png",
	"./data/TEXTURE/glacier/ice.png",
	"./data/TEXTURE/savannah/grassfield.png",
	"./data/TEXTURE/waterside/water.png",

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
	"./data/TEXTURE/stumbler/cuctus.png",
	"./data/TEXTURE/stumbler/iceberg.png",
	"./data/TEXTURE/stumbler/icicle.png",
	"./data/TEXTURE/stumbler/nuts.png",
	"./data/TEXTURE/stumbler/nuts_reverse.png",
	"./data/TEXTURE/stumbler/sandstone.png",
	"./data/TEXTURE/stumbler/bee.png",
	"./data/TEXTURE/stumbler/huneycomb.png",
	"./data/TEXTURE/stumbler/needle.png",

	// �^�[�Q�b�g
	"./data/TEXTURE/goal/tv_off.png",
	"./data/TEXTURE/goal/tv_on.png",
	"./data/TEXTURE/goal/tv_off.png",
	"./data/TEXTURE/goal/tv_on.png",
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
	"./data/TEXTURE/assy/truck.png",
	"./data/TEXTURE/assy/dolly.png",
	"./data/TEXTURE/assy/tram.png",
	"./data/TEXTURE/assy/log.png",
	"./data/TEXTURE/assy/bathtub.png",
	"./data/TEXTURE/assy/sleigh.png",

	//�L�������C�N���UI
	"./data/TEXTURE/select/assy_option.png",
	"./data/TEXTURE/select/costume_option.png",
	"./data/TEXTURE/select/option_details.png",
	"./data/TEXTURE/select/select_cursor.png",
	"./data/TEXTURE/select/select_frame.png",
	"./data/TEXTURE/select/select_bg.png",
	"./data/TEXTURE/select/costume/cos_none.png",
	"./data/TEXTURE/select/costume/cos_knight.png",
	"./data/TEXTURE/select/costume/cos_santa.png",
	"./data/TEXTURE/select/costume/cos_swimwear.png",
	"./data/TEXTURE/select/costume/cos_ninja.png",
	"./data/TEXTURE/select/costume/cos_fighter.png",
	"./data/TEXTURE/select/message/costume/cos_mes_none.png",
	"./data/TEXTURE/select/message/costume/cos_mes_knight.png",
	"./data/TEXTURE/select/message/costume/cos_mes_santa.png",
	"./data/TEXTURE/select/message/costume/cos_mes_swim.png",
	"./data/TEXTURE/select/message/costume/cos_mes_ninja.png",
	"./data/TEXTURE/select/message/costume/cos_mes_fighter.png",
	"./data/TEXTURE/select/vehicle/veh_trum.png",
	"./data/TEXTURE/select/vehicle/veh_dolly.png",
	"./data/TEXTURE/select/vehicle/veh_log.png",
	"./data/TEXTURE/select/vehicle/veh_bathtub.png",
	"./data/TEXTURE/select/vehicle/veh_sleigh.png",
	"./data/TEXTURE/select/vehicle/veh_truck.png",
	"./data/TEXTURE/select/message/vehicle/veh_mes_trum.png",
	"./data/TEXTURE/select/message/vehicle/veh_mes_dolly.png",
	"./data/TEXTURE/select/message/vehicle/veh_mes_log.png",
	"./data/TEXTURE/select/message/vehicle/veh_mes_bathtub.png",
	"./data/TEXTURE/select/message/vehicle/veh_mes_sleigh.png",
	"./data/TEXTURE/select/message/vehicle/veh_mes_truck.png",
	"./data/TEXTURE/select/hyphen_3.png",
	"./data/TEXTURE/select/hyphen_4.png",
	"./data/TEXTURE/select/hyphen_5.png",
	"./data/TEXTURE/select/char_sel_back_01.png",
	"./data/TEXTURE/select/char_sel_chip_01.png",

	// �����f��
	"./data/TEXTURE/number/coron.png",
	"./data/TEXTURE/number/coron_half.png",
	"./data/TEXTURE/number/number.png",
};

// �}�b�v
const char* MAP_PATH[] =
{
	"./data/MAP/stage1-1.txt"
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ÓI�ϐ�
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DTEXTURE9	CImport::m_tex[TEX_MAX];
CMapData*			CImport::m_map[STAGE_MAX];

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

	//----------------------------
	// �}�b�v
	//----------------------------
	for(int cnt = 0; cnt < STAGE_MAX; ++cnt)
	{
		m_map[cnt] = CMapData::Create(MAP_PATH[cnt]);
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

	//----------------------------
	// �}�b�v
	//----------------------------
	for(int cnt = 0; cnt < STAGE_MAX; ++cnt)
	{
		// �e�N�X�`���̊J��
		SAFE_END(m_map[cnt]);
	}
}
