#pragma once

#include <exception>

class InvalidTriangleException :
	public std::exception
{
public:
	InvalidTriangleException(void);
	~InvalidTriangleException(void);
};
