#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"
#include <assert.h>


void test()
{
	//---------�����������-----------------
	qh::string str0("caonan");
	assert(str0 == "caonan");

	qh::string str1("limei",2);
	assert(str1 == "li");

	qh::string str2(str0);
	assert(str2 == "caonan");

	str0 = "�㷨����";
	assert("�㷨����" == str0);
	str0 = str2;
	assert("caonan" == str0);

	qh::string str3;
	str3 = str1+str0;
	assert("licaonan" == str3);

	qh::string str4;
	str4 = "��������ԭ��" + str3;
	assert("��������ԭ��licaonan" == str4);
	
	qh::string str5;
	str5+= str4;
	assert("��������ԭ��licaonan" == str5);
	str5 += "LINUX";
	assert("��������ԭ��licaonanLINUX" == str5);
	str5 += str0;
	assert("��������ԭ��licaonanLINUXcaonan" == str5);
	assert(str5.size() == 33);
	
	assert(str0[1] == 'a');
	
}
int main(int argc, char* argv[])
{
	//TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
	//TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�
	test();
#ifdef WIN32
	system("pause");
#endif

	return 0;
}

