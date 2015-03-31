#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "StringFormatter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TDDD04_lab1Btests
{		
	TEST_CLASS(StringFormatterTest)
	{
		IStringFormatter *formatter;

	public:
		TEST_METHOD_INITIALIZE(setUp)
		{
			formatter = new StringFormatter();
		}
		TEST_METHOD_CLEANUP(tearDown)
		{
			delete formatter;
		}
		
		TEST_METHOD(centerStringTestEven)
		{
			std::string result, expected;

			result = formatter->centerString("even", 0, '*');
			expected = "";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("even", 1, '*');
			expected = "e";
			Assert::AreEqual(result, expected);
		
			result = formatter->centerString("even", 2, '*');
			expected = "ve";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("even", 3, '*');
			expected = "ven";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("even", 4, '*');
			expected = "even";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("even", 5, '*');
			expected = "even*";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("even", 6, '*');
			expected = "*even*";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("even", 7, '*');
			expected = "*even**";
			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(centerStringTestOdd)
		{
			std::string result, expected;

			result = formatter->centerString("odd", 0, '*');
			expected = "";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("odd", 2, '*');
			expected = "dd";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("odd", 3, '*');
			expected = "odd";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("odd", 4, '*');
			expected = "odd*";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("odd", 5, '*');
			expected = "*odd*";
			Assert::AreEqual(result, expected);

			result = formatter->centerString("odd", 6, '*');
			expected = "*odd**";
			Assert::AreEqual(result, expected);
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

			result = formatter->leftString("left", 3, '-');
			expected = "lef";
			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(rightStringTest)
		{
			std::string result, expected;

			result = formatter->rightString("testing", 10, '-');
			expected = "---testing";
			Assert::AreEqual(result, expected);

			result = formatter->rightString("even", 1, '-');
			expected = "n";
			Assert::AreEqual(result, expected);

			result = formatter->rightString("asd", 0, '-');
			expected = "";
			Assert::AreEqual(result, expected);

			result = formatter->rightString("right", 3, '-');
			expected = "ght";
			Assert::AreEqual(result, expected);
		}

	};
}