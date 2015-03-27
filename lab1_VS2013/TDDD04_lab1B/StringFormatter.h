#include "IStringFormatter.h"
#include <string>

class StringFormatter : public IStringFormatter
{
public:

	std::string centerString(const std::string& s, const size_t textWidth, const char paddingChar);
	std::string leftString(const std::string& s, const size_t textWidth, const char paddingChar);
	std::string rightString(const std::string& s, const size_t textWidth, const char paddingChar);

	//virtual std::string centerString(const std::string& s, const size_t textWidth, const char paddingChar) { return ""; }
	//virtual std::string leftString(const std::string& s, const size_t textWidth, const char paddingChar) { return ""; }
	//virtual std::string rightString(const std::string& s, const size_t textWidth, const char paddingChar) { return ""; }
};