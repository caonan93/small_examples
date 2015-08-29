#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CStatisticPer 对话框

class CStatisticPer : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticPer)

public:
	CStatisticPer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatisticPer();

// 对话框数据
	enum { IDD = ID_STATISTIC_PERSON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	// 本月所有员工排名
	CListCtrl m_listInfoSortPerMonth;
	virtual BOOL OnInitDialog();

	void InitPerMonthDialog();
	void Search();
	afx_msg void OnCbnSelchangeCombo5();
	// 个人分值详情
	CComboBox m_cbPersonDetial;
	void InitPersonScoreDeatil();
	void InitPeopleScoreSort();
	int m_ColumnNum;
	afx_msg void OnBnClickedButton2();
	void InitDriverDialog();
	afx_msg void OnCbnSelchangeCombo6();
	CComboBox m_cbDriver;
	void InitCBDriver();
	CDateTimeCtrl m_cbStart;
	CDateTimeCtrl m_cbEnd;
	void InitDriverSort();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	void InitPerMonthDialog_Deatil();
};
