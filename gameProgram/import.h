//*****************************************************************************
//
// CImport�N���X [import.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_IMPORT_H
#define _MY_IMPORT_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CImport
{
public:
	typedef enum
	{
		NONE = 0,

		// �V�X�e��
		FADE,
		VERSION,

		// ���S
		TITLELOGO,

		// ��
		SKY_BG,
		SKY1,
		SKY2,
		SKY3,
		SKY4,
		SKY5,

		// �X
		FOREST_01,

		// ��
		TOWN_01,

		// ��
		DIRT,
		ASPHALT,

		// ��Q��
		SIGNBOARD,
		LION,
		ROCK,
		LOG_LEFT,
		LOG_CENTER,
		LOG_RIGHT,
		BIRD,
		DUSTBOX,
		BARRICADE,

		// �^�[�Q�b�g
		GOAL_OFF,
		GOAL_ON,
		GOAL_CLEAR,

		// �v���C���[
		PLAYER_WAIT,
		PLAYER_ATTACK,
		PLAYER_LIGHT,
		PLAYER_GOODMOOD,
		PLAYER_BADMOOD,

		//�p�[�e�B�N��
		PARTICLE_YELLOW_SMALL,
		PARTICLE_DAIDAI_SMALL,
		PARTICLE_WHITE_SMALL,

		// ��蕨
		ASSY_TRAM,

		TEX_MAX
	} TEXTURES;

	CImport();
	~CImport(){};

	static	CImport* Create(LPDIRECT3DDEVICE9 device);
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);

	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURES tex){return m_tex[tex];}

private:
	static LPDIRECT3DTEXTURE9 m_tex[TEX_MAX];;
};

//=============================================================================
#endif