#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSysCar �Ի���

class CSysCar : public CDialogEx
{
	DECLARE_DYNAMIC(CSysCar)

public:
	CSysCar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysCar();

// �Ի�������
	enum { IDD = ID_SYS_CAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	// ���ƺ�
	CListCtrl m_lsCarInfo;
	// ��ѹ�ȼ�
	CListCtrl m_lsElecLeveInfo;
	// ���복�ƺ�
	CEdit m_edCarNum;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	bool ISAddData(CString &str);
	// �����ѹ�ȼ�
	CEdit m_edElecLeve;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
public:
	void InitElec();
	void InitCar();
	virtual BOOL OnInitDialog();
	void SearchCar();
	void SearchELEC();
};
