//*****************************************************************************
//
// �T�E���h���� [sound.h]
// Author :MAI TANABE
//
//*****************************************************************************

#ifndef _MY_SOUND_H_
#define _MY_SOUND_H_
//=============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h�t�@�C��
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CSound
{
public:
	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,	// �^�C�g��BGM
		SOUND_LABEL_GAMEBGM,		// �Q�[��BGM
		SOUND_LABEL_RESULTBGM,		// ���U���gBGM
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

	IXAudio2*				m_xAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice*	m_masteringVoice;					// �}�X�^�[�{�C�X
	IXAudio2SourceVoice*	m_sourceVoice[SOUND_LABEL_MAX];		// �\�[�X�{�C�X
	BYTE*					m_dataAudio[SOUND_LABEL_MAX];		// �I�[�f�B�I�f�[�^
	DWORD					m_sizeAudio[SOUND_LABEL_MAX];		// �I�[�f�B�I�f�[�^�T�C�Y

};

//=============================================================================
#endif
