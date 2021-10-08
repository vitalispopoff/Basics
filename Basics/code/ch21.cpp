#include "ch21.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <numeric>


namespace ch21
{
	using namespace std;
	
	namespace try_this_1
	{
		using namespace chrono;
		using stopwatch = high_resolution_clock;

		template <typename In, typename T>
			In find_while (In first, In last, const T & val)
		{
			while (first != last && * first != val) 
				++first;
			return first;
		}

		template <typename In, typename T>
			In find_for (In first, In last, const T & val)
		{
			for (In p = first; p != last; ++p)
				if (* p == val) return p;
			return last;
		}

		void main()
		{
			vector <int> 
				v (1000000, 0);

			stopwatch::time_point 
				start {stopwatch::now()};
			find_while (v.begin(), v.end(), 1);			
			stopwatch::time_point 
				stop {stopwatch::now()};
			duration <double> 
				e_time {stop - start};
			cout 
				<< "\n\tfind_while benchmark:\t"
				<< e_time.count();
			start = stopwatch::now();
			find_for(v.begin(), v.end(), 1);
			stop = stopwatch::now();
			e_time = stop - start;
			cout
				<< "\n\tfind_for benchmark:\t"
				<< e_time.count();
		}
	}

	namespace try_this_2
	{
		template <typename In, typename T>
		T m_accumalate (In first, In last, T val)
		{
			while (first != last)
			{
				val += (* first)();
				++first;
			}
			return val;
		}

		void main()
		{
			/*Record 
				r {1.5, 3};
			cout 
				<< r();*/

			vector <Record> 
				v {
					{1.5, 3},
					{2.1, 2},
					{0.5, 6},
					{1.9, 2}
				};
			cout 
				//<< m_accumalate (v.begin(), v.end(), 0.0);
				<< accumulate (v.begin(), v.end(), 0.0, [&](double d, Record & r){return d += r();});
		}
	}

	void main()
	{
		//try_this_1::main();
		try_this_2::main();
	}
}