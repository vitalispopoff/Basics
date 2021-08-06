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
			elem = new T [v.sz];
			space = v.sz;
		}
		sz = v.sz;			
		copy (v.elem, v.elem + sz, elem);
		return * this;
	}
	template <typename T>
		m_vector<T> & m_vector<T>::operator = (m_vector && v) noexcept (true)
	{
		sz = v.sz;
		space = v.space;
		delete [] elem;
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
		T * p = new T [new_space];
		for (int i = 0; i < sz; ++i)
			p [i] = elem [i];
		delete [] elem;
		elem = p;
		space = new_space;
	}
	template <typename T>
		void m_vector<T>::resize (int new_size)
	{		
		reserve (new_size);
		if (new_size > sz)
		{
			for (int i = sz; i < new_size; ++i)
				elem [i] = 0.;
			sz = new_size;
		}
	}
	template <typename T>
	void m_vector<T>::push_back (T d)
	{
		if (space == 0)
			reserve (8);
		if (sz == space)
			reserve (space * 2);
		elem [sz] = d;
		++sz;
	}

	void main()
	{
		
		auto skrt = [](const auto & v)	// XD
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