
// �ڴ�����㷨.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C�ڴ�����㷨App: 
// �йش����ʵ�֣������ �ڴ�����㷨.cpp
//

class C�ڴ�����㷨App : public CWinApp
{
public:
	C�ڴ�����㷨App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C�ڴ�����㷨App theApp;