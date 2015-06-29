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
	int cate;
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
	// データメモリ確保
	//----------------------------
	m_bgData	 = new BG_DATA[m_bgSize];
	m_roadData	 = new ROAD_DATA[m_roadSize];
	m_stumData	 = new STUM_DATA[m_stumSize];
	m_targetData = new TARGET_DATA[m_targetSize];

	//----------------------------
	// 背景データ取得
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'b') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %d", &cate, &type);

			int typeTop = 0;
			switch(cate)
			{
			case 0:
				typeTop = TYPE_FOREST_01;
				break;

			case 1:
				typeTop = TYPE_TWON_01;
				break;

			default:
				break;
			}

			m_bgData[cnt].type = (BG_TYPE)(typeTop + type);
			m_bgData[cnt].index = cnt;

			cnt++;
		}
	}

	//----------------------------
	// 道データ取得
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 'r') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_DIRT;

			m_roadData[cnt].type = (ROAD_TYPE)(typeTop + type);
			m_roadData[cnt].Index = index;

			cnt++;
		}
	}

	//----------------------------
	// 障害物データ取得
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 's') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_SIGNBOARD;

			m_stumData[cnt].type = (STUM_TYPE)(typeTop + type);
			m_stumData[cnt].Index = index;

			cnt++;
		}
	}

	//----------------------------
	// ターゲットデータ取得
	//----------------------------
	cnt = 0;
	fseek(fp, 0, SEEK_SET);

	while((c = fgetc(fp)) != EOF)
	{
		if((c == 't') && ((c = fgetc(fp)) == ' '))
		{
			fscanf(fp, "%d %f %f", &type, &index.x, &index.y);

			int typeTop = TYPE_TARGET_OFF;

			m_targetData[cnt].type = (TARGET_TYPE)(typeTop + type);
			m_targetData[cnt].Index = index;

			cnt++;
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
