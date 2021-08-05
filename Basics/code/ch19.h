#pragma once

namespace ch19
{
	class m_vector
	{
		int sz;
		int space;
		double * elem;

	public : 
		m_vector () :
			sz {0},
			space {8},
			elem {new double (space)}
		{}

		explicit m_vector (int i) :
			sz {i},
			space {i},
			elem {new double (space)}
		{}

		~m_vector ()
		{
			delete [] elem;
			elem = nullptr;		/// just in case...
		}

		int size () {return sz;}
		int capacity () {return space;}
	};


	void main();
}
