#include <iostream>
#include <assert.h>
#include <boost/regex.hpp>

using namespace boost;
using namespace std;
char* Regular_Expression = "[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}";
char* strsource = "192.168.123.4aksdfhkja aas爱的色放127.0.0.1asl;dfj;uyio2138.124.2.3";

void test_match() {
	boost::regex e1(Regular_Expression);
	boost::cmatch m;
	bool res = boost::regex_match(strsource, m, e1);
	std::cout << "m.size:" << m.size() << " ";
	std::cout << "e1.markcount" << e1.mark_count() << " ";

	cout << m[0].str();
	/*assert(m.prefix().first == strsource);
	assert(m.prefix().second == strsource + strlen(strsource)+1);
	assert(m.prefix().matched == false);
	assert(m.suffix().first == strsource + strlen(strsource) + 1);
	assert(m.suffix().second == strsource + strlen(strsource) + 1);
	assert(m.suffix().matched == false);*/
	//std::cout << res << std::endl;
}
int main() {
	std::string Regular_Expressions = "[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}";
	std::string strsources = "192.168.123.4aksdfhkja aas爱的色放127.0.0.1asl;dfj;uyio2138.124.2.3";
	boost::regex e1(Regular_Expressions);
	boost::smatch m;
	//输出所有匹配
	std::string::const_iterator start = strsources.begin();
	std::string::const_iterator end = strsources.end();
	while (regex_search(start, end, m, e1))
	{
		cout << m << " "<<endl;
		start = m[0].second;
	}
	cout << "size:" << e1.size() << e1.mark_count() << e1.str()<<endl;

	e1 = "[0-9]{1,3}\\.[0-9]{1,3}\\.";
	std::string::const_iterator start1 = strsources.begin();
	std::string::const_iterator end1 = strsources.end();
	while (regex_search(start1, end1, m, e1))
	{
		cout << m << " " << endl;
		start1 = m[0].second;
	}
	cout << "size:" << e1.size() << e1.mark_count() << e1.str() << endl;
	//cout << m[0].str();
	//cout << m;
	return 0;
}