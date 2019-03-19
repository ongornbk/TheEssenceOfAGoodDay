#pragma once
#include "Vector.h"
#include <sstream>

class String
{
	string text;

public:
	String();
	~String();
	explicit String(string str);
	explicit String(const char*);
	explicit String(const char);
	explicit String(const int32);

	string get_string();
	const char* c_str();

	float to_float();

	int32 to_int32();

	bool to_bool();

	String& operator = (const String& str);

	String& operator += (const char ch);
	String& operator += (const char* str);

	bool operator ==(String & B);
	bool operator ==(const char* B);
	bool operator ==(const char B);
	bool operator !=(const char B);
	bool operator !=(const char* B);

	void clear();
};

void SplitString(Vector<String*> &vec,String &s, char delim);

