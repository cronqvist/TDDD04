#include "StringFormatter.h"
#include <iostream>
#include <algorithm>

std::string StringFormatter::centerString(const std::string& s, const size_t textWidth, const char paddingChar)
{
	int paddingLength = std::max(0, (int)(textWidth - s.size()));
	int stringLength = std::min(textWidth, s.size());

	int startIndex = std::ceil((s.size() - stringLength) / 2.0);

	return std::string(std::floor(paddingLength / 2.0), paddingChar) 
		+ std::string(s, startIndex, stringLength)
		+ std::string(std::ceil(paddingLength / 2.0), paddingChar);
}

std::string StringFormatter::leftString(const std::string& s, const size_t textWidth, const char paddingChar)
{
	int paddingLength = std::max(0, (int)(textWidth - s.size()));
	int stringLength = std::min(textWidth, s.size());

	return std::string(s, 0, stringLength) + std::string(paddingLength, paddingChar);
}




std::string StringFormatter::rightString(const std::string& s, const size_t textWidth, const char paddingChar)
{
	int paddingLength = std::max(0, (int)(textWidth - s.size()));
	int stringLength = std::min(textWidth, s.size());

	return std::string(paddingLength, paddingChar) + std::string(s, s.size() - stringLength, stringLength);
}