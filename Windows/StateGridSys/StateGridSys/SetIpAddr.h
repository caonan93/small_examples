#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetIpAddr �Ի���

class CSetIpAddr : public CDialogEx
{
	DECLARE_DYNAMIC(CSetIpAddr)

public:
	CSetIpAddr(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetIpAddr();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_SetAddress;
	CEdit m_edUserName;
	CEdit m_edPassWD;
	CEdit m_edPort;
	afx_msg void OnBnClickedButton2();
};
