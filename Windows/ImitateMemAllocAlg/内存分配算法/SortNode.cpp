#include "stdafx.h"
#include "SortNode.h"


CSortNode::CSortNode()
{
	m_pHead = NULL;
	m_pEnd = NULL;
	m_pLoopPos = NULL;
}


CSortNode::~CSortNode()
{
	Node *pTemp = m_pHead;
	Node *del;
	while (pTemp)
	{
		del = pTemp;
		
		pTemp = pTemp->pNext;
		delete del;
		del = NULL;
	}


}
void CSortNode::delteAllList()
{
	Node *pTemp = m_pHead;
	Node *del;
	while (pTemp)
	{
		del = pTemp;

		pTemp = pTemp->pNext;
		delete del;
		del = NULL;
	}
	m_pHead = NULL;
	m_pEnd = NULL;
}
void CSortNode::CreateNodeList(int m_nID, int nValue, int address, int nPos,int State)
{
	
	Node *pTemp = new Node;
	pTemp->pNext = NULL;
	pTemp->pPro = NULL;
	pTemp->m_nID = m_nID;
	pTemp->m_nSize = nValue;
	pTemp->m_nRank = 0;
	pTemp->m_nPosition = nPos;
	pTemp->m_nAddress = address;
	pTemp->m_nState = State;
	if (m_pHead == NULL)
	{
		m_pHead = pTemp;
	}
	else
	{
		m_pEnd->pNext = pTemp;
		pTemp->pPro = m_pEnd;
	}
	m_pEnd = pTemp;
}

bool CSortNode::FirstSort(int nSize)//首次适应算法
{
	Node* temp = m_pHead;
	while (temp)
	{
		if (temp->m_nState == NOTSPAEATED)
		{
			if (nSize <= temp->m_nSize)
			{
				Node *p = new Node;//设置新节点的属性
				p->m_nAddress = temp->m_nAddress;
				p->m_nSize = nSize;
				p->m_nState = HAVESPARATED;
				
				if (temp->pPro ==  NULL)  //新节点的添加
				{
					p->pPro = NULL;
					p->pNext = temp;
					temp->pPro = p;

					p->m_nAddress = m_pHead->m_nAddress;
					p->m_nSize = nSize;
					p->m_nState = HAVESPARATED;
					p->m_nPosition = 1;//记录位置以便最佳算法
					m_pHead = p;
					
				}
				else
				{
					temp->pPro->pNext = p;
					p->pNext = temp;
					p->pPro = temp->pPro;
					temp->pPro = p;
				}
				m_pLoopPos = p;//记录第一次申请的位置，方便loop算法计算下一次
				
				temp->m_nSize -= nSize;
				temp->m_nAddress += nSize;
				return true;
			}
		}
		
		temp = temp->pNext;
	}
	return false;
}

CStringArray* CSortNode::GetData()
{
	Node *ptemp = m_pHead;
	CStringArray *data = new CStringArray[4];
	while (ptemp)
	{
		CString strTemp_0;
		CString strTemp_1;
		CString strTemp_2;
		
		strTemp_0.Format(_T("%d"), ptemp->m_nID);
		data[0].Add(strTemp_0);

		strTemp_1.Format(_T("%d"), ptemp->m_nSize);
		data[2].Add(strTemp_1);

		strTemp_2.Format(_T("%d"), ptemp->m_nAddress);
		data[1].Add(strTemp_2);

		if (ptemp->m_nState == HAVESPARATED)
		{
			data[3].Add(_T("已分配"));
		}
		else
		{
			data[3].Add(_T("空闲分区"));
		}
		ptemp = ptemp->pNext;
	}
	return data;
}

void CSortNode::AlterListData(int iItem,int nState,int DataValue )//修改某行的状态数据
{
	Node *temp = m_pHead;
	int i = 0;
	while (temp)
	{
		if (i == iItem)
		{
			temp->m_nState = nState;
			return;
		}
		i++;
		temp = temp->pNext;
	}
}
int CSortNode::GetCount()
{
	Node *temp = m_pHead;
	int i = 0;
	while (temp)
	{
		i++;
		temp = temp->pNext;
	}
	return i;
}
void CSortNode::CreateReceive()
{
	Node *temp = m_pHead;

	while (temp)
	{
	
		if (temp->pNext == NULL)
		{
			m_pEnd = temp;
			return ;
		}
		else if (temp->pNext->pNext == NULL)
		{
			if (temp->m_nState == temp->pNext->m_nState && temp->m_nState == NOTSPAEATED || temp->pNext->m_nSize == 0)
			{

				temp->m_nSize += temp->pNext->m_nSize;
				Node *del = temp->pNext;
				temp->pNext = temp->pNext->pNext;//只要有两段相邻空闲区域就合并
				delete del;
				del = NULL;
				m_pEnd = temp;
			}

			return ;

		}
		if (temp->m_nState == temp->pNext->m_nState && temp->m_nState == NOTSPAEATED || temp->pNext->m_nSize == 0)
		{
			
			temp->m_nSize += temp->pNext->m_nSize;
			Node *del = temp->pNext;
			temp->pNext = temp->pNext->pNext;//只要有两段相邻空闲区域就合并
			delete del;
			del = NULL;
			
			continue;//精妙之笔
			
		}
		
		temp = temp->pNext;
	}
	
	return ;
}
bool CSortNode::BadSort(int nSize)
{
	Node *maxPos = NULL;
	int max = 0;
	Node* temp = m_pHead;
	while (temp)
	{
		if (temp->m_nState == NOTSPAEATED)
		{
			if (nSize <= temp->m_nSize)
			{
				if (max <= temp->m_nSize - nSize)
				{
					max = temp->m_nSize - nSize;
					maxPos = temp;//记录最小结点位置

				}
			}
		}

		temp = temp->pNext;
	}

	if (!maxPos)
	{
		return false;
	}
	Node *p = new Node;//设置新节点的属性
	p->m_nAddress = maxPos->m_nAddress;
	p->m_nSize = nSize;
	p->m_nState = HAVESPARATED;

	if (maxPos->pPro == NULL)  //新节点的添加
	{
		p->pPro = NULL;
		p->pNext = maxPos;
		maxPos->pPro = p;

		p->m_nAddress = m_pHead->m_nAddress;
		p->m_nSize = nSize;
		p->m_nState = HAVESPARATED;
		p->m_nPosition = 1;//记录位置以便最佳算法
		m_pHead = p;

	}
	else
	{
		maxPos->pPro->pNext = p;
		p->pNext = maxPos;
		p->pPro = maxPos->pPro;
		maxPos->pPro = p;
	}
	maxPos->m_nSize -= nSize;
	maxPos->m_nAddress += nSize;
	return true;
}
bool CSortNode::BestSort(int nSize)
{
	Node *MinPos = NULL;
	int min = 0;
	Node* temp = m_pHead;
	while (temp)
	{
		if (temp->m_nState == NOTSPAEATED)
		{
			if (nSize <= temp->m_nSize)
			{
				if (min == 0)//首次遍历到将min初始化
				{
					min = temp->m_nSize - nSize;
					MinPos = temp;
				}
				else if (min > temp->m_nSize - nSize)
				{
					min = temp->m_nSize - nSize;
					MinPos = temp;//记录最小结点位置

				}			
			}
		}

		temp = temp->pNext;
	}
	
	if (!MinPos)
	{
		return false;
	}
	Node *p = new Node;//设置新节点的属性
	p->m_nAddress = MinPos->m_nAddress;
	p->m_nSize = nSize;
	p->m_nState = HAVESPARATED;

	if (MinPos->pPro == NULL)  //新节点的添加
	{
		p->pPro = NULL;
		p->pNext = MinPos;
		MinPos->pPro = p;

		p->m_nAddress = m_pHead->m_nAddress;
		p->m_nSize = nSize;
		p->m_nState = HAVESPARATED;
		p->m_nPosition = 1;//记录位置以便最佳算法
		m_pHead = p;

	}
	else
	{
		MinPos->pPro->pNext = p;
		p->pNext = MinPos;
		p->pPro = MinPos->pPro;
		MinPos->pPro = p;
	}
	MinPos->m_nSize -= nSize;
	MinPos->m_nAddress += nSize;
	return true;
}
bool CSortNode::LoopSort(int nSize)
{
	Node* temp = m_pLoopPos;
	while (temp)
	{
		if (temp->m_nState == NOTSPAEATED)
		{
			if (nSize <= temp->m_nSize)
			{
				Node *p = new Node;		//设置新节点的属性
				p->m_nAddress = temp->m_nAddress;
				p->m_nSize = nSize;
				p->m_nState = HAVESPARATED;

				if (temp->pPro == NULL)  //新节点的添加
				{
					p->pPro = NULL;
					p->pNext = temp;
					temp->pPro = p;

					p->m_nAddress = m_pHead->m_nAddress;
					p->m_nSize = nSize;
					p->m_nState = HAVESPARATED;
					p->m_nPosition = 1;//记录位置以便最佳算法
					m_pHead = p;

				}
				else
				{
					temp->pPro->pNext = p;
					p->pNext = temp;
					p->pPro = temp->pPro;
					temp->pPro = p;
				}
				m_pLoopPos = p;//记录第一次申请的位置，方便loop算法计算下一次

				temp->m_nSize -= nSize;
				temp->m_nAddress += nSize;
				return true;
			}
		}

		temp = temp->pNext;
	}
	return false;
}