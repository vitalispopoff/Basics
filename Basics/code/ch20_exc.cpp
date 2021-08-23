#include "ch20_exc.h"
#include "testing.h"

#include <iostream>
#include <fstream>

namespace ch20_exc
{
	using namespace testing_space;

	namespace e02
	{
		template <typename T>
		void fill (string file, T * container, int len = 0)
		{
			ifstream 
				ifs {file, ios_base::in};
			if (! ifs)
				throw runtime_error ("Can't open file.");
			double
				tmp {};
			for (int i = 0; ifs >> tmp && i < len; ++i)
				container [i] = tmp;
			ifs.close();
		}
		
		double * get_from_jack (int * count)
		{
			const int
				len = 6;
			double
				* ptr = new double [len] {};
			fill ("/_LAB/_C/Basics/Basics/resources/ch20_e02.txt", ptr, 6);
			* count = len;
			return ptr ;
		}

		vector <double> * get_from_jill()
		{
			vector <double> 
				* ptr = new vector <double> {1, 3, 2, 5, 4, 0};
			return ptr;
		}

		template <typename Iter>
		Iter high (Iter first, Iter last)
		{
			double
				h {- DBL_MAX};
			Iter
				high {};			
			for (Iter p = first; p != last; ++p)
				if (h < *p)
				{
					high = p;
					h = * p;
				}
			return high;
		}

		void fct()
		{
			string
				name {"ch20 e02"};
			int
				no = test_no;

			int
				jack_count {0};
			double
				* jack_data {get_from_jack(& jack_count)},
				* jack_high = high (jack_data, jack_data + jack_count);

			vector <double>
				& jill_data = * get_from_jill();
			auto
				jill_high = high (jill_data.begin(), jill_data.end());

			testing_bundle <double>
				t0_0 {name, * jack_high, 5},
				t0_1 {name, * jill_high, 5};
			report (no, name);

			delete [] jack_data;
			delete & jill_data;
		}
	}

	void main()
	{
		e02::fct();
	}
}