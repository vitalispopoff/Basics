#include "ch19.h"

//#include <iostream>

using namespace std;

namespace ch19
{
	template <typename T>
		m_vector<T> & m_vector<T>::operator = (const m_vector & v)
	{
		if (this == & v)
			return * this;
		if (space < v.sz)
		{
			delete [] elem;
			elem = alloc.allocate (v.sz);
			space = v.sz;
		}
		sz = v.sz;			
		copy (v.elem, v.elem + sz, elem);
		return * this;
	}
	template <typename T>
		m_vector<T> & m_vector<T>::operator = (m_vector && v) noexcept (true)
	{
		// need further investigation
		if (true)
			delete [] elem;
		else
		{
			alloc.destroy (space, elem);
			alloc.deallocate (elem);
		}

		sz = v.sz;
		space = v.space;
		elem = v.elem;
		v.elem = nullptr;
		v.sz = v.space = 0;
		return * this;
	}
	template <typename T>
		void m_vector<T>::reserve (int new_space)
	{
		if (new_space <= space)
			return;
		T * p = alloc.allocate(new_space);

		for (int i = 0; i < sz; ++i)
		{
			alloc.construct(& p [i], elem [i]);
			alloc.destroy (& elem[i]);		/// is it ok ?
		}
		alloc.deallocate (elem, space);
		elem = p;
		space = new_space;
	}
	template <typename T>
		void m_vector<T>::resize (int new_size, T val)
	{		
		reserve (new_size);
		for (int i = sz; i < new_size; ++i)
			alloc.construct (& elem [i], val);
		for (int i = new_size; i < sz; ++i)
			alloc.destroy (& elem [i]);
		sz = new_size;
	}
	template <typename T>
		void m_vector<T>::push_back (T val)
	{
		if (space == 0)
			reserve (8);		
		/// is 'else' redundant?: if space==0 reserve(8) returns sz==0 && space==8
		/// but if space!=0 then and only then space?=sz is to be checked
		else
			if (space == sz)
				reserve (space * 2);
		alloc.construct (& elem [sz], val);
		++sz;
	}

	void main()
	{		
		auto skrt = [](const auto & v)	// 'auto' XD
		{
			for (int i = 0; i < v.size(); ++i)
				cout
					<< v[i] << ", ";
			cout << '\n';
		};

		m_vector <double>
			a {0, 1, 2, 3},
			b;

		skrt(a);
		
		a.push_back(-1);

		skrt(a);

		a.resize (b.capacity());

		skrt(a);
	
		a.resize (-1);

		skrt (a);
	}

}