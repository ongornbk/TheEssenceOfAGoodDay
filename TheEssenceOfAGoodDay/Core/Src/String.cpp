#include "String.h"
#include <cctype>

#define STRING_DEBUG
#ifdef STRING_DEBUG
#include "Console/Console.h"
#endif


String::String()
{

}

String::String(string str)
{
	text = str;
}

String::String(wstring wstr)
{
	text = string(wstr.begin(), wstr.end());
}

String::String(const char *str)
{
	text = str;
}

String::String(const bool boolean)
{
	if (boolean)
		text = "true";
	else text = "false";
}

String::String(const char ch)
{
	text = ch;
}

String::String(const int32 i)
{
	text = std::to_string(i);
}

String::String(const uint32 u)
{
	text = std::to_string(u);
}

String::String(const int64 i)
{
	text = std::to_string(i);
}

String::String(const uint64 u)
{
	text = std::to_string(u);
}

String::~String()
{
	text.clear();
}

string String::get_string() const noexcept
{
	return text;
}

const char* String::c_str() const noexcept
{
	return text.c_str();
}

size_t String::length() const noexcept
{
	return text.length();
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

bool String::is_digit() const
{
		return !text.empty() && std::find_if(text.begin(), text.end(), [](char c) { return !std::isdigit(c); }) == text.end();
}

String& String::operator=(const String& str)
{
	text.clear();
	for (auto c : str.get_string())
	{
		text += c;
	}
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

bool String::operator==(const String& B) const
{

#define STRING_DEBUG
#ifdef STRING_DEBUG
	ConsoleHandle con;
	con < "String :: ";
	con < *this;
	con < " == ";
	con < B;
	con < endl;
#endif

	if (strcmp(this->c_str(), B.c_str()))
		return false;
	else return true;
}

bool String::operator < (const String& B) const
{

#define STRING_DEBUG
#ifdef STRING_DEBUG
	ConsoleHandle con;
	con < "String :: ";
	con < *this;
	con < " < ";
	con < B;
	con < endl;
#endif


	const size_t length = std::min(text.length(), B.length());
	for (uint64 i = 0u; i < length; i++)
	{
		const auto ch0 = text[i];
		const auto ch1 = B.get_string()[i];
		if (ch0 != ch1) return ch0 < ch1;
	}

	return text.length() < B.length();
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

void SplitString(Array<String*> &vec,String &s, char delim)
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

