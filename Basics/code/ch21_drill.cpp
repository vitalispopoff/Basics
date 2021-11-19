#include "ch21.h"

#include <algorithm>
#include <fstream>
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
				stringstream
					ss;				
				ss << t;
				string 
					result;
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

			string initial (bool flag)
			{
				string
					filename {"..\\Basics\\resources\\ch21_d01.txt"};

				if (flag)
				{
					vector <Item>
						source {
							{"Marzena", 2, 1.234},
						{"Bo¿ena", 1, 2.52}, 
						{"Gra¿yna", 4, 6.3}, 
						{"Halyna", 7, 0.352},
						{"Jarzyna", 3, 952.4}, 
						{"Rysiek", 5, -12.5},
						{"Zbysiek", 9, 0.0},
						{"Czesiek", 8, 6.01},
						{"Wiesiek", 8, 2.59},
						{"Gruby", 0, 421.0},
					};

					ofstream
						ofs {filename};
					ostream_iterator <Item>
						oi {ofs, " "};

					copy (source.begin(), source.end(), oi);
					ofs.close();
				}

				return filename;
			}

			vector <Item> import (const string & filename)
			{
				vector <Item>
					vi {10, Item {}};
				ifstream
					ifs {filename};
				istream_iterator <Item>
					ii {ifs};

				copy (ii, istream_iterator <Item> {}, vi.begin());

				ifs.close();

				return vi;
			}

			void local_1 (bool flag)
			{
				for (auto a : import (initial (flag)))
					cout
					<< a.to_string() << '\n';
			}

			void printer (vector <Item> v)
			{
				for (auto a : v)
					cout
					<< a.to_string() << '\n';
			}

			struct No_case
			{
				bool operator () (const Item & x, const Item & y)
				{
					for (int i {0}; i < int (x.name.length()); ++i)
					{
						if (i == y.name.length())
							return false;
						char
							xx {char (tolower (x.name [i]))},
							yy {char (tolower (y.name [i]))};
						if (xx < yy)
							return true;
						if (xx > yy)
							return false;
					}
					if (x.name.length() == y.name.length())
						return false;
					return true;
				}
			};

			void local_2 (bool flag)
			{
				vector <Item> 
					vi = import (initial (flag));

				cout 
					<< "\tpre:\n";
				printer(vi);

				sort (vi.begin(), vi.end(), No_case {});

				cout 
					<< "\tpost:\n";
				printer(vi);

			}

			struct By_id 
			{
				bool operator () (const Item & x, const Item & y)
				{
					return x.iid < y.iid;
				}
			};

			void local_3 (bool flag)
			{
				vector <Item> 
					vi = import (initial (flag));				

				cout 
					<< "\tpre:\n";
				printer (vi);

				sort (vi.begin(), vi.end(), By_id{});

				cout 
					<< "\tpost:\n";
				printer (vi);
			}

			struct By_val
			{
				bool operator () (const Item & x, const Item & y)
				{
					return x.value < y.value;
				}
			};

			void local_4 (bool flag)
			{
				vector <Item> 
					vi = import (initial (flag));				

				cout 
					<< "\tpre:\n";
				printer (vi);

				sort (vi.begin(), vi.end(), By_val{});

				cout 
					<< "\tpost:\n";

				auto 
					iter {vi.rbegin()};
				while (iter != vi.rend())
				{
					cout << iter -> to_string() << '\n';
					++iter;
				}
			}
		}

		void main()
		{
			//_01::local_1(false);
			//_01::local_2(false);
			//_01::local_3(false);
			_01::local_4(false);
		}
	}
}