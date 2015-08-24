#ifndef QIHOO_STRING_H_
#define QIHOO_STRING_H_

#include <stdlib.h>
#include <strstream>
namespace qh
{
	class string {
	public:
		//ctor
		string();
		string(const char* s);
		string(const char* s, size_t len);
		string(const string& rhs);
	public:
		string& operator=(const string& rhs);
		string& operator=(const char* s);
		string operator+(const string& rhs);
		string operator+(const char* s);
		string& operator+=(const string& rhs);
		string& operator+=(const char*s);
		bool operator==(const string& rhs);
		bool operator==(const char* s);
		//dtor
		~string();

		//get
		size_t size() const;
		const char* data() const;
		const char* c_str() const;

		// set & get
		char operator[](size_t index);
	public:
		friend string & operator + (char *s, string &oString);
		friend bool operator == (char *s, string &oString);
	private:
		char*  data_;
		size_t len_;
	};
}

#endif


