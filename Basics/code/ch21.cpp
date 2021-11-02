#include "ch21.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace ch21_txt
{
	using namespace std;
	// 21.2

	template <typename In, typename T>
		In find (In first, In last, const T & val)
	{
		while (first != last && * first != val)
			++first;
		return first;
	}

	template <typename In, typename T>
		In find_1 (In first, In last, const T & val)
	{
		for (In p = first; p != last; ++p)
			if (* p == val) 
				return p;
		return last;
	}

	template <typename In, typename T>
		In find_2 (In first, In last, const T & val)
	{
		for (; first != last; ++first)
			if (* first == val)
				return first;
		return last;
	}

	void func (vector <int> & v, int x) 
	{
		auto 
			p {ch21_txt::find (v.begin(), v.end(), x)};
		
		if (p != v.end())		
			// do stuff like :

			cout 
				<< "\telement " << x 
				<< "was found at " << p - v.begin()
				<< '\n';
		else 
			// do other stuff like:

			cout 
				<< "\telement " << x
				<< "wasn't found in the vector\n";

		// possibly do some more stuff
	}



	void main()
	{
		vector <int>
			v {1, 2, 3, 4, 5, 6};

		func (v, 5);
	}
}

namespace ch21_try
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
			vector <Record> 
				v {
					{1.5, 3},
					{2.1, 2},
					{0.5, 6},
					{1.9, 2}
				};
			cout 
				<< accumulate (
					v.begin(), 
					v.end(), 
					0.0, 
					[](double & d, Record & r)
					{
						return d += r();
					}
				);
		}
	}

	namespace try_this_3
	{
		map <string, double> 
			stock_price
			{
				{"MMA", 0.6},
				{"TVP", 0.11},
			},
			stock_weight
			{
				{"MMA", 2.25},
				{"TVP", 0.41}
			};
		
		double weighted_val (double a, double b) 
			{return a * b;}
		
		void main()
		{
			double
				result {0.0};
			for (auto p : stock_price)
				result += p.second * stock_weight[p.first];
			cout 
				<< result;
		}
	}

	namespace try_this_4
	{
		void main()
		{}	
	}

	namespace try_this_5
	{
		void main()
		{
			string
				from,		// source file address
				to;			// target file address
			cin 
				>> from 
				>> to;
			ifstream
				is {from};
			ofstream
				os {to};
			istream_iterator <string>
				ii {is},
				eos;
			ostream_iterator <string>
				oo {os, "\n"};
			vector <string>
				b {ii, eos};
			sort (b.begin(), b.end());
			copy (b.begin(), b.end(), oo);
		}
	}

	void main()
	{
		//try_this_1::main();
		//try_this_2::main();
		//try_this_3::main();
		//try_this_4::main();
	}
}