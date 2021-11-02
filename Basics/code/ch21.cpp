#include "ch21.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace ch21_txt
{
	using namespace std;
	// 21.2

	template <typename In, typename T>
		In find (In first, In last, const T & query)
	{
		while (first != last && * first != query)
			++first;
		return first;
	}

	template <typename In, typename T>
		In find_1 (In first, In last, const T & query)
	{
		for (In p = first; p != last; ++p)
			if (* p == query) 
				return p;
		return last;
	}

	template <typename In, typename T>
		In find_2 (In first, In last, const T & query)
	{
		for (; first != last; ++first)
			if (* first == query)
				return first;
		return last;
	}

	void report (int query, int answer)
	{
		if (answer + 1)
			cout
			<< "\telement " << query
			<< " was found at " << answer
			<< '\n';
		else 
			cout
			<< "\telement " << query
			<< " wasn't found in the vector\n";
	}

	template <typename In, typename T>
		void func (vector <T> & v, int query, In answer = last)
	{
		int
			slot { 
				answer == v.end()
				? -1
				: answer - v.begin()
			};
		report (query, slot);
	}

	void main_21_2()
	{
		vector <int>
			v {1, 2, 3, 4, 5, 6};
		
		cout
			<< "\n\tsuccess\n";
		int
			query {5};
		auto 
			answer {ch21_txt::find (v.begin(), v.end(), query)};
		func (v, query, answer);
		
		answer = ch21_txt::find_1 (v.begin(), v.end(), query);
		func (v, query, answer);

		answer = ch21_txt::find_2 (v.begin(), v.end(), query);
		func (v, query, answer);

		cout
			<< "\n\tfail\n";
		
		query = 0;

		answer = ch21_txt::find (v.begin(), v.end(), query);
		func (v, query, answer);

		answer = ch21_txt::find_1 (v.begin(), v.end(), query);
		func (v, query, answer);

		answer = ch21_txt::find_2 (v.begin(), v.end(), query);
		func (v, query, answer);
	}

	// 21.2.1

	template <typename In, typename T>
		void report_1 (In first, In last, T query, In answer = last)
	{
		cout
			<< "\telement " << query
			<< (answer == last
				? " wasn't found in the vector.\n"
				: " was found.\n");
	}

	void main_21_2_1 ()
	{
		std::list <int>
			v {1, 2, 3, 4, 5, 6};
		std::cout
			<< "\n\tsuccess\n";
		int 
			query {5};
		auto
			answer {ch21_txt::find (v.begin(), v.end(), query)};

		report_1 (v.begin(), v.end(), query, answer);

		query = 0;
		answer = ch21_txt::find (v.begin(), v.end(), query);
		report_1 (v.begin(), v.end(), query, answer);
	}


	void main()
	{
		//main_21_2();
		main_21_2_1();

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
			std::cout
				<< "\n\tfind_while benchmark:\t"
				<< e_time.count();
			start = stopwatch::now();
			find_for(v.begin(), v.end(), 1);
			stop = stopwatch::now();
			e_time = stop - start;
			std::cout
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