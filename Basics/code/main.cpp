#include "main.h"

#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
	try
	{
		//ch19::main();
		ch19_go_deeper::main();
		return 0;
	}
	catch (exception e)
	{
		cerr
			<< "";
		return 1;
	}
	catch (...)
	{
		return 2;
	}
}