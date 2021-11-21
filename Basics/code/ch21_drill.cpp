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

			string filename {"..\\Basics\\resources\\ch21_d01.txt"};

			string initial ()
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
				ofstream ofs {filename};
				ostream_iterator <Item> oi {ofs, " "};
				copy (source.begin(), source.end(), oi);
				ofs.close();
				return filename;
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

			void local_1()
			{
				import (li, filename);
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

			void local_3()
			{

			}
		}

		void main()
		{
			/*{
				using namespace d_1;
				initial ();
				//local_1();
				//local_2();
				//local_3();
				//local_4();
				//local_5();
				//local_6();
				//local_7();
				local_8();
			}*/
			
			/*{
				using namespace d_2;
				initial();
				import (li, filename);
				//local_1();
				//local_2();
				//local_3();
				//local_4();
				//local_5 ();
				//local_6();
				//local_7();
			}*/

			{
				using namespace d_3;
				
				import();
				d_3::printer (msi.begin(), msi.end());
			}



		}
	}
}
