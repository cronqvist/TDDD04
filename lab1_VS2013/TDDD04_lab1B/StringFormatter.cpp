#include "StringFormatter.h"
#include <iostream>

std::string StringFormatter::centerString(const std::string& s, const size_t textWidth, const char paddingChar)
{
	return "";
}

std::string StringFormatter::leftString(const std::string& s, const size_t textWidth, const char paddingChar)
{
	std::string ret = "";

	int len = textWidth;

	for each (auto c in s)
	{
		if (len-- > 0)
		{
			ret.push_back(c);
		}
		else
		{
			break;
		}
	}

	while (len-- > 0)
	{
		ret.push_back(paddingChar);
	}

	return ret;
}

std::string StringFormatter::rightString(const std::string& s, const size_t textWidth, const char paddingChar)
{
	return "";
}