#include "ch19_exc.h"

namespace testing
{
	int test_no = 1;

	template <typename U>
		void testing_bundle<U>::testing ()
	{
		if (given != expected)
		{			
			cout
				<<  test_no  << ".\t" << name << "\tfailed\n";
				//<< "exp: " << given << "\texp: " << expected; 
		}
		++test_no;
	}

	void report (int & n, string name)
	{
		cout 
			<< '\t' << name << ":\ttests: " << n << " - " << test_no - 1 << '\n';
			n = test_no;
	}
}

namespace ch19_exc
{
	using namespace testing;
	
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
			testing_bundle <vector <double>> 
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
			testing_bundle <double>
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
			//cerr 
			//	<< "\nno key found\n";
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
			testing_bundle<char> 
				t {name, result, '~'};		
			try 
			{
				table.get_value("nope");
				cout 
					<< "\ne03 : error_test failed\n";
			} 
			catch (exception & e) 
			{
				++test_no;
			}
			report (no, name);
		}
	}

	namespace e04
	{
		template <typename T>
			void Link<T>::insert (Link<T> * n)
		{
			if (n) 
			{
				n -> succ = this;
				if (prev)
					n -> prev = prev;
				prev = n;
			}
		}

		template <typename T>
			Link<T> * Link<T>::erase ()	// & instead of * ?
		{				
			if (succ)
				succ -> prev = prev;
			if (prev)
				prev -> succ = succ;
			Link 
				* result = prev ? prev : succ;
			succ = prev = nullptr;
			return result;
		}

		template <typename T>
			void Link<T>::extract ()
		{
			if (succ)
				succ -> prev = prev;
			if (prev)
				prev -> succ = succ;
			succ = prev = nullptr;
		}

		template <typename T>
			Link<T> & Link<T>::add_ordered (Link<T> & lnk)
		{
			lnk.extract();
			Link
				* h = head();
			while (h -> succ && lnk.value > h ->value)
				h = h -> succ;
				//h -> insert (& lnk); // doesn't work
			lnk.prev = h -> prev;
			lnk.succ = h;
			if (h -> prev)
				h -> prev -> succ = & lnk;
			h -> prev = & lnk;
			return lnk;
		}

		template <typename T>
			Link<T> & Link<T>::add_ordered(const T t)
		{
			Link 
				* h = head();
			while (h -> succ && t > h -> value)
				h = h -> succ;
			Link
				* lnk = new Link (t, h -> prev, h);
			if (h -> prev)
				h -> prev -> succ = lnk;
			h -> prev = lnk;
			return * lnk;
		}

		template <typename T>
			Link<T> * Link<T>::head()
		{
				if (!(this -> prev))
				return this;
			Link 
				* p = this;
			while (p -> prev)
			{
				p = p -> prev;
				if (p == this)
					return this;
			}
			return p;
		}

		template <typename T>
			void Link<T>::to_string (bool line_break)
		{
			Link 
				* h = head(),
				* p = h;
			while (p)
			{
				cout 
					<< (T) p -> value;
				if (p = p -> succ)
					cout << (line_break ? "\n" : ", ");
				if (p == h)
					break;
			}
			cout 
				<< '\n';
		}
	
		template <typename T>
			bool operator < (const Link<T> & lnk1, const Link<T> & lnk2)
		{
			return lnk1.value < lnk2.value;
		}
		template <typename T>
			bool operator > (const Link<T> & lnk1, const Link<T> & lnk2)
		{
			return lnk1.value > lnk2.value;
		}
		template <typename T>
			bool operator == (const Link<T> & lnk1, const Link<T> & lnk2)
		{
			return lnk1.value == lnk2.value;
		}		
		template <typename T>
			bool operator != (const Link<T> & lnk1, const Link<T> & lnk2)
		{
			return lnk1.value != lnk2.value;
		}		

	/// --- God --

		bool operator < (God g1, God g2)
		{
			return g1.name < g2.name;
		}
		bool operator > (God g1, God g2)
		{
			return g1.name > g2.name;
		}
		bool operator == (God g1, God g2)
		{
			return g1.name == g2.name;
		}
		bool operator != (God g1, God g2)
		{
			return 
				g1.name != g2.name
				|| g1.mythology != g2.mythology
				|| g1.vehicle != g2.vehicle
				|| g1.weapon != g2.weapon;
		}
		
		ostream & operator << (ostream & os, God g)
		{
			g.to_string (os);
			return os;
		}

	/// --- Test ---

		void test_Link()
		{
			string 
				name {"exc e04 Link"};
			int 
				no = test_no;
			Link<int> 
				lnk3 {1},
				lnk2 {2},
				lnk1 {1},
				lnk0 {0};
			lnk2.insert (& lnk1);
			lnk1.insert (& lnk0);
			Link <int>
				* l_3 = & lnk3,
				* l_2 = & lnk2,
				* l_1 = & lnk1,
				* l_0 = & lnk0;
			testing_bundle<Link<int> *> 
				t0_0 {name, lnk0.succ, & lnk1},
				t0_1 {name, lnk1.prev, & lnk0},
				t0_2 {name, lnk1.forward(), & lnk2},
				t0_3 {name, lnk1.backward(), & lnk0};
			report (no, name + ": constr, traverse");
			lnk2.insert (& lnk3);
			lnk3.erase();
			testing_bundle <Link<int> *>
				t1_1 {name, lnk2.prev, & lnk1},
				t1_2 {name, lnk1.succ, & lnk2},
				t1_3 {name, lnk3.prev, nullptr},
				t1_4 {name, lnk3.succ, nullptr};
			testing_bundle <bool> 
				t2_1 {name, (lnk1 == lnk2), false},
				t2_2 {name, (lnk1 == lnk3), true},
				t2_3 {name, (lnk0 < lnk1), true},
				t2_4 {name, (lnk2 > lnk1), true},
				t2_5 {name, (lnk1 != lnk2), true};
			report (no, name + ": insert, erase");
			Link <int> 
				* rslt0 = & lnk2.add_ordered (1);
			testing_bundle<Link<int> *>
				t3_1{name, rslt0 -> prev, &lnk0},
				t3_2{name, rslt0 -> succ, &lnk1},
				t3_3 {name, lnk0.succ, rslt0},
				t3_4 {name, lnk1.prev, rslt0};
			report (no, name + ": add_ordered");
			Link<int> 
				lnk4 = * Link<int>::make_link({0, 1, 2, 3, 4, 5, 6}),
				* lnk_ptr = & lnk4;
			for (int i = 0; i < 7; ++i)
			{
				testing_bundle<int> 
					t4_ {name, lnk_ptr -> value, i};
				lnk_ptr = lnk_ptr -> succ;					
			}
			report (no, name + ": make_link");
			cout << "to_string test\n";
			lnk4.to_string();
			report(no, name);

		}

		void test_God()
		{
			string
				name {"e04 : God"};
			int no = test_no;
			God
				zeus {"Zeus", "greek", "", "lightning"},
				odin {"Odin", "norse", "Sleipner", "Gungir"},
				venus {"Venus", "roman", "", "Mars"};
			Link<God>
				z {zeus},
				o {odin},
				v {venus};
			testing_bundle <bool>
				t10_0 {name, zeus == odin, false},
				t10_1 {name, zeus == zeus, true},
				t10_2 {name, zeus != venus, true},
				t10_3 {name, zeus != zeus, false},
				t10_4 {name, zeus > odin, true},
				t10_5 {name, odin < venus, true};
			report(no, name);
		}

		void excercise()
		{
			Link <God> 
				* gods = Link<God>::make_link (
					{
						God {"Zeus", "greek", "", "lightning"},
						God {"Odin", "norse", "Sleipner", "Gungir"},
						God {"Venus", "roman", "", "Mars"},
						God {"Apollo", "greek", "chariot", ""},
						God {"Thor", "norse", "", "Mjolnir"},
						God {"Loki", "norse", "", "" },
						God {"Athene", "greek", "", "Aegis"},
						God {"Vulcan", "roman", "", "Titans"},
						God {"Bacchus", "roman", "", "wine"}
					}
				),
				r {}, g{}, n {},
				* roman = & r,
				* greek = & g,
				* norse = & n;
			while (gods)
			{
				string 
					myth = gods -> value.mythology;
				Link<God> 
					& tmp = * gods;
				gods = gods -> succ;
				if (myth == "greek")
					greek -> add_ordered (tmp);
				else if (myth == "roman")
					roman -> add_ordered (tmp);
				else if (myth == "norse")
					norse -> add_ordered (tmp);
			}
			roman = r.erase();
			roman = roman -> head();
			greek = g.erase();
			greek = greek -> head();
			norse = n.erase();
			norse = norse -> head();

			cout << "\nexcercise :\n";
			cout << "\nroman :\n";
			roman -> to_string(true);
			cout << "\ngreek :\n";
			greek -> to_string(true);
			cout << "\nnorse :\n";
			norse -> to_string(true);
		}

		void e04_run()
		{
			e04::test_Link();
			e04::test_God();
			e04::excercise();
		}
	}

	namespace e05
	{
		Int operator + (Int & v1, Int & v2)
		{
			return Int {v1.get() + v2.get()};
		}

		Int operator - (Int & v1, Int & v2)
		{
			return Int {v1.get() - v2.get()};
		}
		
		Int operator * (Int & v1, Int & v2)
		{
			return Int {v1.get() * v2.get()};
		}

		Int operator / (Int & v1, Int & v2)
		{
			if (v2.get() == 0)
				throw runtime_error ("Dividing by 0.");
			return Int {v1.get() / v2.get()};
		}

		Int operator % (Int & v1, Int & v2)
		{
			if (v2.get() == 0)
				throw runtime_error ("Dividing by 0.");
			return Int {v1.get() % v2.get()};
		}

		bool operator == (Int & v1, Int & v2)
		{
			return v1.get() == v2.get();
		}

		bool operator != (Int & v1, Int & v2)
		{
			return v1.get() != v2.get();
		}

		bool operator > (Int & v1, Int & v2)
		{
			return v1.get() > v2.get();
		}

		bool operator < (Int & v1, Int & v2)
		{
			return v1.get() < v1.get();
		}

		ostream & operator << (ostream & os, Int & v)
		{
			os << v.get();
			return os;
		}

		istream & operator >> (istream & is, Int & v)
		{
			for (int i; is >> i ;)
			{
				v.set(i);
				return is;
			}
			throw runtime_error ("Wrong input.");
		}


	// --- testing

		void testing()
		{
			string
				name {"e05"};
			int
				no = test_no;
			Int 
				i0 {0},
				i1 {1},
				i2 {2},
				i3 {1};
			testing_bundle <int>
				t0_0{name, (i1 + i2).get(), i1.get() + i2.get()},
				t0_1 {name, (i1 - i2).get(), i1.get() - i2.get()},
				t0_2 {name, (i1 * i2).get(), i1.get() * i2.get()},
				t0_3 {name, (i1 / i2).get(), i1.get() / i2.get()},
				t0_4 {name, (i1 % i2).get(), i1.get() % i2.get()};
			string error {};
			try
			{
				i1 / i0;
			}
			catch (runtime_error & e)
			{
				error = e.what();
			}
			testing_bundle <string>
				t1_0 {name, error, "Dividing by 0."};
			try
			{
				i1 % i0;
			}
			catch (runtime_error & e)
			{
				error = e.what();
			}
			testing_bundle <string>
				t1_1 {name, error, "Dividing by 0."};
			testing_bundle <bool>
				t2_0 {name, i1 == i3, true},
				t2_1 {name, i1 != i2, true},
				t2_2 {name, i1 > i0, true},
				t2_3 {name, i1 < i2, true};
			try
			{
				Int i {};
				cout << "write a non-integer input, please.";
				cin >> i; 
			}
			catch (runtime_error & e)
			{
				error = e.what();
			}
			testing_bundle<string>
				t3_0 {name, error, "Wrong input."};				
			report (no, name);
		}
	}

	namespace e06
	{
		template <typename T>
			Number<T> operator + (Number<T> & v1, Number<T> & v2)
		{
			return Number<T> {v1.get() + v2.get()};
		}

		template <typename T>
			Number<T> operator - (Number<T> & v1, Number<T> & v2)
		{
			return Number<T> {v1.get() - v2.get()};
		}

		template <typename T>
			Number<T> operator * (Number<T> & v1, Number<T> & v2)
		{
			return Number<T> {v1.get() * v2.get()};
		}

		template <typename T>
			Number<T> operator / (Number<T> & v1, Number<T> & v2)
		{
			string 
				v_type {typeid(v2).name()};
			if (v2.get() == 0 && !(v_type == "float" || v_type == "double"))
				throw runtime_error ("Dividing by 0.");
			return Number<T> {v1.get() / v2.get()};
		}

		template <typename T>
			Number<T> operator % (Number<T> & v1, Number<T> & v2)
		{
			if (v2.get() == 0)
				throw runtime_error ("Dividing by 0.");

			double 
				d1 = v1.get(),
				d2 = v2.get(),
				rslt = d1 - d2 * floor(d1 / d2);
			return Number<T> {(T) rslt};
		}

		template <typename T>
			bool operator == (Number<T> & v1, Number<T> & v2)
		{
			return v1.get() == v2.get();
		}
		template <typename T>
			bool operator != (Number<T> & v1, Number<T> & v2)
		{
			return v1.get() != v2.get();
		}
		template <typename T>
			bool operator > (Number<T> & v1, Number<T> & v2)
		{
			return v1.get() > v2.get();
		}
		template <typename T>
			bool operator < (Number<T> & v1, Number<T> & v2)
		{
			return v1.get() < v2.get();
		}
		template <typename T>
			ostream & operator << (ostream & os, Number<T> & v)
		{
			os << v.get();
			return os;
		}
		template <typename T>
			istream & operator >> (istream & is, Number<T> & v)
		{
			for (T t; is >> t;)
			{
				v.set(t);
				return is;
			}
			throw runtime_error ("Wrong input.");
		}


	// --- testing

		void testing(bool inputs)
		{
			string
				name {"e06"};
			int
				no = test_no;
			Number<int>
				i0 {0},
				i1 {1},
				i2 {2},
				i3 {1};
			Number<double>
				d_i {(double)INFINITY},
				d0 {0},
				d1 {1},
				d2 {2},
				pi {3.5};
			testing_bundle <int>
				t0_0{name, (i1 + i2).get(), i1.get() + i2.get()},
				t0_1 {name, (i1 - i2).get(), i1.get() - i2.get()},
				t0_2 {name, (i1 * i2).get(), i1.get() * i2.get()},
				t0_3 {name, (i1 / i2).get(), i1.get() / i2.get()},
				t0_4 {name, (i1 % i2).get(), i1.get() % i2.get()};
			testing_bundle<double>
				t6_0{name + ": 6_0", (pi % d2).get(), 1.5};
			report (no, name + ": basic arithmetic");
			testing_bundle <bool>
				t2_0 {name + ": 2_0", i1 == i3, true},
				t2_1 {name + ": 2_1", i1 != i2, true},
				t2_2 {name + ": 2_2", i1 > i0, true},
				t2_3 {name + ": 2_3", i1 < i2, true};
			report (no, name + ": comparison ops");
			string 
				error {};
																// division
			try {i1 / i0;}
			catch (runtime_error & e) {error = e.what();}
			testing_bundle <string>
				t1_0 {name, error, "Dividing by 0."};
																// modulo
			try {i1 % i0;}											
			catch (runtime_error & e) {error = e.what();}
			testing_bundle <string>
				t1_1 {name, error, "Dividing by 0."};
																// istream
			if (inputs)
			{
				try
				{
					Number<int> i {};
					cout << "write a non-integer input, please.";
					cin >> i; 
				}
				catch (runtime_error & e)
				{
					error = e.what();
				}
				testing_bundle<string>
					t3_0 {name, error, "Wrong input."};		
			}
			testing_bundle<double>
				t4_0 {name, (d1 / d0).get(), d_i.get()};
																// modulo
			try
			{
				d1 % d0;
			}
			catch (exception & e)
			{
				testing_bundle<string>
					t5_0 {name, e.what(), "Dividing by 0."};
			}			
			report (no, name + ": errors");
			report (no, name);
		}
	}

	void main()
	{
		//e01::test();
		//e02::test();
		//e03::test();
		//e04::e04_run();
		//e05::testing();
		//e06::testing();
	}
}