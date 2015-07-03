//*****************************************************************************
//
// サウンド処理 [sound.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_SOUND_H_
#define _MY_SOUND_H_
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CSound
{
public:
	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,	// タイトルBGM
		SOUND_LABEL_GAMEBGM,		// ゲームBGM
		SOUND_LABEL_RESULTBGM,		// リザルトBGM
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound(){};
	~CSound(){};

	static CSound* Create(HWND wnd);
	HRESULT Init(HWND wnd);
	void Uninit(void);

	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:
	HRESULT CheckChunk(HANDLE file, DWORD format, DWORD *chunkSize, DWORD* chunkDataPosition);
	HRESULT ReadChunkData(HANDLE file, void* buffer, DWORD buffersize, DWORD bufferoffset);

	IXAudio2*				m_xAudio2;							// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice*	m_masteringVoice;					// マスターボイス
	IXAudio2SourceVoice*	m_sourceVoice[SOUND_LABEL_MAX];		// ソースボイス
	BYTE*					m_dataAudio[SOUND_LABEL_MAX];		// オーディオデータ
	DWORD					m_sizeAudio[SOUND_LABEL_MAX];		// オーディオデータサイズ

};

//=============================================================================
#endif
