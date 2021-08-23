#include "ch20.h"

#include <iostream>
#include <list>

namespace ch20_drill
{
	using namespace std;
	using namespace testing_space;

	void drills_1_5()
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

	namespace d06
	{
		template <typename Iter1, typename Iter2>
			Iter2 m_copy (Iter1 f1, Iter1 e1, Iter2 f2)
		{
			Iter1
				iter = f1;
			while (true)
			{
				* f2 = * f1;
				if (++f1 == e1)
					break;
				++f2;
			}
			return f2;
		}

		void test()
		{
			string
				name {"drill 6"};
			int
				no = test_no;

			int
				a [] = {0, 1, 2, 3, 4, 5},
				len {sizeof (a) / sizeof (* a)};
			vector <int>
				v (len);
			auto 
				v_last {m_copy (a, a + 6, v.begin())};
			testing_bundle <int>
				t0_0 {name, * v_last, v [len - 1]};
			int
				ctr {0};
			for ( ; ctr < len ; ++ctr)
				testing_bundle <int>
					t0_1 {name, a [ctr], v [ctr]};
			report (no, name);
					
			list <int>
				l (v.size());
			auto 
				l_end {m_copy (v.begin(), v.end(), l.begin())};
			testing_bundle <int>
				t1_0 {name, * l_end, v [v.size() - 1]};
			ctr = 0;
			for (int i : l)
				testing_bundle <int>
					t1_1 {name, i, v [ctr++]};
			report (no, name);

			int
				a2 [6]{};
			auto 
				a2_end {m_copy (l.begin(), l.end(), a2)};
			testing_bundle <int>
				t2_0 {name, * a2_end, a2 [5]};
			ctr = 0;
			for (int i : l)
				testing_bundle <int>
					t2_1 {name, i, a2 [ctr++]};
			report (no, name);

			int
				looked_for {3};
			auto
				v_ndx = find (v.begin(), v.end(), looked_for);
			testing_bundle <int>
				test3_0 {name, * v_ndx, looked_for};
			looked_for = 21;
				v_ndx = find (v.begin(), v.end(), looked_for);
			testing_bundle <bool>
				test3_1 {name, v_ndx == v.end(), true};
			report (no, name);
		}
	}

	void main()
	{
		//drills_1_5();
		d06::test();
	}
}