#include "ch21.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace ch21
{
	namespace tx
	{
		using namespace std;
	
		namespace _2								//	21.2
		{
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

			void report_1 (int query, int answer)
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
				void verify (vector <T> & v, int query, In answer = last)
			{
				int
					slot { 
						answer == v.end()
						? -1
						: answer - v.begin()
					};
				report_1 (query, slot);
			}

			void local_1()
			{
				vector <int>
					v {1, 2, 3, 4, 5, 6};
		
				cout
					<< "\n\tsuccess\n";
				int
					query {5};
				auto 
					answer {tx::find (v.begin(), v.end(), query)};
				verify (v, query, answer);
		
				answer = find_1 (v.begin(), v.end(), query);
				verify (v, query, answer);

				answer = find_2 (v.begin(), v.end(), query);
				verify (v, query, answer);

				cout
					<< "\n\tfail\n";
		
				query = 0;

				answer = tx::find (v.begin(), v.end(), query);
				verify (v, query, answer);

				answer = find_1 (v.begin(), v.end(), query);
				verify (v, query, answer);

				answer = find_2 (v.begin(), v.end(), query);
				verify (v, query, answer);
			}

			//	21.2.1

			template <typename In, typename T>
				void report_2 (In first, In last, T query, In answer = last)
			{
				cout
					<< "\telement " << query
					<< (answer == last
						? " wasn't found in the vector.\n"
						: " was found.\n");
			}

			void local_2()
			{
				std::list <int>
					v {1, 2, 3, 4, 5, 6};
				std::cout
					<< "\n\tsuccess\n";
				int 
					query {5};
				auto
					answer {_2::find (v.begin(), v.end(), query)};

				report_2 (v.begin(), v.end(), query, answer);

				query = 0;
				answer = _2::find (v.begin(), v.end(), query);
				report_2 (v.begin(), v.end(), query, answer);
			}

			void main()
			{
				local_1();
				local_2();
			}
		}

		namespace _3								//	21.3
		{
			template <typename In, typename Pred>
				In find_if (In first, In last, Pred p)
			{
				while (first != last && !p (int (*first)))
					++first;
				return first;
			}

			bool odd (int x) {return x % 2;}

			void local_1 (vector <int> & v)
			{
				auto 
					p {tx::find_if (v.begin(), v.end(), odd)};
				if (p != v.end())
					std::cout 
						<< "\tAn element satisfying the conditions was found: "
						<< *p << ".\n";
				else
					std::cout
						<< "\tNo element satisfying the conditions was found.\n";
			}

			bool larger_than_42 (double x) {return x > 42.;}

			void local_2 (vector <int> & v)
			{
				auto
					p {_3::find_if (v.begin(), v.end(), larger_than_42)};
				if (p != v.end())
					std::cout
						<< "\tAn element larger than 42 was found: " << *p <<".\n";
				else
					std::cout
						<< "\tNo element larger than 42 found.\n";
			}

			void main ()
			{
				vector <int> 
					v {1, 2, 3, 4, 5, 6};
				local_2 (v);

				v.push_back (43);
				local_2 (v);
			}
		}

		namespace _4								//	21.4
		{	
			bool Larger_than::operator () (int x) const 
			{
				return x > val;
			}

			void report (list <double> & v, int c)
			{
				auto
					p {_3::find_if (v.begin(), v.end(), Larger_than (c))};

				if (p != v.end())
					std::cout
						<< "\tAn element " << * p << " meets the conditions for " << c <<".\n";
				else 
					std::cout
						<< "\tNo element meeting the conditions for " << c << " was found.\n";
			}

			void local_1 ()
			{
				list <double> v {1, 2, 3, 4, 5, 6};

				report (v, 3);
				report (v, 31);
			}

			// 21.4.2

			bool Cmp_by_name::operator () (const Record & a, const Record & b) const
			{
				return a.name < b.name;
			}

			bool Cmp_by_addr::operator () (const Record & a, const Record & b) const
			{
				return strncmp (a.addr, b.addr, 24) < 0;
			}
	
			void local_2 ()
			{
				vector <Record>
					vr;

				sort (vr.begin(), vr.end(), Cmp_by_name());

				sort (vr.begin(), vr.end(), Cmp_by_addr());
			}

			//	21.4.3

			void example_1 ()
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

			void example_2 (list <double> & v, int x)
			{
				auto p {tx::find_if (
						v.begin(), 
						v.end(), 
						[] (double a) {return a > 31;}
					)
				};

				if (p != v.end())
					cout << "\tFound it.\n";

				auto q {tx::find_if (
						v.begin(), 
						v.end(), 
						[&] (double a) {return a > x;}
					)
				};

				if (q != v.end())
					cout << "\tFound it.\n";
			}

			void main()
			{
				local_1();
			}
		}

		namespace _5								// 21.5
		{
			//	21.5.1 sq

			template <typename In, typename T, typename BinOp>
				T accumulate (In first, In last, T init, BinOp op)
			{
				while (first != last)
				{
					init = op (init, * first);
					++first;
				}
				return init;
			}

			void local_1 ()
			{
				vector <double> 
					a {1.1, 2.2, 3.3, 4.4};
				cout 
					<< _5::accumulate (
						a.begin(), 
						a.end(), 
						1.0, 
						multiplies <double> ()			// function object form <functional>
					);
			}

			double Record_1::operator () () 
			{
				return unit_price * double (units);
			}

			void local_2 ()
			{
				cout << Record_1 (1.99, 10)();
			}

			double price (double v, const Record_2 & r)
			{
				return v + r.unit_price * r.units;
			}

			void f (const vector <Record_2> & vr)
			{
				double
					total {tx::accumulate (vr.begin(), vr.end(), 0.0, price)};
				cout 
					<< total;
			}

			void main()
			{
				vector <Record_2>
					v {
						{1.50, 100},
						{2.20, 20},
						{1., 6}
					};
				f(v);
			}

			//	21.5.3

			template <typename In, typename In2, typename T>
				T inner_product (In first, In last, In2 first2, T init)
			{
				while (first != last)
				{
					init += (* first) * (* first2);
					++first;
					++first2;
				}
				return init;
			}

			void example ()
			{
				vector <double> 
					dow_price  {81.86, 34.69, 54.45};
				list <double>
					dow_weight {5.8594, 2.4808, 3.8940};
				double
					dji_index {
						tx::inner_product (
							dow_price.begin(), 
							dow_price.end(),
							dow_weight.begin(),
							0.0
						)
					};
				cout << dji_index;				
			}

			//	21.5.4

			template <
				typename In, 
				typename In2, 
				typename T, 
				typename BinOp,
				typename BinOp2
			> T Inner_product (
				In first, 
				In last, 
				In2 first2, 
				T init, 
				BinOp op, 
				BinOp2 op2)
			{
				while (first != last)
				{
					init = op (init, op2 (* first, * first2));
					++first;
					++first2;
				}
				return init;
			}
		}

		namespace _6
		{
			//	21.6.1

			void ex1()
			{
				map <string, int>
					words;
				for (string s; cin >> s && s != "_esc";)	// needed a loop break condition
					++words [s];

				for (const auto & p : words)
					cout
						<< p.first << ": " << p.second << '\n';
			}

			// 21.6.3

			double weighted_value (
				const pair <string, double> & a,
				const pair <string, double> & b)
			{
				return a.second * b.second;
			}

			void ex2()
			{
				map <string, double> 
					dow_price {
						{"MMM", 81.86},
						{"AA", 34.69},
						{"MO", 54.45}
					},
					dow_weight {
						{"MMM", 5.8549},
						{"AA", 2.4808},
						{"MO", 3.8940}
					};
				map <string, string>
					dow_name {
						{"MMM", "3M Co."},
						{"AA", "Alcoa Inc"},
						{"MO", "Altria Group Inc."}
					};

				double 
					alcoa_price {dow_price ["AA"]},
					altria_price {dow_price ["MO"]};

					if (dow_price.find ("INTC") != dow_price.end())
						cout 
							<< "Intel is in the Dow\n";

				for (const auto & p : dow_price)
				{
					const string & 
						symbol {p.first};
					cout
						<< '\t' << symbol << '\t'
						<< p.second << '\t'
						<< dow_name [symbol] << '\n';
				}

				//	broken code :
				/*double dji_index {
					inner_product (
						dow_price.begin(), 
						dow_price.end(),
						dow_weight.begin(),
						0.0,
						plus <double> (),
						weighted_value
					)
				};
				cout
					<< "\tDow value is " << dji_index << '\n';*/
			}

			//	21.6.4

			void ex3()
			{
				unordered_map <string, double> 
					dow_price {
						{"MMM", 81.86},
						{"AA", 34.69},
						{"MO", 54.45}
					},
					dow_weight {
						{"MMM", 5.8549},
						{"AA", 2.4808},
						{"MO", 3.8940}
					};
				unordered_map <string, string>
					dow_name {
						{"MMM", "3M Co."},
						{"AA", "Alcoa Inc"},
						{"MO", "Altria Group Inc."}
					};

				double 
					alcoa_price {dow_price ["AA"]},
					altria_price {dow_price ["MO"]};

				for (const auto & p : dow_price)
				{
					const string & 
						symbol {p.first};
					cout
						<< '\t' << symbol << '\t'
						<< p.second << '\t'
						<< dow_name [symbol] 
						<< '\n';
				}
			}

			namespace ex4
			{
				struct Fruit
				{
					string
						name;
					int
						count;
					double
						unit_price;
					string
						last_sale_date;

					Fruit (string n, int c, double u, string d) :
						name {n},
						count {c},
						unit_price {u},
						last_sale_date {d}
					{}				
				};

				struct Fruit_order
				{
					bool operator () (const Fruit & a, const Fruit & b) const
					{
						return a.name < b.name;
					}
				};

				void local()
				{
					Fruit
						f_1 {
							"Gloster",
							1000000,
							1.75,
							"21-06-15"
						},
						f_2 {
							"Sawa",
							10000,
							1.90,
							"21-07-20"
						};;

					set <Fruit, Fruit_order> 
						inventory;

					inventory.insert (f_1);
					inventory.insert (f_2);

					for (auto a : inventory)
						cout
							<< '\t' 
							<< a.name
							<< '\n';
				}
			}
	
		}

		namespace _7
		{
			template <typename In, typename Out>
				Out copy (In first, In last, Out res)
			{
				while (first != last)
				{
					* res = * first;
					++res;
					++first;
				}
				return res;
			}

			template <typename T = vector <char>, typename U = list <char> >
				void safe_copy (T src, U dst)
			{
				if (src.size() > dst.size())
					runtime_error ("target container too small");

				_7::copy (src.begin(), src.end(), dst.begin());
			}

			void local_1 ()
			{
				vector <char> 
					v {'l', 'o', 'r', 'e', 'm', ' ', 'i', 'p', 's', 'u', 'm'};
				list <char>
					l (v.size());
				safe_copy (v, l);

				auto 
					v_iter {v.begin()};
				auto
					l_iter {l.begin()};

				while (v_iter != v.end() && l_iter != l.end())
				{
					cout 
						<< "\t v: " << * v_iter << ", l: " << *l_iter << '\n';
					++v_iter;
					++l_iter;
				}

				cout
					<< "\n\t"
					<< (v_iter == v.end() ? "v ended" : "v not ended")
					<< "\n\t"
					<< (l_iter == l.end() ? "l ended" : "l not ended")
					<< '\n';

				for (auto a : l)
					cout << a << '\n';
			}

			string
				from {"..\\Basics\\resources\\herling-grudzinski-gustaw_inny-swiat.txt"},
				to {"..\\Basics\\resources\\destination.txt"};

			void local_2 ()
			{
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
				unique_copy(b.begin(), b.end(), oo);
			}

			// 21.7.3

			void local_3 ()
			{
				ifstream 
					is {from};
				ofstream
					os {to};
				set <string>
					b {
						istream_iterator <string> {is}, 
						istream_iterator<string> {}
					};
				_7::copy (b.begin(), b.end(), ostream_iterator <string> {os, " "});
			}

			//	21.7.4

			template <typename In, typename Out, typename Pred>
			Out copy_if (In first, In last, Out res, Pred p)
			{
				while (first != last)
				{
					if (p (* first)) 
						* res = * first;
					++ res;
					++first;
				}
				return res;
			}

			void local_4 ()
			{
				using _4::Larger_than;

				vector <int> 
					v1 {0, 1, 2, 3, 4, 6, 7},
					v2 (v1.size());
				
				_7::copy_if (v1.begin(), v1.end(), v2.begin(), Larger_than (6));

				for (auto a : v2)
					cout
						<< '\t' << a << '\n';
			}
		}

		namespace _8
		{
			//	21.8

			struct No_case
			{
				bool operator () (const string & x, const string & y)
				{
					for (int i {0}; i < int (x.length()); ++i)
					{
						if (i == y.length())
							return false;
						char
							xx {char (tolower (x [i]))},
							yy {char (tolower (y [i]))};
						if (xx < yy)
							return true;
						if (xx > yy)
							return false;
					}
					if (x.length() == y.length())
						return false;
					return true;
				}
			};

			void sort_and_print (vector <string> & vc)
			{
				sort (vc.begin(), vc.end(), No_case());

				for (const auto & s : vc)
					cout
						<< '\t' << s << '\n';
			}

			void local ()
			{
				


			}
		}

		namespace _9
		{
			void test (vector <int> & v)
			{				
				sort (v.begin(), v.end());
			}

			void local ()
			{
				vector <int>
					v {0, 1, 2, 3, 4, 5, 6, 7};

				sort (v.begin(), v.begin() + v.size());
				sort (v.begin() + v.size(), v.end());

				int
					i {int (v.size()) >> 1};
				
				sort (v.begin(), v.begin() + i);
				sort (v.begin() + i, v.end());			
			}
		}
	}

	namespace tr
	{
		using namespace std;
	
		namespace _2
		{
			using namespace std::chrono;
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

		namespace _3
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

			double Record::operator () ()
			{
				return unit_price * double (units);
			}

			void report_1 (vector <Record> v)
			{
				cout << accumulate (
					v.begin(), 
					v.end(), 
					0.0, 
					[](double & d, Record & r)
					{
						return d += r();
					}		
				);
			}

			double price (double v, const Record & r)
			{
				return v + r.unit_price * r.units;
			}

			void report_2 (vector <Record> v)
			{
				cout << accumulate (
					v.begin(),
					v.end(),
					0.0,
					price
				);
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
				report_1 (v);

				cout << '\n';

				report_2 (v);
			}
		}

		namespace _4
		{

			template <typename In1, typename In2, typename T>
				T inner_product (In1 first_1, In1 last_1, In2 first_2, T init)
			{
				while (first_1 != last_1)
				{
					init += first_1 -> second * first_2 -> second;
					++first_1;
					++first_2;
				}
				return init;
			}

			map <string, double>
				stock_price,
				stock_weight;
			map <string, string>
				stock_name;

			void add_to_stock (string code, string name, double price = 0., double weight = 0.)
			{
				if (stock_name.insert ({code, name}).second)
				{
					stock_price.insert ({code, price});
					stock_weight.insert ({code, weight});
				}			
			}

			void list_stock ()
			{
				for (auto & a :  stock_name)
				{
					cout
						<< '\t' << a.first <<'\t' << a.second 
						<< '\t' << stock_price [a.first]
						<< '\t' << stock_weight [a.first]
						<< '\n';
				}
			}

			struct temp
			{
				string 
					code,
					name;
				double
					price,
					weight;
			};

			void main()
			{
				vector <temp> v {
					{"MMM", "3M Co.", 81.86, 5.8594},
					{"AA", "Alcoa Inc", 34.69, 2.4808},
					{"MO", "Altria Group Inc", 54.45, 3.8940},
					{"MMA", "Mordobicie SA", 0.61, 2.2512},
					{"PKS", "Pogotowie Kulturalno-Spo³eczne", 28.11, 0.4115}
				};

				for (auto & a : v)
				{
					add_to_stock (
						a.code,
						a.name,
						a.price,
						a.weight
					);
				}

				list_stock();

				cout 
					<< '\t' 
					<<	_4::inner_product
					(
						stock_price.begin(),
						stock_price.end(),
						stock_weight.begin(),
						0.
					)
					<< '\n';
			}
		}

		namespace _5
		{
			unordered_map <int, string>
				words;

			void add_to_words (string f)
			{
				ifstream
					ifs (f, ios_base::in);
			
				if (ifs) // ...
				{
					string 
						s {};
					int
						number {0};

					while (ifs >> s)
					{
						words.insert ({number, s});
						++number;
					}
				}

				ifs.close();

				for (auto & a : words)
					cout
						<< '\t' << a.second << '\n';
				cout
					<< "\n\trazem: " << words.size() << " s³ów.\n";
			}

			void local()
			{
				string
					filename {"E:\\_LAB\\_C\\Basics\\Basics\\resources\\herling-grudzinski-gustaw_inny-swiat.txt"};

				add_to_words(filename);
			}	
		}

		namespace _6
		{
			void local_1()
			{
				string
					from {"..\\Basics\\resources\\herling-grudzinski-gustaw_inny-swiat.txt"},
					to {"..\\Basics\\resources\\destination.txt"};

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

			void wrong(int max_size)
			{
				string
					from,
					to;
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
					b (max_size);

				copy (ii, eos, b.begin());
			}

			void local_2()
			{
				string
					from {"..\\Basics\\resources\\herling-grudzinski-gustaw_inny-swiat.txt"},
					to {"..\\Basics\\resources\\destination.txt"};

				ifstream
					is {from};
				ofstream
					os {to};
				istream_iterator <string>
					ii {is},
					eos;
				ostream_iterator <string>
					oo {os, "\n"};
				multiset<string>
					b {ii, eos};
				copy (b.begin(), b.end(), oo);
			}

			void local_3()
			{
				string
					from {"..\\Basics\\resources\\herling-grudzinski-gustaw_inny-swiat.txt"},
					to {"..\\Basics\\resources\\destination.txt"};

				ifstream
					is {from};
				ofstream
					os {to};
				istream_iterator <string>
					ii {is},
					eos;
				ostream_iterator <string>
					oo {os, "\n"};
				unordered_multiset<string>
					b {ii, eos};
				copy (b.begin(), b.end(), oo);
			}

			void temp()
			{
				string
					from {"..\\Basics\\resources\\destination.txt"};
				ifstream
					is {from};
				istream_iterator <string>
					ii {is},
					eos;
				vector <string>
					v {ii, eos};
				for (auto a : v)
					cout
						<< '\t' << a << '\n';
			}
		}
	}

	void main()
	{
		dr::main();
	}
}