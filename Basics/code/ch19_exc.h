#pragma once

#include <stdexcept>	// for the testing namespace
#include <iostream>
#include <initializer_list>
#include <memory>
#include <vector>
#include <typeinfo>

using namespace std;

namespace testing
{
	extern int test_no;

	template <typename U>
		struct testing_bundle
	{
		string name;
		U given, expected;
		testing_bundle () : 
			name {}, given{U ()}, expected {given} 
		{}
		testing_bundle (string n, U g, U e) : 
			name {n}, given {g}, expected {e}
		{
			testing();
		}

		void testing();
	};

	void report (int & no, string name);
}

namespace ch19_exc
{
	namespace e01
	{		
		template <typename T> 
			void f (vector <T> & v1, vector<T> & v2);
		void test();
	}

	namespace e02
	{
		template <typename T, typename U>
			double f (vector<T> v, vector<U> u);
		void test();
	}

	namespace e03
	{
		template <typename T = string, typename U = char>
			struct Pair
		{
			T name;
			U value;
			Pair () : name {""}, value {0} 
			{}
			Pair (T n, U v) : name {n}, value {v} 
			{}
			T & get_name() {return name;}
			const T & get_name() const {return name;}
			U & get_value() {return value;}
			const U & get_value() const {return value;}
		};
	
		class var_table 
		{
			vector<Pair<>> table;
		public :
			var_table () : table {} {}
			var_table (initializer_list<Pair<>> lst) :
				table {lst}
			{}
			char get_value (string key);
		};
	
		void test();
	}

	namespace e04
	{
		template <typename T> 
			struct Link
		{
			T value;
			Link * prev;
			Link * succ;
			Link () : value {T ()}, prev {nullptr}, succ {nullptr} 
			{}				
			explicit Link (const T & v, Link * p = nullptr, Link * s = nullptr) :
				value {v},
				prev {p},
				succ {s}
			{}
			/// returns ordered list based on init_lst
		static Link<T> * make_link (initializer_list<T> lst)
		{
			Link 
				* temp = new Link {T ()};
			for (T t : lst)
				temp -> add_ordered(t);
			Link
				* result = temp -> head();
			temp -> erase();
			delete temp;
			return result;
		}

			/// insert n in front
			void insert (Link * n);
			Link * erase();
			void extract();
			/// returns Link {t}
			Link & add_ordered (const T t);
			Link & add_ordered (Link & lnk);
	
			Link * head();
			Link * forward()
			{
				if (succ)
					return succ;
				return this;
			}
			Link * backward()
			{
				if (prev)
					return prev;
				return this;
			}
			void to_string(bool line_break = false);
		};
	
		template <typename T>
			bool operator < (const Link<T> & lnk1, const Link<T> & lnk2);
		template <typename T>
			bool operator > (const Link<T> & lnk1, const Link<T> & lnk2);
		template <typename T>
			bool operator == (const Link<T> & lnk1, const Link<T> & lnk2);
		template <typename T>
			bool operator != (const Link<T> & lnk1, const Link<T> & lnk2);
	
		void test_Link();
	
	// ----------------
		
		struct God
		{
			string
				name, mythology, vehicle, weapon;
			God () {}
			God (string n, string m, string v, string w) :
				name {n}, 
				mythology {m}, 
				vehicle {v}, 
				weapon {w}
			{}
			ostream & to_string (ostream & os = cout)
			{				
				os
					<< name << ", " 
					<< (mythology == "" ? "n/a" : mythology) << ", "
					<< (vehicle == "" ? "n/a" : vehicle) << ", "
					<< (weapon == "" ? "n/a" : weapon);
				return os;
			}
		};
		bool operator < (God g1, God g2);
		bool operator > (God g1, God g2);
		bool operator == (God g1, God g2);
		bool operator != (God g1, God g2);
		ostream & operator << (ostream & os, God g);
	}

	namespace e05
	{
		class Int
		{
			int value;

		public : 
			Int () : value {0} 
			{}
			explicit Int (int v) : value {v}
			{}
			Int (Int & i) : value {i.value}
			{}
			Int (Int && i) noexcept : value {i.value}
			{}
			int get () {return value;}
			void set (int v) {value = v;}
		};

		Int operator + (Int & v1, Int & v2);
		Int operator - (Int & v1, Int & v2);
		Int operator * (Int & v1, Int & v2);
		Int operator / (Int & v1, Int & v2);
		Int operator % (Int & v1, Int & v2);
		bool operator == (Int & v1, Int & v2);
		bool operator != (Int & v1, Int & v2);
		bool operator > (Int & v1, Int & v2);
		bool operator < (Int & v1, Int & v2);

		ostream & operator << (ostream & os, Int & v);

		istream & operator >> (istream & is, Int & v);

		void testing();
	}

	namespace e06
	{
		template <typename T = double>
			class Number
		{
			T value;

		public : 
			Number () : value {0} 
			{}
			Number (T v) : value {v}
			{}
			Number (const Number & i) : value {i.value}
			{}
			Number (Number && i) noexcept : value {i.value}
			{}
			T get () {return value;}
			void set (T v) {value = v;}
		};

		template <typename T>
			Number<T> operator + (Number<T> & v1, Number<T> & v2);
		template <typename T>
			Number<T> operator - (Number<T> & v1, Number<T> & v2);
		template <typename T>
			Number<T> operator * (Number<T> & v1, Number<T> & v2);
		template <typename T>
			Number<T> operator / (Number<T> & v1, Number<T> & v2);
		template <typename T>
			Number<T> operator % (Number<T> & v1, Number<T> & v2);
		template <typename T>
			bool operator == (Number<T> & v1, Number<T> & v2);
		template <typename T>
			bool operator != (Number<T> & v1, Number<T> & v2);
		template <typename T>
			bool operator > (Number<T> & v1, Number<T> & v2);
		template <typename T>
			bool operator < (Number<T> & v1, Number<T> & v2);
		template <typename T>
			ostream & operator << (ostream & os, Number<T> & v);
		template <typename T>
			istream & operator >> (istream & is, Number<T> & v);

		void testing(bool inputs = false);
	}

	namespace e07
	{
		using e06::Number;
		template <typename T = Number<double>, typename U = Number<double>>
			Number<> f (vector<T> t, vector<U> u);

		void testing();
	}

	namespace e08
	{
		template <typename T, typename A = allocator <T>>	// T is Element <E>()
			class m_vector
		{
			A alloc;
			int sz;
			int space;
			T * elem;
		public : 
			m_vector () :
				sz {0}, space {8}, elem {alloc.allocate (space)}
			{}
			explicit m_vector (int n, T val = T()) :
				sz {max (0, n)}, space {max(1, n)}, elem {alloc.allocate (space)}
			{
				for (int i = 0; i < sz; ++i) 
					alloc.construct (& elem [i], val);
			}
			m_vector (initializer_list <T> lst) :
				sz {(int) lst.size()}, space {(int) lst.size()}, elem {alloc.allocate (space)}
			{
				copy (lst.begin(), lst.end(), elem);
			}
			m_vector (const m_vector & v) :
				sz {v.sz}, space {sz}, elem {new T [sz]}
			{
				copy (v.elem, v.elem + sz, elem);
			}
			m_vector (m_vector && v) noexcept :
				sz {v.sz}, space {v.space}, elem {v.elem}
			{
				v.sz = v.space = 0;
				v.elem = nullptr;
			}
			~m_vector ()
			{
				delete [] elem;
			}
			m_vector & operator = (const m_vector & v);
			m_vector & operator = (m_vector && v) noexcept (true);		
			T & operator [] (int n) {return elem [n];}
			const T & operator [] (int n) const {return elem [n];}
			void reserve (int new_space);
			void resize(int new_size, T val = T());
			void push_back (T val);
			int size () const {return sz;}
			int capacity () const {return space;}
			/// for testing:
			const T * addr () const {return elem;}
		};

		void testing();		
	}

	 void main();
}
