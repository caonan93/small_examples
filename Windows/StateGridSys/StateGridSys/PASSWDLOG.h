#pragma once
#include "afxwin.h"


// CPASSWDLOG 对话框

class CPASSWDLOG : public CDialogEx
{
	DECLARE_DYNAMIC(CPASSWDLOG)

public:
	CPASSWDLOG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPASSWDLOG();

// 对话框数据
	enum { IDD = IDD_PASSWD_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg LRESULT GetPassWDMessage(WPARAM wParam, LPARAM lParam);
	void GetStringData(CString &stringData, CString &stringWorkID, int key);
	CString m_stringData;
	CEdit m_edShow;
	CEdit m_edUserLogIn;
	CEdit m_edPassWD;
	CEdit m_edPassWDReapt;
	CString m_stringWorkID;
	int m_ClassID;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	void InitDialog();
	virtual BOOL OnInitDialog();
};
