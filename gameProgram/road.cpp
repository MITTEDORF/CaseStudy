//=============================================================================
//
// Road�N���X [road.cpp]
// Author : Ken Matsuura
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "road.h"

#define ROAD_SIZE	(64.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRoad::CRoad(int priority, OBJTYPE objType) : CScene2D(priority, objType)
{
	m_next = NULL;
	m_prev = NULL;
}

//=============================================================================
// ����
//=============================================================================
CRoad* CRoad::Create(LPDIRECT3DDEVICE9 device, ROAD_DATA data, POINT_TYPE pointType)
{
	CRoad* pointer = new CRoad;
	pointer->Init(device, (CImport::TEXTURES)(CImport::DIRT + data.type), pointType);
	// �f�[�^�����ɍ��W�̕ύX
	pointer->SetSize(ROAD_SIZE, ROAD_SIZE);
	pointer->SetHitSize(D3DXVECTOR2(ROAD_SIZE, ROAD_SIZE));
	pointer->SetPos(data.Index.x * 64, SCREEN_HEIGHT - ((data.Index.y * 64) + 64));
	return pointer;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CRoad::Init(LPDIRECT3DDEVICE9 device, CImport::TEXTURES texture, POINT_TYPE pointType)
{
	HRESULT hr;

	// �p�����̏������Ăяo��
	hr = CScene2D::Init(device, texture, pointType);
	// �p�����̏������Ɏ��s������
	if(hr == E_FAIL)
	{
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CRoad::Uninit(void)
{
	// �p�����̏I�������Ăяo��
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CRoad::Update(void)
{
	// �p�����̍X�V�����Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CRoad::Draw(void)
{
	// �p�����̕`�揈���Ăяo��
	CScene2D::Draw();

	// �����蔻��{�b�N�X�̕`��
	DrawHitBox();
}

//=============================================================================
// �����Ԃ�����
//=============================================================================
D3DXVECTOR2	CRoad::ReturnPush(D3DXVECTOR2 pos, D3DXVECTOR2 size, POINT_TYPE pointType)
{
	// ������4���_�Ƒ����4���_���v�Z
	D3DXVECTOR2 self[4], target[4], temp, rtn;

	temp = (m_size - m_hitSize)/2;

	// �����̒��_�����v�Z
	if(m_pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		self[0].x = m_pos.x + m_hitOffset.x + temp.x;				self[0].y = m_pos.y + m_hitOffset.y + temp.y;
		self[1].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[1].y = m_pos.y + m_hitOffset.y + temp.y;
		self[2].x = m_pos.x + m_hitOffset.x + m_size.x - temp.x;	self[2].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
		self[3].x = m_pos.x + m_hitOffset.x + temp.x;				self[3].y = m_pos.y + m_hitOffset.y + m_size.y - temp.y;
	}
	else if(m_pointType == POINT_CENTER)	// ���S���_�̏ꍇ
	{
		self[0].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[0].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[1].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[1].y = m_pos.y + m_hitOffset.y - m_hitSize.y/2;
		self[2].x = m_pos.x + m_hitOffset.x + m_hitSize.x/2;	self[2].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
		self[3].x = m_pos.x + m_hitOffset.x - m_hitSize.x/2;	self[3].y = m_pos.y + m_hitOffset.y + m_hitSize.y/2;
	}

	// �n���ꂽ��񂩂璸�_���v�Z
	if(pointType == POINT_LEFTTOP)		// ���㌴�_�̏ꍇ
	{
		target[0].x = pos.x;				target[0].y = pos.y;
		target[1].x = pos.x + size.x;		target[1].y = pos.y;
		target[2].x = pos.x + size.x;		target[2].y = pos.y + size.y;
		target[3].x = pos.x;				target[3].y = pos.y + size.y;
	}
	else if(pointType == POINT_CENTER)	// ���S���_�̏ꍇ
	{
		target[0].x = pos.x - size.x/2;		target[0].y = pos.y - size.y/2;
		target[1].x = pos.x + size.x/2;		target[1].y = pos.y - size.y/2;
		target[2].x = pos.x + size.x/2;		target[2].y = pos.y + size.y/2;
		target[3].x = pos.x - size.x/2;		target[3].y = pos.y + size.y/2;
	}

	rtn = D3DXVECTOR2(0.0f, 0.0f);

	// ���ɓ����蔻��
	if( (self[0].x < target[1].x) &&
		(target[0].x < self[1].x) &&
		(self[0].y < target[3].y) &&
		(target[0].y < self[3].y) )
	{
		/*if(self[0].x < target[0].x && self[1].x > target[0].x && )
			rtn.x = self[0].x - target[1].x;
		if(self[0].x > target[1].x && self[1].x > target[1].x)
			rtn.x = self[1].x - target[0].x;
		if(self[0].y < target[3].y)
			rtn.y = self[0].y - target[3].y;
		if(self[3].y > target[0].y)
			rtn.y = self[3].y - target[0].y;*/
	}

	return rtn;
}

// End of File