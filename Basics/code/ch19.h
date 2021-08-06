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
			sz {(int) lst.size()},
			space {(int) lst.size()},
			elem {new double [sz]}
		{
			copy (lst.begin(), lst.end(), elem);
		}

		m_vector (const m_vector & v) :
			sz {v.sz},
			space {sz},
			elem {new double [sz]}
		{
			copy (v.elem, v.elem + sz, elem);
		}

		m_vector (m_vector && v) :
			sz {v.sz},
			space {v.space},
			elem {v.elem}
		{
			v.sz = v.space = 0;
			v.elem = nullptr;
		}

		~m_vector ()
		{
			delete [] elem;
			elem = nullptr;
		}

		m_vector & operator = (const m_vector & v);
		

		double & operator [] (int n)
		{
			return elem [n];
		}
		const double & operator [] (int n) const
		{
			return elem [n];
		}


		int size () const {return sz;}
		int capacity () const {return space;}
	};


	void main();
}
