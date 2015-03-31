#include "triangle.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

const char* Triangle::TypeToString(Triangle::TriangleType type)
{
	switch (type)
	{
	case EQUILATERAL:
		return "Equilateral";
		break;
	case ISOSCELES:
		return "Isosceles";
		break;
	case SCALENE:
		return "Scalene";
		break;
	}
	return "unknown triangle type";
}

Triangle::TriangleType Triangle::getType(int sides[], int sides_length)
{
	if (sides_length != 3){
		throw InvalidTriangleException();
	}

	int* s = new int[sides_length];

	TriangleType result = INVALID;

	try
	{
		for (int i = 0; i < sides_length; i++)
			s[i] = sides[i];

		if (s[0] > s[1])
		{
			swap(s, 0, 1);
		}
		else
		{
			;
		}

		if (s[0] > s[2])
		{
			swap(s, 0, 2);
		}
		else
		{
			;
		}

		if (s[1] > s[2])
		{
			swap(s, 1, 2);
		}
		else
		{
			;
		}

		if (s[0] <= 0 || s[2] - s[0] >= s[1])
		{
			throw InvalidTriangleException();
		}

		if (s[0] == s[2])
		{
			result = EQUILATERAL;
		}
		else if (s[0] == s[1] || s[1] == s[2])
		{
			result = ISOSCELES;
		}
		else
		{
			result = SCALENE;
		}
	}
	catch (...)
	{
		delete[] s;
		result = INVALID;
		throw; //re throw
	}

	delete[] s;
	return result;
}

void Triangle::swap(int  s[], int i, int j)
{
	int tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}
