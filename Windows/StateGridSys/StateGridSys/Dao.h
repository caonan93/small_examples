#pragma once
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","ADOEOF") rename("BOF","ADOBOF")
#define DATEBASE_TYPE_ACCESS	0
#define DATEBASE_TYPE_SQL2000   1
#define DATEBASE_TYPE_SQL2005   2
#define DATEBASE_TYPE_OTHER		3
#include <atlimage.h>

class CDao
{
public:
	CDao(void);
	BOOL InitCom();        //��ʼ��com���
	void releaseCom();     //�ͷ�com���
public:
	~CDao(void);

	//��ʼ�����ݿ�
	BOOL OpenDateBase(CString strDateBaseName,int nDataType,CString strUser,CString strPassWord,CString strIP); 
	//��ȡ����
	BOOL GetData(CString strSql,CString *strQueryCloum,int nCloumNum,CStringArray& strDataValue);
	CString DataToCStringType(VARIANT Var);

	BOOL GetImgData(CString strSql,CString *strQueryCloum,int nCloumNum,CImage* pImg);

	//�������
	BOOL AddData(CString strTableName,CStringArray& strCloumValue,int nCloumNum,CString* pstrReturnID = NULL);
	BOOL CStringToDataType(CString strValue,int nDataType, VARIANT *pVar);
	BOOL SaveImg(CString strPath,VARIANT *pVar);

	//�޸�����
	BOOL EditData(CString strSQL, int nColumnNum, CString* pStrFieldName, CStringArray &saValue);

	//ɾ������
	BOOL DeleteData(CString strSQL);

public:
	_ConnectionPtr m_pConnection;  //�������ݿ��ָ�����
	_RecordsetPtr  m_pRecordset;   //������¼����ָ�����
	_CommandPtr    m_pCommandmsg;  //SQL�����ָ�����
private:
	BOOL m_binitComFlag;
	CString m_strErrorMsg;         //������Ϣ
	CString m_strConnect;            //���Ӵ�
};
