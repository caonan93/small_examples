
// StateGridSys.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Dao.h"

// CStateGridSysApp: 
// �йش����ʵ�֣������ StateGridSys.cpp
//

class CStateGridSysApp : public CWinApp
{
public:
	CStateGridSysApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	CDao m_database;
	CString m_edName;
	CString m_edPassWD;
	CString m_edIPAddr;
	CString m_edPort;
	afx_msg void OnSetIpAddr();
};

extern CStateGridSysApp theApp;