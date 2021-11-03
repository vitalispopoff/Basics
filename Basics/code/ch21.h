#pragma once

#include <list>
#include <string>
#include <vector>

namespace ch21_txt
{
	using namespace std;

	//	21.2
	namespace txt_2								
	{
		template <typename In, typename T>
			In find (In first, In last, const T & query);

		template <typename In, typename T>
			In find_1 (In first, In last, const T & query);

		template <typename In, typename T>
			In find_2 (In first, In last, const T & query);

		void report_1 (int query, int answer);

		template <typename In, typename T>
			void verify (vector <T> & v, int query, In answer);
		
		void local_1();

		template <typename In, typename T>
			void report_2 (In first, In last, T query, In answer);

		void local_2 ();

		void main();
	}

	//	21.3
	namespace txt_3
	{
		template <typename In, typename Pred>
			In find_if (In first, In last, Pred p);

		void local_1 (vector <int> & v);

		bool larger_than_42 (double x);

		void local_2 (vector <int> & v);

		void main();
	}

	//	21.4
	namespace txt_4
	{
		class Larger_than
		{
			int
				val;
		public :
			Larger_than (int v) :
				val {v}
			{}

			bool operator () (int x) const;
		};

		void report (list <double> & v, int c);

		void local_1 ();

		//	21.4.1

		struct S {};
		struct T {};

		class F									// function object
		{
			S s;

		public :

			F (const S & ss) :
				s (ss)
			{}

			T operator () (const S & ss) const	// function call operator
			{
				// do something
			}

			const S & state () const {return s;}
			void reset (const S & ss) {s = ss;}
		};

		//	21.4.2

		struct Record
		{
			string
				name;
			char 
				addr [24];
		};

		struct Cmp_by_name
		{
			bool operator () (const Record & a, const Record & b) const;
		};

		struct Cmp_by_addr
		{
			bool operator () (const Record & a, const Record & b) const;
		};

		void local_2();

		//	21.4.3

		void example_1 ();

		void example_2 (list <double> & v, int x);

		void main();
	}

	//	21.5
	namespace txt_5
	{
		template <typename In, typename T, typename BinOp>
			T accumulate (In first, In last, T init, BinOp op);

		void local_1 ();

		/*struct Record
		{
			double 
				unit_price;
			int 
				units;
			Record (double p, int u) :
				unit_price {p},
				units {u}
			{}

			double operator () (const double & p, const double & u);
		};*/

	}


	

	void main();
}


namespace ch21_try
{

	//	try_this 1 p.765


	namespace try_this_2
	{
		template <typename In, typename T>
		In find_while (In first, In last, const T & val);

		template <typename In, typename T>
		In find_for (In first, In last, const T & val);
	
		void main();
	}

	//	p.774
	namespace try_this_3
	{
		struct Record
		{
			double 
				unit_price;
			int 
				units;
			Record (double u_p, int u) :
				unit_price {u_p},
				units {u}
			{}
			double operator () ()
			{
				return unit_price * double (units);
			}
		};

		void main();

	}

	//	p.785
	namespace try_this_4
	{
		void main();
	}

	//	p.787
	namespace try_this_5
	{
		void main();
	}

	//	p.792
	namespace try_this_6
	{
		void main();
	}


	void main();
}

namespace ch21_drill
{

}

namespace ch21_exc
{


}