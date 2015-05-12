#include "stdafx.h"
#include "CppUnitTest.h"

#include "Rectangle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackLagoontests
{
	TEST_CLASS(RectangleTests)
	{

	public:
		geometric::Rectangle<float>* _rect1;
		geometric::Rectangle<float>* _rect2;

		TEST_METHOD_INITIALIZE(setUp)
		{
			_rect1 = new geometric::Rectangle<float>();
			_rect2 = new geometric::Rectangle<float>();
		}

		TEST_METHOD_CLEANUP(tearDown)
		{
			delete _rect1;
			delete _rect2;
		}

		TEST_METHOD(testRectangleOverlapFromRight)
		{
			bool result = false;

			geometric::Rectangle<float>* _rect1 = new geometric::Rectangle<float>(0, 1800, 30, 1860);
			geometric::Rectangle<float>* _rect2 = new geometric::Rectangle<float>(3.24, 1748.43, 47.24, 1826.43);

			result = _rect1->overlap(*_rect2);
			Assert::AreEqual(true, result, L"Rectangle should overlap but did not");
		}
	};
}