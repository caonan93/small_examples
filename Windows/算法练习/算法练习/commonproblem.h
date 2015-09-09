#include <stdlib.h>
#include <stdio.h>
//ʵ��һ��Memcpy����
//ע��Ҫ�����ڴ��ص�,Ҫ��֤��������Ŀ�ĵ�ַ���Ḳ��Դ��ַ�ռ�
namespace mymemcpy {
	void* memcpy(void* dst, const void *src, size_t len) {
		if (!dst || !src || len <= 0)
		{
			return NULL;
		}
		void *ret = dst;
		if ((char*)dst >= (char*)src+len || dst < src)
		{
			//�ڴ�û���ص� ��dst�ĵ͵�ַ��������
			while (len--)
			{
				*(char*)dst = *(char*)src;
				dst = (char*)dst + 1;
				src = (char*)src + 1;
			}		
		}
		else{
			//�Ӹߵ�ַ����
			while (len--)
			{
				dst = (char*)dst + len - 1;
				src = (char*)src + len - 1;
				*(char*)dst = *(char*)src;
			}		
		}
		return ret;
	}
}

//��дstl��vector
/*
vector�����ݰ����Լ�������ʽ����array�ǳ����ơ����ߵ�Ψһ�������ڿռ�����õ�����ԡ�
array�Ǿ�̬�ռ䣬һ�������˾Ͳ��ܸı䣻Ҫ�����󣨻�С��һ��ķ��ӣ����ԣ�һ����ϸ�����ɿͻ�����
��������������һ���¿ռ䣬Ȼ��Ԫ�شӾ�ַһһ������ַ���ٰ�ԭ���Ŀռ��ͻ���ϵͳ��vector�Ƕ�̬
�ռ䣬����Ԫ�صļ��룬�����ڲ����ƻ���������ռ���������Ԫ�ء���ˣ�vector�����ö����ڴ�ĺ���
���������õ�������кܴ�İ�����������Ҳ������Ϊ���¿ռ䲻���һ��ʼҪ��һ�����ͷ��array�ˣ���
�ǿ��԰���ʹ��array���Զ����ö��١�
vector��ʵ�ּ������ؼ�������Դ�С�Ŀ����Լ���������ʱ�������ƶ�Ч�ʡ�һ��vector�ľ��пռ�����
������ͻ���ÿ����һ��Ԫ�أ�vector���ڲ�ֻ������һ��Ԫ�صĿռ䣬ʵΪ���ǡ���Ϊ��ν����ռ�
�����۶�󣩣�һ��������˵���ǡ�  �����¿ռ� / �����ƶ� / �ͻ��ɿռ�  ���Ĵ󹤳̣�ʱ��ɱ��ܸߣ�
Ӧ�ü���ĳ��δ����ѵĿ��ǡ��Ժ����Ǳ�ɿ���SGI vector�Ŀռ����ò����ˡ�
���⣬����  vectorά������һ���������Կռ䣬����vector֧�������ȡ  ��
ע�⣺vector��̬���Ӵ�Сʱ����������ԭ�ռ�֮������¿ռ䣨��Ϊ�޷���֤ԭ�ռ�֮�����пɹ����õ�
�ռ䣩��������ԭ��С��������������һ��ϴ�Ŀռ䣬Ȼ��ԭ���ݿ���������Ȼ��ſ�ʼ��ԭ����֮��
����Ԫ�أ����ͷ�ԭ�ռ䡣��ˣ�  ��vector���κβ�����һ������ռ��������ã�ָ��ԭvector������
�������Ͷ�ʧЧ��  �����ǳ���Ա�׷���һ����������С�ġ�*/

//��c++���һ�������Ա��̳е���
namespace vb {
	template<typename T>
	class grandfather {
		friend T;
	private: 
		grandfather() {}
		~grandfather() {}
	};
	//����ͨ����̳еĻ���ʹ��child��̳�parentʵ���ϼ̳е���grandfather��
	//grandfatherʵ���Ϲ��캯����˽�е����Բ��ܽ��й���
	class parent :public virtual grandfather<parent> {
	public:
		parent() {
			cout << "parnet";
		}
		~parent() {
			cout << "~parent";
		}
	};
}

//��ζ���һ��ֻ���ڶ��ϣ�ջ�ϣ����ɶ������?
namespace onlyheapobect {
	//ֻ�ܶ����ڶ���
	class A {
	protected:
		A() {}
		~A() {}
	public:
		static A* create() {
			return new A;
		}
		void destroy() {
			delete this;
		}
	};

	//ֻ�ܽ�����ջ��
	//����new��delete���������
	class B {
	private:
		void* operator new(size_t){}
		void operator delete(void* ptr) {}
	public:
		B() {}
		~B() {}
	};
}

//ʵ��kmp�㷨
namespace kmp
{
	int* GetNext(const char* str)
	{
		if (!str) return NULL;
		int i = 1;
		int ID = i - 1;
		int* pNext = new int[strlen(str)];
		pNext[ID] = 0;
		while (str[i] != '\0')
		{
			if (str[pNext[ID]] == str[i])
			{
				pNext[i] = pNext[ID] + 1;
				i++;
				ID = i - 1;
				continue;
			}
			if (pNext[ID] == 0)
			{
				pNext[i] = 0;
				i++;
				ID = i - 1;
				continue;
			}
			ID = pNext[ID] - 1;
		}
		return pNext;
	}
	char* KMP(char* src, const char* dest)
	{
		if (!src || !dest) return NULL;
		int* Next = GetNext(dest);
		int j = 0;
		const char* substr = dest;
		while (*src != '\0')
		{	
			if (*src == substr[j])
			{
				while (substr[j] == *src)
				{
					j++;
					src++;
					if (substr[j] == '\0')
					{
						delete[] Next;
						Next = NULL;
						return src - j;
					}
				}
			}
			else
			{
				if (j == 0)
					src++;
				else
					j = Next[j - 1];
			}		
		}
		delete[]Next;
		Next = NULL;
		return NULL;
	}
}