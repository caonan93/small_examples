////////////////////////////////////////////////////////////////////  
//                          _ooOoo_                               //  
//                         o8888888o                              //      
//                         88" . "88                              //      
//                         (| ^_^ |)                              //      
//                         O\  =  /O                              //  
//                      ____/`---'\____                           //                          
//                    .'  \\|     |//  `.                         //  
//                   /  \\|||  :  |||//  \                        //      
//                  /  _||||| -:- |||||-  \                       //  
//                  |   | \\\  -  /// |   |                       //  
//                  | \_|  ''\---/''  |   |                       //          
//                  \  .-\__  `-`  ___/-. /                       //          
//                ___`. .'  /--.--\  `. . ___                     //      
//              ."" '<  `.___\_<|>_/___.'  >'"".                  //  
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 //      
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 //  
//      ========`-.____`-.___\_____/___.-`____.-'========         //      
//                           `=---='                              //  
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //  
//         ���汣��       ����BUG     �����޸�                  //  
////////////////////////////////////////////////////////////////////
#include <string>
#include <iostream>
#include <assert.h>
#include <vector>
#include <stack>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class Solution {
	public:
	int StrToInt(string str) {
		if (str.empty())
		{
			return 0;
		}
		const char *num = str.c_str();
		char *pnum = const_cast<char*>(num);
		int bj10 = 1;
		int sum = 0;

		while (*pnum != '\0')
		{
			pnum++;
		}
		pnum--;

		while (pnum != num)
		{
			if (*pnum <= '9' && *pnum >= '0')
			{
				sum += bj10*(*pnum - '0');
				bj10 *= 10;
			} else
			{
				return 0;
			}
			pnum--;
		}

		if (*pnum == '-' || *pnum == '+')
		{
			if (*pnum == '-')
			{
				return -sum;
			}
			return sum;
		}


		if (*pnum <= '9' || *pnum >= '0')
		{
			sum += bj10*(*pnum - '0');
			bj10 *= 10;
		} else
		{
			return 0;
		}

		return sum;
	}
};

bool Find(vector<vector<int> > array, int target) {
	if (array.empty())
	{
		return false;
	}
	int j = array[0].size() - 1;
	int i = 0;
	for (; i < array.size(); i++)//��
	{
		for (; j >= 0; j--)//��
		{
			if (array[i][j] < target)
			{
				break;
			} else if (array[i][j] == target)
			{
				return true;
			} else
			{
				continue;
			}

		}
	}
	return false;
}

void replaceSpace(char *str, int length) {
	//We Are Happy  %20
	if (str == NULL)
	{
		return;
	}
	char*p = str;
	int space = 0;
	int iLen = 0;
	while (*p != '\0')
	{
		if (*p == ' ')
		{
			space++;
		}
		p++;
		iLen++;
	}

	int end = space * 2 + iLen + 1;//1ռλ��\0��

	if (end <= length)
	{
		str[end--] = '\0';

		while (end > 0)
		{
			if (str[iLen] == ' ')
			{
				iLen--;
				str[end--] = '0';
				str[end--] = '2';
				str[end--] = '%';
			} else
			{
				str[end--] = str[iLen--];
			}
		}
	}
}

class Solution2 {
	public:
	void push(int node) {
		stack1.push(node);
		if (stack2.empty())
		{
			while (!stack1.empty())
			{
				stack2.push(stack1.top());
				stack1.pop();
			}
		}

	}

	int pop() {

		if (stack2.empty())
		{
			while (!stack1.empty())
			{
				stack2.push(stack1.top());
				stack1.pop();
			}
		}
		int a = stack2.top();
		stack2.pop();
		return a;
	}

	private:
	stack<int> stack1;
	stack<int> stack2;
};

int Fibonacci(int n) {
	if (n < 0)
	{
		return 0;
	}
	int res[2] = { 0, 1 };

	if (n < 2)
	{
		return res[n];
	}

	int sum = 0;
	int first = 0;
	int second = 1;
	for (int i = 2; i <= n; i++)
	{
		sum = first + second;
		first = second;
		second = sum;
	}
	return sum;
}

bool IsPopOrder(vector<int> pushV, vector<int> popV) {
	//o(n)

	if (pushV.empty() || popV.empty())
	{
		return false;
	}

	if (pushV.size() != popV.size())
	{
		return false;
	}

	stack<int> ostack;//����һ��ջ�ĸ����ռ�
	vector<int>::iterator itPop = popV.begin();
	vector<int>::iterator itpush = pushV.begin();
	while (itpush != pushV.end())
	{
		if (*itpush != *itPop)
		{
			ostack.push(*itpush);
		} else
		{
			itPop++;
			while (itPop != popV.end() && *itPop == ostack.top())
			{
				ostack.pop();
				itPop++;
			}

		}
		itpush++;
	}

	if (ostack.empty())
	{
		return true;
	} else
	{
		return false;
	}
}

class Solution3 {
	public:
	void push(int value) {

		ostackNormal.push(value);

		if (ostackMin.empty())
		{
			ostackMin.push(value);
		} else
		{
			if (ostackMin.top() > value)
			{
				ostackMin.push(value);
			}
		}

	}
	void pop() {
		if (ostackMin.top() == ostackNormal.top())
		{
			ostackMin.pop();
		}
		ostackNormal.pop();
	}
	int top() {
		return ostackNormal.top();
	}
	int min() {
		return ostackMin.top();
	}

	stack<int> ostackNormal;
	stack<int> ostackMin;
};

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};

vector<int> printListFromTailToHead(struct ListNode* head)//��β��ͷ��ӡ����
{
	vector<int> res;
	if (head == NULL)
	{
		return res;
	}
	struct ListNode* p1 = head;
	struct ListNode* p2 = p1->next;
	if (p2 == NULL) { res.push_back(p1->val); return res; }
	struct ListNode* p3 = p2->next;
	if (p3 == NULL) { res.clear(); res.push_back(p2->val); res.push_back(p1->val); return res; }
	//���ڵ����������
	p1->next = NULL;
	while (p3->next != NULL)
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	p3->next = p2;
	p2->next = p1;

	head = p3;
	p2 = p3->next;
	p1 = p3;
	p3 = p2->next;

	while (head != NULL)
	{
		res.push_back(head->val);
		head = head->next;
	}

	//�ڸ���������
	p1->next = NULL;
	while (p3->next != NULL)
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	p3->next = p2;
	p2->next = p1;
	return res;
}

void reOrderArray(vector<int> &array) {
	if (array.empty())
	{
		return;
	}
	vector<int> a;
	for (vector<int>::iterator it = array.begin(); it != array.end(); it++)
	{
		if (*it % 2 == 1)
		{
			a.push_back(*it);
		}
	}

	for (vector<int>::iterator it = array.begin(); it != array.end(); it++)
	{
		if (*it % 2 == 0)
		{
			a.push_back(*it);
		}
	}

	array.clear();
	array.insert(array.begin(), a.begin(), a.end());
}

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
	if (!pListHead || k <= 0)
	{
		return NULL;
	}
	//���ÿ���ָ��
	ListNode *plow = pListHead;
	ListNode* pQuick = pListHead;
	for (int i = 0; i < k; i++)
	{
		if (pQuick == NULL)
		{
			return NULL;
		}
		pQuick = pQuick->next;
	}

	while (pQuick != NULL)
	{

		pQuick = pQuick->next;
		plow = plow->next;
	}
	return plow;
}

int  NumberOf1(int n) {
	//���ƶ�����Ǹ����Ļ���������油1������
	int count = 0;
	while (n)
	{
		count++;
		n = (n - 1)&n;
	}
	return count;
}

struct RandomListNode {
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :
		label(x), next(NULL), random(NULL) {
	}
};

RandomListNode* Clone(RandomListNode* pHead) {
	if (pHead == NULL)
	{
		return NULL;
	}
	RandomListNode *tmpHead = pHead;

	while (tmpHead->next)
	{
		RandomListNode *temp = new RandomListNode(tmpHead->label);
		temp->next = tmpHead->next;
		tmpHead->next = temp;
		tmpHead = tmpHead->next->next;
	}
	tmpHead->next = new RandomListNode(tmpHead->label);//�������һ�����

	tmpHead = pHead;
	while (tmpHead)//���Ƹ��ӽ��
	{
		if (tmpHead->random == NULL)
		{
			tmpHead->next->random = NULL;
		} else
		{
			tmpHead->next->random = tmpHead->random->next;
		}
		tmpHead = tmpHead->next->next;
	}

	//������
	tmpHead = pHead;
	RandomListNode* tmpHeadnew = tmpHead->next;

	RandomListNode* res = tmpHeadnew;

	while (tmpHeadnew->next != NULL)
	{
		tmpHead->next = tmpHead->next->next;
		tmpHeadnew->next = tmpHeadnew->next->next;

		tmpHeadnew = tmpHeadnew->next;
		tmpHead = tmpHead->next;
	}
	tmpHead->next = NULL;
	return res;
}

void inPermutation(string str, int index, vector<string>& s) {
	if (index == str.size())
	{
		string res(str.begin(), str.end());
		cout << "[" << str << "]" << endl;
		s.push_back(res);
	} else
	{
		for (size_t i = index; i < str.size(); i++)
		{
			swap(str.at(i), str.at(index));
			inPermutation(str, index + 1, s);
			swap(str.at(i), str.at(index));
		}
	}
}

vector<string> Permutation(string str) {
	//abc, acb, bac, bca, cab cba	
	vector<string> strs;
	if (str.empty())
	{
		return strs;
	}
	inPermutation(str, 0, strs);
	return strs;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {
	}
};

/*
TreeNode* consturctor(vector<int>::iterator Preleft, vector<int>::iterator Preright,
vector<int>::iterator inLeft, vector<int>::iterator inRight)
{
TreeNode* root = new TreeNode(*Preleft);

//Ѱ���м�ڵ�
vector<int>::iterator it = inLeft;
int iCount = 0;
while (*Preleft != *it)
{
iCount++;
it++;
}
Preright = Preleft + iCount;
//����������
root->left = consturctor(Preleft + 1, Preleft+iCount, inLeft, it - 1);
//right tree
//root->right = consturctor(Preleft + iCount,);
}
struct TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in) {
if (pre.empty() || in.empty || pre.size() != in.size())
{
return NULL;
}
return consturctor(pre.begin(), pre.end(), in.begin, in.end());
}*/

int FirstNotRepeatingChar(string str) {
	if (str.empty())
	{
		return -1;
	}
	unsigned int hash[256];
	for (int i = 0; i < 256; i++)
	{
		hash[i] = 0;
	}
	for (int i = 0; i < str.size(); i++)
	{
		char c = str.at(i);
		hash[c]++;
	}

	for (int i = 0; i < str.size(); i++)
	{
		char c = str.at(i);
		if (hash[c] == 1)
		{
			return i;
		}
	}
	return -1;
}

vector<int> PrintFromTopToBottom(TreeNode *root) {
	vector<int> res;
	if (!root)
	{
		return res;
	}
	queue<TreeNode*> que;
	que.push(root);
	while (!que.empty())
	{
		TreeNode* tree = que.front();
		res.push_back(tree->val);
		que.pop();
		if (tree->left)
		{
			que.push(tree->left);
		}

		if (tree->right)
		{
			que.push(tree->right);
		}
	}
	return res;
}

ListNode* ReverseList(ListNode* pHead) {
	if (!pHead) return NULL;
	ListNode * p1 = pHead;
	ListNode * p2 = p1->next;
	if (!p2) return p1;
	ListNode * p3 = p2->next;
	if (!p3) { p2->next = p1; p1->next = NULL; return p2; }

	p1->next = NULL;
	while (p3)
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	p2->next = p1;
	return p2;
}

int MoreThanHalfNum_Solution(vector<int> numbers) {
	if (numbers.empty()) return 0;
	//time o(n)
	int time = 0;
	int num = 0;
	num = numbers.at(0);
	time = 1;
	for (vector<int>::iterator it = numbers.begin() + 1; it != numbers.end(); it++)
	{
		if (num != *it)
		{
			time--;
		} else
		{
			time++;
		}

		if (time == 0) { num = *it; time++; }
	}

	int middle = numbers.size() / 2;
	time = 0;
	for (vector<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		if (num == *it)
		{
			time++;
		}
	}
	return time > middle ? num : 0;
}

int partion(vector<int>& data, int start, int end) {
	int compare = data[start];

	std::swap(data[start], data[end]);
	int small = start - 1;
	for (int index = start; index < end; index++)
	{
		if (data[index] < compare)
		{
			++small;
			if (small != index)
			{
				std::swap(data[small], data[index]);
			}
		}
	}
	small++;
	swap(data[small], data[end]);
	return small;
}

void quicksort(vector<int>& arr, int start, int end) {
	if (arr.empty() || start < 0 || end < 0) return;
	if (start < end)
	{
		int index = partion(arr, start, end);
		if (index >start) quicksort(arr, start, index - 1);
		if (index < end) quicksort(arr, index + 1, end);
	}
}

vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
	vector<int> res;
	if (input.empty() || k < 0 || k> input.size()) return res;

	int index = partion(input, 0, input.size() - 1);
	while (1)
	{
		if (index + 1 == k)
		{
			res.assign(input.begin(), input.begin() + k);
			break;
		}

		if (index + 1 < k)
		{
			index = partion(input, index + 1, input.size() - 1);
		} else
		{
			index = partion(input, 0, index - 1);
		}
	}
	return res;
}

//������
/*TODO
vector<int> heapSort(vector<int> input) {
TreeNode* root =
}*/
double PowerEfficient(double base, unsigned int exponent) {
	if (exponent == 0)
	{
		return 1;
	}
	if (exponent == 1)
	{
		return base;
	}
	double result = PowerEfficient(base, exponent / 2);
	result *= result;
	if (exponent % 2 == 1)
	{
		result *= base;
	}
	return result;
}
double Power(double base, int exponent) {
	if (base - 0 < 0.0000001 && 0 - base < 0.0000001)
	{
		if (exponent == 0)
		{
			return 1;
		} else
		{
			return 0;
		}

	}
	int ex = exponent;
	if (exponent < 0)
	{
		ex = -exponent;
	}
	double res = PowerEfficient(base, ex);
	if (exponent < 0)
	{
		res = 1.0 / res;
	}
	
	return res;
}
//{3,4,5,1,2}Ϊ{1,2,3,4,5}
int minNumberInRotateArray(vector<int> rotateArray) {
	 //every number not same
	if (rotateArray.empty())
	{
		return 0;
	}
	int pHead = 0;
	int pEnd = rotateArray.size()-1;
	 
	while (1)
	{
		if (pHead == pEnd)
		{
			return rotateArray.at(0);
		}
		int pmid = (pHead + pEnd) / 2;
		if (rotateArray.at(pmid) > rotateArray.at(0))
		{
			pHead = pmid + 1;
		} else if (rotateArray.at(pmid) == rotateArray.at(pHead)) {
			//�������״��o(n)���Ӷ�
			int min = rotateArray[0];
			for (vector<int>::iterator it = rotateArray.begin()+1; 
					 it != rotateArray.end();
					 ++it)
			{
				if (*it < min)
				{
					min = *it;
				}
			}
			return min;
		}else {//mid_val < phead_val
 			while (pHead != pmid+1)//see if the left val less than this 
			{
				if (rotateArray.at(pmid) >= rotateArray.at(pmid - 1))
				{
					pmid--;
				}
				else {
					return rotateArray.at(pmid);
				}
			}			
		}
	}	
}

ListNode* FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
	if (!pHead1 || !pHead2)
	{
		return NULL;
	}
	//�ֱ�������������ĸ��Ƚϳ�
	ListNode* headtmp1 = pHead1;
	ListNode* headtmp2 = pHead2;
	int step1 = 0, step2 = 0;
	while (headtmp1)
	{
		headtmp1 = headtmp1->next;
		step1++;
	}
	while (headtmp2)
	{
		headtmp2 = headtmp2->next;
		step2++;
	}
	headtmp1 = pHead1;
	headtmp2 = pHead2;
	int num = step1 > step2 ? step1 - step2 : step2 - step1;
	if (num)
	{
		if (step1>step2)
		{
			while (num--)
			{
				headtmp1 = headtmp1->next;
			}
		}
		else{
			while (num--)
			{
				headtmp2 = headtmp2->next;
			}
		}
	}
	
	while (headtmp1&&headtmp2)
	{
		if (headtmp1 == headtmp2)
		{
			return headtmp1;
		}
		headtmp1 = headtmp1->next;
		headtmp2 = headtmp2->next;
	}
	return NULL;
}

class soutaion {
public:
	//������������{3��32��321}�����ӡ���������������ųɵ���С����Ϊ321323��
	string PrintMinNumber(vector<int> numbers) {
		if (numbers.empty())
		{
			return NULL;
		}
		//�Ƚ�����ת�����ַ������ڽ��ַ���֮����бȽ�
		vector<string> stringArry;
		char buf[16];
		for (int i = 0; i < numbers.size(); ++i)
		{
			_snprintf(buf, sizeof(buf), "%d", numbers[i]);
			string str = buf;
			stringArry.push_back(str);
		}
		sort(stringArry.begin(), stringArry.end());
		string min_number;
//TODO������for_each�ķ���ֵ������Ϊ���棡
		min_number = for_each(stringArry.begin(), stringArry.end(), print());
		return min_number;
	}

	class print {
	private:
		string min_number_;
	public:
		void operator()(string& str) {
			min_number_ += str;
		}
		operator string() {
			return min_number_;
		}
	};

	bool compare(string& str1, string& str2) {
		//�ж�str1str2����str2str1��
		string strcompare1 = str1 + str2;
		string strcompare2 = str2 + str1;
		return strcompare1 > strcompare2 ? true : false;
	}
};


/*
��һ������Ϊn����������������ֶ���0��n - 1�ķ�Χ�ڡ� ������ĳЩ�������ظ��ģ�
����֪���м����������ظ��ġ�Ҳ��֪��ÿ�������ظ����Ρ����ҳ�����������һ���ظ������֡�
���磬������볤��Ϊ7������{ 2, 3, 1, 0, 2, 5, 3 }����ô��Ӧ��������ظ�������2����3��*/
bool duplicate(int numbers[], int length, int* duplication) {
	if (numbers == NULL || length <= 0)
	{
		return false;
	}
	for (int i = 0; i < length;++i)
	{
		if (numbers[i]<0||numbers[i]>length-1)
		{
			return false;
		}
	}
	for (int i = 0; i < length;i++)
	{
		while (numbers[i]!=i)
		{
			if (numbers[i] == numbers[numbers[i]])
			{
				*duplication = numbers[i];
				return true;
			}
			std::swap(numbers[i], numbers[numbers[i]]);
		}
	}
	return false;
}
//�ϲ���������
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (!pHead1)
	{
		return pHead2;
	}
	else if (!pHead2)
	{
		return pHead1;
	}
	ListNode* pHead = 0;
	if (pHead1->val < pHead2->val)
	{
		pHead = pHead1;
		pHead->next = Merge(pHead1->next, pHead2);
	}
	else
	{
		pHead = pHead2;
		pHead->next = Merge(pHead1, pHead2->next);
	}
	return pHead;
}

//���������������6,-3,-2,7,-15,1,2,2����Ϊ8
int FindGreatestSumOfSubArray(vector<int> array)
{
	if (array.empty())
	{
		return 0;
	}
	int cur = 0;
	int max = array[0];
	for (int i = 0; i < array.size();i++)
	{
		cur += array[i];
		if (cur < 0)
		{
			if (max < cur)
			{
				max = cur;
			}
		}
		if (max <= cur)
		{
			max = cur;
		}
		if (cur < 0)
		{
			cur = 0;
		}
	}
	return max;
}

//ͳ��һ�����������������г��ֵĴ����� 
namespace getnumofk
{
	int getLastK(vector<int> data, int start, int end, int k)
	{
		if (start > end)
		{
			return -1;
		}
		int mid = (start + end) / 2;
		if (data[mid] == k)
		{
			if (mid == end || data[mid + 1] != k)//�ж�ǰһ���ǲ���k
			{
				return mid;
			}
			else
			{
				return getLastK(data, mid + 1, end, k);
			}
		}
		else if (data[mid] < k)
		{
			return getLastK(data, mid + 1, end, k);
		}
		else//data[mid] > k
		{
			return getLastK(data, start, mid - 1, k);			
		}
	}

	int getFirstK(vector<int> data, int start, int end, int k)
	{
		if (start > end)
		{
			return -1;
		}

		int mid = (start + end) / 2;
		if (data[mid] == k)
		{
			if (mid == 0 || data[mid - 1] != k)//�ж�ǰһ���ǲ���k
			{
				return mid;
			}
			else
			{
				return getFirstK(data, start, mid - 1, k);
			}
		}
		else if (data[mid] < k)
		{			
			return getFirstK(data, mid + 1, end, k);
		}
		else//data[mid] > k
		{
			return getFirstK(data, start, mid - 1, k);
		}
	}
	//���Ӷ�nlogn
	int GetNumberOfK(vector<int> data, int k)
	{
		if (data.empty())
		{
			return 0;
		}
		int first = getFirstK(data, 0, data.size() - 1, k);
		int ilast = getLastK(data, 0, data.size() - 1, k);
		
		if (first != -1 && ilast != -1)
		{
			return ilast - first + 1;
		}
		else
		{
			return 0;
		}
	}
}

//һ�����������������������֮�⣬���������ֶ����������Ρ���д�����ҳ�������ֻ����һ�ε����֡� 
namespace findnumonce
{
	//{2,4,3,6,3,2,5,5}
	unsigned int getindexof0(int index)
	{
		int i = 0;
		while (((index & 1) == 0) && (i<8 * sizeof(index)))//һ��Ҫע���������������ȼ�˳��
		{
			index = index >> 1;
			i++;
		}
		return i;
	}

	int isBit(int data,int offset)
	{
		data = data >> offset;
		return data & 1 ? 1 : 0;
	}
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2)
	{
		if (data.empty())return;
		*num1 = *num2 = 0;
		if (data.size() == 1)
		{
			return;
		}
		int index0 = 0;
 		for (int i = 0; i < data.size();i++)
		{
			index0 ^= data[i];//ֻ����������ͬ�Ż����ɷ�0����
		}
		unsigned int indexof0 = getindexof0(index0);//��Ҫ���Ƽ�λ
		//����
		for (int i = 0; i < data.size(); i++)
		{
			if (isBit(data[i], indexof0))
			{
				*num1 ^= data[i];
			}
			else
			{
				*num2 ^= data[i];
			}
		}
	}
}

//��1+2+3+...+n��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case
//�ȹؼ��ּ������ж���䣨A?B:C����
class sum
{
public:
	sum()
	{
		i++;
		tsum += i;
	}
	static void reset()
	{
		i = 0;
		tsum = 0;
	}
	static int getsum()
	{
		return tsum;
	}
	~sum() {}
private:
	static int i;
	static int tsum;
};
int sum::i = 0;
int sum::tsum = 0;
class Solution4
{
public:
	int Sum_Solution(int n)
	{
		sum::reset();
		sum* p = new sum[n];
		delete[] p;
		return sum::getsum();
	}
};

//ɾ�������������ظ����
ListNode* deleteDuplication(ListNode* pHead)
{
	if (!pHead )return NULL;
	ListNode* tmp = pHead;
	//�ж��Ƿ�ͷ���Ϊ�ظ����

	if (tmp->val == tmp->next->val)
	{
		
	}
	return pHead;
}