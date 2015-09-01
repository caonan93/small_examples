#include <curl/curl.h>
#include <iostream>
#include <stdio.h>
using namespace std;

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
	FILE *fp = static_cast<FILE*>(userp);
	size_t return_size = ::fwrite(buffer, size, nmemb, fp);
	cout << (char*)buffer;
	return return_size;
}

int test_single() {
	//��ʼ��ȫ�ֱ���
	//�ڳ�����Ӧ�þ��������ε���curl_global_init��curl_global_cleanup
	curl_global_init(CURL_GLOBAL_ALL);

	//�����ϣ�ÿ���̶߳�Ӧ�����Լ���easy handle��������ͨ�ţ������Ҫ�Ļ�����
	//ǧ��Ҫ�ڶ��߳�֮�乲��ͬһ��easy handle

	/*ʹ��curl_easy_setopt������������easy handle�����ԺͲ�����
	��Щ���ԺͲ�������libcurl�����Զ��������������ͨ�š�
	һ����easy handle����������Ӧ�����ԺͲ��������ǽ�һֱ���ø�easy handle��
	Ҳ����˵���ظ�ʹ��easy hanle��Զ����������������ǰ���õ�������Ȼ��Ч��*/
	CURL *easy_handle = curl_easy_init();
	const char* str_url = "https://www.baidu.com/s?wd=302%20Found%20�����";
	CURLcode res = curl_easy_setopt(easy_handle, CURLOPT_URL, str_url);
	if (CURLE_OK != res)
	{
		cout << "curl_easy_setopt CURLOPT_URL failed\n";
		return -1;
	}
	res = curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, write_data);
	if (CURLE_OK != res)
	{
		cout << "curl_easy_setopt CURLOPT_WRITEFUNCTION failed\n";
		return -1;
	}
	FILE* fp = fopen("aa.index", "ab+");
	res = curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);
	if (CURLE_OK != res)
	{
		cout << "curl_easy_setopt CURLOPT_WRITEFUNCTION failed\n";
		return -1;
	}

	if (0 != curl_easy_perform(easy_handle))
	{
		cout << "curl_easy_perform failed\n";
		return -1;
	}

	/*����һ������ԭ����ǣ����Բ�Ӧ�����߳�֮�乲��ͬһ��libcurl handle��
	������easy handle����multi handle�����������н��ܣ���һ���߳�ÿ��ֻ��ʹ��һ��handle��*/

	//������Դ
	fclose(fp);
	curl_easy_cleanup(easy_handle);
	curl_global_cleanup();
}

void test2() {
	//https://www.baidu.com/s?wd=ubuntu
	CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
	CURL *easy_handle = curl_easy_init();


	//curl_easy_setopt(easy_handle, CURLOPT_URL, "https://www.baidu.com/s?wd=302%20Found%20�����");
	// ������post
	code = curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, "https://www.baidu.com/s?wd=302%20Found%20�����");
	if (0 != code)
	{
		cout << "post failed\n";
	}

	const char* url_str = "http://www.baidu.com/s?wd=��������";
	// �����ͷ��ģ�����������
	char array[][100] = { "Host:www.baidu.com",
		"Content-Type:application/x-www-form-urlencoded",//post����
		"Connection: keep-alive",
		'Referer:http://www.baidu.com',
		'User-Agent: Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0; BIDUBrowser 2.6)' };


	curl_easy_setopt(easy_handle, CURLOPT_URL, url_str);
	curl_easy_setopt(easy_handle, CURLOPT_HTTPHEADER, array);
	//curl_easy_setopt(easy_handle, CURLOPT_RETURNTRANSFER, 1);
	curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, write_data);
	code = curl_easy_perform(easy_handle);

	const char* p = NULL;
	code = curl_easy_getinfo(easy_handle, CURLINFO_EFFECTIVE_URL, &p);
	if (0 != code)
	{
		cout << "curl_easy_getinfo failed\n";
	}
	cout << p << endl;

	curl_easy_cleanup(easy_handle);
	curl_global_cleanup();
	//test_single();
}

int socketCallback(CURL* c, int fd, int what, void* userp, void* socketp) {

}

int timerCallback(CURLM* curlm, long ms, void* userp) {

}
int main() {
	CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
	CURL *easy_handle = curl_easy_init();
	CURLM* curlm_ = curl_multi_init();

//	curl_multi_setopt(curlm_, CURLMOPT_SOCKETFUNCTION, socketCallback);
//	curl_multi_setopt(curlm_, CURLMOPT_SOCKETDATA, this);
//	curl_multi_setopt(curlm_, CURLMOPT_TIMERFUNCTION, timerCallback);
//	curl_multi_setopt(curlm_, CURLMOPT_TIMERDATA, this);

	return 0;
}
