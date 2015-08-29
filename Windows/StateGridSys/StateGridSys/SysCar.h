#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSysCar 对话框

class CSysCar : public CDialogEx
{
	DECLARE_DYNAMIC(CSysCar)

public:
	CSysCar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysCar();

// 对话框数据
	enum { IDD = ID_SYS_CAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();
public:
	// 车牌号
	CListCtrl m_lsCarInfo;
	// 电压等级
	CListCtrl m_lsElecLeveInfo;
	// 输入车牌号
	CEdit m_edCarNum;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	bool ISAddData(CString &str);
	// 输入电压等级
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
