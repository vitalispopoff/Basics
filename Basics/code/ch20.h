#pragma once

#include "testing.h"
#include <vector>

namespace ch20
{
	using namespace std;

	/// deals with try this 1 & 2
	namespace try_this_1
	{
		void test();
	}

	namespace try_this_3
	{
		void copy (int * f1, int * e1, int * f2);

		void test();
	}

	void main();
}