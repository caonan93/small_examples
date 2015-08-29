#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CWorkRecord 对话框

class CWorkRecord : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkRecord)

public:
	CWorkRecord(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkRecord();

// 对话框数据
	enum { IDD = IDD_WORK_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	//afx_msg LRESULT onMSG(WPARAM wparam, LPARAM lparam);
	CDateTimeCtrl m_dtWorkDate;
	CComboBox m_cbElecLv;
	CComboBox m_cbCar;
	CComboBox m_cbOperate;
	CComboBox m_cbOperaTime;
	CComboBox m_cbDriver;
	CComboBox m_cbWork1;
	CComboBox m_cbWork2;
	CComboBox m_cbWork3;
	CEdit m_edWDetail;
	void GetData(CString &data1);//获取数据
	CString m_ClassID;
	void InitDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnCbnSelchangeCombo7();
	int m_iWorker1;
	int m_iWorker2;
	int m_iWorker3;
	double CalculateScore(double ratio, CString OperateID, int Time);
	bool InitWorkCtrl(CComboBox *work, int workID, double radio);
	bool CheckMessageBox(CString strInfoName, CString strCheck);
	void InitDriver();
	bool SaveDriveInfo();
};
