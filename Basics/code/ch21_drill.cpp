#include "ch21.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

namespace ch21
{
	namespace dr
	{
		using namespace std;

		namespace _01
		{
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

				Item () : name {}, iid {}, value {} {}

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

			string initial (bool flag = false)
			{
				string
					filename {"..\\Basics\\resources\\ch21_d01.txt"};

				if (flag)
				{
					vector <Item>
						source {
							{"Marzena", 2, 1.234},
							{"Borzena", 1, 2.52}, 
							{"Grarzyna", 4, 6.3}, 
							{"Halyna", 7, 0.352},
							{"Jarzyna", 3, 952.4}, 
							{"Rysiek", 5, -12.5},
							{"Zbysiek", 9, 0.0},
							{"Czesiek", 8, 6.01},
							{"Wiesiek", 6, 2.59},
							{"Gruby", 0, 421.0},
					};
					ofstream ofs {filename};
					ostream_iterator <Item> oi {ofs, " "};
					copy (source.begin(), source.end(), oi);
					ofs.close();
				}

				return filename;
			}

			template <typename Iter>
			void printer (Iter first, Iter last)
			{
				while (first != last)
				{
					cout << first -> to_string() << '\n';
					++first;
				}
			}

			vector <Item> import (const string & filename)
			{
				vector <Item> vi {10, Item {}};
				ifstream ifs {filename};
				istream_iterator <Item> ii {ifs};

				copy (ii, istream_iterator <Item> {}, vi.begin());
				ifs.close();
				return vi;
			}

			template <typename Pred = less <string>>
			struct By_name
			{
				Pred predicate;
				explicit By_name (Pred p = less <string> {}) : predicate {p} {}					
				bool operator () (const Item & x, const Item & y)
				{
					return predicate (x.name, y.name);
				}
			};

			template <typename Pred = less <int>>
			struct By_id
			{
				Pred predicate;
				explicit By_id (Pred p = less <int> {}) : predicate {p} {}
				bool operator () (const Item & x, const Item & y)
				{
					return predicate (x.iid, y.iid);
				}
			};

			template <typename Pred = less <double>>
			struct By_value
			{
				Pred predicate;
				explicit By_value (Pred p = less <double> {}) : predicate {p} {}
				bool operator () (const Item & x, const Item & y)
				{
					return predicate (x.value, y.value);
				}
			};

			template <typename T = vector <Item>>
			void local_1 (T data, bool flag = false)
			{
				for (auto a : data)
					cout << a.to_string() << '\n';
			}

			template <typename T = vector <Item>, typename Pred>
			void local_2 (T data, Pred predicate, bool flag = false)
			{
				sort (data.begin(), data.end (), predicate);
				cout << "\tpost:\n";
				printer (data.begin(), data.end());
			}
			
			template <typename T = vector <Item>, typename Pred>
			void local_4 (T & data, Pred predicate, bool flag = false)
			{
				sort (data.begin(), data.end (), predicate);
				cout << "\tpost:\n";
				printer (data.rbegin(), data.rend());
			}
		}

		void main()
		{
			using Item = _01::Item;
			vector <Item> v {_01::import (_01::initial())};
			_01::local_1 (v);
			//_01::local_2 (v, _01::By_name <>{});
			//_01::local_2 (v, _01::By_id <> {});
			//_01::local_4 (v, _01::By_value <> {});
		}
	}
}