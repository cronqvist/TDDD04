#pragma once
#include <string>

class IStringFormatter
{
public:
	IStringFormatter(void){};
	virtual ~IStringFormatter(void){};

	virtual std::string centerString(const std::string& s, const size_t textWidth, const char paddingChar) = 0;
	virtual std::string leftString(const std::string& s, const size_t textWidth, const char paddingChar) = 0;
	virtual std::string rightString(const std::string& s, const size_t textWidth, const char paddingChar) = 0;
};
