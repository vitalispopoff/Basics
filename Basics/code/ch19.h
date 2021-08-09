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
		int sz, space;
		T * elem;

		vector_base (const A & a, int n = 0) :			
			alloc {a},
			sz {0},
			space {max (0, n)},
			elem {(bool) space ? alloc.allocate (space) : nullptr}
		{}

		~vector_base () 
		{
			for (int i = 0; i < sz; ++i)
				alloc.destroy (elem + i);
		}
	};
		
	template <typename T, typename A = allocator <T>>
		class m_vector : private vector_base
		
		
		<T, A>
	{
	public : 

		explicit m_vector (int n = 0, T val = T()) :
			vector_base<T, A>::vector_base {A(), n}		
		{
			if (n > 0)
			{
			for (int i = 0; i < n; ++i) 
				this->alloc.construct (& (this -> elem [i]), val);
			this -> sz = n;
			}
		}

		m_vector (initializer_list <T> lst) :
			vector_base<T, A>::vector_base {A(), (int) lst.size()}
		{
			this -> sz = this -> space;
			copy (lst.begin(), lst.end(), this -> elem);
		}

		T & operator [] (int n) {return this -> elem [n];}
		const T & operator [] (int n) const {return this -> elem [n];}

		void reserve (int new_space);
		void resize(int new_size, T val = T());
		void push_back (T val);

		int size () const {return this -> sz;}
		int capacity () const {return this -> space;}

		/// for testing:
		const T * addr () const {return this -> elem;}
	};


	void main();
}

/// covers the last try_this excercise
namespace ch19_try_this
{
	template <typename T, typename A = allocator <T>>
		class m_vector
	{
		A alloc;
		int sz, space;
		T * elem;
	public :
		m_vector () :
			alloc {A ()},
			sz {0},
			space {8},
			elem {alloc.allocate (space)}
		{}

		explicit m_vector (int n, T val = T()) :
			sz {max (0, n)},
			space {max (1, n)},
			elem {alloc.allocate (space)}
		{
			for (int i = 0; i < sz; ++i)
				alloc.construct (& elem [i], val);
		}

		m_vector (initializer_list <T> lst) :
			sz {(int) lst.size()},
			space {(int) lst.size()},
			elem {alloc.allocate (space)}
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

		m_vector (m_vector && v) noexcept :
			sz {v.sz},
			space {v.space},
			elem {v.elem}
		{
			v.sz = v.space = 0;
			v.elem = nullptr;
		}

		~m_vector()
		{
			delete [] elem;	
		}

		m_vector & operator = (const m_vector & v);
		m_vector & operator = (m_vector && v) noexcept;

		T & operator [] (int n) {return elem [n];}
		const T & operator [] (int n) const {return elem [n];}

		void reserve (int new_space);
		void resize (int new_size, T val = T());
		void push_back (T val);

		int size() const {return sz;}
		int capacity() const {return space;}

		/// for testing
		const T * addr () const {return elem;}
	};


	void main();
}
