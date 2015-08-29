#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSysOperate 对话框

class CSysOperate : public CDialogEx
{
	DECLARE_DYNAMIC(CSysOperate)

public:
	CSysOperate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysOperate();

// 对话框数据
	enum { IDD = ID_SYS_OPERTECLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	void InitDialog();
	CListCtrl m_lsInfo;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	void Search();
	CEdit m_edAddName;
	CEdit m_edAddScore;
	CComboBox m_cbAddMaxTime;
	CComboBox m_cbNormalAddTime;
	CEdit m_edEditName;
	CEdit m_edEditScore;
	CComboBox m_cbEditMaxTime;
	CComboBox m_cbNormalEditTime;
	CEdit m_cbDelName;
	CEdit m_edDelScore;
	CEdit m_edDelMax;
	CEdit m_edDelNormal;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_iKey;
};
