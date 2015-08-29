#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// CStatisticClass �Ի���

class CStatisticClass : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticClass)

public:
	CStatisticClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisticClass();

// �Ի�������
	enum { IDD = ID_STATISTIC_CLASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	// ���༶��ѯ
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
