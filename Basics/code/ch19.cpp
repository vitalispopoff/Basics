#include "ch19.h"

#include <iostream>

using namespace std;

namespace ch19
{
	void main()
	{
		m_vector * m = nullptr;

		if (true)
		{
			m_vector v(6);
			m = & v;

			cout
				<< "within the inner scope\t"
				<< (m != nullptr ? "yup" : "nay")
				<< '\n';
		}
			cout
				<< "outside inner scope\t"
				<< (m != nullptr ? "yup" : "nay")
				//<< hex 
				//<< m -> elem [0]
				<< '\n';
	}
}