#include "String.h"

String::String()
{
	text = new string();
}

String::String(string str)
{
	text = new string();
	*text = str;
}

String::~String()
{
	safe_delete(text);
}

string String::get_string()
{
	return *text;
}

int32 String::to_int32()
{
	return std::stoi(*text);
}

float String::to_float()
{
	return std::stof(*text);
}

bool String::to_bool()
{
	if (strcmp("true",text->c_str()))
		return false;
	return true;
}




void SplitString(Vector<String*> &vec,String &s, char delim)
{
	std::stringstream ss(s.get_string());
	string item;
	while (std::getline(ss, item, delim))
		vec.push_back(new String(item));
}

