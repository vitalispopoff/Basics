#include "ch19.h"

//#include <iostream>

using namespace std;

namespace ch19
{
	m_vector & m_vector::operator = (const m_vector & v)
	{
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

	void main()
	{
		auto skrt = [](const m_vector & v) 
		{
			cout
			<< v.size() << ", " << v.capacity() << '\n';
		};

		m_vector 
			a {0, 1, 2, 3},
			b;

		skrt(a);
		
		a.reserve(b.capacity());

		skrt(a);
	}
}