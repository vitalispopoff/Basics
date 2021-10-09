#pragma once

namespace ch21
{

	namespace try_this_1
	{
		template <typename In, typename T>
		In find_while (In first, In last, const T & val);

		template <typename In, typename T>
		In find_for (In first, In last, const T & val);
	
		void main();
	}

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

	namespace try_this_3
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