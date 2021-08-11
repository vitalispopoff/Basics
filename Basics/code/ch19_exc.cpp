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
		char var_table::get_value (string key)
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
		template <typename T>
			Link<T> * insert (Link<T> * p, Link<T> * n)
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

		template <typename T>
			Link<T> * erase (Link<T> * p)
		{	
			if (p == nullptr)
				return nullptr;
			if (p -> succ)
				p -> succ -> prev = p -> prev;
			if (p -> prev)
				p -> prev -> succ = p -> succ;
			return p -> succ;
		}
	// -----------------

		template <typename T>
			void Link<T>::insert (Link<T> * n)
		{
			if (/*(bool)*/ n) 
			{
				n -> succ = this;
				if (prev)
					n -> prev = prev;
				prev = n;
			}
		}

		template <typename T>
			Link<T> * Link<T>::erase ()
		{				
			if (succ)
				succ -> prev = prev;
			if (prev)
				prev -> succ = succ;
			Link 
				* result = prev;
			succ == prev == nullptr;
			return result;
		}

		template <typename T>
			Link<T> * Link<T>::head()
		{
			Link 
				* p = prev;
			while (p->prev != nullptr)
				p = p -> prev;				
			return p;
		}
		template <typename T>
		Link<T> * find (Link<T> * p, const T & s)
		{
			while (p)
			{
				if (p -> value == s)
					return p;
					p = p->succ;				
			}
				return nullptr;
		}

		template <typename T>
		Link<T> * advance (Link<T> * p, int n)
		{
			if (p == nullptr)
				return nullptr;
			if (n > 0)
			{
				while (n--)
				{
					if (p -> succ == nullptr)
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

		template <typename T>
		void print_all (Link<T> * p)
		{
			cout << '\n';
			while (p)
			{
				cout << p -> value;
				if (p = p -> succ)
					cout << ", ";
			}
			cout << '\n';
		}

		void test_01()
		{
			Link<int> 
				l2 {2},
				l1 {1},
				l0 {0};
			l2.insert (& l1);
			l1.insert (& l0);

			cout << l2.head() -> value;

			//Link<int> * starter = & l0;
			//print_all (starter);

			//cout 
			//	<< "\n* * *\n";
			//cout 
			//	<< (l2.head() != nullptr);
		}

		void test_02()
		{
			God
				zeus {"Zeus", "greek", "", "lightning"},
				odin {"Odin", "norse", "Sleipner", "Gungir"},
				venus {"Venus", "roman", "", "Mars"};
			Link<God>
				z {zeus},
				o {odin},
				v {venus};


		}
	}

	void main()
	{
		//e01::test();
		//e02::test();
		//e03::test();
		e04::test_01();
	}
}