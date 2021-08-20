#include "ch20.h"

#include <string>
#include <iostream>

namespace ch20
{
	//using namespace std;
	using namespace testing_space;

	namespace try_this_1
	{
		/// these two implemented to avoid building errors only
		double * get_from_jack (int * count)
		{
			* count = 3;			
			return new double [3] { -1, -1, -1};
		}
		vector <double> * get_from_jill ()
		{
			return new vector <double> {-1, -1, -1};
		}

		void fct()
		{
			int
				jack_count = 0;
			double
				* jack_data = get_from_jack (& jack_count);
			vector <double>
				& jill_data = * get_from_jill();

			double 
				h = -1,
				* jack_high = nullptr;
			for (int i = 0; i < jack_count; ++i)
				if (h <= jack_data [i])
				{
					jack_high = &jack_data [i];
					h = jack_data [i];
				}
			
			double
				* jill_high = nullptr;
			h = -1;
			for (int i = 0; i < (int) jill_data.size(); ++i)
				if (h <= jill_data [i])
				{
					jill_high = & jill_data [i];
					h = jill_data [i];
				}

			delete [] jack_data;
			delete & jill_data;
		}

		void test()
		{
			string 
				name {"e20: try_this"};
			int
				no = test_no;
			
			int 
				* len = new int {INT_MIN};
			double 
				* d = get_from_jack(len);
			testing_bundle <int>
				t0_0 {name + ": pre", * len, 3};
			testing_bundle <bool>
				t0_1 {name + ": pre", d == nullptr, false};

			for (int i = 0; i < * len; ++i)
				testing_bundle <double>
					t0_2 {name + ": pre", d[i], -1};
			if (len != nullptr)
				delete len;
			if (d != nullptr)
				delete [] d;

			report (no, name + ": pre");

			fct();
		}
	}

	namespace try_this_3
	{
		void copy (int * f1, int * e1, int * f2)
		{
			for (int * i = f1; i != e1; ++i, ++f2)
				* f2 = * i;
		}

		void test()
		{
			string
				name {"ch20 : try_this_3"};
			int
				no = test_no;
			int 
				* ptr1 = new int [3] {0, 1, 2},
				* ptr2 = (int *) malloc (sizeof (int) * 3);
			copy (ptr1, & (ptr1 [3]), ptr2);
			for (int i = 0; i < 3; ++i)
				testing_bundle <int>
					t0_0 {name, ptr2 [i], i};
			report (no, name);
		}
	}
	

	void main()
	{
		try_this_3::test();
	}
}