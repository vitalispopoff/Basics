#pragma once

#include <iostream>
#include <initializer_list>
#include <algorithm>	//for the copy function in initializer_list constructor
#include <memory>

using namespace std;
namespace ch19
{
	template <typename T>	// T is Element <E>()
	class m_vector
	{
		allocator<T> alloc;
		int sz;
		int space;
		T * elem;

	public : 

		m_vector () :
			sz {0},
			space {8},
			//elem {new T [space]}
			elem {alloc.allocate (space)}
		{}

		explicit m_vector (int i, T val = T()) :
			sz {i},
			space {i},
			//elem {new T [space]}
			elem {alloc.allocate (space)}
		{
			for (int c = 0; c < sz; ++c) 
				//elem [c] = c; 
				alloc.construct (& elem [i], val);
		}

		m_vector (initializer_list <T> lst) :
			sz {(int) lst.size()},
			space {(int) lst.size()},
			//elem {new T [sz]}
			elem {alloc.allocate (space)}
		{
			copy (lst.begin(), lst.end(), elem);
		}

		m_vector (const m_vector & v) :
			sz {v.sz},
			space {sz},
			//elem {new T [sz]}
			elem {alloc.allocate (space)}
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
			delete [] elem;		// keep delete or connect with alloc ?
			//elem = nullptr;	// redundant, innit?
		}

		m_vector & operator = (const m_vector & v);
		m_vector & operator = (m_vector && v) noexcept (true);
		

		T & operator [] (int n) {return elem [n];}
		const T & operator [] (int n) const {return elem [n];}

		void reserve (int new_space);
		void resize(int new_size, T val = T());
		void push_back (T val);

		int size () const {return sz;}
		int capacity () const {return space;}
	};


	void main();
}
