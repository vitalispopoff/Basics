#include "ch19.h"

//#include <iostream>

using namespace std;

namespace ch19
{
	m_vector & m_vector::operator = (const m_vector & v)
	{
		if (this == & v)
			return * this;

		if (space < v.sz)
		{
			delete [] elem;
			elem = new double [v.sz];
			space = v.sz;
		}
		sz = v.sz;			
		copy (v.elem, v.elem + sz, elem);
		return * this;
	}

	m_vector & m_vector::operator = (m_vector && v) noexcept (true)
	{
		sz = v.sz;
		space = v.space;
		delete [] elem;
		elem = v.elem;
		v.elem = nullptr;
		v.sz = v.space = 0;
		return * this;
	}

	void m_vector::reserve (int new_space)
	{
		if (new_space <= space)
			return;
		double 
			* p = new double [new_space];
		for (int i = 0; i < sz; ++i)
			p [i] = elem [i];
		delete [] elem;
		elem = p;
		space = new_space;
	}

	void m_vector::resize (int new_size)
	{		
		reserve (new_size);
		if (new_size > sz)
		{
			for (int i = sz; i < new_size; ++i)
				elem [i] = 0.;
			sz = new_size;
		}
	}

	void m_vector::push_back (double d)
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
		auto skrt = [](const m_vector & v) 
		{
			for (int i = 0; i < v.size(); ++i)
				cout
					<< v[i] << ", ";
			cout << '\n';
		};

		m_vector 
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