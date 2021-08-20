#pragma once

#include "testing.h"
#include <vector>

namespace ch20
{
	using namespace std;

	/// deals with try this 1 & 2
	namespace try_this_1
	{
		void test();
	}

	namespace try_this_3
	{
		void copy (int * f1, int * e1, int * f2);

		void test();
	}

	namespace try_this_4
	{
		void test();
	}

	/// copy from ch19_go_deeper
	namespace try_this_5
	{
		template <typename T, typename A = allocator <T>>
		struct vector_base
		{
			A alloc;
			int sz, space;
			unique_ptr<T> elem;
			explicit vector_base (const A & a = A (), int n = 0) :
				alloc {a},
				sz {n},
				space {n > 0 ? n : 8},
				elem {alloc.allocate (space)}
			{}
			~vector_base () {elem.reset();}
		};

		template <typename T, typename A = allocator <T>>
		class m_vector : private vector_base <T, A>
		{
		public :
			m_vector () :
				vector_base <T, A>::vector_base{}
			{}

			explicit m_vector (int n, T val = T()) :
				vector_base <T,A>::vector_base {A (), max (0, n)}
			{
				for (int i = 0; i < this -> sz; ++i)
					this->alloc.construct (& this -> elem.get() [i], val);
			}

			m_vector (initializer_list <T> lst) :
				vector_base <T, A>::vector_base {A (), (int) lst.size()} 
			{
				copy (lst.begin(), lst.end(), this -> elem.get());
			}

			m_vector (const m_vector & v) :
				vector_base <T, A>::vector_base {A (), v.sz}
			{
				copy (v.elem.get(), v.elem.get() + v.sz, this -> elem.get());
			}

			m_vector (m_vector && v) noexcept :
				vector_base <T, A>::vector_base {}
			{
				this -> sz = this -> space = v.sz;			
				this -> elem.reset (v.elem.release());
			}

			m_vector & operator = (const m_vector & v);
			m_vector & operator = (m_vector && v) noexcept;

			T & operator [] (int n) {return this -> elem.get() [n];}
			const T & operator [] (int n) const {return this -> elem.get() [n];}

			void reserve (int new_space);
			void resize (int new_size, T val = T());
			void push_back (T val);
			void push_front (T val);

			int size() const {return this -> sz;}
			int capacity() const {return this -> space;}

			const T * addr () const {return & this -> elem.get()[0];} // this is curious
			unique_ptr<T> & get() {return this -> elem;}
		};		

	}

	void main();
}