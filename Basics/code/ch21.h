#pragma once

#include <list>
#include <string>
#include <vector>

namespace ch21
{
	// text examples
	namespace tx
	{
		using namespace std;

		//	21.2
		namespace _2								
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
		namespace _3
		{
			template <typename In, typename Pred>
				In find_if (In first, In last, Pred p);

			void local_1 (vector <int> & v);

			bool larger_than_42 (double x);

			void local_2 (vector <int> & v);

			void main();
		}

		//	21.4
		namespace _4
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
		namespace _5
		{
			template <typename In, typename T, typename BinOp>
				T accumulate (In first, In last, T init, BinOp op);

			void local_1 ();

			struct Record_1
			{
				double 
					unit_price;
				int 
					units;
				Record_1 (double p, int u) :
					unit_price {p},
					units {u}
				{}

				double operator () ();
			};

			struct Record_2
			{
				double 
					unit_price;
				int
					units;
			};

			double price (double v, const Record_2 & r);

			void f (const vector <Record_2> & vr);
	
			//	21.5.3

			template <typename In, typename In2, typename T>
				T inner_product (In first, In last, In2 first2, T init);

		}

		namespace _6
		{
			//	21.6.1

			void example();

			//	21.6.2

			/*
			template <typename Key, typename Value, typename Cmp = less <Key>>
				class _map
			{
				using value_type = pair <Key, Value>;

				using iterator = sometype1;
				using const_iterator = sometype2;

				iterator begin();
				iterator end();

				Value & operator [] (const Key & k);

				iterator find (const Key & k);

				void erase (iterator p);
				pair <iterator, bool> insert (const value_type &);
			};
			*/

			template <typename T1, typename T2>
				struct pair
			{
				using first_type = T1;
				using second_type = T2;

				T1 first;
				T2 second;
			};

			template <typename T1, typename T2>
				pair <T1, T2> make_pair (T1 x, T2 y)
			{
				return {x,y};
			}

			//	21.6.3




		

		}

		namespace _7
		{}
	}

	// text 'try this' drills
	namespace tr
	{
		//	try_this 1 p.765

		namespace _2
		{
			template <typename In, typename T>
			In find_while (In first, In last, const T & val);

			template <typename In, typename T>
			In find_for (In first, In last, const T & val);
	
			void main();
		}

		//	p.774
		namespace _3
		{

			template <typename In, typename T>
				T m_accumulate (In first, In last, T val);


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

				double operator () ();
			};

			double price (double v, const Record & r);

			void main();

		}

		//	p.785
		namespace _4
		{
			void main();
		}

		//	p.787
		namespace _5
		{
			void main();
		}

		//	p.789
		namespace _6
		{
			void local();
			void wrong (int max_size);
		}

		//	p.789

		namespace _7{}

		//	p. 794
		namespace _8
		{
			//template <typename Ran> void sort (Ran first, Ran last);
			//template <typename Ran, typename Cmp> void sort (Ran first, Ran last, Cmp cmp);

			struct No_case{};
		}
	}

	// homework drills
	namespace dr
	{	
		void main();
	}

	// homework excercises
	namespace ex
	{


	}

		void main();
}