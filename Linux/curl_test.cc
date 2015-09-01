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
	//初始化全局变量
	//在程序中应该尽量避免多次调用curl_global_init和curl_global_cleanup
	curl_global_init(CURL_GLOBAL_ALL);

	//基本上，每个线程都应该有自己的easy handle用于数据通信（如果需要的话）。
	//千万不要在多线程之间共享同一个easy handle

	/*使用curl_easy_setopt函数可以设置easy handle的属性和操作，
	这些属性和操作控制libcurl如何与远程主机进行数据通信。
	一旦在easy handle中设置了相应的属性和操作，它们将一直作用该easy handle。
	也就是说，重复使用easy hanle向远程主机发出请求，先前设置的属性仍然生效。*/
	CURL *easy_handle = curl_easy_init();
	const char* str_url = "https://www.baidu.com/s?wd=302%20Found%20刘亦菲";
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

	/*首先一个基本原则就是：绝对不应该在线程之间共享同一个libcurl handle，
	不管是easy handle还是multi handle（将在下文中介绍）。一个线程每次只能使用一个handle。*/

	//清理资源
	fclose(fp);
	curl_easy_cleanup(easy_handle);
	curl_global_cleanup();
}

void test2() {
	//https://www.baidu.com/s?wd=ubuntu
	CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
	CURL *easy_handle = curl_easy_init();


	//curl_easy_setopt(easy_handle, CURLOPT_URL, "https://www.baidu.com/s?wd=302%20Found%20刘亦菲");
	// 单个域post
	code = curl_easy_setopt(easy_handle, CURLOPT_POSTFIELDS, "https://www.baidu.com/s?wd=302%20Found%20刘亦菲");
	if (0 != code)
	{
		cout << "post failed\n";
	}

	const char* url_str = "http://www.baidu.com/s?wd=生命动力";
	// 构造包头，模拟浏览器请求
	char array[][100] = { "Host:www.baidu.com",
		"Content-Type:application/x-www-form-urlencoded",//post请求
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
