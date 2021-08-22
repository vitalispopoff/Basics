#include "ch20.h"

#include <iostream>
#include <list>

namespace ch20_drill
{
	using namespace std;
	using namespace testing_space;

	void drill()
	{
		string
			name {"ch20 drills"};
		int
			no = test_no;

		int
			arr [10],
			len {sizeof arr / sizeof arr [0]};
		vector <int>
			vec (10);
		list <int>
			lst {};
		for (int i = 0; i < len; ++i)
		{
			arr [i] = vec [i] = i;
			lst.push_back (i);
		}
		int
			ctr {0};
		for (; ctr < len; ++ctr)
			testing_bundle <int>
				t0_0 {name, arr [ctr], ctr},
				t0_1 {name, vec [ctr], ctr};
		ctr = 0;
		for (int i : lst)
			testing_bundle <int>
				t0_2 {name, i, ctr++};
		report (no, name);

		int
			* arr_cp {arr};		// shallow copy :(
		vector <int>
			vec_cp {vec};
		list <int>
			lst_cp {lst};
		ctr = 0;
		for (; ctr < len; ++ctr)
		{
			arr_cp [ctr] += 2;
			vec_cp [ctr] += 3;
		}
		for (int & i : lst)
			i += 5;
		ctr = 0;
		for (; ctr < len; ++ctr)
			testing_bundle <int>
				t1_0 {name, arr_cp [ctr], ctr + 2},
				t1_1 {name, vec_cp [ctr], ctr + 3};
		ctr = 5;
		for (int i : lst)
			testing_bundle <int>
				t1_2 {name, i, ctr++};
		report (no, name);
	}



	void main()
	{
		drill();
	}
}