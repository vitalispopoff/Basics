#include "ch19.h"

#include <iostream>

using namespace std;

namespace ch19
{
	void main()
	{
		m_vector m (5);

		cout 
			<< m.capacity() << '\t' 
			<< m.size () << '\n';
	}
}