#include "ch21.h"

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
							{"Marzena", 0, 1.234},
							{"Bo¿ena", 1, 2.52}, 
							{"Gra¿yna", 2, 6.3}, 
							{"Halyna", 3, 0.352},
							{"Jarzyna", 4, 952.4}, 
							{"Rysiek", 5, -12.5},
							{"Zbysiek", 6, 0.0},
							{"Czesiek", 7, 6.01},
							{"Wiesiek", 8, 2.59},
							{"£ysy", 9, 421.0},
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

			void local_1 ()
			{
				for (auto a : import (initial (false)))
					cout
					<< a.to_string() << '\n';
			}

			void local_2 ()
			{



			}
		}

		void main()
		{
			_01::local_1();
		}
	}
}