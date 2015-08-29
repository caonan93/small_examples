#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// CStatisticClass 对话框

class CStatisticClass : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticClass)

public:
	CStatisticClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatisticClass();

// 对话框数据
	enum { IDD = ID_STATISTIC_CLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	// 按班级查询
	CComboBox m_cbClassSel;
	CDateTimeCtrl m_dtStart;
	CDateTimeCtrl m_dtEnd;
	void InitDialogClass();
	void InitSelClass();
	virtual BOOL OnInitDialog();
	CListCtrl m_listInfo;
	afx_msg void OnBnClickedButton4();
	void InitClassSort();
	int m_ColumnNum;
};
