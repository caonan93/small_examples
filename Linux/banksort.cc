﻿#include <iostream>
using namespace std;
const int nRow = 500;
const int nColumn = 500;

int Max[nRow][nColumn];//资源最大需求矩阵
int Allocation[nRow][nColumn];//已分配资源矩阵
int Need[nRow][nColumn];//需要资源矩阵
int BeginSource[nColumn];//最开始各种资源的数量
int Available[nColumn];//当前可用各类资源数量
int Requset[nColumn];//提出资源请求个数
int safeOrder[nRow];//安全序列
int nSource;
int nPortNum;
int iTime = 0;//系统时刻
void show()
{

	/*显示用户已经输入的数据*/
	cout << "------------Allocation-----------------" << endl;
	for (int i = 0; i < nPortNum; i++)
	{
		cout << "port" << i << "\t";
		for (int j = 0; j < nSource; j++)
		{
			cout << Allocation[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "------------Need-----------------------" << endl;
	for (int i = 0; i < nPortNum; i++)
	{
		cout << "port" << i << "\t";
		for (int j = 0; j < nSource; j++)
		{
			cout << Need[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	cout << "---------------------------------------" << endl;
}
void Init()//初始化函数
{
	cout << "请输入资源种类数" << endl;
	cin >> nSource;
	cout << "请输入进程数量" << endl;
	cin >> nPortNum;
	if (nSource > 500|| nPortNum >500)
	{
		cout << "资源种类或进程数量过多，请控制在500以内" << endl;
		return;
	}
	cout << "MAX请输入现有各资源最大需求数量" << nPortNum<<"*"<<nSource<<"的矩阵"<<endl;
	for (int i = 0; i < nPortNum;i++)
	{
		for (int j = 0; j < nSource;j++)
		{
			cin >> Max[i][j];
		}
	}
	cout << "ALLOCATION请输入已经分配各个资源的数量" << nPortNum << "*" << nSource << "的矩阵" << endl;
start:
	for (int i = 0; i < nPortNum; i++)
	{
		for (int j = 0; j < nSource; j++)
		{
			cin >> Allocation[i][j];
			if (Allocation[i][j]>Max[i][j])
			{
				cout << "已分配的资源数量大于最大需求量，请重新分配" << endl;
				goto start;
			}
		}
	}

	
	//计算Need矩阵
	for (int i = 0; i < nPortNum; i++)
	{
		for (int j = 0; j < nSource; j++)
		{
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}

	//计算当前可用资源数量Available
	for (int i = 0; i < nPortNum; i++)
	{
		for (int j = 0; j < nSource; j++)
		{
			Available[j] += Allocation[i][j];
		}
	}

	cout << "请输入各种资源开始的数量" << nSource << "列" << endl;
begin:
	for (int i = 0; i < nSource; i++)
	{
		cin >> BeginSource[i];
		if (BeginSource[i] < Available[i])
		{
			cout << "第"<<i<<"个资源开始资源数量个数太少，请重新输入" << endl;
			goto begin;
		}
	}

	for (int i = 0; i < nSource; i++)
	{
		Available[i] = BeginSource[i] - Available[i];
	}	
}
//安全性算法，计算此刻状态是否安全
bool Safe()
{
	
	int Work[nColumn];
	bool Finish[nColumn];
	//将work工作向量初始化
	for (int i = 0; i < nSource;i++)
	{
		Work[i] = Available[i];
	}
	//初始化finish全为false
	for (int i = 0; i < nPortNum; i++)
	{
		Finish[i] = false;
	}

	int nCount = 0;
	int k = nPortNum;
	while (k--)//看工作向量是否操作了nSource次
	{

		for (int i = 0; i < nPortNum; i++)
		{
			int iCount = 0;//计数
			int iNum = 0;
			for (int j = 0; j < nSource; j++)
			{
				//所有资源Need都大于工作向量，则不安全
				if (Need[i][j] <= Work[j])
				{
					iNum++;
				}
			}
			if (iNum == nSource)//该进程满足
			{
				if (Finish[i] == true)
				{
					continue;
				}
				for (int j = 0; j < nSource; j++)
				{
					Work[j] += Allocation[i][j];
				}
				safeOrder[nCount] = i;
				Finish[i] = true;
				if (nPortNum == ++nCount)
				{					
					return true;
				}
			}
		}
	
	}
	return false;
}
//银行家算法
void BankSort()
{
	int n;
	show();
	a:
	cout << "请输入此刻哪个进程请求申请资源" << endl;
	cin >> n;
	if (n >= nPortNum)
	{
		cout << "没有这个进程号";
		goto a;
	}
	cout << "请输入每类资源的请求个数" << endl;
	
	for (int i = 0; i < nSource; i++)
	{
		mis:
		cin >> Requset[i];
		if (Requset[i] > Need[n][i ])
		{
			cout << "出错，申请资源大于需要资源,请重新输入"<<endl;
			goto mis;
		}
		if (Requset[i] > Available[i])
		{
			//进程pi阻塞，返回
			cout << "出错，申请资源大于现有资源,请重新输入" << endl;
			goto mis;
		}
	}
	for (int i = 0; i < nSource; i++)
	{
		Available[i] -= Requset[i];
		Allocation[n][i] += Requset[i];
		Need[n][i] -= Requset[i];
	}
	//调用安全性算法,计算此刻系统状态是否安全
	
	if (Safe())
	{

		char c;
		cout << "T"<<iTime<<"时刻系统安全安全序列为" <<"  ";
		for (int i = 0; i < nPortNum;i++)
		{
			if (i == nPortNum-1)
			{
				cout << safeOrder[i] << " ";
				break;
			}
			cout <<safeOrder[i]<<"-->";//安全序列
		}
		cout << "是否继续调度按键盘任意键继续" << endl;
		cin >> c;
		if (c >= 0||c <= 127)
		{
			iTime++;
			BankSort();		
		}

	}
	else
	{
		//此时资源分配状态不安全，恢复数据到未分配状态
		for (int i = 0; i < nSource; i++)
		{
			Available[i] += Requset[i];
			Allocation[n][i] -= Requset[i];
			Need[n][i] += Requset[i];
		}
		char c;
		cout << "T" << iTime << "时刻系统不安全不能分配任意键继续" << endl;
		cin >> c;
		if (c >= 0 || c <= 127)
		{
			BankSort();
		}
	}
	
}

int main()
{
	Init();
	BankSort();
	return 0;
}