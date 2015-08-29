#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAmdClass 对话框

class CAmdClass : public CDialogEx
{
	DECLARE_DYNAMIC(CAmdClass)

public:
	CAmdClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAmdClass();

// 对话框数据
	enum { IDD = ID_AMID_CLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	CEdit m_edClassName;
	CListCtrl m_lsInfo;
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
public:
	void InitDialog();
	void search();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CEdit m_edClassEdit;
	bool ISAddData(CString &str);
};
