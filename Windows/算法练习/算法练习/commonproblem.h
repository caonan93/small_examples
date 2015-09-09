#include <stdlib.h>
#include <stdio.h>
//实现一个Memcpy函数
//注意要避免内存重叠,要保证拷贝到的目的地址不会覆盖源地址空间
namespace mymemcpy {
	void* memcpy(void* dst, const void *src, size_t len) {
		if (!dst || !src || len <= 0)
		{
			return NULL;
		}
		void *ret = dst;
		if ((char*)dst >= (char*)src+len || dst < src)
		{
			//内存没有重叠 从dst的低地址拷贝即可
			while (len--)
			{
				*(char*)dst = *(char*)src;
				dst = (char*)dst + 1;
				src = (char*)src + 1;
			}		
		}
		else{
			//从高地址拷贝
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

//仿写stl的vector
/*
vector的数据安排以及操作方式，与array非常相似。两者的唯一区别在于空间的运用的灵活性。
array是静态空间，一旦配置了就不能改变；要换个大（或小）一点的房子，可以，一切琐细都得由客户端自
己来：首先配置一块新空间，然后将元素从旧址一一搬往新址，再把原来的空间释还给系统。vector是动态
空间，随着元素的加入，它的内部机制会自行扩充空间以容纳新元素。因此，vector的运用对于内存的合理
利用与运用的灵活性有很大的帮助，我们再也不必因为害怕空间不足而一开始要求一个大块头的array了，我
们可以安心使用array，吃多少用多少。
vector的实现技术，关键在于其对大小的控制以及重新配置时的数据移动效率。一旦vector的旧有空间满载
，如果客户端每新增一个元素，vector的内部只是扩充一个元素的空间，实为不智。因为所谓扩充空间
（不论多大），一如稍早所说，是”  配置新空间 / 数据移动 / 释还旧空间  “的大工程，时间成本很高，
应该加入某种未雨绸缪的考虑。稍后我们便可看到SGI vector的空间配置策略了。
另外，由于  vector维护的是一个连续线性空间，所以vector支持随机存取  。
注意：vector动态增加大小时，并不是在原空间之后持续新空间（因为无法保证原空间之后尚有可供配置的
空间），而是以原大小的两倍另外配置一块较大的空间，然后将原内容拷贝过来，然后才开始在原内容之后构
造新元素，并释放原空间。因此，  对vector的任何操作，一旦引起空间重新配置，指向原vector的所有
迭代器就都失效了  。这是程序员易犯的一个错误，务需小心。*/

//用c++设计一个不可以被继承的类
namespace vb {
	template<typename T>
	class grandfather {
		friend T;
	private: 
		grandfather() {}
		~grandfather() {}
	};
	//这里通过虚继承的机制使得child类继承parent实际上继承的是grandfather而
	//grandfather实际上构造函数是私有的所以不能进行构造
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

//如何定义一个只能在堆上（栈上）生成对象的类?
namespace onlyheapobect {
	//只能定义在堆上
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

	//只能建立在栈上
	//重载new和delete运算符即可
	class B {
	private:
		void* operator new(size_t){}
		void operator delete(void* ptr) {}
	public:
		B() {}
		~B() {}
	};
}

//实现kmp算法
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