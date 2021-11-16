#include "ch21.h"

#include <fstream>
#include <iostream>
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
					iid;
				double
					value;
			};

			ostream & operator << (ostream & os, Item i)
			{
				os 
					<< i.name << '\t'
					<< i.iid << '\t'
					<< i.value;
				return os;
			}

			void local ()
			{
				vector <Item>
					v {
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

				ofstream
					ofs {"..\\Basics\\resources\\ch21_d01.txt"};
				ostream_iterator <Item>
					oi {ofs, "\n"};
				copy (v.begin(), v.end(), oi);
			}


		}

		void main()
		{
			_01::local();
		}
	}
}