#include "testing.h"

#include <string>
#include <iostream>

namespace testing_space
{
	using namespace std;

	int test_no = 1;

	template <typename U>
	void testing_bundle<U>::testing ()
	{
		if (given != expected)
		{			
			cout
				<<  test_no  << ".\t" << name << "\tfailed\n";
			//<< "exp: " << given << "\texp: " << expected; 
		}
		++test_no;
	}

	void report (int & n, string name)
	{
		cout 
			<< '\t' << name << ":\ttests: " << n << " - " << test_no - 1 << '\n';
		n = test_no;
	}

}