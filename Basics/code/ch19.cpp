#include "ch19.h"

//#include <iostream>

using namespace std;

namespace ch19
{
	m_vector & m_vector::operator = (const m_vector & v)
	{
		cout
			<< "\n\tassign-by-copy operator\n";

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
		cout
			<< "\n\tassign-by-move operator\n";
		sz = v.sz;
		space = v.space;
		delete [] elem;
		elem = v.elem;
		v.elem = nullptr;
		v.sz = v.space = 0;
		return * this;
	}

	void main()
	{
		auto a = []() -> m_vector
		{
			cout
				<< "\n\ta() called\n";
			m_vector result {0, 1, 2, 3};
			cout 
				<< "\n\ta() returns:\n";
				
			return result;
		};

		cout << "1";

		m_vector 
			v {a()};

		cout << "2";

		if (true)
			v = m_vector {1, 2, 3, 4, 5};

		cout << "3";
	}
}