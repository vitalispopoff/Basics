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
			struct Item
			{
				string
					name;
				int
					iid {};
				double
					value {};

				int iid_from_string(string s)
				{
					stringstream
						ss {s};
					int 
						result;
					ss >> result;
					return result;
				}

				double value_from_string (string s)
				{
					stringstream
						ss {s};
					double
						result;
					ss >> result;
					return result;
				}

				Item (string n, int i, double v) :
					name {n},
					iid {i},
					value {v}
				{}

				Item (string n, string i, string v) :
					name {n},
					iid {iid_from_string (i)},
					value {value_from_string (v)}
				{}

				string to_string()
				{
					string
						i,
						v;
					stringstream
						s1,
						s2;
					s1 << iid;
					s1 >> i;
					s2 << value;
					s2 >> v;
					
					return name + "\t" + i + "\t" + v;
				}
			};

			ostream & operator << (ostream & os, Item i)
			{
				os 
					<< i.name //<< '\t'
					;
					//<< i.iid << '\t'
					//<< i.value;
				return os;
			}

			istream & operator >> (istream & is, Item item)
			{
				//string 
				//	n;
				//int
				//	i;
				//double
				//	v;
				is
					>> item.name 
				;
					//>> item.iid 
					//>> item.value;

				//item.name = n;
				//item.iid = i;
				//item.value = v;

				return is;
			}

			void local ()
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
						{"Czesiek", 7, 6.0},
						{"Wiesiek", 8, 2.59},
						{"£ysy", 9, 421.},
					};

				string
					filename {"..\\Basics\\resources\\ch21_d01.txt"};
					
				Item
					it {"nazwa", "1", "0.1"};
				
				cout << double (it.iid) + it.value;
			}
		}

		void main()
		{
			_01::local();
		}
	}
}