#include "ch19.h"

#include <vector>

namespace ch19_drill
{
	template <typename T> T & S <T>::get() {return val;}
	
	template <typename T> void show (S<T> in) {cout << in.get() << '\n';}
	
	void main()
	{
		S <int> i {-1};
		show (i);
		S <char> c {'@'};
		show (c);
		S <double> d {1.618};
		show (d);
		S <string> s {""};
		show (s);
		S <vector<int>> v {{1,2,3}};
		for (int x : v.get())
			cout 
				<< x << ", ";
	}
}