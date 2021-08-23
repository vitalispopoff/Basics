#include "ch20_exc.h"

#include <iostream>

namespace ch20_exc
{
	namespace e02
	{
		double * get_from_jack (int * count)
		{
			double 
				* ptr = new double [6] {1, 3, 2, 4, 5, 0};
			//* count = sizeof (ptr) / sizeof (ptr [0]); // wrn C6384
			* count = 6;
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
			int
				jack_count {0};
			double
				* jack_data {get_from_jack(& jack_count)},
				* jack_high = high (jack_data, jack_data + jack_count);

			cout << '\n' << * jack_high;
			delete [] jack_data;

			vector <double>
				& jill_data = * get_from_jill();
			auto
				jill_high = high (jill_data.begin(), jill_data.end());
			cout << '\n' << * jill_high;
		}
	}

	void main()
	{
		e02::fct();
	}
}