#include "stdafx.h"
#include "CppUnitTest.h"

#include "Rectangle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackLagoontests {

	using Rect = const geometric::Rectangle<double>;

	TEST_CLASS(RectangleTests) {
	public:

		TEST_METHOD(rectangleOverlapsFromRight) {			
			Rect rect1(0, 1800, 30, 1860);
			Rect rect2(3.24, 1748.43, 47.24, 1826.43);

			Assert::IsTrue(rect1.overlap(rect2), L"Rectangle should overlap but did not");
		}
	};

}