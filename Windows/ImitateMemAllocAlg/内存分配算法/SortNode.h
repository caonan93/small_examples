#pragma once
#define HAVESPARATED 1
#define NOTSPAEATED 0
class CSortNode
{
public:
	CSortNode();
	~CSortNode();
public:
	struct Node
	{
		int m_nID;
		int m_nSize;
		int m_nRank;
		int m_nPosition;
		int m_nAddress;
		int m_nState;		
		Node *pNext;
		Node *pPro;
	};
	int m_nLength;
	Node *m_pHead;
	Node *m_pEnd;
	Node *m_pLoopPos;
	
public:
	void CreateNodeList(int m_nID, int nValue, int address, int nPos, int State = HAVESPARATED);
	bool FirstSort(int nSize);
	void CreateReceive();//创建回收垃圾链表
	CStringArray* GetData();
	void AlterListData(int iItem, int nState,int DataValue = 0 );
	void delteAllList();
	int GetCount();
	bool LoopSort(int nSize);
	bool BestSort(int nSize);
	bool BadSort(int nSize);
};

