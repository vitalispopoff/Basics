#include "ch19.h"

#include <vector>

namespace ch19_drill
{
	template <typename T> 
		T & S<T>::get() {return val;}
	template <typename T> 
		const T & S<T>::get() const {return val;}
	template <typename T> 
		S<T> S<T>::operator = (const T & t)
	{		
		val = t;
		return * this;		
	}
	template <typename T>
		void read_val (T & v) {cin >> v;}
	
	template <typename T> void show (S<T> in) {cout << in.get() << '\n';}
	
	void main()
	{
		S <int> i {-1};
		read_val(i.get());		
		show (i);
		S <char> c {'@'};
		read_val (c.get());
		show (c);
		S <double> d {1.618};
		read_val (d.get());
		show (d);
		S <string> s {""};
		const string str {"nope"};
		s = str;
		show (s);
		read_val (s.get());
		show (s);
		S <vector<int>> v {{}};
		v.set ({1, 2, 3});
		for (int x : v.get())
			cout 
				<< x << ", ";
	}
}