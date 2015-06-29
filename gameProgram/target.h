//*****************************************************************************
//
// target�N���X [target.h]
// Author : KEN MATSUURA
//
//*****************************************************************************

#ifndef _TARGET_H
#define _TARGET_H
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "scene2D.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �\����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �摜�f�[�^����
typedef enum{
	TYPE_NULL
}TARGET_TYPE;

// ��Q�����
typedef struct{
	TARGET_TYPE type;
	D3DXVECTOR2 Index;
}TARGET_DATA;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CTarget : public CScene2D
{
public:
	CTarget(int priority = PRIORITY_MAX - 1, OBJTYPE objType = OBJTYPE_2D);
	~CTarget(){};

	static	CTarget* Create(LPDIRECT3DDEVICE9 device, TARGET_DATA data, POINT_TYPE pointType);

	HRESULT	Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType);
	HRESULT	Init(LPDIRECT3DDEVICE9 device, const char* texture, POINT_TYPE pointType);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	// �X�N���[������
	void	Scroll(float scroll){m_pos.x -= scroll; CScene2D::SetVertexPolygon();}

	// ����Q���|�C���^�Z�b�g����
	void		SetTargetNext(CTarget* next){m_next = next;}
	// ����Q���|�C���^�Q�b�g����
	CTarget*	GetTargetNext(void){return m_next;}
	// �O��Q���|�C���^�Z�b�g����
	void		SetTargetPrev(CTarget* prev){m_prev = prev;}
	// �O��Q���|�C���^�Q�b�g����
	CTarget*	GetTargetPrev(void){return m_prev;}

protected:
	CTarget* m_next;						// ����Q���ւ̃|�C���^
	CTarget* m_prev;						// �O��Q���ւ̃|�C���^
};

//=============================================================================
#endif