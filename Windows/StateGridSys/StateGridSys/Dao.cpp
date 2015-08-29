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

BOOL CDao::InitCom()        //��ʼ��com���
{
#if _WIN32_WINNT > 0x500
	//�����֣�����Ϊnull�� �����ط�ʽ COINIT_MULTITHREADED���̵߳ķ�ʽ����
	// �Զ��̷߳�ʽ��comͨ��
	::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	::CoInitialize(NULL);
#endif
	m_binitComFlag = TRUE;
	return TRUE;
}
void CDao::releaseCom()     //�ͷ�com���
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
			m_strErrorMsg = _T("�Ҳ������ݿ�");
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
		m_strErrorMsg = _T("û�к��ʵ����⴮");
		return FALSE;
	}


	//ʵ����ָ�����
	HRESULT hRes;
	//��CStringת����com�������ַ�������
	_bstr_t bstrConnection(m_strConnect);
	_bstr_t bstrUser(strUser);
	_bstr_t bstrPassword(strPassWord);

	try
	{
		//�������Ӷ��� ������
		hRes = m_pConnection.CreateInstance(__uuidof(Connection));
		if (!SUCCEEDED(hRes))
		{
			m_strErrorMsg = _T("ʵ��������ָ�����ʧ��");
			return FALSE;
		}

		//�������ݿ�(���⴮���û���������,�򿪷�ʽ)
		//�ַ���Ҫ�õ���com������ַ��� adModeShareDenyNone���û���ͬ���Է���һ�����ݿ�
		hRes = m_pConnection->Open(bstrConnection,bstrUser,bstrPassword,adModeShareDenyNone);
		if (!SUCCEEDED(hRes))
		{
			m_strErrorMsg = _T("�����ݿ�ʧ��");
			return FALSE;
		}

		//ʵ�������ݼ�ָ�����
		hRes = m_pRecordset.CreateInstance(__uuidof(Recordset));
		if (!SUCCEEDED(hRes))
		{
			m_strErrorMsg = _T("ʵ�������ݼ�ָ�����ʧ��");
			return FALSE;
		}
		//ʵ�������ָ�����
		hRes = m_pCommandmsg.CreateInstance(__uuidof(Command));
		if (!SUCCEEDED(hRes))
		{
			m_strErrorMsg = _T("ʵ�������ָ�����ʧ��");
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
	//_bstr_t    �ַ���    		_variant_t �����������ͼ��� vt����   ..valueֵ								//com
	_bstr_t bstrSql = strSql;				//ִ��sql
	_bstr_t bstrConnect = m_strConnect;		//���⴮
	_bstr_t bstrQueryCloum;					//����

	Fields *fields;
	FieldPtr fieldPtr;


	CString strValue;
	_variant_t varBLOB;
	try
	{
		//1.�򿪱�
		/*m_pRecordset->Open(��ѯSQL���,���Ӵ����򿪷�ʽ������Դ����ʱ����������������ʲô��ʽ����)
			�򿪷�ʽ��
			adOpenUnspecified = -1,  Ĭ�ϵķ�ʽ��
			adOpenForwardOnly = 0,    ��ǰ�ƶ����α��
			adOpenKeyset = 1,         �Լ�ֵ��
			adOpenDynamic = 2,        �����������ʱ����Ҳ�п����������������ݣ�˭��ǰ˭��ӵ�ǰ�棨���������ݿ�ʱ��
			adOpenStatic = 3          ����Ҳ���������������һֱͣ���ڴ�ʱ��

			�����������ʽ��
			adLockReadOnly = 1,         ֻ���Ĳ��ܸı�����
			adLockPessimistic = 2,		 ������ʽ��������� �C �༭ʱ������������Դ�ļ�¼
			adLockOptimistic = 3,		 ������ʽ��������� �C ֻ�ڵ���update����ʱ��������¼
			adLockBatchOptimistic = 4     ����ʽ ���Ը���һ�����ݸ���ģʽ
			+		bstrConnect	{"Driver={SQL Native Client};Server=192.168.1.92,2433;Uid=sa;Pwd=sa;Database=colin0716" (1)}	_bstr_t
			+		bstrSql	{"select * from student" (1)}	_bstr_t

		*/
		het = m_pRecordset->Open(bstrSql,bstrConnect,adOpenDynamic,adLockOptimistic,adCmdText);
		if (!SUCCEEDED(het))
		{
			AfxMessageBox(_T("�򿪱�ʧ��"));
			m_strErrorMsg = _T("��ѯ��ʧ��");
			return FALSE;
		}
		//ѭ�����
		while(!m_pRecordset->ADOEOF)
		{
			for(int i=0;i<nCloumNum;i++)
			{
				bstrQueryCloum = strQueryCloum[i];
				fields = m_pRecordset->GetFields();

				fieldPtr = fields->GetItem(bstrQueryCloum);

				varBLOB = fieldPtr->GetValue();

				//long nSize =fieldPtr->ActualSize;


				//ע��ͼƬ���Ʊ���ΪͼƬ����ǰһ���ֶ�
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
	//У��
	if (strTableName.IsEmpty() || strCloumValue.GetCount() == 0 || nCloumNum == 0)
	{
		m_strErrorMsg = _T("��������");
		AfxMessageBox(_T("���������������������"));
		return FALSE;
	}


	CString strQuery;
	strQuery.Format(_T("select * from [%s]"),strTableName);

	//�Դ����ַ�������
	_bstr_t bstrQuery(strQuery);
	_bstr_t bstrCource(m_strConnect);

	HRESULT hres;
	Fields *pFiles = NULL;
	//ado�����е��������Ͷ�д��VARIANT������
	VARIANT varIndex;
	varIndex.vt = VT_I4; //R����float CY==Ǯ��  VT_����Ķ���comADO�������������

	Field  *pFile = NULL;
	DataTypeEnum dataType;

	VARIANT varValue;
	try
	{
		//�򿪱�
		hres = m_pRecordset->Open(bstrQuery,bstrCource,adOpenDynamic,adLockBatchOptimistic,adCmdText);
		if (!SUCCEEDED(hres))
		{
			m_strErrorMsg = _T("�򿪱�ʧ��");
			return FALSE;
		}
		else
		{
			//������Ӽ�¼������
			int nRosNum = (int)(strCloumValue.GetCount()/nCloumNum);
			if(nRosNum <= 0 )
			{
				m_strErrorMsg = _T("������������");
				AfxMessageBox(_T("���������������������"));
				return FALSE;
			}
			//��Ӽ�¼ ѭ����
			for (int i=0; i<nRosNum; i++)
			{
				//��¼������Ҫ��Ӽ�¼
				m_pRecordset->AddNew();
				//Ҫ�Ѽ�¼һ��һ�е�д��ȥ
				for (int ncloum=0;ncloum<nCloumNum;ncloum++)
				{
					//����Ķ����ַ��� ��Ҫ�ȵõ��е��������� Ȼ��������Ӧ��ת�� �ٰ�������ӵ����ݿ���
					//�����ݿ����ж����Լ�����ʽ���ڵģ�������Ҫ�õ����е��У��ڴ��еõ�ÿһ����
					//Fields *pFiles �Ǹ�˫ָ��
					//1.�õ����е���
					m_pRecordset->get_Fields(&pFiles);

					//2.�õ��������
					//ADO��COM�����ݿ��� ���˶������ַ���������û�о��嶨�� ado�����е��������Ͷ�д��VARIANT������
					varIndex.intVal = ncloum;
					pFiles->get_Item(varIndex,&pFile);

					//3.�õ���(�ֶ�)��Ӧ����������
					pFile->get_Type(&dataType);

					//4.ת�� CString--����Ӧ������ 0 1 2 3 4 5   3
					if (CStringToDataType(strCloumValue.GetAt(ncloum+i*nCloumNum),dataType,&varValue))
					{
						//5.��Ӽ�¼
						pFile->put_Value(varValue);
						if (varValue.vt == (VT_UI1|VT_ARRAY))
						{
							SafeArrayDestroy(varValue.parray);
						}
					}

				}
				//��������
				m_pRecordset->UpdateBatch(adAffectCurrent);

			}
			//�رռ�¼�� ������رվͻᱻһֱռ�ã��ʹ򲻿���
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
	case adInteger: //����
		pVar->vt = VT_I2;
		pVar->intVal = _ttoi(strValue);
		break;
	case adBoolean: //BOOL����
		pVar->vt = VT_BOOL;
		pVar->bVal = _ttoi(strValue);
		break;
	case adSingle:   //������
		pVar->vt = VT_R4;
		pVar->fltVal = (float)_tstof(strValue);
		break;
	case adDouble:  //˫����
		pVar->vt = VT_R8;
		pVar->dblVal = _tstof(strValue);
		break;
	case adBSTR:   //�ַ���
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
		ULONGLONG nSize = f.GetLength();          //�ȵõ��ļ�����
		BYTE * pBuffer = new BYTE [(size_t)nSize];  //���ļ��Ĵ�С�ڶ�������һ���ڴ�
		if (f.Read(pBuffer, (UINT)nSize) > 0 )    //���ļ�����pBuffer(��������һ���ڴ�)
		{ 
			BYTE *pBuf = pBuffer;     ///������һ����ǰ�pBuffer������ݷŵ�����
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
			m_strErrorMsg = _T("�򿪱�ʧ�ܣ�");
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


//�޸����ݵĲ�ѯ���   �� �еĸ���   �� �޸ĵ�����   �� ������Ӧֵ
BOOL CDao::EditData(CString strSQL, int nColumnNum, CString* pStrFieldName, CStringArray &saValue)
{
	//todu:У��

	int nIndex = 0;    //�е�����
	int nCount = 0;		//�޸ĵ�����
	int nTotal = (int)saValue.GetCount();  //һ���޸ĵĸ���

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
			m_strErrorMsg = _T("�򿪱�ʧ�ܣ�");
			return FALSE;
		}
		if (m_pRecordset->ADOEOF)
		{
			m_strErrorMsg = _T("û��ѡ���޸ĵ���");
			m_pRecordset->Close();
			return FALSE;
		}
		Fields *pFiles = NULL;
		//ado�����е��������Ͷ�д��VARIANT������
		VARIANT varIndex;
		varIndex.vt = VT_I4; //R����float CY==Ǯ��  VT_����Ķ���comADO�������������

		Field  *pFile = NULL;
		VARIANT vtImg;
		while(!m_pRecordset->ADOEOF)
		{
			////�޸���һ��  s#  sname    1 'ss'  2 'ss2'   stringarr  4    2
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
	_bstr_t bstrSql = strSql;				//ִ��sql
	_bstr_t bstrConnect = m_strConnect;		//���⴮
	_bstr_t bstrQueryCloum;					//����

	Fields *fields;
	FieldPtr fieldPtr;

	CString strValue;
	_variant_t varBLOB;
	try
	{
		het = m_pRecordset->Open(bstrSql,bstrConnect,adOpenDynamic,adLockOptimistic,adCmdText);
		if (!SUCCEEDED(het))
		{
			AfxMessageBox(_T("�򿪱�ʧ��"));
			m_strErrorMsg = _T("��ѯ��ʧ��");
			return FALSE;
		}
		//ѭ�����

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

				//��ȡ���ݿ����еĴ�С
				long nSize =fieldPtr->ActualSize;
				if (!pImg->IsNull())
				{
					pImg->Destroy();
				}
				if( varBLOB.vt ==  (VT_ARRAY | VT_UI1))
				{
					IStream *pStream;   //���������

					BYTE *pBuf = NULL; 
					//����ȫ�ֵĿռ�
					pBuf = (BYTE*)GlobalAlloc(GMEM_FIXED,nSize);
					GlobalLock((HGLOBAL)pBuf);  //������Ŀռ����
					SafeArrayAccessData(varBLOB.parray,(void **)&pBuf); 
					GlobalUnlock((HGLOBAL)pBuf);  //������Ŀռ����

					SafeArrayUnaccessData (varBLOB.parray);


					if ( CreateStreamOnHGlobal((HGLOBAL)pBuf, TRUE, &pStream ) !=S_OK )  
					{
						m_strErrorMsg = _T("��������������");
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
