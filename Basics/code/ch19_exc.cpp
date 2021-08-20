#include "ch19_exc.h"
#include "testing.h"

namespace ch19_exc
{
	using namespace testing_space;
	
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
			throw runtime_error ("Key not found.");
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
				t0_0 {name, result, '~'};		
			try 
			{
				table.get_value("nope");
				cout 
					<< "\ne03 : error_test failed\n";
			} 
			catch (exception & e) 
			{
				testing_bundle <string>
					t1_0 {name, e.what(), "Key not found."};
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

	namespace e07
	{
		template <typename T, typename U>
		Number<double> f (vector<T> t, vector<U> u)
		{
			double result {0};
			for (int i = 0; i < (int) t.size() && i < (int) u.size(); ++i)
				result += ((double) t[i].get() * (double) u[i].get());
			return Number<double> {result};
		}

		void testing()
		{
			string
				name {"e07"};
			int
				no = test_no;
			vector<Number<int>>
				v1 {
					{
						Number<int> {0},
						Number<int> {1},
						Number<int> {2}
					}
				};
			vector<Number<>>
				v2 {
					{
						Number<> {2.},
						Number<> {1.}
					}
				};
			testing_bundle<double>
				t0_0 {name, f (v1, v2).get(), 1.};
			report (no, name);
		}	
	}

	namespace e08
	{
		template <typename T>
			T * m_allocator<T>::allocate(int n)
		{
			int len = sizeof (T);
			return (T *) malloc(sizeof (T) * n);
		}
		
		template <typename T>
			void m_allocator<T>::deallocate (T * p)
		{			
			free (p);
		}

		template <typename T>
			void m_allocator<T>::construct (T * p, const T & v)
		{
			::new (p) T (v);
		}

		template <typename T>
			void m_allocator<T>::destroy (T * p, int n)
		{	
			for ( ; p < p + n; ++p)
			p -> ~T();
			free (p -= n);
		}

	//	--------------------
	
		template <typename T, typename A>
			m_vector<T, A> & m_vector<T, A>::operator = (const m_vector & v)
		{
			if (this == & v)
				return * this;
			if (space < v.sz)
			{
				alloc.detroy (elem, space);
				elem = alloc.allocate (v.sz);
				space = v.sz;
			}
			sz = v.sz;			
			copy (v.elem, v.elem + sz, elem);
			return * this;
		}
	
		template <typename T, typename A>
			m_vector<T, A> & m_vector<T, A>::operator = (m_vector && v) noexcept (true)
		{
			if (true)
				delete [] elem;
			else
			{
				alloc.destroy (space, elem);
				alloc.deallocate (elem);
			}

			sz = v.sz;
			space = v.space;
			elem = v.elem;
			v.elem = nullptr;
			v.sz = v.space = 0;
			return * this;
		}
	
		template <typename T, typename A>
			void m_vector<T, A>::reserve (int new_space)
		{
			if (new_space <= space)
				return;
			T * p = alloc.allocate(new_space);

			for (int i = 0; i < sz; ++i)
			{
				alloc.construct(& p [i], elem [i]);
				alloc.destroy (& elem[i]);
			}
			alloc.deallocate (elem, space);
			elem = p;
			space = new_space;
		}
	
		template <typename T, typename A>
			void m_vector<T, A>::resize (int new_size, T val)
		{		
			if (new_size < 0)
				return;

			reserve (new_size);
				for (int i = sz; i < new_size; ++i)
					alloc.construct (&elem [i], val);
				for (int i = new_size; i < sz; ++i)
					alloc.destroy (&elem [i]);
				sz = new_size;
		}
	
		template <typename T, typename A>
			void m_vector<T, A>::push_back (T val)
		{
			if (space == 0)
				reserve (8);		
			else
				if (space == sz)
					reserve (space * 2);
			alloc.construct (& elem [sz], val);
			++sz;
		}

	//	--------------------
	
		void testing_allocations ()
		{
			string 
				name {"e08 : allocations"};
			int 
				no = test_no,
				* ptr = nullptr;
			ptr = (int *) malloc (sizeof (int));
			testing_bundle <bool>
				t0_0 {name + ": malloc", ptr == nullptr, false};
			::new (ptr) int (-1);
			testing_bundle <int>
				t0_1 {name + ": init", * ptr, -1};
			free (ptr);
			testing_bundle <bool>
				t0_2 {name + ": free", ptr == nullptr, false};
			report (no, name);
		}

		void testing_m_allocator()
		{
			string 
				name {"e08: allocator"};
			int 
				no = test_no;
			struct Int
			{
				m_allocator<int>
					alloc ;
				int 
					* i;
				bool
					initialized;
				explicit Int (int v = 0) :
					alloc {m_allocator<int> ()},
					i {alloc.allocate (max (v, 1))},
					initialized {v > 0}
				{
					if (initialized)
						alloc.construct (i, v);
				}
				~Int ()
				{
					if (initialized)
						alloc.destroy (i);
					else 
						alloc.deallocate (i);
				}
			};

			int * ptr = nullptr;
			{
				Int
					o{0};
				ptr = o.i;
				testing_bundle<bool>
					t0_0{name + ": alloc", o.i == nullptr, false};
			}
			testing_bundle<bool>
				t0_1{name + ": alloc", ptr == nullptr, false};

			report (no, name);
		}

		void testing_m_vector()
		{
			string
				name {"e08 m_vector"};
			int
				no = test_no;
			m_vector <int> 
				v0 {};
			testing_bundle<int>
				t0_0 {name + ": 0_0", v0.size(), 0},
				t0_1 {name + ": 0_1", v0.capacity(), 8};
			report (no, name + ": empty cnstr");
			m_vector <int> 
				v1 (1, -1);
			testing_bundle <int>
				t1_0 {name + ": 1_0", v1.size(), 1},
				t1_1 {name + ": 1_1", v1.capacity(), 1},
				t1_2 {name + ": 1_2", v1 [0], -1};
			report (no, name + ": expl cnstr");
			m_vector <int>
				v2 {-1};
			testing_bundle <int>
				t2_0 {name + ": 2_0", v2.size(), 1},
				t2_1 {name + ": 2_1", v2.capacity(), 1},
				t2_2 {name + ": 2_2", v2 [0], -1};
			report (no, name + ": init cnstr");
			m_vector <int>
				u3 {-1},
				v3 {u3};
			testing_bundle <int>
				t3_0 {name + ":3_0", v3.size(), 1},
				t3_1 {name + ":3_1", v3.capacity(), 1},
				t3_2 {name + ":3_2", v3 [0], -1};
			report (no, name + ": copy cnstr");
			auto a4 = []() -> m_vector <int>
			{
				m_vector <int> temp {-1};
				return temp;
			};
			m_vector <int> 
				v4 {a4()};
			testing_bundle <int>
				t4_0 {name + ": 4_0", v4.size(), 1},
				t4_1 {name + ": 4_1", v4.capacity(), 1},
				t4_2 {name + ": 4_2", v4 [0], -1};
			report (no, name + ": move cnstr");
			m_vector<int>
				v5 = m_vector<int> {-1};
			testing_bundle <int>
				t5_0 {name + ":5_0", v5.size(), 1},
				t5_1 {name + ":5_1", v5.capacity(), 1},
				t5_2 {name + ":5_2", v5 [0], -1};
			report (no, name + ": std assgn");
			m_vector<int> 
				u6 {-1},
				v6 = u6;
			testing_bundle <int>
				t6_0 {name + ": 6_0", u6.size(), v6.size()},
				t6_1 {name + ": 6_1", u6.capacity(), v6.capacity()},
				t6_2 {name + ": 6_2", u6 [0], v6 [0]};
			report (no, name + ": copy assgn");
			void 
				* ptr7 = nullptr;
			auto a7 = [&]() -> m_vector<int>
			{
				m_vector<int> temp {-1};
				ptr7 = (void *)temp.addr();
				return temp;
			};
			m_vector<int>
				v7 = a7();
			testing_bundle <int>
				t7_0 {name + ": 7_0", v7.size(), 1},
				t7_1 {name + ": 7_1", v7.capacity(), 1},
				t7_2 {name + ": 7_2", v7 [0], -1},
				t7_3 {name + ": 7_3", (int) ptr7, (int) v7.addr()};
			report (no, name + ": move assgn");
			m_vector<int>
				v8(0);
			v8.reserve (4);
			testing_bundle <int>
				t8_0 {name + ": 8_0", v8.size(), 0},
				t8_1 {name + ": 8_1", v8.capacity(), 4};
			report (no, name + ": reserve");
			m_vector<int>
				v9 {-1};
			v9.resize(2);
			testing_bundle <int>
				t9_0 {name + ": 9_0", v9.size(), 2},
				t9_1 {name + ": 9_1", v9.capacity(), 2},
				t9_2 {name + ": 9_2", v9 [0], -1};
			report (no, name + ": resize");
			report (no, name + ": m_vector");
		}
	}

	namespace e10
	{
		void testing()
		{
			struct Int
			{
				int
					val;
				explicit Int (int v = 0) : val {v} {}

			};

			string
				name {"e10"};
			int
				no = test_no;
			int 
				i {-1},
				* p = nullptr;
			{
				m_pointer <int> m {i};
				testing_bundle <int>
					t0_0 {name + ": init", * m.ptr, -1};
				p = m.ptr;
			}
			testing_bundle <bool>
				t1_0 {name + ": ~", * p == -1, false};

			m_pointer<int> m {i};
			testing_bundle <int>
				t2_0 {name + ": *", * m, -1};

			int
				* v = m.release();
			testing_bundle <bool>
				t3_0 {name + ": rel", m.ptr == nullptr, true};
			testing_bundle <int>
				t3_1 {name + ": rel", * v, -1};
			report (no, name);
		}
	}

	namespace e11
	{
		void testing()
		{
			string
				name {"e11"};
			int
				no = test_no;
			{
				counted_ptr <int> c {-1};
				testing_bundle <int>
					t0_0 {name + ": init", *c.ptr, -1},
					t0_1 {name + ": init", *c.counter, 1};
			}
			counted_ptr <int> 
				c {-1},
				d = c;
			testing_bundle <bool>
				t1_0 {name + ": =", c.ptr == d.ptr, true},
				t1_1 {name + ": =", c.counter == d.counter, true};
			testing_bundle <int>
				t1_2 {name + ": =", * c.counter, 2};

			c.destroy();
			testing_bundle <bool>
				t2_0 {name + ": dstr", c.ptr == nullptr, true},
				t2_1 {name + ": dstr", c.counter == nullptr, true},
				t2_2 {name + ": dstr", d.ptr == nullptr, false},
				t2_3 {name + ": dstr", * d.counter == 1, true};
			d.destroy();
			testing_bundle <bool>
				t3_1 {name + ": dstr", d.ptr == nullptr, true},
				t3_2 {name + ": dstr", d.counter == nullptr, true};

			report (no, name);
		}
	}

	namespace e12
	{
		void testing()
		{
			string
				name {"e12"};
			int 
				no = test_no;

			string
				file {"e12_test.txt"};
			{
				File_handle
					f {file};
				testing_bundle <bool>
					t0_0 {name + ": init", f.name == file, true},
					t0_1 {name + ": init", f.fs == nullptr, false};
			}
			report (no, name);
		}
	}

	namespace e13
	{
		void testing()
		{
			string
				name {"e13"};
			int
				no = test_no;
			{
				Tracer
					t {"\nbulk of this excercise is in \n\tch19, \n\tch19_try_this, \n\tch19_go_deeper\n"};
			}
			report (no, name);
		}
	}

	namespace e16
	{
		void testing()
		{
			string
				name {"e16"};
			int
				no = test_no;
			vector_base<int> v {1};
			testing_bundle <bool>
				t0_0 {name, v.elem == nullptr, false};
			
			m_vector<int> v1 (1);
			testing_bundle <bool>
				t1_0 {name, v1.elem == nullptr, false},
				t1_1 {name, * v1.elem == 0, true};
			
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
		//e07::testing();
		//e08::testing_allocations();
		//e08::testing_m_allocator();
		//e08::testing_m_vector();
		//e10::testing();
		//e11::testing();
		e16::testing();
	}
}