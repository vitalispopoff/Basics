#include "ch19.h"

#include <iostream>

using namespace std;

namespace ch19
{
	void main()
	{
		m_vector v {0., 0.1, 0.2, 0.3};

		for (int i = 0; i < v.size(); ++i)
			cout
				<< v [i] << ", ";
		cout 
			<< '\n';
	}
}