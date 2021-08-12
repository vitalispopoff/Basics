#include "ch19.h"

namespace ch19_exc
{
	int 
		test_no {0};
	
	template <typename U>
		struct testing_bundle
	{
		string name;
		U given, expected;
		testing_bundle () : name {}, given{U ()}, expected {given} {}
		testing_bundle (string n, U g, U e) : name {n}, given {g}, expected {e}
		{
			testing();
		}
		void testing ()
		{
			++test_no;
			if (given != expected)
				cout
				<<  test_no << ".\t" << name << "\tfailed\n";
		}
	};

	//template <typename T>
	//	struct error_testing
	//{
	//	string name;
	//	T func
	//	error_testing () : name {}, func {T ()} {}
	//	error_testing (string n, T f) : name {n}, func {f}
	//	{
	//	}
	//};

	void report (int no, string name)
	{
		cout 
			<< '\t' << name << ":\ttests: " << no << " - " << test_no - 1 << '\n';
	}
// --------------------------
	
	namespace e01
	{
		template <typename T> void f (vector<T> & v1, vector<T> & v2)
		{
			for (int i = 0; i < (int) v1.size() && i < (int) v2.size(); ++i)
				v1[i] += v2[i];
		}

		void test()
		{
			string 
				name {"exc 01"};
			int 
				no = test_no;
			vector<double> 
				v1 {3, 2, 1},
				v2 { -3, -2, -1, 0, 1};

			f (v1, v2);
			
			ch19_exc::testing_bundle <vector <double>> 
				t {name, v1, vector<double> {0, 0, 0}};
			report(no, name);
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
			string 
				name {"exc 02"};
			int 
				no = test_no;
			vector<char> 
				v {0, 2, 10, 50, 127};
			vector<bool> 
				u {true, false, false, true, true, false};

			double
				result = f (v, u);
			ch19_exc::testing_bundle <double>
				t {name, result, 0. + 0. + 50. + 127.};
			report (no, name);
		}
	}

	namespace e03
	{
		char var_table::get_value (string key)
		{
			for (Pair<> p : table)
				if (p.name == key)
					return p.value;
			cerr 
				<< "\nno key found\n";
			throw runtime_error ("no key found");
		}

		template <typename T, typename U>
			ostream & operator << (ostream & os, const Pair<T, U> & p)
		{
			return os << p.name << " : " << p.value << '\n';
		}

		void test()
		{
			string 
				name {"exc 03"};
			int
				no = test_no;

			var_table table {
				{"mailing", '@'},
				{"surfing", '~'},
				{"snowman", '&'},
				{"sun", '*'}
			};

			char
				result = table.get_value("surfing");
			ch19_exc::testing_bundle<char> 
				t {name, result, '~'};
			
			var_table
				* tmp = & table;
			char 
				(e03::var_table:: * get_value) (string) = nullptr;
			get_value = & e03::var_table::get_value;


			//try {table.get_value("nope");} catch (exception & e) {}
			report (no, name);
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
			while (p -> prev)
			{
				p = p -> prev;
				if (p == this)
					return this;
			}
			return p;
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
			void Link<T>::print_all ()
		{
			Link 
				* h = head(),
				* p = h;
			cout 
				<< '\n';
			while (p)
			{
				cout 
					<< p -> value;
				if (p = p -> succ)
					cout << ", ";
				if (p == h)
					break;
			}
			cout 
				<< '\n';
		}

		void test_01()
		{
			Link<int> 
				lnk2 {2},
				lnk1 {1},
				lnk0 {0};
			lnk2.insert (& lnk1);
			lnk1.insert (& lnk0);

			if (true)
			{
				//lnk2.prev == 

			}

			lnk2.print_all();
			lnk0.insert (& lnk2);
			lnk2.print_all();
		}

		void test()
		{
			Link<int> 
				lnk2 {2},
				lnk1 {1},
				lnk0 {0};
			lnk2.insert (& lnk1);
			lnk1.insert (& lnk0);

			cout << lnk1.forward() -> value << '\n';
			cout << lnk1.backward() -> value << 'n';
		}

		void test_0n()
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
		//e04::test();

		/// definition of non-static method pointer w/ initialization
		//char (e03::var_table:: * get_value) (string) = nullptr;
	}
}