#include "testing.h"

namespace testing_space
{
	using namespace std;

	int test_no = 1;

	void report (int & n, string name)
	{
		cout 
			<< '\t' << name << ":\ttests: " << n << " - " << test_no - 1 << '\n';
		n = test_no;
	}
}