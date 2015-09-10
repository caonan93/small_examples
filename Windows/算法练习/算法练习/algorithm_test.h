#include "algorithm.h"

void test_StrToInt() {
	Solution s;

	assert(14 == s.StrToInt("14"));
	assert(140 == s.StrToInt("140"));
	assert(141324 == s.StrToInt("141324"));
	assert(0 == s.StrToInt("7d3"));
	assert(0 == s.StrToInt("7d3d"));
	assert(0 == s.StrToInt("a7d3"));
	assert(123 == s.StrToInt("+123"));
	assert(-123 == s.StrToInt("-123"));
	assert(13344 == s.StrToInt("13344"));
}

void test_Find() {
	vector<vector<int> > array(10);
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		array[i].resize(10);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			array[i][j] = sum;
			sum += 2;
		}
	}
	assert(Find(array, 100));
	assert(Find(array, 2));
	assert(!Find(array, 5));
	assert(!Find(array, 7));
	assert(!Find(array, 21));
	assert(!Find(array, 43));
	assert(!Find(array, 59));
	assert(!Find(array, 59));
	assert(Find(array, 20));
	assert(Find(array, 26));
	assert(Find(array, 8));
	assert(Find(array, 46));
	assert(!Find(array, 83));
	assert(Find(array, 128));

}

void test_replaceSpace() {
	char str[100] = " you are my sunm shine  haha ";

	replaceSpace(str, 100);
}

void test_twostack_toqueue() {
	Solution2 b;
	for (int i = 0; i < 5; i++)
	{
		b.push(i);
	}

	for (int i = 0; i < 2; i++)
	{
		cout << b.pop() << " ";
	}

	for (int i = 5; i < 10; i++)
	{
		b.push(i);
	}

	for (int i = 0; i < 8; i++)
	{
		cout << b.pop() << " ";
	}
}

void test_feibonaqi() {
	assert(2 == Fibonacci(3));
	assert(3 == Fibonacci(4));
	assert(5 == Fibonacci(5));
	assert(8 == Fibonacci(6));
	assert(13 == Fibonacci(7));
}

void test_IsPopOrder() {
	int a[] = { 2, 3, 3, 4, 5 };
	int b[] = { 4, 3, 5, 3, 2 };
	vector<int> a1(a, a + 5);
	vector<int> b1(b, b + 5);
	bool isture = IsPopOrder(a1, b1);
}

void test_Solution3() {
	Solution3 s;
	s.push(7);
	s.push(3);
	s.push(5);
	s.push(4);
	s.push(2);
	assert(2 == s.min());
	s.pop();
	assert(3 == s.min());
	assert(4 == s.top());
	s.pop();
	assert(3 == s.min());
}

void test_printListFromTailToHead() {

	int i = 4;
	ListNode *phead = NULL;
	ListNode *pend = NULL;
	while (i--)
	{
		if (!phead)
		{
			phead = new ListNode(i);
			pend = phead;
		}
		else
		{
			pend->next = new ListNode(i);
			pend = pend->next;
		}

	}

	vector<int> res = printListFromTailToHead(phead);

}

void swap_int(int *a, int *b) {
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void test_reOrderArray() {
	int a[] = { 1, 3, 5, 9, 4, 7, 6, 2 };
	vector<int> arr(a, a + 8);
	reOrderArray(arr);
}
ListNode* createList(int i) {
	if (i < 0)
	{
		return NULL;
	}
	ListNode *phead = NULL;
	ListNode *pend = NULL;
	while (i--)
	{
		if (!phead)
		{
			phead = new ListNode(i);
			pend = phead;
		}
		else
		{
			pend->next = new ListNode(i);
			pend = pend->next;
		}

	}
	return phead;
}
void test_FindKthToTail() {
	ListNode* phead = createList(4);
	ListNode *p = FindKthToTail(phead, 3);
}

void test_Clone() {
	int i = 4;
	RandomListNode *phead = NULL;
	RandomListNode *pend = NULL;
	while (i--)
	{
		if (!phead)
		{
			phead = new RandomListNode(i);
			pend = phead;
		}
		else
		{
			pend->next = new RandomListNode(i);
			pend = pend->next;
		}

	}
	RandomListNode* phead1 = phead;
	RandomListNode* phead2 = phead->next;
	RandomListNode* phead3 = phead->next->next;
	RandomListNode* phead4 = phead->next->next->next;
	phead1->random = phead3;
	phead2->random = phead4;
	phead4->random = phead1;
	RandomListNode* res = Clone(phead);
}

void test_NumberOf1() {
	int i = NumberOf1(255);
}

void test_inPermutation() {
	string test("a");
	vector<string> str = Permutation(test);
}

void test_FirstNotRepeatingChar() {
	string str = "abaccdeff";
	int i = FirstNotRepeatingChar(str);
}

TreeNode* createsortTree(const int n) {
	if (n < 0)
	{
		return NULL;
	}

	TreeNode* Root = new TreeNode(n / 2);
	TreeNode* root;
	for (int i = 0; i < n; i++)
	{
		if (i == n / 2)
		{
			continue;
		}
		TreeNode* newnode = new TreeNode(i);
		root = Root;
		while (1)
		{
			if (newnode->val < root->val)
			{
				if (root->left == NULL)
				{
					root->left = newnode;
					break;
				}
				else
				{
					root = root->left;
				}
			}
			else //newnode->val > root->val
			{
				if (root->right == NULL)
				{
					root->right = newnode;
					break;
				}
				else
				{
					root = root->right;
				}
			}
		}
	}
	return Root;

}
void test_PrintFromTopToBottom() {
	TreeNode* root = createsortTree(19);
	vector<int> res = PrintFromTopToBottom(root);
}

void test_ReverseList() {
	ListNode* phead = createList(1);
	ListNode* res = ReverseList(phead);
}
void test_MoreThanHalfNum_Solution() {
	int a1[] = { 2, 2, 2, 2, 2, 1, 3, 4, 5 };
	vector<int> a(a1, a1 + 9);
	int res = MoreThanHalfNum_Solution(a);
}

void test_partion() {
	int a[] = { 1, 4, 7, 2, 2, 4, 5, 2, 3, 1, 2, 3, 4, 56, 7 };
	vector<int> a1(a, a + sizeof(a) / 4);
	quicksort(a1, 0, a1.size() - 1);
}

void test_Power() {
	unsigned int a = -1;
	double res = Power(0, 0);
}
void test_GetLeastNumbers_Solution() {
	int a[] = { 4, 5, 1, 6, 2, 7, 3, 8 };
	vector<int> a1(a, a + sizeof(a) / 4);
	vector<int> res = GetLeastNumbers_Solution(a1, 4);
}


void test_minNumberInRotateArray() {
	int arr[] = { 31322, 31329, 31330, 31339, 31347,
		31348, 31349, 31351, 31357, 31361, 31365, 31371, 31371, 31375, 31376, 31391,
		31395, 31413, 31417, 31417, 31418, 31426, 31426, 31429, 31441, 31443, 31447,
		31450, 31453, 31458, 31461, 31461, 31463, 31464, 31467, 31468, 31476, 31478,
		31480, 31490, 31493, 31493, 31495, 31496, 31497, 31499, 31502, 31503, 31504,
		31505, 31506, 31520, 31522, 31523, 31531, 31539, 31539, 31540, 31543, 31544,
		31547, 31550, 31552, 31556, 31559, 31561, 31565, 31577, 31579, 31584, 31585,
		31587, 31588, 31591, 31593, 31594, 31597, 31597, 31597, 31598, 31599, 31601,
		31620, 31620, 31622, 31623, 31623, 31626, 31627, 31628,
		31065, 31066, 31068, 31071, 31074, 31077, 31088, 31089, 31094,
		31098, 31098, 31099, 31101, 31102, 31103, 31107, 31111, 31111, 31115, 31119,
		31121, 31122, 31126, 31127, 31139, 31142, 31146, 31148, 31149, 31151, 31153,
		31155, 31155, 31159, 31163, 31165, 31168, 31172, 31173, 31175, 31180, 31184,
		31185, 31196, 31197, 31199, 31202, 31203, 31210, 31215, 31219, 31219, 31221,
		31226, 31230, 31238, 31240, 31244, 31245, 31248, 31250, 31256, 31258, 31260,
		31261, 31262, 31269, 31270, 31274, 31274, 31276, 31283, 31286, 31302, 31310,
		31310, 31311, 31313, 31314, 31316, 31321
	};
	vector<int> varr(arr, arr + sizeof(arr) / sizeof(int));
	int res = minNumberInRotateArray(varr);
}

void test_FindFirstCommonNode() {
	ListNode *list1 = createList(10);
	ListNode *list2 = createList(4);
	/*ListNode *tmp = list2;
	while (tmp->next)
	{
	tmp = tmp->next;
	}
	tmp->next = list1->next->next->next;*/
	ListNode *res = FindFirstCommonNode(list1, list2);
}

void test_PrintMinNumber() {
	int a[] = { 3, 32, 321 };
	vector<int> numarrary(a, a + sizeof(a) / 4);
	soutaion stest;
	string res = stest.PrintMinNumber(numarrary);
}

void test_duplicate() {
	int num[] = { 2, 3, 1, 0, 2, 5, 3 };
	int num1;
	bool res = duplicate(num, 7, &num1);
}

void test_Merge()
{
	ListNode *pHead1 = createList(5);
	ListNode *pHead2 = createList(10);
	ListNode*res = Merge(pHead1, pHead2);
}

void test_FindGreatestSumOfSubArray()
{
	vector<int> arr = { 6, -3, -2, 7, -15, 1, 2, 2 };
	int max = FindGreatestSumOfSubArray(arr);
}

void test_GetNumberOfK()
{
	vector<int> arr = { 1, 2, 2, 2,2,2,3 ,3,4,4,5,6,7};
	int n = getnumofk::GetNumberOfK(arr, 2);
}

void test_FindNumsAppearOnce()
{
	vector<int> arr = { 5, 5 };
	int n1, n2;
	findnumonce::FindNumsAppearOnce(arr, &n1, &n2);
}

void test_Sum_Solution()
{
	Solution4 a;
	int n = a.Sum_Solution(5);
}

void test_VerifySquenceOfBST()
{
	vector<int> arr = { 7,4,6,5};
	bool ret = verfying::VerifySquenceOfBST(arr);
}

void test_Convert()
{
	TreeNode* proot = new TreeNode(5);

	TreeNode* x = new TreeNode(3);
	TreeNode* p2 = new TreeNode(2);
	TreeNode* p3 = new TreeNode(4);
	TreeNode* p4 = new TreeNode(1);
	TreeNode* p5 = new TreeNode(7);
	TreeNode* p6 = new TreeNode(6);
	TreeNode* p7 = new TreeNode(8);
	proot->left = x;//TODO:这里命名很诡异如果是p1就会报错，具体和文件包含问题相关，最好不要.h包含.h
	proot->right = p5;
	x->left = p2;
	x->right = p3;
	p2->left = p4;
	p5->left = p6;
	p5->right = p7;

	TreeNode*root = convert_tree::Convert(proot);
}

void test_Mirror()
{
	TreeNode* root = createsortTree(10);
	Mirror(root);
}

void test_HasSubtree()
{
	TreeNode* proot1 = createsortTree(40);
	TreeNode* proot2 = proot1->left;
	bool res = subtree::HasSubtree(proot1, proot2);
}

void test_TreeDepth()
{
	TreeNode* proot1 = createsortTree(40);
	int dep = TreeDepth(proot1);
}

void test_IsBalanced_Solution()
{
	TreeNode* proot1 = createsortTree(2);
	bool res = isBalance::IsBalanced_Solution(proot1);
}

void test_FindPath()
{
	TreeNode* proot1 = new TreeNode(10);
	TreeNode* pnode2 = new TreeNode(5);
	TreeNode* pnode3 = new TreeNode(12);
	TreeNode* pnode4 = new TreeNode(4);
	TreeNode* pnode5 = new TreeNode(7);
	proot1->left = pnode2;
	proot1->right = pnode3;
	pnode2->left = pnode4;
	pnode2->right = pnode5;

	TreeNode* proot2 = new TreeNode(5);
	TreeNode* pn1 = new TreeNode(4);
	TreeNode* pn2 = new TreeNode(3);
	TreeNode* pn3 = new TreeNode(2);
	TreeNode* pn4 = new TreeNode(1);
	proot2->left = pn1;
	pn1->right = pn2;
	pn2->right = pn3;
	pn3->right = pn4;
	TreeNode* proot3 = createsortTree(100);

  vector<vector<int> > ret = findpath_::FindPath(proot3, 1275);
}

void test_EntryNodeOfLoop()
{
	ListNode* ring = createList(5);
	ListNode* tmp = ring;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	ListNode* tmp2 = ring->next->next;
	tmp->next = tmp2;
	ListNode* node = EntryNodeOfLoop(ring);
}


void test_deleteDuplication()
{
	ListNode*head = createList(5);
	ListNode* t1 = new ListNode(4);
	t1->next = head;
	ListNode*t2 = new ListNode(4);
	t2->next = t1;
	
	ListNode*p =new struct ListNode(2);
	p->next = head->next->next;
	head->next->next = p;

	ListNode* node_head = delsamenode_::deleteDuplication(t2);
}

void test_GetNext()
{
	TreeLinkNode *root = new TreeLinkNode(1);
	TreeLinkNode *node1 = new TreeLinkNode(2);
	TreeLinkNode *node2 = new TreeLinkNode(3);
	TreeLinkNode *node3 = new TreeLinkNode(4);
	TreeLinkNode *node4 = new TreeLinkNode(5);
	root->left = node1;
	node1->next = root;
	root->right = node2;
	node2->next = root;
	node1->left = node3;
	node1->right = node4;
	node3->next = node1;
	node4->next = node1;
	TreeLinkNode*ret = GetNext(node4);
}

void test_reConstructBinaryTree()
{
	vector<int> pre = { 1, 2, 4, 7, 3, 5, 6, 8 };
	vector<int> in = { 4, 7, 2, 1, 5, 3, 8, 6 };
	TreeNode* root = rebuidtree::reConstructBinaryTree(pre,in);
}

void test_maxInWindows()
{
	vector<int> window = { 10, 14, 12, 11 };
	vector<int> ret = maxInWindows(window, 5);
}

void test_getPos()
{
	vector<int> test = { 1, 3, 3,3,5, 7, 9 };
	int ret = getPos(test, 5, 3);
}

void test_findFirstRepeat()
{
	string arr = "kdbaaak";
	char c = findFirstRepeat(arr, 7);
}

void test_findCoder()
{
	vector<string> arr = { "coder", 
		"xfcoderjbixcoderpuvwhcoderodpacoderycacoderjskcoderptcoderkcod \
		erdtwcodergalucoderfnjpwcoderagmtcodermkzoqcoderysqsycoderlvc \
		codervbycoderacuagcodereueucoderscoderrbcoder", 
		"xbxcoderlafrcoderyuccoderjcoderefldcodersstujcoderelcoder", 
		"dvfowcoderfencoderqekcoderbtmcoderehcoderriyjdcodermocoder", 
		"ncbacoderjnvcoderfqcoderenwjpcoderkintcoderwtgcoder" };
	vector<string> ret = find_::findCoder(arr, 5);
}