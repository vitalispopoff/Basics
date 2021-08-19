#pragma once

#include <string>
#include <iostream>

namespace testing_space
{
	using namespace std;

	extern int test_no;

	template <typename U>
	struct testing_bundle
	{
		string name;
		U given, expected;
		testing_bundle () : 
			name {}, given{U ()}, expected {given} 
		{}
		testing_bundle (string n, U g, U e) : 
			name {n}, given {g}, expected {e}
		{
			if (given != expected)
				cout
					<<  test_no  << ".\t" << name << "\tfailed\n";
			++test_no;
		}
	};

	void report (int & no, string name);
}