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
			T string_to_num (string s, T & t)
			{
				stringstream
					ss {s};
				ss >> t;
				return t;
			}

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

				Item (string n, int i, double v) :
					name {n},
					iid {i},
					value {v}
				{}

				Item (const Item & item) :
					name {item.name},
					iid {item.iid},
					value {item.value}
				{}

				//Item (string n, string i, string v) :
				//	name {n},
				//	iid {},
				//	value {}
				//{
				//	num_from_string (i, iid);
				//	num_from_string (v, value);				
				//}

				//Item & operator = (const Item & item)
				//{
				//	if (this == & item)
				//		return * this;
				//	name = item.name;
				//	iid = item.iid;
				//	value = item.value;
				//	return * this;
				//}

				string to_string()
				{					
					return name + " " + num_to_string (iid) + " " + num_to_string (value);
				}
			};

			ostream & operator << (ostream & os, const Item & i)
			{
				os 
					<< i.name << " "
					<< i.iid << " "
					<< i.value;

				//os 
				//	<< i.name << " " 
				//	<< num_to_string (i.iid) << " " 
				//	<< num_to_string (i.value);

				return os;
			}

			istream & operator >> (istream & is, Item & item)
			{
				//vector <string>
				//	v {3,""};
				//for (auto & s : v)
				//	is >> s;
			
				//item.name = v[0];
				//string_to_num (v[1], item.iid);
				//string_to_num (v[2], item.value);

				is 
					>> item.name 
					>> item.iid 
					>> item.value;

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
						{"Czesiek", 7, 6.01},
						{"Wiesiek", 8, 2.59},
						{"£ysy", 9, 421.0},
					};

				string
					filename {"..\\Basics\\resources\\ch21_d01.txt"};

				ofstream
					ofs {filename};
				ostream_iterator <Item>
					oi {ofs, " "};
				copy (source.begin(), source.end(), oi);

				ofs.close();	// shouldn't be like that?

				vector <Item>
					vi {10, Item {}};
				ifstream
					ifs {filename};
				istream_iterator <Item>
					ii {ifs};
				//copy (ii, istream_iterator <Item> {}, vi.begin());

				auto 
					iter {vi.begin()};
				while (ii != istream_iterator <Item> {} && iter != vi.end())
				{
					* iter = * ii;
					++iter;
					++ii;
				}

				ifs.close();

				for (auto a : vi)
					cout
						<< a.to_string() << '\n';
			}
		}

		void main()
		{
			_01::local();
		}
	}
}