#pragma once

#include <iostream>
#include <initializer_list>
#include <algorithm>	//for the copy function in initializer_list constructor
#include <memory>

using namespace std;
namespace ch19
{

	template <typename T, typename A = allocator <T>>
		struct vector_base
	{
		A alloc;
		T * elem;
		int sz;
		int space;

		vector_base () :
			alloc {A ()},
			elem {alloc.allocate (8)},
			sz {0},
			space {8}
		{}

		vector_base (const A & a, int n) :
			alloc {a},
			elem {alloc.allocate (n)},
			sz {n},
			space {n}
		{}
		~vector_base () {alloc.deallocate (elem, space);}
	};
		
	template <typename T, typename A = allocator <T>>	// T is Element <E>()
	class m_vector : private vector_base<T, A>
	{
		//A alloc;
		//int sz;
		//int space;
		//T * elem;

	public : 

		m_vector ()
		//	sz {0},
		//	space {8},
		//	elem {alloc.allocate (space)}
		{
			this -> alloc = A ();
			this -> sz = 0;
			this -> space = 8;
			this -> elem = this -> alloc.allocate (this -> space);
		
		}

		explicit m_vector (int n, T val = T())
		{
			this -> sz = max (0, n);
			this -> space = max(1, n);
			this -> elem = this -> alloc.allocate (this -> space);

			for (int i = 0; i < this -> sz; ++i) 
				this->alloc.construct (& (this->elem [i]), val);
		}

		//m_vector (initializer_list <T> lst) :
		//	sz {(int) lst.size()},
		//	space {(int) lst.size()},
		//	elem {alloc.allocate (space)}
		//{
		//	copy (lst.begin(), lst.end(), elem);
		//}

		//m_vector (const m_vector & v) :
		//	sz {v.sz},
		//	space {sz},
		//	elem {new T [sz]}
		//{
		//	copy (v.elem, v.elem + sz, elem);
		//}

		//m_vector (m_vector && v) noexcept (true) :
		//	sz {v.sz},
		//	space {v.space},
		//	elem {v.elem}
		//{
		//	v.sz = v.space = 0;
		//	v.elem = nullptr;
		//}

		~m_vector ()
		{
			//delete [] elem;		// keep delete or connect with alloc ?
		}

		//m_vector & operator = (const m_vector & v);
		//m_vector & operator = (m_vector && v) noexcept (true);
		

		T & operator [] (int n) {return this -> elem [n];}
		const T & operator [] (int n) const {return this -> elem [n];}

		//void reserve (int new_space);
		//void resize(int new_size, T val = T());
		//void push_back (T val);

		int size () const {return this -> sz;}
		int capacity () const {return this -> space;}

		/// for testing:
		const T * addr () const {return this -> elem;}
	};


	void main();
}
