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
				<<  test_no 
				<< ".\t" << name << "\tfailed\n";
		}
		++test_no;
	}

	void report (int no, string name)
	{
		cout 
			<< '\t' << name << ":\ttests: " << no << " - " << test_no - 1 << '\n';
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
	/// --- Link ---
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
			Link<T> * Link<T>::erase ()
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
			Link<T> & Link<T>::add_ordered (Link<T> & lnk)
		{
			lnk.erase();
			Link
				* h = head();
			while (h -> succ && lnk.value > h ->value)
				h = h -> succ;
			if (h -> prev)
				h -> insert (& lnk);
			return lnk;
		}

		template <typename T>
			Link<T> * Link<T>::head()
		{
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
			void Link<T>::to_string ()
		{
			Link 
				* h = head(),
				* p = h;
			cout 
				<< '\n';
			while (p)
			{
				cout 
					<< (T) p -> value;
				if (p = p -> succ)
					cout << ", ";
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
				if (myth == "greek")
					greek -> add_ordered (* gods);
				if (myth == "roman")
					roman -> add_ordered (* gods);
				if (myth == "norse")
					norse -> add_ordered (* gods);
				gods = gods -> succ;
			}
			roman = r.erase();
			greek = g.erase();
			norse = n.erase();

			//cout << "\n\texcercise :\n";
			//cout << "roman :\n";
			roman -> to_string();
			//cout << "greek :\n";
			//greek -> to_string();
			//cout << "norse :\n";
			//norse -> to_string();
			//cout << "gode :\n";
			//gods -> to_string();
		}
	}

	void main()
	{
		//e01::test();
		//e02::test();
		//e03::test();
		e04::test_Link();
		e04::test_God();
		e04::excercise();
	}
}