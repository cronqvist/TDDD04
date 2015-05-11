#include "stdafx.h"
#include "CppUnitTest.h"
#include <triangle.h>
#include "ToStringMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace TraingleTest
{		
	TEST_CLASS(TraingleTest)
	{

		Triangle *_triangle;
	public:
		TEST_METHOD_INITIALIZE(setUp)
		{
			_triangle = new Triangle();
		}
		TEST_METHOD_CLEANUP(tearDown)
		{
			delete _triangle;
		}

		TEST_METHOD(testEquilateral)
		{
			int sides[3] = { 3, 3, 3 };

			/*
			* To write a custom message for verbose...
			*/
			//wchar_t message[200];
			//_swprintf(message, L"Trangle is not equlaterial: %d %d %d", sides[0], sides[1], sides[2]);
			//Assert::IsTrue(Triangle::EQUILATERAL != _triangle->getType(sides, 3), message);

			//Assert::IsTrue(Triangle::EQUILATERAL == _triangle->getType(sides, 3), L"Trangle is not equlaterial");
			Assert::AreEqual(Triangle::EQUILATERAL, _triangle->getType(sides, 3), L"Trangle is not equlaterial");
		}
		TEST_METHOD(testInvalidTriangle)
		{
			int sides[3] = { 0, 0, 0 };

			/*
			* Method 1: Testing exceptional cases - Using try-catch block
			*/
			bool exceptionThrown = false;
			try
			{
				_triangle->getType(sides, 3);
			}
			catch (InvalidTriangleException& ex)
			{
				auto desc = ex.what();
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Exception not thrown");

			/*
			* Method 2: Testing exceptional cases - Using C++11 Lambda expression
			*/
			Assert::ExpectException<InvalidTriangleException>([&]
			{
				_triangle->getType(sides, 3);
			});
		}

		// 1
		TEST_METHOD(testIsoscelesTriangle)
		{
			int sides[3] = { 3, 2, 2 };

			Assert::AreEqual(Triangle::ISOSCELES, _triangle->getType(sides, 3), L"Trangle is not isosceles");


			int sides2[3] = { 2, 3, 3 };
			Assert::AreEqual(Triangle::ISOSCELES, _triangle->getType(sides2, 3), L"Trangle is not isosceles");
		}

		TEST_METHOD(testScaleneTriangle)
		{
			int sides[3] = { 3, 4, 5 };

			Assert::AreEqual(Triangle::SCALENE, _triangle->getType(sides, 3), L"Triangle is not scalene");
		}

		// 2
		TEST_METHOD(testTriangleSort)
		{
			int sides[3] = { 5, 4, 3 };

			Assert::AreEqual(Triangle::SCALENE, _triangle->getType(sides, 3), L"Triangle is not scalene");
		}

		TEST_METHOD(testTriangleArgumentSides)
		{
			int sides[3] = { 5, 4, 3 };

			Assert::ExpectException<InvalidTriangleException>([&]
			{
				_triangle->getType(sides, 2);
			});

			int sides2[3] = { 1, 9, 10 };

			Assert::ExpectException<InvalidTriangleException>([&]
			{
				_triangle->getType(sides2, 3);
			});
		}

		TEST_METHOD(testTriangleTypeToString)
		{
			Assert::AreEqual(_triangle->TypeToString(Triangle::EQUILATERAL), "Equilateral");
			Assert::AreEqual(_triangle->TypeToString(Triangle::ISOSCELES), "Isosceles");
			Assert::AreEqual(_triangle->TypeToString(Triangle::SCALENE), "Scalene");
			Assert::AreEqual(_triangle->TypeToString(Triangle::INVALID), "unknown triangle type");
		}

	

		/*
		insert your test implementation here
		*/
	};
}