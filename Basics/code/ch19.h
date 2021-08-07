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

		vector_base (const A & a = A(), int n = 0) :			
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
		
	template <typename T, typename A = allocator <T>>	// T is Element <E>()
	class m_vector : private vector_base<T, A>
	{
	public : 

		explicit m_vector (int n = 0, T val = T())
		{
			this -> sz = max (0, n);
			this -> space = max(1, n);
			this -> elem = this -> alloc.allocate (this -> space);
			for (int i = 0; i < this -> sz; ++i) 
				this->alloc.construct (& (this->elem [i]), val);
		}

		m_vector (initializer_list <T> lst)
		{
			this -> sz = this -> space = (int) lst.size();
			this -> elem = this -> alloc.allocate (this -> space);
			copy (lst.begin(), lst.end(), this -> elem);
		}

		m_vector (const m_vector & v)
		{
			this -> sz = this -> space = v.sz;			
			this -> elem = this -> alloc.allocate (v.sz);
			copy (v.elem, v.elem + v.sz, this -> elem);
		}

		m_vector (m_vector && v) noexcept (true)
		{
			this -> sz = v.sz;
			this -> space = v.space;
			this -> elem = v.elem;
			//v.sz = v.space = 0;
			//v.elem = nullptr;
		}

		/// disposable
		//m_vector & operator = (const m_vector & v);
		//m_vector & operator = (m_vector && v) noexcept (true);		

		T & operator [] (int n) {return this -> elem [n];}
		const T & operator [] (int n) const {return this -> elem [n];}

		void reserve (int new_space);
		//void resize(int new_size, T val = T());
		//void push_back (T val);

		int size () const {return this -> sz;}
		int capacity () const {return this -> space;}

		/// for testing:
		const T * addr () const {return this -> elem;}
	};


	void main();
}
