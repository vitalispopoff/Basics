#include "ch19.h"

namespace ch19_exc
{
	namespace e01
	{
		template <typename T> void f (vector<T> & v1, vector<T> & v2)
		{
			for (int i = 0; i < (int) v1.size() && i < (int) v2.size(); ++i)
				v1[i] += v2[i];
		}

		void test()
		{
			vector<double> 
				v1 {3, 2, 1},
				v2 { -3, -2, -1, 0, 1};
			f (v1, v2);
			for (double d : v1)
				cout
					<< d << ", ";
			cout 
				<< '\n';
		}
	}

	namespace e02
	{
		template <typename T, typename U>
			double f (vector<T> v, vector<U> u)
		{
			double result {0};
			for (int i = 0; i < (int) v.size() && i < (int) u.size(); ++i)
				result += (v [i] * u [i]);
			return result;
		}

		void test()
		{
			vector<char> v {0, 2, 10, 50, 127};
			vector<bool> u {true, false, false, true, true, false};
			cout << f (v, u);

		}

	}

	void main()
	{
		//e01::test();
		//e02::test();
	}
}