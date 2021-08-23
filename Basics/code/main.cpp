#include "main.h"

#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
	try
	{
		ch20_exc::main();
		return 0;
	}
	catch (exception & e)
	{
		cerr
			<< e.what();
		return 1;
	}
	catch (...)
	{
		return 2;
	}
}