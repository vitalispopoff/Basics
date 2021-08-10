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
				result += ((double)v [i] * (double) u [i]);
			return result;
		}

		void test()
		{
			vector<char> v {0, 2, 10, 50, 127};
			vector<bool> u {true, false, false, true, true, false};
			cout << f (v, u);

		}

	}

	namespace e03
	{
		template <typename T, typename U>
		ostream & operator << (ostream & os, const Pair<T, U> & p)
		{
			return os << p.name << " : " << p.value << '\n';
		}
		char & var_table::get_value (string key)
		{
			for (Pair<> p : table)
				if (p.name == key)
					return p.value;
			cerr << "\nno key found\n";
			throw runtime_error ("no key found");
		}



		void test()
		{
			var_table table {
				{"mailing", '@'},
				{"surfing", '~'},
				{"snowman", '&'},
				{"sun", '*'}
			};
			//cout << table.get_value("mailing");
			cout << table.get_value("nope");
		}

	}

	namespace e04
	{
		Link * insert (Link * p, Link * n)
		{
			if (n == nullptr)
				return p;
			if (p != n && p != nullptr)
			{
				n -> succ = p;
				if (p -> prev) 
					p -> prev -> succ = n;
				n -> prev = p -> prev;
				p -> prev = n;
			}
			return n;
		}
		
		Link * erase (Link * p)
		{	
			if (p == nullptr)
				return nullptr;
			if (p -> succ)
				p -> succ -> prev = p -> prev;
			if (p -> prev)
				p -> prev -> succ = p -> succ;
			return p -> succ;
		}

		Link * find (Link * p, const string & s)
		{
			while (p)
			{
				if (p -> value == s)
					return p;
					p = p->succ;				
			}
				return nullptr;
		}

		Link * advance (Link * p, int n)
		{
			if (p == nullptr)
				return nullptr;
			if (n > 0)
			{
				while (n--)
				{
					if (p -> succ = nullptr)
						return nullptr;
					p = p -> succ;
				}
			}
			else
				if (n < 0)
				{
					while (n++)
					{
						if (p -> prev == nullptr)
							return nullptr;
						p = p -> prev;
					}
				}
			return p;
		}

		void test()
		{

		}
	}

	void main()
	{
		//e01::test();
		//e02::test();
		//e03::test();
	}
}