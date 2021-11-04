#include "main.h"

#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
	try
	{		
		//midi_vs_freq::main();

		ch21_txt::main();
		ch21_try::main();

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