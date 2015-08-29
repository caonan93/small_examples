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
	BOOL InitCom();        //初始化com组件
	void releaseCom();     //释放com组件
public:
	~CDao(void);

	//初始化数据库
	BOOL OpenDateBase(CString strDateBaseName,int nDataType,CString strUser,CString strPassWord,CString strIP); 
	//获取数据
	BOOL GetData(CString strSql,CString *strQueryCloum,int nCloumNum,CStringArray& strDataValue);
	CString DataToCStringType(VARIANT Var);

	BOOL GetImgData(CString strSql,CString *strQueryCloum,int nCloumNum,CImage* pImg);

	//添加数据
	BOOL AddData(CString strTableName,CStringArray& strCloumValue,int nCloumNum,CString* pstrReturnID = NULL);
	BOOL CStringToDataType(CString strValue,int nDataType, VARIANT *pVar);
	BOOL SaveImg(CString strPath,VARIANT *pVar);

	//修改数据
	BOOL EditData(CString strSQL, int nColumnNum, CString* pStrFieldName, CStringArray &saValue);

	//删除数据
	BOOL DeleteData(CString strSQL);

public:
	_ConnectionPtr m_pConnection;  //连接数据库的指针对象
	_RecordsetPtr  m_pRecordset;   //操作记录集的指针对象
	_CommandPtr    m_pCommandmsg;  //SQL命令的指针对象
private:
	BOOL m_binitComFlag;
	CString m_strErrorMsg;         //错误信息
	CString m_strConnect;            //连接串
};
