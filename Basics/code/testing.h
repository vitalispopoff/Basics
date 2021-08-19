#pragma once

#include <string>

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
			testing();
		}

		void testing();
	};

	void report (int & no, string name);
}