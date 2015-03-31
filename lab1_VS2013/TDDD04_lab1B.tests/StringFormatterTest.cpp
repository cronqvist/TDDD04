#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "StringFormatter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TDDD04_lab1Btests
{		
	TEST_CLASS(StringFormatterTest)
	{
		StringFormatter *formatter;

	public:
		TEST_METHOD_INITIALIZE(setUp)
		{
			formatter = new StringFormatter();
		}
		TEST_METHOD_CLEANUP(tearDown)
		{
			delete formatter;
		}

		TEST_METHOD(centerStringTest)
		{
			std::string result, expected;

			result = formatter->centerString("EVEN", 3, '*');
			expected = "VEN";
			Assert::AreEqual(0, expected.compare(result));
		}

		TEST_METHOD(leftStringTest)
		{
			std::string result, expected;

			result = formatter->leftString("testing", 10, '-');
			expected = "testing---";
			Assert::AreEqual(result, expected);

			result = formatter->leftString("even", 1, '-');
			expected = "e";
			Assert::AreEqual(result, expected);

			result = formatter->leftString("asd", 0, '-');
			expected = "";
			Assert::AreEqual(result, expected);

			result = formatter->leftString("", 3, '-');
			expected = "---";
			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(rightStringTest)
		{
			std::string result, expected;

			result = formatter->centerString("Software", 4, '*');
			expected = "ware";
			Assert::AreEqual(result, expected);
		}

	};
}