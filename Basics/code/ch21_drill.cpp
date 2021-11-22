#include "ch21.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

namespace ch21
{
	namespace dr
	{
		using namespace std;

			template <typename T>
			string num_to_string (T & t)
			{
				stringstream ss;				
				ss << t;
				string  result;
				ss >> result;
				return result;
			}

			struct Item
			{
				string
					name;
				int
					iid {};
				double
					value {};

				explicit Item () : name {}, iid {}, value {} {}

				Item (string n, int i, double v) : name {n}, iid {i}, value {v} {}

				string to_string()
				{					
					return name + " " + num_to_string (iid) + " " + num_to_string (value);
				}
			};

			ostream & operator << (ostream & os, const Item & i)
			{
				return os << i.name << " " << i.iid << " " << i.value;
			}

			istream & operator >> (istream & is, Item & item)
			{
				return is  >> item.name  >> item.iid  >> item.value;
			}

			template <typename T>
			void initial (vector <T> source, string filename)
			{
				ofstream ofs {filename};
				ostream_iterator <T> oi {ofs, " "};
				copy (source.begin(), source.end(), oi);
				ofs.close();
			}

			template <typename Iter>
			void printer (Iter first, Iter last, bool flag = false)
			{
				while (first != last)
				{
					cout << first -> to_string() << '\n';
					++first;
				}
			}

			template <typename T = vector <Item>>
			void import (T & data, const string & filename)
			{
				ifstream ifs {filename};
				istream_iterator <Item> ii {ifs};
				copy (ii, istream_iterator <Item> {}, data.begin());
				ifs.close();
			}

		namespace d_1
		{
			vector <Item> source {
				{"marzena", 2, 1.234},
				{"borzena", 1, 2.52}, 
				{"grarzyna", 4, 6.3}, 
				{"halyna", 7, 0.352},
				{"jarzyna", 3, 952.4}, 
				{"rysiek", 5, -12.5},
				{"zbysiek", 9, 0.0},
				{"czesiek", 8, 6.01},
				{"wiesiek", 6, 2.59},
				{"gruby", 0, 421.0},
			};
			string filename {"..\\Basics\\resources\\ch21_d01.txt"};

			void local_0 ()
			{
				initial <Item> (source, filename);
			}

			vector <Item> vi {10, Item{}};

			void local_1 ()
			{
				import (vi, filename);
				printer  (vi.begin(), vi.end());
			}

			void local_2 ()
			{
				auto a = [] (const Item & i1, const Item & i2) {return i1.name < i2.name;};
				import (vi, filename);
				sort (vi.begin(), vi.end(), a);
				printer (vi.begin(), vi.end());
			}

			void local_3 ()
			{
				auto a = [] (const Item & i1, const Item & i2) {return i1.iid < i2.iid;};

				import (vi, filename);
				sort (vi.begin(), vi.end(), a);
				printer (vi.begin(), vi.end());
			}

			void local_4()
			{
				auto a = [] (const Item & i1, const Item & i2) {return i1.value < i2.value;};

				import (vi, filename);
				sort (vi.begin(), vi.end(), a);
				printer (vi.rbegin(), vi.rend());
			}

			void local_5(bool print_it = true)
			{
				auto a = [] (const Item & i1, const Item & i2) {return i1.name < i2.name;};
				import (vi, filename);
				sort (vi.begin(), vi.end(), a);				
				auto iter {vi.begin()};
				while (iter != vi.end() && iter -> name <= "horse shoe")
					++iter;
				vi.insert(iter, Item {"horse shoe", 99, 12.34});
				iter = vi.begin();
				while (iter != vi.end() && iter -> name <= "canons400")
					++iter;
				vi.insert (iter, Item {"canons400", 9988, 499.95});
				printer (vi.begin(), vi.end());
			}

			void local_6 ()
			{
				local_5(false);
				auto iter {vi.cbegin()};
				while (iter != vi.cend() && iter -> name != "horse shoe")
					++iter;
				vi.erase (iter);
				iter = vi.cbegin();
				while (iter != vi.cend() && iter -> name != "canons400")
					++iter;
				vi.erase (iter);
				printer (vi.begin(), vi.end());
			}

			void local_7 ()
			{
				local_5(false);
				auto iter {vi.cbegin()};
				while (iter != vi.cend() && iter -> iid != 99)
					++iter;
				vi.erase (iter);
				iter = vi.cbegin();
				while (iter != vi.cend() && iter -> iid != 9988)
					++iter;
				vi.erase (iter);
				printer (vi.begin(), vi.end());				
			}

			void local_8 ()
			{
				local_5(false);
				auto iter {vi.cbegin()};
				while (iter != vi.cend() && iter -> value != 12.34)
					++iter;
				vi.erase (iter);
				iter = vi.cbegin();
				while (iter != vi.cend() && iter -> value != 499.95)
					++iter;
				vi.erase (iter);
				printer (vi.begin(), vi.end());				
			}
		}

		namespace d_2
		{
			list <Item> li {10, Item {}};

			void local_0()
			{
				initial <Item> (d_1::source, d_1::filename);
			}

			void local_1()
			{
				import (li, d_1::filename);
				printer (li.begin(), li.end());
			}

			void local_2()
			{
				li.sort ([] (const Item & i1, const Item &i2) {return i1.name < i2.name;});
				printer (li.begin(), li.end());
			}

			void local_3()
			{
				li.sort ([] (const Item & i1, const Item & i2) {return i1.iid < i2.iid;});
				printer (li.begin(), li.end());
			}

			void local_4()
			{
				li.sort ([] (const Item & i1, const Item & i2) {return i1.value < i2.value;});
				printer (li.rbegin(), li.rend());
			}

			Item
				horse {"horse shoe", 99, 12.34},
				canon {"canons400", 9988, 499.95};

			void local_5(bool print_it = true)
			{
				li.sort ([] (const Item & i1, const Item & i2) {return i1.name < i2.name;});
				auto iter {li.begin()};
				while (iter != li.end() && iter -> name < horse.name)
					++iter;
				li.insert (iter, horse);
				iter = li.begin();
				while (iter != li.end() && iter -> name < canon.name)
					++iter;
				li.insert(iter, canon);
				//if (print_it) 
					printer (li.begin(), li.end());
			}

			void local_6 ()
			{
				local_5 (false);

				auto iter {li.begin()};
				while (iter != li.end() && iter -> name != horse.name)
					++iter;
				li.erase (iter);
				iter = li.begin();
				while (iter != li.end() && iter -> name != canon.name)
					++iter;
				li.erase (iter);
				printer (li.begin(), li.end());
			}

			void local_7()
			{
				local_5 (false);
				auto iter {li.begin()};
				while (iter != li.end() && iter -> iid != horse.iid)
					++iter;
				li.erase (iter);
				iter = li.begin();
				while (iter != li.end() && iter -> iid != canon.iid)
					++iter;
				li.erase (iter);
				printer (li.begin(), li.end());
			}
		}

		namespace d_3
		{			
			string to_string(pair <string, int> p)
			{					
				return p.first + " " + num_to_string (p.second);
			}

			template <typename Iter = map <string, int>::iterator>
			void printer (Iter first, Iter last)
			{
				while (first != last)
				{
					cout << to_string (* first) <<'\n';
					++first;
				}
			}

			map <string, int> msi {};

			initializer_list <pair <string, int>> source
			{
				{"marzena", 2},
				{"borzena", 1}, 
				{"grarzyna", 4}, 
				{"halyna", 7},
				{"jarzyna", 3}, 
				{"rysiek", 5},
				{"zbysiek", 9},
				{"czesiek", 8},
				{"wiesiek", 6},
				{"gruby", 0}
			};

			void import()
			{
				msi.insert (
					{
						{"marzena", 2},
						{"borzena", 1}, 
						{"grarzyna", 4}, 
						{"halyna", 7},
						{"jarzyna", 3}, 
						{"rysiek", 5},
						{"zbysiek", 9},
						{"czesiek", 8},
						{"wiesiek", 6},
						{"gruby", 0}
					}
				);
			}

			void local_4()
			{
				pair <string, int>
					horse {"horse shoe", 99},
					canon {"canons400", 9988};

				msi.insert(horse);
				msi.insert(canon);

				printer (msi.begin(), msi.end());
			}

			void local_5()
			{
				for (pair <string, int> p; cin >> p.first >> p.second;)
				{
					msi.insert (p);
				}
				printer (msi.begin(), msi.end());
			}

			void local_6()
			{
				string
					filename {"..\\Basics\\resources\\ch21_d03.txt"};				
				ifstream ifs {filename};
				istream_iterator <string>
					ii {ifs},
					last {};
				pair <string, int> p {};
				stringstream ss {};
				while (ii != last)
				{
					p.first = * ii;
					++ii;
					ss << * ii;
					ss >> p.second;
					++ii;
					msi.insert (p);
				}
			}

			void local_7()
			{
				cout << "\tBegin of search.\n";
				string s{};
				while (cin >> s)	// ctr-c breaks loop
				{
					cout << '\t' << s << " " << msi[s] << '\n';
				}
				cout << "\tEnd of search.\n";
			}

			void local_8()
			{
				int result {};
				for (auto a : msi)
				{
					result += a.second;
				}
				cout << '\t' << result << '\n';
			}

			map <int, string> mis {};

			void local_A()
			{
				for (auto a : msi)
				{
					mis.insert({a.second, a.first});
				}

				auto iter {mis.begin()};
				while (iter != mis.end())
				{
					cout << iter -> first << " " << iter -> second  <<'\n';
					++iter;
				}
			}
		}

		namespace d_4
		{
			vector <double> source {
				123.05, 
				72715.0213,
				-120.2539,
				0.0,
				-12.5,
				72.05826,
				785.745,
				79.3656,
				259.81,
				1.63,
				89.1,
				-68.99
			};
			string filename {"..\\Basics\\resources\\ch21_d04.txt"};

			template <typename Iter>
			void printer (Iter first, Iter last)
			{
				while (first != last)
				{
					cout << '\t' << * first << '\n';
					++first;
				}
			}

			vector <double> local_1()
			{
				vector <double> vd {};
				ifstream ifs {filename};
				istream_iterator <double> ii {ifs};
				while (ii != istream_iterator <double> {})
				{	
					vd.push_back (* ii);
					++ii;
				}
				return vd;
			}

			void local_2(vector <double> & vd)
			{
				for (auto a : vd)
					cout << '\t' << fixed << a << '\n';
			}

			vector <double> vi;

			vector <int> local_3(vector <double> & vd)
			{
				vector <int> vi (vd.size());
				copy (vd.begin(), vd.end(), vi.begin());
				return vi;
			}

			template <typename Iter1, typename Iter2>
			void local_4 (Iter1 first1, Iter1 last1, Iter2 first2)
			{
				pair <double, int>	p {};
				while (first1 != last1)
				{
					p.first = * first1;
					p.second = * first2;
					cout << '\t' << p.first << '\t' << p.second << '\n';
					++first1;
					++first2;
				}
			}

			template <typename Iter, typename T = double>
			T local_5 (Iter first, Iter last, T accumulator = 0.)
			{
				while (first != last)
				{
					accumulator += * first;
					++first;
				}
				return accumulator;
			}

			template <typename Iter1, typename Iter2>
			void local_6(Iter1 first1, Iter1 last1, Iter2 first2)
			{
				double accu1 {};
				int accu2 {};
				while (first1 != last1)
				{
					accu1 += * first1;
					accu2 += * first2;
					++first1;
					++first2;
				}
				cout << '\t' << fixed << accu1 - double (accu2) << '\n';
			}
		
			template <typename Iter>
			void local_7(Iter first, Iter last)
			{
				cout << "pre:\n";
				printer (first, last);
				reverse (first, last);
				cout << "post:\n";
				printer (first, last);
			}

			template <typename Iter>
			double local_8(Iter first, Iter last, double accumulator = 0.0)
			{
				double length {double (last - first)};
				while (first != last)
				{
					accumulator += * first;
					++first;
				}
				return accumulator / length;
			}
		
			vector <double> local_9 (vector <double> vd, double mean)
			{
				vector <double> vd2 (vd.size());
				copy_if (vd.begin(), vd.end(), vd2.begin(), [&](double d){return d < mean;});
				return vd2;
			}

			template <typename Iter>
			void local_A (Iter first, Iter last)
			{
				sort (first, last, less <double> {});
			}
		}

		void main()
		{
			// drills 01 : vector
			if (false)
			{
				using namespace d_1;
				local_0 ();

				//local_1();
				//local_2();
				//local_3();
				//local_4();
				//local_5();
				//local_6();
				//local_7();
				//local_8();
			}

			//drills 02 : list
			if (false) 
			{
				using namespace d_2;
				local_0();

				//local_1();
				//local_2();
				//local_3();
				//local_4();
				//local_5 ();
				//local_6();
				//local_7();
			}

			//drills 03 : map
			if (false)
			{
				using namespace d_3;				
				import();

				//local_4();
				//local_5();
				//local_6();
				//d_3::printer (msi.begin(), msi.end());
				//local_7();
				//local_8();
				//local_A();
			}

			//drills 04 : moar vectah
			if (true)
			{
				using namespace d_4;
				initial(source, filename);

				vector <double> vd {local_1()};
				//local_2();
				vector <int> vi {local_3(vd)};
				//d_4::printer (vi.begin(), vi.end());
				//local_4 (vd.begin(), vd.end(), vi.begin());
				//cout << fixed << local_5(vd.begin(), vd.end()) << '\n';
				//local_6 (vd.begin(), vd.end(), vi.begin());
				//local_7(vd.begin(), vd.end());
				double mean {local_8 (vd.begin(), vd.end())};
				//cout << '\t' << fixed << mean << '\n';
				//vector <double> vd2 {local_9(vd, mean)};
				//d_4::printer (vd2.begin(), vd2.end());
				//local_A(vd.begin(), vd.end());
				//d_4::printer (vd.begin(), vd.end());
			}
		}
	}
}
