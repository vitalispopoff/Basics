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

	m_vector & m_vector::operator = (m_vector && v) noexcept (true)
	{
		sz = v.sz;
		space = v.space;
		elem = v.elem;
		delete [] v.elem;
		v.elem = nullptr;
		v.sz = v.space = 0;
		return * this;
	}

	void main()
	{
		auto a = []() -> m_vector
		{
			return m_vector {0., .1, .2, .3};
		};

		m_vector v {a()},
		 u = a();

		auto print = [](const m_vector & m)
		{
			for (int i = 0 ; i < m.size(); ++i)
				cout
					<< m[i] << ", ";
			cout 
				<< '\n';
		};		
		print(v);
		print(u);
	}
}