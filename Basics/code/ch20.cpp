#include "ch20.h"

#include <string>
#include <iostream>
#include <list>

namespace ch20
{
	using namespace std;
	using namespace testing_space;

	namespace try_this_1
	{
		double * get_from_jack (int * count)
		{
			* count = 3;			
			return new double [3] { -1, -1, -1};
		}
		vector <double> * get_from_jill ()
		{
			return new vector <double> {-1, -1, -1};
		}

		void fct()
		{
			int
				jack_count = 0;
			double
				* jack_data = get_from_jack (& jack_count);
			vector <double>
				& jill_data = * get_from_jill();

			double 
				h = -1,
				* jack_high = nullptr;
			for (int i = 0; i < jack_count; ++i)
				if (h <= jack_data [i])
				{
					jack_high = &jack_data [i];
					h = jack_data [i];
				}
			
			double
				* jill_high = nullptr;
			h = -1;
			for (int i = 0; i < (int) jill_data.size(); ++i)
				if (h <= jill_data [i])
				{
					jill_high = & jill_data [i];
					h = jill_data [i];
				}

			delete [] jack_data;
			delete & jill_data;
		}

		void test()
		{
			string 
				name {"e20: try_this"};
			int
				no = test_no;
			
			int 
				* len = new int {INT_MIN};
			double 
				* d = get_from_jack(len);
			testing_bundle <int>
				t0_0 {name + ": pre", * len, 3};
			testing_bundle <bool>
				t0_1 {name + ": pre", d == nullptr, false};

			for (int i = 0; i < * len; ++i)
				testing_bundle <double>
					t0_2 {name + ": pre", d[i], -1};
			if (len != nullptr)
				delete len;
			if (d != nullptr)
				delete [] d;

			report (no, name + ": pre");

			fct();
		}
	}

	namespace try_this_3
	{
		void copy (int * f1, int * e1, int * f2)
		{
			for (int * i = f1; i != e1; ++i, ++f2)
				* f2 = * i;
		}

		void test()
		{
			string
				name {"ch20 : try_this_3"};
			int
				no = test_no;
			int 
				* ptr1 = new int [3] {0, 1, 2},
				* ptr2 = (int *) malloc (sizeof (int) * 3);
			copy (ptr1, & (ptr1 [3]), ptr2);
			for (int i = 0; i < 3; ++i)
				testing_bundle <int>
					t0_0 {name, ptr2 [i], i};
			report (no, name);
		}
	}

	namespace try_this_4
	{
		bool flag {false};
		double * get_from_jack (int * count, bool b = flag)
		{
			if (b)
				* count = 3;			
				return new double [3] { -1, -1, -1};
			return nullptr;
		}
		vector <double> * get_from_jill(bool b = flag)
		{			
			return b ? 
				new vector <double> {-1, -1, -1}
				: nullptr;
		}

		template <typename Iterator>
		Iterator high (Iterator first, Iterator last)
		{
			if (first == last)
				throw runtime_error ("No data available");

			Iterator 
				high = first;
			for (Iterator p = first; p != last; ++p)
				if (* high < * p) 
					high = p;
			return high;
		}

		void fct()
		{
			int
				jack_count = 0;
			double
				* jack_data = get_from_jack (& jack_count);
			vector <double> 
				* jill_data = get_from_jill ();
			double
				* jack_high = high (jack_data, jack_data + jack_count);
			vector <double>
				& v = * jill_data;
			double 
				* jill_high = high (& v [0], & v [0] + v.size());

			delete [] jack_data;
			delete jill_data;
		}

		void test()
		{
			string
				name {"ch20: try this 4"};
			int 
				no = test_no;
			try
			{
				fct();
			}
			catch (exception & e)
			{
				testing_bundle <string>
					t_err {name, e.what(), "No data available"};
			}
			report (no, name);
		}

	}

	namespace try_this_5
	{
		template <typename T, typename A>
		m_vector <T, A> & m_vector <T, A>::operator = (const m_vector & v)
		{
			if (this == & v)
				return * this;
			if (this -> space < v.sz)
			{
				this -> elem.reset (this -> alloc.allocate (v.sz));
				this -> space = v.sz;
			}
			this -> sz = v.sz;
			copy (v.elem.get(), v.elem.get() + this -> sz, this -> elem.get());
			return * this;
		}

		template <typename T, typename A>
		m_vector <T, A> & m_vector <T, A>::operator = (m_vector && v) noexcept
		{
			this -> sz = v.sz;
			this -> space = v.space;
			this -> elem.reset(v.elem.release());
			return * this;
		}

		template <typename T, typename A>
		void m_vector <T, A>::reserve (int new_space)
		{
			if (new_space <= this -> space)
				return;
			unique_ptr <T> 
				ptr {this -> alloc.allocate (new_space)};
			copy (this -> elem.get(), this -> elem.get() + this -> sz, ptr.get());
			this -> elem.reset (ptr.release());		
			this -> space = new_space;
		}

		template <typename T, typename A>
		void m_vector <T, A>::resize (int new_size, T val)
		{
			if (new_size < 0)
				return;
			reserve (new_size);
			for (int i = this -> sz; i < new_size; ++i)
				this -> alloc.construct (& this -> elem.get() [i], val);
			for (int i = new_size; i < this -> sz; ++i)
				this -> alloc.destroy (& this -> elem.get() [i]);
			this -> sz = new_size;
		}

		template <typename T, typename A>
		void m_vector <T, A>::push_back (T val)
		{
			if (this -> space == 0)
				reserve (8);
			else 
				if (this -> space == this -> sz)
					reserve (2 * this -> space);
			this -> alloc.construct (& this -> elem.get() [this -> sz], val);
			++this -> sz;
		}

		template <typename T, typename A>
		void m_vector <T, A>::push_front (T val)
		{
			int
				new_space {this -> sz < this -> space ? this -> space : this -> space * 2};
			unique_ptr <T>
				ptr {this -> alloc.allocate (new_space)};
			* ptr.get() = val;
			copy (this -> elem.get(), this -> elem.get() + this -> sz, ptr.get() + 1);
			this -> elem.reset (ptr.release());
			this -> space = new_space;
			++ this-> sz;
		}

		template <typename T>
		void printing (m_vector <T> & v)
		{
			cout
				<< "\nsz : " << v.size() <<",\tspace : " << v.capacity() << '\n';
		}

		void test_min()
		{
			string
				name {"ch20: try this 5"};
			int 
				no = test_no;
				
			m_vector <int> 
				v0;
			testing_bundle <int>
				t0_0 {name + ": empty size", v0.size(), 0},
				t0_1 {name + ": empty space", v0.capacity(), 8};
			report (no, name + ": empty");

			m_vector <int> 
				v1 (1, -1);
			testing_bundle <int>
				t1_0 {name + ": expl size", v1.size(), 1},
				t1_1 {name + ": expl space", v1.capacity(), 1},
				t1_2 {name + ": expl elem", v1[0], -1};
			report (no, name + ": expl");

			m_vector <int> v2 {-1, -2};
			testing_bundle <int>
				t2_0 {name + ": init size", v2.size(), 2},
				t2_1 {name + ": init space", v2.capacity(), 2},
				t2_2 {name + ": init elem", v2 [0], -1},
				t2_3 {name + ": init elem", v2 [1], -2};
			report (no, name + ": init");

			m_vector <int> 
				u3 {-1},
				v3 {u3};
			testing_bundle <int>
				t3_0 {name + ": copy size", v3.size(), 1},
				t3_1 {name + ": copy space", v3.capacity(), 1},
				t3_2 {name + ": copy elem", v3 [0], -1};
			report (no, name + ": copy");

			void 
				* temp_ptr4 = nullptr;
			auto a4 = [&]() -> m_vector <int>
			{
				m_vector <int> 
					temp {-1};
				temp_ptr4 = (void *) temp.addr();
				return temp;
			};
			m_vector <int> 
				v4 {a4()};
			testing_bundle <int>
				t4_0 {name + ": move size", v4.size(), 1},
				t4_1 {name + ": move space", v4.capacity(), 1},
				t4_2 {name + ": move *", (int) temp_ptr4, (int) v4.addr()};
			report (no, name + ": move");
			
			m_vector <int>
				v5 = m_vector <int> {-1};
			testing_bundle <int>
				t5_0 {name + ": = size", v5.size(), 1},
				t5_1 {name + ": = space", v5.capacity(), 1},
				t5_2 {name + ": = elem", v5[0], -1};
			report (no, name + ": =");
	
			m_vector <int>
				u6 {-1},
				v6 = u6;
			testing_bundle <int>
				t6_0 {name + ": = copy size", u6.size(), v6.size()},
				t6_1 {name + ": = copy space", u6.capacity(), v6.capacity()},
				t6_2 {name + ": = copy elem", u6 [0], v6 [0]};
			report (no, name + ": = copy");

			void 
				* ptr7 = nullptr;
			auto a7 = [&]() -> m_vector <int>
			{
				m_vector <int> temp {-1};
				ptr7 = (void *) temp.addr();
				return temp;
			};
			m_vector <int>
				v7 = a7();
			testing_bundle <int>
				t7_0 {name + ": = move size", v7.size(), 1},
				t7_1 {name + ": = move space", v7.capacity(), 1},
				t7_2 {name + ": = move: *", (int) ptr7, (int) v7.addr()};
			report (no, name + "= move");
		}

		void test_reserve()
		{
			string
				name {"reserve"};
			int
				no = test_no;
			m_vector <int> 
				v;
			v.reserve (1);
			testing_bundle <int>
				t8_0 {name + ": empty, 1: size", v.size(), 0},
				t8_1 {name + ": empty, 1: space", v.capacity(), 8},
				t8_2 {name + ": empty, 1: *", int (v.addr() != nullptr), 1};
			report (no, name);
		}

		void test_resize()
		{
			string 
				name {"resize"};
			int
				no = test_no;
			m_vector <int> 
				v1;
			v1.resize(0);
			testing_bundle <int>
				t9_0 {name + ": init, 0 : size", v1.size(), 0},
				t9_1 {name + ": init, 0 : space", v1.capacity(), 8},
				t9_2 {name + ": init, 0 : *", int (v1.addr() != nullptr), 1};
			report (no, name);

			m_vector <int> 
				vA;
				vA.resize(1);
			testing_bundle <int>
				tA_0 {name + ": init, 1 : size", vA.size(), 1},
				tA_1 {name + ": init, 1 : space", vA.capacity(), 8},
				tA_2 {name + ": init, 1 : elem", vA [0], 0};
			report (no, name);

			m_vector <int> 
				vB;
			vB.resize(1, -1);
			testing_bundle <int>
				tB_0 {name + ": init, 1 : size", vB.size(), 1},
				tB_1 {name + ": init, 1 : space", vB.capacity(), 8},
				tB_2 {name + ": init, 1 : elem", vB [0], -1};
			report (no, name);

			m_vector <int> vC {-1, -2};
			vC.resize (1);
			testing_bundle <int>
				tC_0 {name + ": init 2, 1 : size", vC.size(), 1},
				tC_1 {name + ": init 2, 1 : space", vC.capacity(), 2},
				tC_2 {name + ": init 2, 1 : elem", vC [0], -1};
			report (no, name);
		}

		void test_push_back()
		{
			string
				name {"push_back"};
			int
				no = test_no;

			m_vector <int> 
				vD;
			vD.push_back (-1);
			testing_bundle <int>
				tD_0 {name + ": empty size", vD.size(), 1},
				tD_1 {name + ": empty space", vD.capacity(), 8},
				tD_2 {name + ": empty elem", vD[0], -1};
			report (no, name);

			m_vector <int> 
				vE (8);
			void 
				* ptrE = (void *) vE.addr();
			vE.push_back (-1);
			testing_bundle <int>
				tE_0 {name + ": expl 8 size", vE.size(), 9},
				tE_1 {name + ": expl 8 space", vE.capacity(), 16},
				tE_2 {name + ": expl 8 elem", vE [8], -1},
				tE_3 {name + ": expl 8 *", int (ptrE !=  (void *) vE.addr()), 1};
			report (no, name);
		}

		void test_push_front()
		{
			string
				name {"push_front"};
			int
				no = test_no;
			
			m_vector <int>
				vF;

			vF.push_front (-1);
			testing_bundle <int>
				tF_0 {name + ": empty size", vF.size(), 1},
				tF_1 {name + ": empty space", vF.capacity(), 8},
				tF_2 {name + ": empty elem", vF [0], -1};

			vF = m_vector <int> {};		
			for (int i = 0; i < vF.capacity() - 1; ++i)
				vF.push_back(i + 1);
			
			vF.push_front(0);
			testing_bundle <int>
				tF_3 {name + ": full size", vF.size(), 8},
				tF_4 {name + ": full space", vF.capacity(), 8};
			for (int i = 0; i < vF.size(); ++i)
				testing_bundle <int>
					tF_5 {name + ": full elem", vF [i], i};
			report (no, name);
		}

		void tests()
		{
			test_min();
			test_reserve();
			test_resize();
			test_push_back();
			test_push_front();

			cout << "\nAll tests done (" << test_no << ").\n";		
		}

		void main()
		{
			tests();
		}	
	}

	namespace try_this_6
	{
		template <typename Iter>
			void advance (Iter & p, int n)
		{
			int 
				direction {get_direction(n)};
			while (n)			
			{				
				p += direction;
				n -= direction;
			}
		}

		int get_direction (int n) 
		{
			return (n > 0) - (n < 0);
		}

		void test()
		{
			string
				name {"try this 6"};
			int
				no = test_no;
			int
				i {2},
				j {-2},
				k {0};
			testing_bundle <int>
				t0_0 {name, get_direction (i), 1},
				t0_1 {name, get_direction (j), -1},
				t0_2 {name, get_direction (k), 0};
			report (no, name);

		}
	}

	namespace try_this_7
	{	
		template <typename T>
			int len (T & t)
		{
			return t.size();
		}
		template <typename T>
			int array_len (T * t)	// changed from value pass
		{
			//return sizeof (t); // surprisingly returns wrong value
			int c {0};
			while (* t != 0)
			{
				++t;
				++c;
			}
			return c;
		}
		template <typename T>
			bool is_equal (T & t, string s = "Hello")
		{
			return t == s;
		}
		template <typename T>
			bool is_array_equal (T t, string s = "Hello")
		{
			int 
				i {0};
			while (t [i] != 0 && s [i] == t [i])
				++i;
			return i == s.size() && t [i] == 0;
		}
		template <typename T>
			bool is_vector_equal (vector <T> t, string s = "Hello")
		{
			if (s.size() != t.size())
				return false;
			int 
				i {0};
			for (; i < s.size() && s [i] == t [i]; ++i);				
			return i == s.size();
		}
		template <typename T>
			bool is_list_equal (list <T> t, string s = "Hello")
		{
			auto 
				iter = t.begin();
			int
				i {0};
			while (iter != t.end() && * iter == s [i])
			{				
				++iter ;
				++i;
			}
			return i == t.size();
		}

		void test()
		{
			string 
				name {"try this 7"};
			int
				no = test_no;
			string
				howdy {"Howdy"},
				hello {"Hello"};
			testing_bundle <int>
				t0_0 {name, len (hello), 5},
				t0_1 {name, is_equal (hello), 1},
				t0_2 {name, is_equal (hello, howdy), 0};
			report (no, name);

			char 
				hello_arr [6] = {};
			strcpy_s (hello_arr, hello.c_str());	// recomended over strcpy : err C4996
			testing_bundle <int>
				t1_0 {name, array_len (hello_arr), 5},
				t1_1 {name, is_array_equal (hello_arr), 1},
				t1_2 {name, is_array_equal (hello_arr, howdy), 0};
			report (no, name);

			vector <char>
				hello_v {};
			for (char c : hello)
				hello_v.push_back (c);
			testing_bundle <int>
				t2_0 {name, len(hello_v), 5},
				t2_1 {name, is_vector_equal (hello_v), 1},
				t2_2 {name, is_vector_equal (hello_v, howdy), 0};
			report (no, name);

			list <char>
				hello_l {};
			for (char c: hello)
				hello_l.push_back (c);
			testing_bundle <int>
				t3_0 {name, len (hello_l), 5},
				t3_1 {name, is_list_equal (hello_l), 1},
				t3_2 {name, is_list_equal (hello_l, howdy), 0};
			report (no, name);
		}
	}

	void main()
	{
		//try_this_5::tests();
		//try_this_6::test();
		//try_this_7::test();		
	}
}