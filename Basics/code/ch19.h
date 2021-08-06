#pragma once

#include <initializer_list>
#include <algorithm>	//for the copy function in initializer_list constructor

using namespace std;
namespace ch19
{
	class m_vector
	{
		int sz;
		int space;
		double * elem;

	public : 

		m_vector () :
			sz {0},
			space {8},
			elem {new double [space]}
		{}

		explicit m_vector (int i) :
			sz {i},
			space {i},
			elem {new double [space]}
		{			
			for (int c = 0; c < sz; ++c) 
				elem [c] = c; 
		}

		m_vector (initializer_list <double> lst) :
			sz {(int)lst.size()},
			space {(int)lst.size()},
			elem {new double [sz]}
		{
			copy (lst.begin(), lst.end(), elem);
		}

		~m_vector ()
		{
			delete [] elem;
			elem = nullptr;
		}

		double & operator [] (int n)
		{
			return elem [n];
		}
		const double & operator [] (int n) const
		{
			return elem [n];
		}


		int size () {return sz;}
		int capacity () {return space;}
	};


	void main();
}
