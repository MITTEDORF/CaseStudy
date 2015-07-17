//*****************************************************************************
//
// サウンド処理 [sound.cpp]
// Author :MAI TANABE
//
//*****************************************************************************

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルードファイル
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "sound.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// パラメータ構造体定義
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	char *pFilename;	// ファイル名
	bool bLoop;			// ループするかどうか
} PARAM;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 各音素材のパラメータ
const PARAM SOUND_PARAM[CSound::SOUND_LABEL_MAX] =
{
	{"data/SOUND/title.wav",	true},					// タイトルBGM
	{"data/SOUND/game.wav",		true},					// ゲームBGM
	{"data/SOUND/result_clear.wav",	false},				// リザルトクリアBGM
	{"data/SOUND/result_gameover.wav",	false},			// リザルトゲームオーバーBGM
	{"data/SOUND/stage_charcter_select.wav",	true},	// セレクトBGM
};

//=============================================================================
// 生成
//=============================================================================
CSound* CSound::Create(HWND wnd)
{
	CSound* pointer = new CSound;
	pointer->Init(wnd);

	return pointer;
}

//=============================================================================
// サウンドの初期化
//=============================================================================
HRESULT CSound::Init(HWND wnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_xAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(wnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}
	
	// マスターボイスの生成
	hr = m_xAudio2->CreateMasteringVoice(&m_masteringVoice);
	if(FAILED(hr))
	{
		MessageBox(wnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if(m_xAudio2)
		{
			// XAudio2オブジェクトの開放
			m_xAudio2->Release();
			m_xAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE file;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		file = CreateFile(SOUND_PARAM[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(file == INVALID_HANDLE_VALUE)
		{
			MessageBox(wnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(file, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(wnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVEファイルのチェック
		hr = CheckChunk(file, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(wnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(file, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(wnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if(dwFiletype != 'EVAW')
		{
			MessageBox(wnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// フォーマットチェック
		hr = CheckChunk(file, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(wnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(file, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(wnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(file, 'atad', &m_sizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(wnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		m_dataAudio[nCntSound] = (BYTE*)malloc(m_sizeAudio[nCntSound]);
		hr = ReadChunkData(file, m_dataAudio[nCntSound], m_sizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(wnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// ソースボイスの生成
		hr = m_xAudio2->CreateSourceVoice(&m_sourceVoice[nCntSound], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(wnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_sizeAudio[nCntSound];
		buffer.pAudioData = m_dataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = 0;

		// オーディオバッファの登録
		m_sourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}

//=============================================================================
// サウンドの終了処理
//=============================================================================
void CSound::Uninit(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(m_sourceVoice[nCntSound])
		{
			// 一時停止
			m_sourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			m_sourceVoice[nCntSound]->DestroyVoice();
			m_sourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(m_dataAudio[nCntSound]);
			m_dataAudio[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	m_masteringVoice->DestroyVoice();
	m_masteringVoice = NULL;
	
	if(m_xAudio2)
	{
		// XAudio2オブジェクトの開放
		m_xAudio2->Release();
		m_xAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// セグメント再生(停止)
//=============================================================================
HRESULT CSound::Play(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio[label];
	buffer.pAudioData = m_dataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = 0;

	// ループ処理
	if(SOUND_PARAM[label].bLoop)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE; 
	}

	// 状態取得
	m_sourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_sourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_sourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_sourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_sourceVoice[label]->Start(0);

	return S_OK;
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::Stop(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_sourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		m_sourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_sourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::Stop(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(m_sourceVoice[nCntSound])
		{
			// 一時停止
			m_sourceVoice[nCntSound]->Stop(0);
		}
	}
}

//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE file, DWORD format, DWORD *chunkSize, DWORD* chunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(file, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(file, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(file, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(file, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(file, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*chunkSize         = dwChunkDataSize;
			*chunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE file, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(file, bufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(file, buffer, buffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

