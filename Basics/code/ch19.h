#pragma once

#include <iostream>
#include <initializer_list>
#include <algorithm>	//for the copy() calls
#include <memory>
#include <vector>

using namespace std;
namespace ch19
{
	template <typename T, typename A = allocator <T>>
		struct vector_base
	{
		A alloc;
		int sz, space;
		T * elem;

		vector_base (const A & a, int n = 0) :			
			alloc {a},
			sz {0},
			space {max (0, n)},
			elem {(bool) space ? alloc.allocate (space) : nullptr}
		{}

		~vector_base () 
		{
			for (int i = 0; i < sz; ++i)
				alloc.destroy (elem + i);
		}
	};
		
	template <typename T, typename A = allocator <T>>
		class m_vector : private vector_base <T, A>
	{
	public : 

		explicit m_vector (int n = 0, T val = T()) :
			vector_base<T, A>::vector_base {A(), n}		
		{
			if (n > 0)
			{
			for (int i = 0; i < n; ++i) 
				this->alloc.construct (& (this -> elem [i]), val);
			this -> sz = n;
			}
		}

		m_vector (initializer_list <T> lst) :
			vector_base<T, A>::vector_base {A(), (int) lst.size()}
		{
			this -> sz = this -> space;
			copy (lst.begin(), lst.end(), this -> elem);
		}

		T & operator [] (int n) {return this -> elem [n];}
		const T & operator [] (int n) const {return this -> elem [n];}

		void reserve (int new_space);
		void resize(int new_size, T val = T());
		void push_back (T val);

		int size () const {return this -> sz;}
		int capacity () const {return this -> space;}

		/// for testing:
		const T * addr () const {return this -> elem;}
	};

	void main();
}

/// covers the last try_this excercise
namespace ch19_try_this
{
	template <typename T, typename A = allocator <T>>
		class m_vector
	{
		A alloc;
		int sz, space;
		unique_ptr<T> elem;
	public :
		m_vector () :
			alloc {A ()},
			sz {0},
			space {8},
			elem {alloc.allocate (space)}
		{}

		explicit m_vector (int n, T val = T()) :
			sz {max (0, n)},
			space {max (1, n)},
			elem {alloc.allocate (space)}
		{
			for (int i = 0; i < sz; ++i)
				alloc.construct (& elem.get() [i], val);
		}

		m_vector (initializer_list <T> lst) :
			sz {(int) lst.size()},
			space {(int) lst.size()},
			elem {alloc.allocate (space)}
		{
			copy (lst.begin(), lst.end(), elem.get());
		}

		m_vector (const m_vector & v) :
			sz {v.sz},
			space {sz},
			elem {alloc.allocate (sz)}
		{
			copy (v.elem.get(), v.elem.get() + sz, elem.get());
		}

		m_vector (m_vector && v) noexcept :
			sz {v.sz},
			space {v.space},
			elem {}
		{
			v.sz = v.space = 0;
			elem.swap (v.elem);
		}

		~m_vector()
		{
			elem.reset();	// reset deletes, release ... returns the owned pointer
		}

		m_vector & operator = (const m_vector & v);
		m_vector & operator = (m_vector && v) noexcept;

		T & operator [] (int n) {return elem.get() [n];}
		const T & operator [] (int n) const {return elem.get() [n];}

		void reserve (int new_space);
		void resize (int new_size, T val = T());
		void push_back (T val);

		int size() const {return sz;}
		int capacity() const {return space;}

		/// for testing
		const T * addr () const {return & elem.get()[0];} // this is curious
	};

	void main();
}

/// combines unique_ptr with inheritance (vector_base)
namespace ch19_go_deeper
{
	template <typename T, typename A = allocator <T>>
		struct vector_base
	{
		A alloc;
		int sz, space;
		unique_ptr<T> elem;
		explicit vector_base (const A & a = A (), int n = 0) :
			alloc {a},
			sz {n},
			space {n > 0 ? n : 8},
			elem {alloc.allocate (space)}
		{}
		~vector_base () {elem.reset();}
	};


	template <typename T, typename A = allocator <T>>
		class m_vector : private vector_base <T, A>
	{
	public :
		m_vector () :
			vector_base <T, A>::vector_base{}
		{}

		explicit m_vector (int n, T val = T()) :
			vector_base <T,A>::vector_base {A (), max (0, n)}
		{
			for (int i = 0; i < this -> sz; ++i)
				this->alloc.construct (& this -> elem.get() [i], val);
		}

		m_vector (initializer_list <T> lst) :
			vector_base <T, A>::vector_base {A (), (int) lst.size()} 
		{
			copy (lst.begin(), lst.end(), this -> elem.get());
		}

		m_vector (const m_vector & v) :
			vector_base <T, A>::vector_base {A (), v.sz}
		{
			copy (v.elem.get(), v.elem.get() + v.sz, this -> elem.get());
		}

		m_vector (m_vector && v) noexcept :
			vector_base <T, A>::vector_base {}
		{
			this -> sz = this -> space = v.sz;			
			this -> elem.reset (v.elem.release());
		}

		m_vector & operator = (const m_vector & v);
		m_vector & operator = (m_vector && v) noexcept;

		T & operator [] (int n) {return this -> elem.get() [n];}
		const T & operator [] (int n) const {return this -> elem.get() [n];}

		void reserve (int new_space);
		void resize (int new_size, T val = T());
		void push_back (T val);

		int size() const {return this -> sz;}
		int capacity() const {return this -> space;}

		/// for testing
		const T * addr () const {return & this -> elem.get()[0];} // this is curious
		unique_ptr<T> & get() {return this -> elem;}
	};

	void main();
}

namespace ch19_drill
{
	template <typename T> 
		struct S
	{
		explicit S (T t) :
			val {t}
		{}
		T & get();
		const T & get() const;
		void set (T t) {val = t;}
		S operator = (const T & t);		
	private : 
		T val;		
	};

	void main();
}

namespace ch19_exc
{
	namespace testing
	{
		int test_no {0};

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
		void testing ()
		{
			++test_no;
			if (given != expected)
				cout
				<<  test_no << ".\t" << name << "\tfailed\n";
		}
	};

	void report (int no, string name)
	{
		cout 
			<< '\t' << name << ":\ttests: " << no << " - " << test_no - 1 << '\n';
	}

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
	}

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
			Link (const T & v, Link * p = nullptr, Link * s = nullptr) :
				value {v},
				prev {p},
				succ {s}
			{}
			~ Link ()
			{
				delete [] value;
			}
			/// insert n in front
			void insert (Link * n);
			Link * erase();
			/// returns Link {t}
			Link * add_ordered (T t);

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


			void print_all();
		};

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

		//template <typename T> 
		//	Link<T> * insert (Link<T> * p, Link<T> * n);

		//// p keeps the links
		//template <typename T>
		//	Link<T> * erase (Link<T> * p);

		//template <typename T>
		//	Link<T> * advance (Link<T> * p, int n);
	
		void test();

	// ----------------
		
		struct God
		{
			string
				name, mythology, vehicle, weapon;
			God () {}
			God (string n, string m, string v, string w) :
				name {n}, mythology {m}, vehicle {v}, weapon {w}
			{}
			void to_string ()
			{
				cout 
					<< name << ", " 
					<< mythology << ", "
					<< vehicle << ", "
					<< weapon << '\n';
			}
		};
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
	}

	 void main();
}
