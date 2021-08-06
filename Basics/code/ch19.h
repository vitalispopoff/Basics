#pragma once

namespace ch19
{
	struct m_vector
	{
		int sz;
		int space;
		int * elem;

	//public : 
		m_vector () :
			sz {0},
			space {8},
			elem {new int [space]}
		{}

		explicit m_vector (int i) :
			sz {i},
			space {i},
			elem {new int [space]}
		{			
			for (int c = 0; c < sz; ++c) 
				elem [c] = c; 
		}



		/// gotta check it...
		~m_vector ()
		{
			delete [] elem;
			elem = nullptr;
		}

		int size () {return sz;}
		int capacity () {return space;}
	};


	void main();
}
