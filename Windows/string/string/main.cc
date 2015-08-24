#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"
#include <assert.h>


void test()
{
	//---------创建对象测试-----------------
	qh::string str0("caonan");
	assert(str0 == "caonan");

	qh::string str1("limei",2);
	assert(str1 == "li");

	qh::string str2(str0);
	assert(str2 == "caonan");

	str0 = "算法导论";
	assert("算法导论" == str0);
	str0 = str2;
	assert("caonan" == str0);

	qh::string str3;
	str3 = str1+str0;
	assert("licaonan" == str3);

	qh::string str4;
	str4 = "计算机组成原理" + str3;
	assert("计算机组成原理licaonan" == str4);
	
	qh::string str5;
	str5+= str4;
	assert("计算机组成原理licaonan" == str5);
	str5 += "LINUX";
	assert("计算机组成原理licaonanLINUX" == str5);
	str5 += str0;
	assert("计算机组成原理licaonanLINUXcaonan" == str5);
	assert(str5.size() == 33);
	
	assert(str0[1] == 'a');
	
}
int main(int argc, char* argv[])
{
	//TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
	//TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
	test();
#ifdef WIN32
	system("pause");
#endif

	return 0;
}

