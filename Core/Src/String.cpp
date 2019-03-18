#include "String.h"

String::String()
{

}

String::String(string str)
{
	text = str;
}

String::String(const char *str)
{
	text = str;
}

String::~String()
{
	text.clear();
}

string String::get_string()
{
	return text;
}

const char* String::c_str()
{
	return text.c_str();
}

int32 String::to_int32()
{
	return std::stoi(text);
}

float String::to_float()
{
	return std::stof(text);
}

bool String::to_bool()
{
	if (strcmp("true",text.c_str()))
		return false;
	return true;
}

String& String::operator=(const String& str)
{
	this->text = str.text;
	return *this;
}

String& String::operator+=(const char ch)
{
	text.push_back(ch);
	return *this;
}

String& String::operator+=(const char* str)
{
	text += str;
	return *this;
}

bool String::operator==(String & B)
{
	if (strcmp(this->c_str(), B.c_str()))
		return false;
	else return true;
}

bool String::operator==(const char* B)
{
	if (strcmp(this->c_str(),B))
		return false;
	else return true;
}

bool String::operator==(const char B)
{
	if (text.length()==1u&&text.at(0)==B)
		return true;
	else return false;
}

bool String::operator!=(const char B)
{
	if (text.length() != 1u || text.at(0) == B)
		return false;
	else return true;
}

bool String::operator!=(const char* B)
{
	return (!(*this == B));
}

void SplitString(Vector<String*> &vec,String &s, char delim)
{
	std::stringstream ss(s.get_string());
	string item;
	while (std::getline(ss, item, delim))
		vec.push_back(new String(item));
}

void String::clear()
{
	text.clear();
}

