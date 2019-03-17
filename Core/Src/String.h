#pragma once
#include "Vector.h"
#include <sstream>

class String
{
	string* text;

public:
	String();
	~String();
	String(string str);

	string get_string();

	float to_float();

	int32 to_int32();

	bool to_bool();
};

void SplitString(Vector<String*> &vec,String &s, char delim);

