//*****************************************************************************
//
// CMapDataクラス [mapData.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "mapData.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=============================================================================
// コンストラクタ
//=============================================================================
CMapData::CMapData(void)
{
	m_bgSize	 = 0;
	m_roadSize	 = 0;
	m_stumSize	 = 0;
	m_targetSize = 0;

	m_bgData	 = nullptr;
	m_roadData	 = nullptr;
	m_stumData	 = nullptr;
	m_targetData = nullptr;
}

//=============================================================================
// 生成
//=============================================================================
CMapData* CMapData::Create(const char* file)
{
	CMapData* pointer = new CMapData;
	if(FAILED(pointer->Init(file)))
	{
		MessageBox(NULL, "マップデータファイルがありません", "MapData", MB_OK);
	}
	return pointer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CMapData::Init(const char* file)
{
	char c;
	int cnt;
	int typeTop;
	int type;
	D3DXVECTOR2 index;

	//----------------------------
	// ファイル読み込み開始
	//----------------------------
	FILE* fp = fopen(file, "rt");

	if(fp == nullptr)
	{
		return E_FAIL;
	}

	//----------------------------
	// データ数取得
	//----------------------------
	fseek(fp, 0, SEEK_SET);
	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'n') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp,
					"%d %d %d %d",
					&m_bgSize, &m_roadSize, &m_stumSize, &m_targetSize);
		}
	}

	//----------------------------
	// 背景データ取得
	//----------------------------
	if(m_bgSize > 0)
	{
		m_bgData = new BG_DATA[m_bgSize];
		typeTop = TYPE_FOREST_01;
		cnt		= 0;
		fseek(fp, 0, SEEK_SET);

		while((c = fgetc(fp)) != EOF)
		{
			if((c == 'b') && ((c = fgetc(fp)) == ' '))
			{
				fscanf(fp, "%d", &type);

				m_bgData[cnt].type = (BG_TYPE)(typeTop + type);
				m_bgData[cnt].index = cnt;

				cnt++;
			}
		}
	}

	//----------------------------
	// 道データ取得
	//----------------------------
	if(m_roadSize > 0)
	{
		m_roadData	 = new ROAD_DATA[m_roadSize];
		typeTop = TYPE_DIRT;
		cnt		= 0;
		fseek(fp, 0, SEEK_SET);

		while((c = fgetc(fp)) != EOF)
		{
			if((c == 'r') && ((c = fgetc(fp)) == ' '))
			{
				fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

				m_roadData[cnt].type = (ROAD_TYPE)(typeTop + type);
				m_roadData[cnt].Index = index;

				cnt++;
			}
		}
	}

	//----------------------------
	// 障害物データ取得
	//----------------------------
	if(m_stumSize > 0)
	{
		m_stumData	 = new STUM_DATA[m_stumSize];
		typeTop = TYPE_SIGNBOARD;
		cnt		= 0;
		fseek(fp, 0, SEEK_SET);

		while((c = fgetc(fp)) != EOF)
		{
			if((c == 's') && ((c = fgetc(fp)) == ' '))
			{
				fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

				m_stumData[cnt].type = (STUM_TYPE)(typeTop + type);
				m_stumData[cnt].Index = index;

				cnt++;
			}
		}
	}

	//----------------------------
	// ターゲットデータ取得
	//----------------------------
	if(m_targetSize > 0)
	{
		m_targetData = new TARGET_DATA[m_targetSize];
		typeTop = TYPE_TARGET_OFF;
		cnt		= 0;
		type	= 0;
		index	= D3DXVECTOR2(0.0f, 0.0f);
		fseek(fp, 0, SEEK_SET);

		while((c = fgetc(fp)) != EOF)
		{
			if((c == 't') && ((c = fgetc(fp)) == ' '))
			{
				fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

				m_targetData[cnt].type = (TARGET_TYPE)(typeTop + type);
				m_targetData[cnt].Index = index;

				cnt++;
			}
		}
	}

	//----------------------------
	// ファイル読み込み終了
	//----------------------------
	// 読み込みファイル
	fclose(fp);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CMapData::Uninit(void)
{
	SAFE_DELETE_ARRAY(m_bgData);
	SAFE_DELETE_ARRAY(m_roadData);
	SAFE_DELETE_ARRAY(m_stumData);
	SAFE_DELETE_ARRAY(m_targetData);
}
