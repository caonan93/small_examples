
// WinProcessManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyWinProcessManagerApp:
// �йش����ʵ�֣������ WinProcessManager.cpp
//

class CMyWinProcessManagerApp : public CWinApp
{
public:
	CMyWinProcessManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyWinProcessManagerApp theApp;
