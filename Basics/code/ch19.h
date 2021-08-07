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
		class m_vector : private vector_base <T, A>
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
