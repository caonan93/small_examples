#include "algorithm_test.h"
#include "commonproblem_test.h"
#pragma warning(disable:4996)
void test() {
	test_StrToInt();
	test_Find();
	test_replaceSpace();
	test_twostack_toqueue();
	test_feibonaqi();
	test_IsPopOrder();
	test_Solution3();
	test_printListFromTailToHead();
	test_reOrderArray();
	test_FindKthToTail();
	test_Clone();
	test_NumberOf1();
	test_inPermutation();
	test_FirstNotRepeatingChar();
	test_PrintFromTopToBottom();
	test_ReverseList();
	test_MoreThanHalfNum_Solution();
	test_partion();
	test_GetLeastNumbers_Solution();
	test_Power();
	test_minNumberInRotateArray();
	test_FindFirstCommonNode();
	test_PrintMinNumber();
	test_duplicate();
	test_Merge();
	test_FindGreatestSumOfSubArray();
	test_GetNumberOfK();
	test_FindNumsAppearOnce();
	test_Sum_Solution();
	test_deleteDuplication();
	test_VerifySquenceOfBST();
	test_Convert();
	test_Mirror();
	test_HasSubtree();
	test_TreeDepth();
	test_IsBalanced_Solution();
	test_FindPath();
	test_EntryNodeOfLoop();
	test_deleteDuplication();
	test_GetNext();
	test_reConstructBinaryTree();
	test_maxInWindows();
	test_getPos();
	test_findFirstRepeat();
	test_findCoder();
}

void common() {
	common_memcpy();
	common_noinherit();
	common_heap_stack_only();
	common_KMP();
}

int main() {
	test();
	common();
	return 0;
}