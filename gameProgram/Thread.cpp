// Thread.cpp
// Author:RYUYA NAKAMURA



// include 
#include <process.h>
#include "manager.h"
#include "main.h"
#include "Thread.h"




// variable





// function




// CThread()
// �R���X�g���N�^
CThread::CThread()
{

}



// ~CThread()
// �f�X�g���N�^
CThread::~CThread()
{

}



// Create()
// ����
unsigned int CThread::Create(void *function)
{

	// �ϐ��錾
	unsigned int ThreadID;


	// �X���b�h����
	m_Thread = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall*)(void*))function, NULL, 0, &ThreadID);


	// �X���b�h�����`�F�b�N
	if (m_Thread == 0)
	{
		return 0;
	}


	// �X���b�h�̏����D��x��ݒ�
	int ThreadPriority = GetThreadPriority(m_Thread);
	SetThreadPriority(m_Thread, THREAD_PRIORITY_TIME_CRITICAL);
	ThreadPriority = GetThreadPriority(m_Thread);


	// ���^�[��
	return (unsigned int)m_Thread;
}



// Release()
// �X���b�h�j��
bool CThread::Release()
{

	// �ϐ��錾
	HRESULT Result;


	// �X���b�h�I���m�F
	if (m_Thread != NULL)
	{
		// �X���b�h���̏����̏I���҂�
		WaitForSingleObject(m_Thread, INFINITE);

		// �X���b�h�j��
		Result = CloseHandle(m_Thread);

	}
	else
	{
		// ���^�[��
		return false;
	}

	// ���^�[��
	return SUCCEEDED(Result);
}


// EOF