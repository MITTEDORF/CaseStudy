//*****************************************************************************
//
// CNLoad�N���X [nowload.h]
// Author :KAZUMA OOIGAWA
//
//*****************************************************************************

#ifndef _NOW_LOAD_H_
#define _NOW_LOAD_H_
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <process.h>
#include "main.h"
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �\���̒�`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CThrObj;
class CLIcon;
class CNLoad
{
public:
	static const float UP_MAX;
	static const float DOWN_MAX;

	CNLoad();
	~CNLoad(){};

	static	CNLoad* Create(LPDIRECT3DDEVICE9 device);
	HRESULT	Init(LPDIRECT3DDEVICE9 device);
	void	Uninit(void);


	bool	  GetUpDown( void ){ return m_up_down;}
	void	  SetUpDown( bool up_down ){ m_up_down = up_down;}

	static bool GetEndThread( void ){ return m_EndThread;}//(����)
	static void SetEndThread( bool endthread ){ m_EndThread = endthread;}//(����)
	CLIcon* GetLIcon( void ){ return m_LoadIcon ;}
	void	SetLIcon( CLIcon* load_icon ){ m_LoadIcon = load_icon ;}
	CNLoad* GetThis( void ){ return m_now_load ;}
	void	SetThis( CNLoad* now_load ){ m_now_load = now_load ;}
private:
	LPDIRECT3DDEVICE9 m_device;
	static volatile bool		m_EndThread;//�X���b�h�I���p�t���O(����)

	bool		m_flg;
	bool		m_up_down;
	HANDLE		m_ThrHandle;//�X���b�h�I���҂��p�n���h��(����)
	CLIcon*		m_LoadIcon;
	CNLoad*		m_now_load;
};

//=============================================================================
#endif