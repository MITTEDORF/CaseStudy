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

	// �R���X�g���N�^�E�f�X�g���N�^
	CThread();
	~CThread();


	// ����
	unsigned int Create(void *function);
	

	// �j��
	bool Release();



private:







	// parameter =================================


public:

	// static parameter


	// local parameter




private:

	// static parameter



	// local parameter


	// �X���b�h�n���h��
	HANDLE m_Thread;


};





#endif //__THREAD_H__