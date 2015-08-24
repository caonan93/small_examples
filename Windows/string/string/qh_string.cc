#include "qh_string.h"

#include <string.h>

namespace qh
{
	// TODO 将在这里写实现代码

	string::string()
		: data_(NULL), len_(0)
	{
	}

	string::string(const char* s)
	{
		if (NULL == s)
		{
			data_ = new char[1];
			data_[0] = '\0';
			len_ = 0;
		}
		else
		{
			int iLen = strlen(s) + 1;
			data_ = new char[iLen];
			strcpy_s(data_, iLen, s);
			len_ = iLen - 1;
		}
		
	}

	string::string(const char* s, size_t len)
	{
		if (NULL == s)
		{
			data_ = new char[1];
			data_[0] = 0;
			len_ = 0;
		}
		else
		{
			len_ = len;
			data_ = new char[len + 1];
			strncpy_s(data_,len+1, s, len);
			data_[len] = '\0';
		}

	}

	string::string(const string& rhs)
	{
		try
		{
			if (this != &rhs)
			{
				int iLen = strlen(rhs.data_) + 1;
				len_ = iLen - 1;
				char *cTemp = new char[iLen];
				if (NULL != cTemp)
				{
					strcpy_s(cTemp, iLen, rhs.data_);
					data_ = cTemp;
				}
				else
				{
					throw "new failed";
				}
			}
		}
		catch (char* e)
		{
			printf("%s", e);
		}
		
		
	}

	string& string::operator=(const string& rhs)
	{
		try
		{
			if (this == &rhs)
			{
				return *this;
			}
			int iLen = strlen(rhs.data_) + 1;
			len_ = iLen - 1;
			char *cTemp = new char[iLen];
			if (NULL == cTemp)
			{
				throw "new failed";				
			}

			strcpy_s(cTemp, iLen, rhs.data_);

			if (data_)
			{
				delete[] this->data_;
			}

			data_ = cTemp;
			cTemp = NULL;
			return *this;
		}
		catch (char* e)
		{
			printf("%s",e);
			return *this;
		}		
	}
	string& string::operator=(const char* s)
	{
		try
		{
			int iLen = strlen(s) + 1;

			char *cTemp = new char[iLen];
			if (NULL == cTemp)
			{
				throw "new failed";
				return *this;
			}

			strcpy_s(cTemp, iLen, s);

			if (data_)
			{
				delete[] data_;
			}

			data_ = cTemp;
			cTemp = NULL;
			len_ = iLen - 1;
			return *this;
		}
		catch (char* e)
		{
			printf("%s", e);
			return *this;
		}
		
	}
	string string::operator+(const string& rhs)
	{
		string oTemp;
		int iLen = strlen(data_) + strlen(rhs.data_) + 1;
		
		oTemp.data_ = new char[iLen];
		strcpy_s(oTemp.data_, strlen(data_)+1 , data_);
		strcat_s(oTemp.data_, iLen, rhs.data_);
		len_ = iLen - 1;
		return oTemp;
	}
	string string::operator+(const char* s)
	{
		string oTemp;
		int iLen = strlen(data_) + strlen(s) + 1;
		oTemp.data_ = new char[iLen];
		strcpy_s(oTemp.data_, strlen(data_) + 1, data_);
		strcat_s(oTemp.data_, iLen, s);
		len_ = iLen - 1;
		return oTemp;
	}

	string& string::operator+=(const string& rhs)
	{
		try
		{
			char* ctmp;
			if (NULL == data_)
			{
				int iLen = strlen(rhs.data_) + 1;
				ctmp = new char[iLen];
				if (NULL == ctmp)
				{
					throw "failed new";
					return *this;
				}
				strcpy_s(ctmp, iLen, rhs.data_);
				data_ = ctmp;
				len_ = iLen - 1;
			}
			else
			{
				int iLen = strlen(data_) + strlen(rhs.data_) + 1;
				ctmp = new char[iLen];
				if (NULL == ctmp)
				{
					throw "failed new";
					return *this;
				}

				strcpy_s(ctmp, strlen(data_) + 1, this->data_);
				strcat_s(ctmp, iLen, rhs.data_);

				if (data_)
				{
					delete[]data_;
					data_ = NULL;
				}
				data_ = ctmp;
				len_ = iLen - 1;
			}

			return *this;
		}
		catch (char* e)
		{
			printf("%s", e);
			return *this;
		}		
	}
	string& string::operator+=(const char*s)
	{
		try
		{
			char* ctmp;
			if (NULL == data_)
			{
				int iLen = strlen(s) + 1;
				ctmp = new char[iLen];
				if (NULL == ctmp)
				{
					throw "failed new";
					return *this;
				}
				strcpy_s(ctmp, iLen, s);
				data_ = ctmp;
				len_ = iLen - 1;
			}
			else
			{
				int iLen = strlen(data_) + strlen(s) + 1;
				ctmp = new char[iLen];
				if (NULL == ctmp)
				{
					throw "failed new";
					return *this;
				}

				strcpy_s(ctmp, strlen(data_) + 1, this->data_);
				strcat_s(ctmp, iLen, s);

				if (data_)
				{
					delete[]data_;
					data_ = NULL;
				}
				data_ = ctmp;
				len_ = iLen - 1;
			}
			return *this;
		}
		catch (char* e)
		{
			printf("%s", e);
			return *this;
		}
		
	}
	bool string::operator==(const string& rhs)
	{
		if (0 == strcmp(data_, rhs.data_))
		{
			return true;
		}
		return false;
	}
	bool string::operator==(const char* s)
	{
		if (0 == strcmp(data_, s))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string::~string()
	{
		if (data_)
		{
			delete[] data_;
			data_ = NULL;
		}
	}

	size_t string::size() const
	{
		return len_;
	}

	const char* string::data() const//字符数组
	{
		return c_str();
	}

	const char* string::c_str() const//c_string
	{
		return data_;
	}

	char string::operator[](size_t index)
	{
		if (index < 0 || index > strlen(data_))
		{
			return '0';
		}
		else
		{
			return data_[index];
		}
	}

	string & operator + (char *s, string &oString)
	{
		int iLen = strlen(s) + strlen(oString.data_) + 1;

		char *cTemp = new char[iLen];
		strcpy_s(cTemp, strlen(s) + 1, s);
		strcat_s(cTemp, iLen, oString.data_);
		oString.data_ = cTemp;
		
		return oString;
	}
	bool operator == (char *s, string &oString)
	{
		if (0 == strcmp(s, oString.data_))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}
