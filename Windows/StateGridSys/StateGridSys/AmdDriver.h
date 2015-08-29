#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAmdDriver 对话框

class CAmdDriver : public CDialogEx
{
	DECLARE_DYNAMIC(CAmdDriver)

public:
	CAmdDriver(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAmdDriver();

// 对话框数据
	enum { IDD = IDD_AMID_DRIVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listInfo;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_edName;
	void Search();
	virtual BOOL OnInitDialog();
	void InitDialog();
};
