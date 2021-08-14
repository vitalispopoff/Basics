#pragma once

#include <iostream>
#include <initializer_list>
#include <memory>
#include <vector>

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

	void report (int no, string name);
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
			static Link * make_link (initializer_list<T> lst)
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

			/// insert n in front
			void insert (Link * n);
			Link * erase();
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
			void to_string();
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
				name {n}, mythology {m}, vehicle {v}, weapon {w}
			{}
			ostream & to_string (ostream & os = cout)
			{				
				os
					<< name << ", " 
					<< mythology << ", "
					<< vehicle << ", "
					<< weapon << '\n';
				return os;
			}

		};
		bool operator < (God g1, God g2);
		bool operator > (God g1, God g2);
		bool operator == (God g1, God g2);
		bool operator != (God g1, God g2);
		ostream & operator << (ostream & os, God g);
	}

	 void main();
}
