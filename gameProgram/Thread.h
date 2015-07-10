// Thread.h
// Author:RYUYA NAKAMURA


// include guard
#pragma once
#ifndef __THREAD_H__
#define __THREAD_H__


// class
class CThread
{



	// funciton ==================================

	// static funciton
public:


private:

	// local function

public:

	// コンストラクタ・デストラクタ
	CThread();
	~CThread();


	// 生成
	unsigned int Create(void *function);
	

	// 破棄
	bool Release();



private:







	// parameter =================================


public:

	// static parameter


	// local parameter




private:

	// static parameter



	// local parameter


	// スレッドハンドル
	HANDLE m_Thread;


};





#endif //__THREAD_H__