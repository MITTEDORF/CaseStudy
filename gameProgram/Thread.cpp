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
// コンストラクタ
CThread::CThread()
{

}



// ~CThread()
// デストラクタ
CThread::~CThread()
{

}



// Create()
// 生成
unsigned int CThread::Create(void *function)
{

	// 変数宣言
	unsigned int ThreadID;


	// スレッド生成
	m_Thread = (HANDLE)_beginthreadex(NULL, 0, (unsigned int(__stdcall*)(void*))function, NULL, 0, &ThreadID);


	// スレッド生成チェック
	if (m_Thread == 0)
	{
		return 0;
	}


	// スレッドの処理優先度を設定
	int ThreadPriority = GetThreadPriority(m_Thread);
	SetThreadPriority(m_Thread, THREAD_PRIORITY_TIME_CRITICAL);
	ThreadPriority = GetThreadPriority(m_Thread);


	// リターン
	return (unsigned int)m_Thread;
}



// Release()
// スレッド破棄
bool CThread::Release()
{

	// 変数宣言
	HRESULT Result;


	// スレッド終了確認
	if (m_Thread != NULL)
	{
		// スレッド内の処理の終了待ち
		WaitForSingleObject(m_Thread, INFINITE);

		// スレッド破棄
		Result = CloseHandle(m_Thread);

	}
	else
	{
		// リターン
		return false;
	}

	// リターン
	return SUCCEEDED(Result);
}


// EOF