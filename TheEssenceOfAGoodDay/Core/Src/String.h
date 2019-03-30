#pragma once
#include "Array.h"
#include <sstream>


class String
{
	string text;

public:
	String();
	~String();
	explicit String(string str);
	explicit String(wstring wstr);
	explicit String(const char*);
	explicit String(const bool);
	explicit String(const char);
	explicit String(const int32);
	explicit String(const int64);
	explicit String(const uint32);
	explicit String(const uint64);
	explicit String(const double);

	string get_string() const noexcept;
	const char* c_str() const noexcept;

	size_t length() const noexcept;

	float to_float();

	int32 to_int32();

	bool to_bool();
	bool is_digit() const;

	String& operator = (const String& str);

	String& operator += (const char ch);
	String& operator += (const char* str);

	bool operator ==(const String& B) const;
	bool operator ==(const char* B);
	bool operator ==(const char B);
	bool operator !=(const char B);
	bool operator !=(const char* B);

	bool operator <(const String& B) const;

	void clear();
};

void SplitString(Array<String*> &vec,String &s, char delim);

