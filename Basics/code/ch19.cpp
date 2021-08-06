#include "ch19.h"

#include <iostream>

using namespace std;

namespace ch19
{
	void main()
	{
		m_vector 
			v {0., 0.1, 0.2, 0.3};
		m_vector u;
		cout
			<< u.size() << '\t' << u.capacity() << '\n';
		u = v;
		for (int i = 0; i < v.size(); ++i)
			cout
				<< (v [i] == u [i]) << ", ";
		cout 
			<< '\n';		
	}
}