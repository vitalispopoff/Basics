#include "ch19.h"

#include <iostream>

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

	void main()
	{
		auto a = []() -> m_vector
		{
			return m_vector {0., .1, .2, .3};
		};

		m_vector v {a()};

		for (int i = 0 ; i < v.size(); ++i)
			cout
				<< v[i] << ", ";
	}
}