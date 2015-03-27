// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "StringFormatter.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	StringFormatter formatter;

	std::string lol = "Lol";
	formatter.centerString("lol", 2, '*');

	system("Pause");
	return 0;
}

