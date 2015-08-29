#include "StdAfx.h"

#include "Dao.h"

CDao::CDao(void)
{
	InitCom();
}

CDao::~CDao(void)
{
	releaseCom();
}

BOOL CDao::InitCom()        //初始化com组件
{
#if _WIN32_WINNT > 0x500
	//保留字（必须为null） ，加载方式 COINIT_MULTITHREADED多线程的方式加载
	// 以多线程方式打开com通道
	::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	::CoInitialize(NULL);
#endif
	m_binitComFlag = TRUE;
	return TRUE;
}
void CDao::releaseCom()     //释放com组件
{
	if (m_binitComFlag)
	{
		::CoUninitialize();
	}
}


BOOL CDao::OpenDateBase(CString strDateBaseName,int nDataType,CString strUser,CString strPassWord,CString strIP)
{
	//"colin",DATEBASE_TYPE_SQL2005,"sa","sa","127.0.0.1,2433"
	if (nDataType == DATEBASE_TYPE_ACCESS)
	{
		CFileFind filefind;
		BOOL bFind = filefind.FindFile(strDateBaseName);

		if (!bFind)
		{
			m_strErrorMsg = _T("找不到数据库");
			return FALSE;
		}
		else
		{
			m_strConnect.Format(_T("provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s"),strDateBaseName);
		}
	}
	else if (nDataType == DATEBASE_TYPE_SQL2000)
	{
		m_strConnect.Format(_T("Driver={SQL Server};Server=%s;Uid=%s;Pwd=%s;Database=%s"),strIP,strUser,strPassWord,strDateBaseName);
	}
	else if (nDataType == DATEBASE_TYPE_SQL2005)
	{
		m_strConnect.Format(_T("Driver={SQL Server};Server=%s;Uid=%s;Pwd=%s;Database=%s"),strIP,strUser,strPassWord,strDateBaseName);
	}
	else
	{
		m_strErrorMsg = _T("没有合适的连库串");
		return FALSE;
	}


	//实例化指针对象
	HRESULT hRes;
	//把CString转换成com组件里的字符串变量
	_bstr_t bstrConnection(m_strConnect);
	_bstr_t bstrUser(strUser);
	_bstr_t bstrPassword(strPassWord);

	try
	{
		//创建连接对象 序列码
		hRes = m_pConnection.CreateInstance(__uuidof(Connection));
		if (!SUCCEEDED(hRes))
		{
			m_strErrorMsg = _T("实例化连接指针对象失败");
			return FALSE;
		}

		//连接数据库(连库串，用户名，密码,打开方式)
		//字符串要用的是com组件的字符串 adModeShareDenyNone多用户共同可以访问一个数据库
		hRes = m_pConnection->Open(bstrConnection,bstrUser,bstrPassword,adModeShareDenyNone);
		if (!SUCCEEDED(hRes))
		{
			m_strErrorMsg = _T("打开数据库失败");
			return FALSE;
		}

		//实例化数据集指针对象
		hRes = m_pRecordset.CreateInstance(__uuidof(Recordset));
		if (!SUCCEEDED(hRes))
		{
			m_strErrorMsg = _T("实例化数据集指针对象失败");
			return FALSE;
		}
		//实例化命令集指针对象
		hRes = m_pCommandmsg.CreateInstance(__uuidof(Command));
		if (!SUCCEEDED(hRes))
		{
			m_strErrorMsg = _T("实例化命令集指针对象失败");
			return FALSE;
		}

	}catch(_com_error *e)
	{
		AfxMessageBox(e->Description());
		m_strErrorMsg.Format(_T("%s"),e->Description());
		return FALSE;
	}

	return TRUE;
}


BOOL CDao::GetData(CString strSql,CString *strQueryCloum,int nCloumNum,CStringArray& strDataValue)
{
	HRESULT het;
	//_bstr_t    字符串    		_variant_t 多种数据类型集合 vt类型   ..value值								//com
	_bstr_t bstrSql = strSql;				//执行sql
	_bstr_t bstrConnect = m_strConnect;		//连库串
	_bstr_t bstrQueryCloum;					//列名

	Fields *fields;
	FieldPtr fieldPtr;


	CString strValue;
	_variant_t varBLOB;
	try
	{
		//1.打开表
		/*m_pRecordset->Open(查询SQL语句,连接串，打开方式，数据源更新时如何锁定结果集，以什么形式传入)
			打开方式：
			adOpenUnspecified = -1,  默认的方式打开
			adOpenForwardOnly = 0,    向前移动的游标打开
			adOpenKeyset = 1,         以键值打开
			adOpenDynamic = 2,        当你添加数据时别人也有可能往这个表添加数据，谁在前谁添加到前面（多人用数据库时）
			adOpenStatic = 3          别人也想往里面添加数据一直停留在打开时候

			锁定结果集方式：
			adLockReadOnly = 1,         只读的不能改变数据
			adLockPessimistic = 2,		 （保守式锁定）逐个 – 编辑时立即锁定数据源的纪录
			adLockOptimistic = 3,		 （开放式锁定）逐个 – 只在调用update方法时才锁定纪录
			adLockBatchOptimistic = 4     开方式 可以更新一批数据更新模式
			+		bstrConnect	{"Driver={SQL Native Client};Server=192.168.1.92,2433;Uid=sa;Pwd=sa;Database=colin0716" (1)}	_bstr_t
			+		bstrSql	{"select * from student" (1)}	_bstr_t

		*/
		het = m_pRecordset->Open(bstrSql,bstrConnect,adOpenDynamic,adLockOptimistic,adCmdText);
		if (!SUCCEEDED(het))
		{
			AfxMessageBox(_T("打开表失败"));
			m_strErrorMsg = _T("查询表失败");
			return FALSE;
		}
		//循环结果
		while(!m_pRecordset->ADOEOF)
		{
			for(int i=0;i<nCloumNum;i++)
			{
				bstrQueryCloum = strQueryCloum[i];
				fields = m_pRecordset->GetFields();

				fieldPtr = fields->GetItem(bstrQueryCloum);

				varBLOB = fieldPtr->GetValue();

				//long nSize =fieldPtr->ActualSize;


				//注意图片名称必须为图片流的前一个字段
				//strValue = DataToCStringType(varBLOB,nSize,strValue);
				strValue = DataToCStringType(varBLOB);
				strDataValue.Add(strValue);
				//varBLOB.Detach();
			}
			m_pRecordset->MoveNext();
		}

		m_pRecordset->Close();
	}
	catch(_com_error *e)
	{
		m_strErrorMsg = e->ErrorMessage();
		AfxMessageBox(e->ErrorMessage());
	}

	return TRUE;
}


CString CDao::DataToCStringType(VARIANT Var)
{
	CString strValue;
	switch(Var.vt)
	{
	case VT_BOOL:
		strValue.Format(_T("%d"), Var.boolVal);
		break;
	case VT_I4:
		strValue.Format(_T("%d"), Var.intVal);
		break;
	case VT_R8:
	case VT_DECIMAL:

		strValue.Format(_T("%0.2f"), Var.dblVal);
		break;
	case VT_BSTR:
		strValue= Var.bstrVal;
		break;
	default:
		strValue = _T("");
		break;
	}

	return strValue;
}

BOOL CDao::AddData(CString strTableName,CStringArray& strCloumValue,int nCloumNum,CString* pStrReturnID)
{
	//校验
	if (strTableName.IsEmpty() || strCloumValue.GetCount() == 0 || nCloumNum == 0)
	{
		m_strErrorMsg = _T("参数错误");
		AfxMessageBox(_T("输入参数错误，请重新输入"));
		return FALSE;
	}


	CString strQuery;
	strQuery.Format(_T("select * from [%s]"),strTableName);

	//自带的字符串类型
	_bstr_t bstrQuery(strQuery);
	_bstr_t bstrCource(m_strConnect);

	HRESULT hres;
	Fields *pFiles = NULL;
	//ado把所有的数据类型都写在VARIANT这里面
	VARIANT varIndex;
	varIndex.vt = VT_I4; //R代表float CY==钱数  VT_带表的都是comADO代表的数据类型

	Field  *pFile = NULL;
	DataTypeEnum dataType;

	VARIANT varValue;
	try
	{
		//打开表
		hres = m_pRecordset->Open(bstrQuery,bstrCource,adOpenDynamic,adLockBatchOptimistic,adCmdText);
		if (!SUCCEEDED(hres))
		{
			m_strErrorMsg = _T("打开表失败");
			return FALSE;
		}
		else
		{
			//计算添加记录的行数
			int nRosNum = (int)(strCloumValue.GetCount()/nCloumNum);
			if(nRosNum <= 0 )
			{
				m_strErrorMsg = _T("参数个数错误");
				AfxMessageBox(_T("输入参数错误，请重新输入"));
				return FALSE;
			}
			//添加记录 循环行
			for (int i=0; i<nRosNum; i++)
			{
				//记录集告诉要添加记录
				m_pRecordset->AddNew();
				//要把记录一列一列的写进去
				for (int ncloum=0;ncloum<nCloumNum;ncloum++)
				{
					//传入的都是字符串 我要先得到列的数据类型 然后在做相应的转换 再把数据添加到数据库里
					//在数据库里列都是以集合形式存在的，所以先要得到所有的列，在从中得到每一个列
					//Fields *pFiles 是个双指针
					//1.得到所有的列
					m_pRecordset->get_Fields(&pFiles);

					//2.得到具体的列
					//ADO的COM对数据库编程 除了定义了字符串其他的没有具体定义 ado把所有的数据类型都写在VARIANT这里面
					varIndex.intVal = ncloum;
					pFiles->get_Item(varIndex,&pFile);

					//3.得到列(字段)对应的数据类型
					pFile->get_Type(&dataType);

					//4.转换 CString--》对应的类型 0 1 2 3 4 5   3
					if (CStringToDataType(strCloumValue.GetAt(ncloum+i*nCloumNum),dataType,&varValue))
					{
						//5.添加记录
						pFile->put_Value(varValue);
						if (varValue.vt == (VT_UI1|VT_ARRAY))
						{
							SafeArrayDestroy(varValue.parray);
						}
					}

				}
				//更新数据
				m_pRecordset->UpdateBatch(adAffectCurrent);

			}
			//关闭记录集 如果不关闭就会被一直占用，就打不开了
			if (pStrReturnID)
			{
				m_pRecordset->MoveLast();
				m_pRecordset->get_Fields(&pFiles);

				varIndex.intVal = 0;
				pFiles->get_Item(varIndex,&pFile);
				VARIANT varKey;
				pFile->get_Value(&varKey);

				pStrReturnID->Format(_T("%d"),varKey.intVal);
			}

			m_pRecordset->Close();
		}
	}catch(_com_error *e)
	{
		AfxMessageBox(e->Description());
		m_strErrorMsg.Format(_T("%s"),e->Description());
		return FALSE;
	}
	return TRUE;
}


BOOL CDao::CStringToDataType(CString strValue,int nDataType, VARIANT *pVar)
{
	switch(nDataType)
	{
	case adInteger: //整形
		pVar->vt = VT_I2;
		pVar->intVal = _ttoi(strValue);
		break;
	case adBoolean: //BOOL类型
		pVar->vt = VT_BOOL;
		pVar->bVal = _ttoi(strValue);
		break;
	case adSingle:   //单精度
		pVar->vt = VT_R4;
		pVar->fltVal = (float)_tstof(strValue);
		break;
	case adDouble:  //双精度
		pVar->vt = VT_R8;
		pVar->dblVal = _tstof(strValue);
		break;
	case adBSTR:   //字符串
	case adChar:
	case adVarChar:
	case adVarWChar:	
	case adWChar:
	case adLongVarWChar:
	case adLongVarChar:
		pVar->vt = VT_BSTR;
		pVar->bstrVal = (bstr_t)strValue;
		break;
	case adLongVarBinary:
		SaveImg(strValue,pVar);
		break;
	default:
		pVar->vt = VT_EMPTY;
		break;
	}
	return TRUE;
}

BOOL CDao::SaveImg(CString strPath,VARIANT *pVar)
{
	CFile f;
	CString FilePathName = strPath;
	if(f.Open(FilePathName, CFile::modeRead | CFile::typeBinary)) 
	{
		ULONGLONG nSize = f.GetLength();          //先得到文件长度
		BYTE * pBuffer = new BYTE [(size_t)nSize];  //按文件的大小在堆上申请一块内存
		if (f.Read(pBuffer, (UINT)nSize) > 0 )    //把文件读到pBuffer(堆上申请一块内存)
		{ 
			BYTE *pBuf = pBuffer;     ///下面这一大段是把pBuffer里的数据放到库中
			SAFEARRAY		*psa;
			SAFEARRAYBOUND	rgsabound[1];
			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = (ULONG)nSize;
			psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
			for (long i = 0; i < (long)nSize; i++)
			{
				SafeArrayPutElement (psa, &i, pBuf++);
			}
			pVar->vt = VT_ARRAY | VT_UI1;
			pVar->parray = psa;
			delete []pBuffer;

		}
		f.Close();
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDao::DeleteData(CString strSQL)
{
	HRESULT hRet;

	_bstr_t bstrQuery = strSQL;
	_bstr_t bstrConnent = m_strConnect;

	try
	{
		hRet = m_pRecordset->Open(bstrQuery, bstrConnent, adOpenDynamic, adLockOptimistic, adCmdText);
		if(!SUCCEEDED(hRet))
		{
			m_strErrorMsg = _T("打开表失败！");
			return FALSE;
		}
		while(!m_pRecordset->ADOEOF)
		{
			m_pRecordset->Delete(adAffectCurrent);
			m_pRecordset->MoveNext();
		}

		m_pRecordset->Close();
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->Description());
		return FALSE;
	}

	return TRUE;
}


//修改数据的查询语句   ， 列的个数   ， 修改的猎命   ， 列名对应值
BOOL CDao::EditData(CString strSQL, int nColumnNum, CString* pStrFieldName, CStringArray &saValue)
{
	//todu:校验

	int nIndex = 0;    //列的索引
	int nCount = 0;		//修改的总数
	int nTotal = (int)saValue.GetCount();  //一共修改的个数

	HRESULT hRet;
	_variant_t varFieldName;
	_variant_t varValue;

	_bstr_t bstrQuery = strSQL;
	_bstr_t bstrConnent = m_strConnect;


	try
	{
		hRet = m_pRecordset->Open(bstrQuery, bstrConnent, adOpenDynamic, adLockOptimistic, adCmdText);
		if(!SUCCEEDED(hRet))
		{
			m_strErrorMsg = _T("打开表失败！");
			return FALSE;
		}
		if (m_pRecordset->ADOEOF)
		{
			m_strErrorMsg = _T("没有选择修改的行");
			m_pRecordset->Close();
			return FALSE;
		}
		Fields *pFiles = NULL;
		//ado把所有的数据类型都写在VARIANT这里面
		VARIANT varIndex;
		varIndex.vt = VT_I4; //R代表float CY==钱数  VT_带表的都是comADO代表的数据类型

		Field  *pFile = NULL;
		VARIANT vtImg;
		while(!m_pRecordset->ADOEOF)
		{
			////修改哪一列  s#  sname    1 'ss'  2 'ss2'   stringarr  4    2
			if(m_pRecordset->GetFields()->GetItem((bstr_t)pStrFieldName[nIndex])->GetType() == adLongVarBinary)
			{
				
				if (SaveImg(saValue.GetAt(nCount),&vtImg))
				{
					m_pRecordset->GetFields()->GetItem((bstr_t)pStrFieldName[nIndex])->PutValue(vtImg);
					m_pRecordset->Update();
				}	
			} 
			else
			{
				varFieldName.SetString((bstr_t)pStrFieldName[nIndex]);
				varValue.SetString((bstr_t)saValue.GetAt(nCount));
				m_pRecordset->Update(varFieldName,varValue);
			}
			

			
			nIndex++;
			nCount++;
			if(nIndex>=nColumnNum)
			{
				nIndex = 0;
				m_pRecordset->MoveNext();
			}

			if (nColumnNum == 1)
			{
				if(nCount == nTotal)
				{
					break;
				}
			}
			else
			{
				if(nCount > nTotal)
				{
					break;
				}
			}


			//nIndex++;
		}
		m_pRecordset->Close();
	}
	catch(_com_error *e)
	{
		m_strErrorMsg = e->ErrorMessage();
		AfxMessageBox(e->Description());
		return FALSE;
	}

	return TRUE;
}


BOOL CDao::GetImgData(CString strSql,CString *strQueryCloum,int nCloumNum,CImage* pImg)
{

	HRESULT het;
	//com
	_bstr_t bstrSql = strSql;				//执行sql
	_bstr_t bstrConnect = m_strConnect;		//连库串
	_bstr_t bstrQueryCloum;					//列名

	Fields *fields;
	FieldPtr fieldPtr;

	CString strValue;
	_variant_t varBLOB;
	try
	{
		het = m_pRecordset->Open(bstrSql,bstrConnect,adOpenDynamic,adLockOptimistic,adCmdText);
		if (!SUCCEEDED(het))
		{
			AfxMessageBox(_T("打开表失败"));
			m_strErrorMsg = _T("查询表失败");
			return FALSE;
		}
		//循环结果

		if (m_pRecordset->ADOEOF)
		{
			m_pRecordset->Close();
			return FALSE;
		}
		while(!m_pRecordset->ADOEOF)
		{
			for(int i=0;i<nCloumNum;i++)
			{
				bstrQueryCloum = strQueryCloum[i];
				fields = m_pRecordset->GetFields();
				fieldPtr = fields->GetItem(bstrQueryCloum);

				varBLOB = fieldPtr->GetValue();

				//获取数据库中列的大小
				long nSize =fieldPtr->ActualSize;
				if (!pImg->IsNull())
				{
					pImg->Destroy();
				}
				if( varBLOB.vt ==  (VT_ARRAY | VT_UI1))
				{
					IStream *pStream;   //定义输出流

					BYTE *pBuf = NULL; 
					//申请全局的空间
					pBuf = (BYTE*)GlobalAlloc(GMEM_FIXED,nSize);
					GlobalLock((HGLOBAL)pBuf);  //给申请的空间枷锁
					SafeArrayAccessData(varBLOB.parray,(void **)&pBuf); 
					GlobalUnlock((HGLOBAL)pBuf);  //给申请的空间解锁

					SafeArrayUnaccessData (varBLOB.parray);


					if ( CreateStreamOnHGlobal((HGLOBAL)pBuf, TRUE, &pStream ) !=S_OK )  
					{
						m_strErrorMsg = _T("创建缓冲流错误");
						return FALSE;
					}

					
					pImg->Load(pStream);
					GlobalFree((HGLOBAL)pBuf);

				}


				varBLOB.Detach();
			}
			m_pRecordset->MoveNext();
		}

		m_pRecordset->Close();
	}
	catch(_com_error *e)
	{
		m_strErrorMsg = e->ErrorMessage();
		AfxMessageBox(e->ErrorMessage());
	}

	return TRUE;
}
