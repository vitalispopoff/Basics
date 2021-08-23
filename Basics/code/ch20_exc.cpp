#include "ch20_exc.h"

#include <iostream>
#include <fstream>

namespace ch20_exc
{
	namespace e02
	{
		template <typename T>
		void fill_container (string source_file, T & container, int len = 0)
		{
			string
				file {"/_LAB/_C/Basics/Basics/resources/ch20_e02.txt"};
			ifstream 
				ifs {file, ios_base::in};
			if (! ifs)
				throw runtime_error ("Can't open file.");
			double
				* ptr = new double [len] {},
				tmp {};
			for (int i = 0; ifs >> tmp && i < len; ++i)
			ifs.close();
		}
		
		double * get_from_jack (int * count)
		{
			const int
				len = 6;
			string
				file {"/_LAB/_C/Basics/Basics/resources/ch20_e02.txt"};
			ifstream 
				ifs {file, ios_base::in};
			if (! ifs)
				throw runtime_error ("Can't open file.");
			double
				* ptr = new double [len] {},
				tmp {};
			for (int i = 0; ifs >> tmp && i < len; ++i)
				ptr [i] = tmp;
			* count = len;
			ifs.close();
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