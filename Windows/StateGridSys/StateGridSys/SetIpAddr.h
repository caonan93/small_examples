#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetIpAddr 对话框

class CSetIpAddr : public CDialogEx
{
	DECLARE_DYNAMIC(CSetIpAddr)

public:
	CSetIpAddr(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetIpAddr();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_SetAddress;
	CEdit m_edUserName;
	CEdit m_edPassWD;
	CEdit m_edPort;
	afx_msg void OnBnClickedButton2();
};
