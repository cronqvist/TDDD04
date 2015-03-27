#pragma once
#include "InvalidTriangleException.h"

class Triangle
{

private:
	void swap(int s [], int i, int j);

public:
	Triangle();
	~Triangle();

	enum TriangleType {INVALID = 0, EQUILATERAL, ISOSCELES, SCALENE};

	Triangle::TriangleType getType(int  sides [], int sides_length);
	const char* TypeToString(Triangle::TriangleType type);

}; 
