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
//         佛祖保佑       永无BUG     永不修改                  //  
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
	for (; i < array.size(); i++)//行
	{
		for (; j >= 0; j--)//列
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

	int end = space * 2 + iLen + 1;//1占位‘\0’

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

	stack<int> ostack;//借用一个栈的辅助空间
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

vector<int> printListFromTailToHead(struct ListNode* head)//从尾到头打印链表
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
	if (p3 == NULL) 
	{ 
		res.clear(); 
		res.push_back(p2->val);
		res.push_back(p1->val); 
		return res; 
	}
	//大于等于三个结点
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

	//在给它调回来
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
	//利用快慢指针
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
	//右移动如果是负数的话会出现左面补1的现象
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
	tmpHead->next = new RandomListNode(tmpHead->label);//复制最后一个结点

	tmpHead = pHead;
	while (tmpHead)//复制复杂结点
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

	//拆开链表
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
//重建二叉树例如输入前序遍历序列TODO:
//{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
namespace rebuidtree
{
	TreeNode* reConstructBinaryTree(int* pre, 
																	int* preEnd,
																	int* in,
																	int* inEnd)
	{
		int rootval = pre[0];
		TreeNode* root = new TreeNode(rootval);
		if (pre == preEnd)
		{
			if (in == inEnd && *pre == *in)
			{
				return root;
			}
		}

		//在中序遍历找到根结点的值
		int *rootIn = in;
		while (rootIn <= inEnd && *rootIn != rootval)
		{
			rootIn++;
		}
		if (rootIn == inEnd && *rootIn != rootval)
		{
			return NULL;//不合法的前序和中序遍历
		}
		int left_len = rootIn - in;
		int* left_pre_end = pre + left_len;
		if (left_len>0)
		{
			root->left = reConstructBinaryTree(pre + 1, left_pre_end, in, rootIn - 1);
		}
		if (left_len < preEnd-pre)
		{
			root->right = reConstructBinaryTree(left_pre_end + 1, preEnd, 
																					rootIn + 1, inEnd);
		}
		return root;
	}

	struct TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in)
	{
		if (pre.empty() || in.empty() || pre.size() != in.size())
			return NULL;
		int* prepre = new int[pre.size()];
		int* inin = new int[in.size()];
		memcpy(prepre, &*pre.begin(), pre.size()*sizeof(int));
		memcpy(inin, &*in.begin(), in.size()*sizeof(int));
		return reConstructBinaryTree(prepre, prepre + pre.size() - 1,
																 inin, inin + in.size() - 1);
	}
}

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

//堆排序
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
//{3,4,5,1,2}为{1,2,3,4,5}
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
			//出现相等状况o(n)复杂度
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
	//分别遍历两个链表看哪个比较长
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
	//例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。
	string PrintMinNumber(vector<int> numbers) {
		if (numbers.empty())
		{
			return NULL;
		}
		//先将数字转换成字符串，在将字符串之间进行比较
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
//TODO：这里for_each的返回值重载颇为神奇！
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
		//判断str1str2大还是str2str1大
		string strcompare1 = str1 + str2;
		string strcompare2 = str2 + str1;
		return strcompare1 > strcompare2 ? true : false;
	}
};


/*
在一个长度为n的数组里的所有数字都在0到n - 1的范围内。 数组中某些数字是重复的，
但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。
例如，如果输入长度为7的数组{ 2, 3, 1, 0, 2, 5, 3 }，那么对应的输出是重复的数字2或者3。*/
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
//合并排序链表
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

//连续子数组的最大和6,-3,-2,7,-15,1,2,2最大和为8
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

//统计一个数字在排序数组中出现的次数。 
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
			if (mid == end || data[mid + 1] != k)//判断前一个是不是k
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
			if (mid == 0 || data[mid - 1] != k)//判断前一个是不是k
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
	//复杂度nlogn
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

//一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。 
namespace findnumonce
{
	//{2,4,3,6,3,2,5,5}
	unsigned int getindexof0(int index)
	{
		int i = 0;
		while (((index & 1) == 0) && (i<8 * sizeof(index)))//一定要注意这里的运算符优先级顺序
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
			index0 ^= data[i];//只有两个数不同才会异或成非0的数
		}
		unsigned int indexof0 = getindexof0(index0);//需要右移几位
		//分组
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

//求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case
//等关键字及条件判断语句（A?B:C）。
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

namespace delsamenode_
{
	//删除排序链表中重复结点
	ListNode* deleteDuplication(ListNode* pHead)
	{
		if (!pHead) return NULL;
		ListNode *pPre = NULL;
		ListNode* node = pHead;
		while (node)
		{
			ListNode* pNext = node->next;
			bool shouldDel = false;
			if (pNext && node->val == pNext->val)
			{
				shouldDel = true;
			}
			if (!shouldDel)
			{
				pPre = node;
				node = node->next;
			}
			else
			{
				ListNode* to_be_del = node;
				int val = node->val;
				while (to_be_del&&to_be_del->val == val)
				{
					pNext = to_be_del->next;
					delete to_be_del;
					to_be_del = NULL;
					to_be_del = pNext;
				}
				if (!pPre)
				{
					pHead = pNext;
				}
				else
				{
					pPre->next = pNext;
				}
				node = pNext;
			}
		}	
		return pHead;
	}
}



//输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes, 
//否则输出No。假设输入的数组的任意两个数字都互不相同。
namespace verfying
{
	bool verfy(vector<int>& data, int start, int end)
	{
		if (start>=end)
		{
			return true;
		}
		int i = end;
		int ending = data[end];
		for (; i >= start; i--)
		{
			if (data[i] < ending)
			{
				//找到了左子树
				break;
			}
		}

		if (i < start)//没有左子树
		{
			return true;
		}
	
		//判断左子树有没有大于右子树的
		for (int j = i; j >= start; j--)
		{
			if (data[j] > ending)
			{
				return false;
			}
		}
		bool left = true;
		//判断左子树
		left = verfy(data, 0, i);
		//判断右子树
		bool right = true;
		right = verfy(data, i + 1, end);
		return left&&right;
	}
	bool VerifySquenceOfBST(vector<int> sequence)
	{
		if (sequence.empty())
		{
			return false;
		}
		int end = sequence.size() - 1;
		return verfy(sequence, 0, end);
	}
}

//二叉搜索树与双向链表
namespace convert_tree
{
	void convert(TreeNode* node, TreeNode** lastnode)
	{
		if (!node)
		{
			return;
		}
		TreeNode* current = node;
		if (node->left)
		{
			convert(node->left, lastnode);
		}		
		node->left = *lastnode;
		if (*lastnode)
		{
			(*lastnode)->right = current;
		}
		*lastnode = current;

		if (node->right)
		{
			convert(node->right, lastnode);
		}
	}
	TreeNode* Convert(TreeNode* pRootOfTree)
	{
		if (!pRootOfTree)
		{
			return NULL;
		}
		TreeNode* lastNode = NULL;
		convert(pRootOfTree, &lastNode);
		TreeNode* pHeadList = lastNode;
		while (pHeadList!= NULL && pHeadList->left != NULL)
		{
			pHeadList = pHeadList->left;
		}
		return pHeadList;
	}
}

//操作给定的二叉树，将其变换为源二叉树的镜像。
void Mirror(TreeNode *pRoot)
{
	if (!pRoot)
	{
		return;
	}
	std::queue<TreeNode*> oTreeQueue;
	oTreeQueue.push(pRoot);
	while (!oTreeQueue.empty())
	{
		TreeNode* out = oTreeQueue.front();
		oTreeQueue.pop();
		if (out->left || out->right)
		{
			std::swap(out->left,out->right);
			if (out->left)
			{
				oTreeQueue.push(out->left);
			}
			if (out->right)
			{
				oTreeQueue.push(out->right);
			}
		}
	}
}

namespace subtree
{
	TreeNode* find_same_value(TreeNode*pRoot1, TreeNode* pRoot2)
	{
		if (pRoot1)
		{
			if (pRoot1->val == pRoot2->val)
			{
				return pRoot1;
			}
			TreeNode *left = find_same_value(pRoot1->left, pRoot2);
			if (left)
			{
				return left;
			}
			TreeNode *right = find_same_value(pRoot1->right, pRoot2);
			if (right)
			{
				return right;
			}
		}
		return NULL;
	}

	bool hasSubSub(TreeNode* pRoot1, TreeNode* pRoot2)
	{
		bool res = true;
		if (pRoot1 == NULL && pRoot2 == NULL)
		{
			return true;
		}
		else if (pRoot1 == NULL && pRoot2!=NULL)
		{
			return false;
		}
		if (pRoot2==NULL)
		{
			return true;
		}

		if (pRoot1->val != pRoot2->val)
		{
			return false;
		}
		else
		{
			res = hasSubSub(pRoot1->left, pRoot2->left);
			if (res == false)
			{
				return false;
			}
			res = hasSubSub(pRoot1->right, pRoot2->right);
			if (res == false)
			{
				return false;
			}
		}
		return res;
	}
	//判断root2是不是root1的子结构
	bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
	{
		if (!pRoot1 || !pRoot2)
		{
			return false;
		}
		//先找到第一个值相同的结点
		TreeNode*root1 = find_same_value(pRoot1, pRoot2);
		if (!root1)
		{
			return false;
		}
		bool has = hasSubSub(root1, pRoot2);
		if (!has)
		{
			bool res = HasSubtree(root1->left, pRoot2);
			if (res)
			{
				return true;
			}
			res = HasSubtree(root1->right, pRoot2);
			if (res)
			{
				return true;
			}
		}
		else
		{
			return true;
		}
		return false;
	}
}

//二叉树的深度
int TreeDepth(TreeNode* pRoot)
{
	if (pRoot == NULL)
	{
		return 0;
	}
	int leftDep = TreeDepth(pRoot->left);
	int rightDep = TreeDepth(pRoot->right);
	if (leftDep>rightDep)
	{
		return leftDep + 1;
	}
	else
	{
		return rightDep + 1;
	}
}

namespace isBalance
{
	int TreeDepthBalanced(TreeNode* pRoot)
	{
		if (pRoot == NULL)
		{
			return 0;
		}
		int leftDep = TreeDepthBalanced(pRoot->left);
		int rightDep = TreeDepthBalanced(pRoot->right);
		if (leftDep > rightDep)
		{
			return leftDep + 1;
		}
		else
		{
			return rightDep + 1;
		}
	}

	//输入一棵二叉树，判断该二叉树是否是平衡二叉树。
	bool IsBalanced_Solution(TreeNode* pRoot)
	{
		if (!pRoot)
		{
			return true;
		}

		bool res = IsBalanced_Solution(pRoot->left);
		if (res == false)
		{
			return false;
		}
		res = IsBalanced_Solution(pRoot->right);
		if (res == false)
		{
			return false;
		}
		//计算左子树的深度
		int leftDept = TreeDepthBalanced(pRoot->left);
		//计算右子树的深度
		int rightDept = TreeDepthBalanced(pRoot->right);

		if (leftDept>rightDept)
		{
			if (leftDept-rightDept > 1)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (leftDept<rightDept)
		{
			if (rightDept-leftDept >1)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else//leftDept == rightDept
		{
			return true;
		}		
	}

}

namespace findpath_
{
	void findpath(TreeNode* root, 
								int expectNum, 
								vector<vector<int> >&ret,
								int currentsum, vector<int> &oStackValue)
	{
		static int i = 0;
		//用一个vector模拟栈区存储二叉树的路径
		
		oStackValue.push_back(root->val);
		currentsum += root->val;
		bool isleaf = root->left == NULL && root->right == NULL;	

		if (currentsum == expectNum && isleaf)
		{
			//输出序列
			ret.resize(++i);//这样做效率有点低
			ret[i - 1].resize(oStackValue.size());
			ret[i - 1].assign(oStackValue.begin(), oStackValue.end());
		}

		if (root->left)
			findpath(root->left, expectNum, ret, currentsum, oStackValue);
		if (root->right)
			findpath(root->right, expectNum, ret, currentsum, oStackValue);
		oStackValue.pop_back();
	}
	//二叉树中和为某一值的路径
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber)
	{		
		vector<vector<int> > ret;
		if (!root)
		{
			return ret;
		}	
		//前序遍历
		int current_sum = 0;
		vector<int> oStackValue;
		findpath(root, expectNumber, ret, current_sum, oStackValue);
		return ret;
	}
}//end namespace

//链表中环的入口结点
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	if (!pHead)
	{
		return NULL;
	}
	ListNode* low = pHead;
	ListNode* quick = pHead->next;
	if (!quick)
	{
		return NULL;
	}
	bool hasring = false;
	//判断链表有没有环
	do
	{
		if (quick == low)
		{
			//链表有环
			hasring = true;
			break;
		}
		low = low->next;
		quick = quick->next;
		if (quick)
		{
			quick = quick->next;
		}
	}while (quick&&low);

	int iringCount = 0;
	if (hasring)
	{
		//计算环中有几个结点
		do 
		{
			low = low->next;
			iringCount++;
		} while (quick != low);

		//重新初始化快慢链表指针
		low = pHead;
		quick = pHead;
		while (iringCount--)
		{
			quick = quick->next;
		}
		//一起向后走
		while (1)
		{
			if (quick == low)
			{
				return quick;
			}
			quick = quick->next;
			low = low->next;
		}
	}
	return NULL;
}

struct TreeLinkNode
{
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL)
	{

	}
};

//二叉树的下一个结点
TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
	if (!pNode) return NULL;
	TreeLinkNode *current_parent = NULL;
	TreeLinkNode *pNext = NULL;

	if (pNode->right != NULL)
	{
		pNode = pNode->right;
		pNext = pNode;
		while (pNext&&pNext->left != NULL)
		{
			pNext = pNext->left;
		}
	}
	else if (pNode->next)//存在父节点
	{
		//判断是不是该父亲的右子树
		current_parent = pNode->next;
		TreeLinkNode* node = pNode;
		while (current_parent&&node == current_parent->right)
		{
			current_parent = current_parent->next;
			node = node->next;
		}
		pNext = current_parent;
	}
	
	return pNext;
}

//滑动窗口的最大值
/*给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组
{ 2, 3, 4, 2, 6, 2, 5, 1 }及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为
{ 4, 4, 6, 6, 6, 5 }； 针对数组{ 2, 3, 4, 2, 6, 2, 5, 1 }的滑动窗口有以下6个：
{ [2, 3, 4], 2, 6, 2, 5, 1 }，{ 2, [3, 4, 2], 6, 2, 5, 1 }，
{ 2, 3, [4, 2, 6], 2, 5, 1 }，{ 2, 3, 4, [2, 6, 2], 5, 1 }，
{ 2, 3, 4, 2, [6, 2, 5], 1 }，{ 2, 3, 4, 2, 6, [2, 5, 1] }*/
vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
	vector<int> ret;
	if (num.emplace()) return ret;
	
}