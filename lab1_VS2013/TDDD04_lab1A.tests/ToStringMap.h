#pragma once

#include <string>
#include "CppUnitTest.h"
#include <triangle.h>

/*! 
 * For Using Assert::AreEqual(act, exp) for "enum Triangle::TriangleType" type as operands, we need
 * to overload "std::wstring ToString<Q>(const Q&)" in Microsoft::VisualStudio::CppUnitTestFramework 
 * namespace
*/
namespace Microsoft{
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<>
			static std::wstring ToString<enum Triangle::TriangleType>(const enum Triangle::TriangleType& type)
			{
				std::wstringstream _s;
				switch (type)
				{
				case Triangle::EQUILATERAL:
					_s << "Equilateral";
					return _s.str();
				case Triangle::ISOSCELES:
					_s << "Isosceles";
					return _s.str();
				case Triangle::SCALENE:
					_s << "Scalene";
					return _s.str();
				}
				_s << "unknown triangle type";
				return _s.str();
			}
		}
	}
}
