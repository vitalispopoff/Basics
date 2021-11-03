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
	//	21.2

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

	void main_2()
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

	//	21.2.1

	template <typename In, typename T>
		void report_1 (In first, In last, T query, In answer = last)
	{
		cout
			<< "\telement " << query
			<< (answer == last
				? " wasn't found in the vector.\n"
				: " was found.\n");
	}

	void main_2_1 ()
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

	//	21.3

	template <typename In, typename Pred>
		In find_if (In first, In last, Pred p)
	{
		while (first != last && !p (*first))
			++first;
		return first;
	}

	bool odd (int x) {return x % 2;}

	void report_1 (vector <int> & v)
	{
		auto 
			p {ch21_txt::find_if (v.begin(), v.end(), odd)};
		if (p != v.end())
			std::cout 
				<< "\tAn element satisfying the conditions was found: "
				<< *p << ".\n";
		else
			std:cout
				<< "\tNo element satisfying the conditions was found.\n";
	}

	bool larger_than_42 (double x) {return x > 42.;}

	void report_2 (vector <int> & v)
	{
		auto
			p {ch21_txt::find_if (v.begin(), v.end(), larger_than_42)};
		if (p != v.end())
			std:cout
				<< "\tAn element larger than 42 was found: " << *p <<".\n";
		else
			std::cout
				<< "\tNo element larger than 42 found.\n";
	}

	void main_3 ()
	{
		vector <int> 
			v {1, 2, 3, 4, 5, 6};
		report_2 (v);

		v.push_back (43);
		report_2 (v);
	}


	//	21.4


	class Larger_than 
	{
		int value;

	public :
		
		Larger_than (int v) :
			value {v}
		{}

		bool operator () (int x) const {return x > value;}
	};

	void report_3 (list <double> & v, int c)
	{
		auto
			p {ch21_txt::find_if (v.begin(), v.end(), Larger_than (c))};

		if (p != v.end())
			std::cout
				<< "\tAn element " << *p << " meets the conditions for " << c <<".\n";
		else 
			std::cout
				<< "\tNo element meeting the conditions for " << c << " was found.\n";
	}

	void main_4 ()
	{
		list <double> v {1, 2, 3, 4, 5, 6};

		report_3 (v, 3);
		report_3 (v, 31);
	}

	//	21.4.1

	struct S {};
	struct T {};

	
	class F														// function object
	{
		S s;
	
	public :

		F (const S & ss) :
			s (ss)
		{}
		
		T operator () (const S & ss) const						// function call operator
		{
			// do something
		}

		const S & state () const {return s;}
		void reset (const S & ss) {s = ss;}
	};

	// 21.4.2


	struct Record
	{
		string
			name;
		char
			addr [24];
	};

	struct Cmp_by_name
	{
		bool operator () (const Record & a, const Record & b) const
		{
			return a.name < b.name;
		}
	};

	struct Cmp_by_addr
	{
		bool operator () (const Record & a, const Record & b) const
		{
			return strncmp (a.addr, b.addr, 24) < 0;
		}
	};
	
	void main_4_2 ()
	{
		vector <Record>
			vr;

		sort (vr.begin(), vr.end(), Cmp_by_name());

		sort (vr.begin(), vr.end(), Cmp_by_addr());
	}

	//	21.4.3

	void f_4_3_a ()
	{

		vector <Record>
			vr;

		sort (
			vr.begin(), 
			vr.end(),
			[] (const Record & a, const Record & b) {
				return a. name < b.name;
			}
		);

		sort (
			vr.begin(),
			vr.end(),
			[] (const Record & a, const Record & b) {
				return strncmp (a.addr, b.addr, 24) < 0;
			}
		);
	}

	void f_4_3_b (list <double> & v, int x)
	{
		auto p {ch21_txt::find_if (
				v.begin(), 
				v.end(), 
				[] (double a) {return a > 31;}
			)
		};

		if (p != v.end())
			cout << "\tFound it.\n";

		auto q {ch21_txt::find_if (
				v.begin(), 
				v.end(), 
				[&] (double a) {return a > x;}
			)
		};

		if (q != v.end())
			cout << "t\Found it.\n";
	}

	//	21.5.1 sq

	template <typename In, typename T>
		T accumulate_0 (In first, In last, T init)
	{
		while (first != last)
		{
			init += * first;
			++first;
		}
		return init;
	}



	//	--------------------------------------- //

	void main()
	{
		//main_2();
		//main_2_1();
		//main_3();
		//main_4();

	}
}

namespace ch21_try
{
	using namespace std;
	
	namespace try_this_2
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

	namespace try_this_3
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

	namespace try_this_4
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

	namespace try_this_5
	{
		void main()
		{}	
	}

	namespace try_this_6
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