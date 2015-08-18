#include "StdAfx.h"
#include "list_Right.h"


list_Right::list_Right(void)
{
	pHead = NULL;
	pEnd = NULL;
}


list_Right::~list_Right(void)
{
	while (pHead)
	{
		m_list *del = pHead;
		pHead = pHead->pNext;
		delete del;
		del = NULL;		
	}
}

void list_Right::AddNode(DWORD addreass,int nsize)
{
	m_list *temp = new m_list;
	temp->address = addreass;
	temp->size = nsize;
	temp->pNext = NULL;
	if (pHead == NULL)
	{
		pHead = temp;
	}
	else
	{

		pEnd->pNext = temp;
	}
	pEnd = temp;
}

m_list* list_Right::GetHead()
{
	return pHead;
}
void list_Right::GetNext()
{
	pHead = pHead->pNext;
}

int list_Right::GetSize()
{
	return pHead->size;
}
DWORD list_Right::GetAddress()
{
	return pHead->address;
}