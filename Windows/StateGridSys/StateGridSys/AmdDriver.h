#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAmdDriver �Ի���

class CAmdDriver : public CDialogEx
{
	DECLARE_DYNAMIC(CAmdDriver)

public:
	CAmdDriver(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAmdDriver();

// �Ի�������
	enum { IDD = IDD_AMID_DRIVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
