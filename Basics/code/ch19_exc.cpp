#include "ch19.h"

namespace testing
{
	int test_no = 1;

	template <typename U>
		void testing_bundle<U>::testing ()
	{
		++test_no;
		if (given != expected)
			cout
			<<  test_no << ".\t" << name << "\tfailed\n";
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

// --------------------------
	
	namespace e01
	{
		template <typename T> void f (vector<T> & v1, vector<T> & v2)
		{
			for (int i = 0; i < (int) v1.size() && i < (int) v2.size(); ++i)
				v1[i] += v2[i];
		}

		/*void test()
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
		}*/
	}

	//namespace e02
	//{
	//	/*using testing::testing_bundle;
	//	using testing::test_no;
	//	using testing::report;*/
	//	template <typename T, typename U>
	//		double f (vector<T> v, vector<U> u)
	//	{
	//		double result {0};
	//		for (int i = 0; i < (int) v.size() && i < (int) u.size(); ++i)
	//			result += ((double)v [i] * (double) u [i]);
	//		return result;
	//	}
	//	/*void test()
	//	{
	//		string 
	//			name {"exc 02"};
	//		int 
	//			no = test_no;
	//		vector<char> 
	//			v {0, 2, 10, 50, 127};
	//		vector<bool> 
	//			u {true, false, false, true, true, false};
	//		double
	//			result = f (v, u);
	//		testing_bundle <double>
	//			t {name, result, 0. + 0. + 50. + 127.};
	//		report (no, name);
	//	}*/
	//}
	//namespace e03
	//{
	//	/*using testing::testing_bundle;
	//	using testing::test_no;
	//	using testing::report;*/
	//	char var_table::get_value (string key)
	//	{
	//		for (Pair<> p : table)
	//			if (p.name == key)
	//				return p.value;
	//		cerr 
	//			<< "\nno key found\n";
	//		throw runtime_error ("no key found");
	//	}
	//	template <typename T, typename U>
	//		ostream & operator << (ostream & os, const Pair<T, U> & p)
	//	{
	//		return os << p.name << " : " << p.value << '\n';
	//	}
	//	/*void test()
	//	{
	//		string 
	//			name {"exc 03"};
	//		int
	//			no = test_no;
	//		var_table table {
	//			{"mailing", '@'},
	//			{"surfing", '~'},
	//			{"snowman", '&'},
	//			{"sun", '*'}
	//		};
	//		char
	//			result = table.get_value("surfing");
	//		testing_bundle<char> 
	//			t {name, result, '~'};
	//		
	//		//var_table
	//		//	* input_ptr = & table;
	//		//char 
	//		//	(e03::var_table:: * get_value) (string) = nullptr;
	//		//get_value = & e03::var_table::get_value;
	//		try 
	//		{
	//			table.get_value("nope");
	//			cout 
	//				<< "\ne03 : error_test failed\n";
	//		} 
	//		catch (exception & e) 
	//		{
	//			++test_no;
	//		}
	//		report (no, name);
	//	}*/
	//}
	//namespace e04
	//{
	//	/*using testing::testing_bundle;
	//	using testing::test_no;
	//	using testing::report;*/
	///// --- Link ---
	//	template <typename T>
	//		void Link<T>::insert (Link<T> * n)
	//	{
	//		if (/*(bool)*/ n) 
	//		{
	//			n -> succ = this;
	//			if (prev)
	//				n -> prev = prev;
	//			prev = n;
	//		}
	//	}
	//	template <typename T>
	//		Link<T> * Link<T>::erase ()
	//	{				
	//		if (succ)
	//			succ -> prev = prev;
	//		if (prev)
	//			prev -> succ = succ;
	//		Link 
	//			* result = prev;
	//		succ == prev == nullptr;
	//		return result;
	//	}
	//	template <typename T>
	//		Link<T> * Link<T>::add_ordered(const T t)
	//	{
	//		Link * h = head();
	//		while (t > h -> value)
	//			h -> forward();
	//		Link
	//			lnk (t);
	//		h -> insert (& lnk);
	//		return h -> prev;
	//	}
	//	template <typename T>
	//		Link<T> * Link<T>::head()
	//	{
	//		Link 
	//			* p = prev;
	//		while (p -> prev)
	//		{
	//			p = p -> prev;
	//			if (p == this)
	//				return this;
	//		}
	//		return p;
	//	}
	//	template <typename T>
	//		Link<T> * advance (Link<T> * p, int n)
	//	{
	//		if (p == nullptr)
	//			return nullptr;
	//		if (n > 0)
	//		{
	//			while (n--)
	//			{
	//				if (p -> succ == nullptr)
	//					return nullptr;
	//				p = p -> succ;
	//			}
	//		}
	//		else
	//			if (n < 0)
	//			{
	//				while (n++)
	//				{
	//					if (p -> prev == nullptr)
	//						return nullptr;
	//					p = p -> prev;
	//				}
	//			}
	//		return p;
	//	}
	//	template <typename T>
	//		void Link<T>::print_all ()
	//	{
	//		Link 
	//			* h = head(),
	//			* p = h;
	//		cout 
	//			<< '\n';
	//		while (p)
	//		{
	//			cout 
	//				<< p -> value;
	//			if (p = p -> succ)
	//				cout << ", ";
	//			if (p == h)
	//				break;
	//		}
	//		cout 
	//			<< '\n';
	//	}
	///// --- God --
	///// --- Test ---
	//	/*void test()
	//	{
	//		string 
	//			name {"exc e04 Link"};
	//		int 
	//			no = test_no;
	//		Link<int> 
	//			lnk3 {1},
	//			lnk2 {2},
	//			lnk1 {1},
	//			lnk0 {0};
	//		lnk2.insert (& lnk1);
	//		lnk1.insert (& lnk0);
	//		testing_bundle<Link<int> *> 
	//			t0 {name, lnk1.prev, & lnk0},
	//			t1 {name, lnk1.forward(), & lnk2},
	//			t2 {name, lnk1.backward(), & lnk0};
	//		testing_bundle <bool> 
	//			t3 {name, (lnk1 == lnk2), false},
	//			t4 {name, (lnk1 == lnk3), true},
	//			t5 {name, (lnk0 < lnk1), true},
	//			t6 {name, (lnk2 > lnk1), true},
	//			t7 {name, (lnk1 != lnk2), true};
	//		Link <int> * rslt0 = lnk2.add_ordered (1);
	//		testing_bundle<Link<int> *>
	//			t8 {name, rslt0 -> prev, & lnk0};
	//		report(no, name);
	//	}*/
	//	//void test_0n()
	//	//{
	//	//	God
	//	//		zeus {"Zeus", "greek", "", "lightning"},
	//	//		odin {"Odin", "norse", "Sleipner", "Gungir"},
	//	//		venus {"Venus", "roman", "", "Mars"};
	//	//	Link<God>
	//	//		z {zeus},
	//	//		o {odin},
	//	//		v {venus};
	//	//}
	//}

	void main()
	{
		//e01::test();
		//e02::test();
		//e03::test();
		/*e04::test();*/
	}
}