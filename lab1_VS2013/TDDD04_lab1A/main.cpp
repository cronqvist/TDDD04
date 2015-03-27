// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "triangle.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int exitCode = 0;
	Triangle tr;
	const int nrOfEntries = 3;
	int sides[nrOfEntries];

	cout << "Enter your triangle's sides length (" << nrOfEntries << " entries): ";

	try
	{
		for(int i = 0; i < nrOfEntries; i++)
			cin >> sides[i];

		Triangle::TriangleType tt = tr.getType(sides, nrOfEntries);
		cout << tr.TypeToString(tt) << endl;
	}
	catch(const InvalidTriangleException& e)
	{
		cout << e.what() << endl;
	}
	catch(...)
	{
		cout << "Unknown error occured. The program will exit." << endl;
		exitCode = 1;
	}

#ifdef DEBUG
	system("pause");
#endif

	return exitCode;
}

