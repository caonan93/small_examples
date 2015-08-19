#pragma once
struct m_list
{
	DWORD address;
	int size;
	m_list *pNext;
};

class list_Right
{
private:
	m_list *pHead;
	m_list *pEnd;
public:
	list_Right(void);
	~list_Right(void);
public:
	void AddNode(DWORD addreass,int nsize);
	m_list* GetHead();
	void GetNext();
	int GetSize();
	DWORD GetAddress();
};

