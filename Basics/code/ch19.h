#pragma once

#include <iostream>
#include <initializer_list>
#include <algorithm>	//for the copy function in initializer_list constructor

using namespace std;
namespace ch19
{
	template <typename T>
	class m_vector
	{
		int sz;
		int space;
		T * elem;

	public : 

		m_vector () :
			sz {0},
			space {8},
			elem {new T [space]}
		{}

		explicit m_vector (int i) :
			sz {i},
			space {i},
			elem {new T [space]}
		{
			for (int c = 0; c < sz; ++c) 
				elem [c] = c; 
		}

		m_vector (initializer_list <T> lst) :
			sz {(int) lst.size()},
			space {(int) lst.size()},
			elem {new T [sz]}
		{
			copy (lst.begin(), lst.end(), elem);
		}

		m_vector (const m_vector & v) :
			sz {v.sz},
			space {sz},
			elem {new T [sz]}
		{
			copy (v.elem, v.elem + sz, elem);
		}

		m_vector (m_vector && v) noexcept (true) :
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

		m_vector & operator = (m_vector && v) noexcept (true);
		

		T & operator [] (int n)
		{
			return elem [n];
		}
		const T & operator [] (int n) const
		{
			return elem [n];
		}

		void reserve (int i);
		void resize(int i);
		void push_back (T d);

		int size () const {return sz;}
		int capacity () const {return space;}
	};


	void main();
}
