#include "commonproblem.h"

void common_memcpy() {
	char arr[10];
	char arr2[] = "asdfsadf";
	mymemcpy::memcpy(arr,arr2,sizeof(arr2));
}

/*error:
class child :public vb::parent {
public:
	child() {
		cout << "child";
	}
	~child() {
		cout << "~child";
	}
};*/
void common_noinherit() {
	vb::parent oparent;//������ջ�϶���
	vb::parent *p = new vb::parent;//�����ٶ��϶���	
}

void common_heap_stack_only() {
	onlyheapobect::A *a = onlyheapobect::A::create();//ֻ���ڶ��϶���
	onlyheapobect::B b;
	//onlyheapobect::B *b = new onlyheapobect::B;  error
}