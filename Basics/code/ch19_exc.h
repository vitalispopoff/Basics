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
			T value;
			Link * prev;
			Link * succ;
			explicit Link (const T & v, Link * p = nullptr, Link * s = nullptr) :
				value {v},
				prev {p},
				succ {s}
			{}
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
	
		void test();
	
	// ----------------
		
		//struct God
		//{
		//	string
		//		name, mythology, vehicle, weapon;
		//	God () {}
		//	God (string n, string m, string v, string w) :
		//		name {n}, mythology {m}, vehicle {v}, weapon {w}
		//	{}
		//	void to_string ()
		//	{
		//		cout 
		//			<< name << ", " 
		//			<< mythology << ", "
		//			<< vehicle << ", "
		//			<< weapon << '\n';
		//	}
		//};
		//bool operator < (God g1, God g2)
		//{
		//	return g1.name < g2.name;
		//}
		//bool operator > (God g1, God g2)
		//{
		//	return g1.name > g2.name;
		//}
		//bool operator == (God g1, God g2)
		//{
		//	return g1.name == g2.name;
		//}
		//bool operator != (God g1, God g2)
		//{
		//	return 
		//		g1.name != g2.name
		//		|| g1.mythology != g2.mythology
		//		|| g1.vehicle != g2.vehicle
		//		|| g1.weapon != g2.weapon;
		//}
	}

	 void main();
}
