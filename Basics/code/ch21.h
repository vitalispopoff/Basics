#pragma once

#include <vector>

namespace ch21_txt
{
	using namespace std;

	// 21.2 

	template <typename In, typename T>
		In find (In first, In last, const T & val);

	template <typename In, typename T>
		In find_1 (In first, In last, const T & val);

	template <typename In, typename T>
		In find_2 (In first, In last, const T & val);

	void func (vector <int> & v, int x);





	void main();
}


namespace ch21_try
{

	//	p.765
	namespace try_this_1
	{
		template <typename In, typename T>
		In find_while (In first, In last, const T & val);

		template <typename In, typename T>
		In find_for (In first, In last, const T & val);
	
		void main();
	}

	//	p.774
	namespace try_this_2
	{
		struct Record
		{
			double 
				unit_price;
			int 
				units;
			Record (double u_p, int u) :
				unit_price {u_p},
				units {u}
			{}
			double operator () ()
			{
				return unit_price * double (units);
			}
		};

		void main();

	}

	//	p.785
	namespace try_this_3
	{
		void main();
	}

	//	p.787
	namespace try_this_4
	{
		void main();
	}

	//	p.792
	namespace try_this_5
	{
		void main();
	}


	void main();
}

namespace ch21_drill
{

}

namespace ch21_exc
{


}