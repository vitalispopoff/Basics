#include "ch20_exc.h"
#include "testing.h"

#include <fstream>
#include <iostream>
//#include <vector>

namespace ch20_exc
{
	using namespace std;
	using namespace testing_space;
	
	namespace text_editor
	{
		Text_iterator & Text_iterator::operator ++()
		{			
			++pos;
			if (pos == ln -> end())	// doesn't check against the end
			{
				++ln;
				pos = ln -> begin();
			}
			return * this;
		}

		bool match (Text_iterator first, Text_iterator last, const string s)		
		{
			for (int i = 0; i < (int) s.size() && first != last; ++i, ++first)
				if ( * first != s [i])
					return false;
			return true;
		}

		template <typename T>
			T find_txt (T first, T last, const string & s)
		{
			if (s.size() == 0)
				return last;
			char
				first_char = s [0];
			while (true)
			{
				auto 
					p = find (first, last, first_char);
				if (p == last || match (p, last, s))
					return p;
				first = ++p;
			}
			return last;
		}

		void Document::erase_line (int n)
		{
			if (n < 0 || n >= line.size() - 1)
				return;
			auto
				p = line.begin();
			advance (p, n);
			line.erase (p);
		}

		void print (Document & d)
		{
			for (auto p : d)
				cout << p;
		}
	}

	namespace e02
	{
		template <typename T>
		void fill (string file, T * container, int len = 0)
		{
			ifstream 
				ifs {file, ios_base::in};
			if (! ifs)
				throw runtime_error ("Can't open file.");
			double
				tmp {};
			for (int i = 0; ifs >> tmp && i < len; ++i)
				container [i] = tmp;
			ifs.close();
		}
		
		double * get_from_jack (int * count)
		{
			const int
				len = 6;
			double
				* ptr = new double [len] {};
			fill ("/_LAB/_C/Basics/Basics/resources/ch20_e02.txt", ptr, 6);
			* count = len;
			return ptr;
		}

		vector <double> * get_from_jill()
		{
			vector <double> 
				* ptr = new vector <double> {1, 3, 2, 5, 4, 0};
			return ptr;
		}

		template <typename Iter>
		Iter high (Iter first, Iter last)
		{
			double
				h {- DBL_MAX};
			Iter
				high {};			
			for (Iter p = first; p != last; ++p)
				if (h < *p)
				{
					high = p;
					h = * p;
				}
			return high;
		}

		void fct()
		{
			string
				name {"ch20 e02"};
			int
				no = test_no;

			int
				jack_count {0};
			double
				* jack_data {get_from_jack(& jack_count)},
				* jack_high = high (jack_data, jack_data + jack_count);

			vector <double>
				& jill_data = * get_from_jill();
			auto
				jill_high = high (jill_data.begin(), jill_data.end());

			testing_bundle <double>
				t0_0 {name, * jack_high, 5},
				t0_1 {name, * jill_high, 5};
			report (no, name);

			delete [] jack_data;
			delete & jill_data;
		}
	}

	namespace e04
	{
		double * get_from_jack (int * count) 
		{
			return nullptr;
		}
		vector <double> * get_from_jill()
		{
			return nullptr;
		}
		template <typename Iterator>
			Iterator high (Iterator first, Iterator last)
		{			
			if (! first || first == last)
				return first;
			Iterator 
				high = first;
			for (Iterator p = first; p != last; ++p)
				if (* high > * p) 
					high = p;
			return high;
		}

		void fct()
		{
			string
				name {"ch20 : e04"};
			int
				no = test_no;

			int
				jack_count {0};
			double
				* jack_data = get_from_jack (& jack_count);
			double 
				* jack_high {high (jack_data, jack_data + jack_count)};
			testing_bundle <bool>
				t0_0 {name, jack_high == jack_data, true};
			delete [] jack_data;

			vector <double> 
				* jill_data {get_from_jill()};
			if (jill_data)
			{
				vector <double>
					& v = *jill_data;
				double
					* jill_high {high (&v [0], &v [0] + v.size())};
				delete jill_data;
			}
			report (no, name);
		}
	}

	namespace e05
	{
		template <typename T>
			istream & operator >> (istream & is, vector <T> & v)
		{
			T temp;
			if (is >> temp)
				v.push_back(temp);
			return is;
		}

		template <typename T>
			ostream & operator << (ostream & os, vector <T> & v) 
		{
			for (T & t : v)
				os << t << '\n';
			return os;
		}

		void test()
		{
			vector <char>
				v {};
			for (int i = 0; i < 10 && cin >> v ; ++i);
			cout << v;
		}
	}

	namespace e07
	{	
		string find_lex_last (vector <string> & v)
		{
			string
				result {* v.begin()};
			for (auto iter = v.begin(); iter != v.end(); ++iter)
				if (result < * iter)
					result = * iter;
			return result;
		}
		
		void test()
		{
			string 
				name {"ch20 e07"};
			int
				no = test_no;
			vector <string>
				v {
					"aaaaby",
					"beka",
					"zoo",
					"foobar",
					"noga"
				};
				
			testing_bundle <string>
				t0_0 {name, find_lex_last (v), "zoo"};
			report (no, name);
		}
	}

	namespace e08
	{
		using namespace text_editor;

		int count_chars (Document & d)
		{
			int
				result {0};
			for (Line l : d.line)
				result += l.size();
			return result;
		}

		void test()
		{
			string
				name {"ch20 e08"};
			int
				no = test_no;
			vector <char> 
				v {'f','o','o','b','a','r'};
			Document
				d{};
			d.line.push_back (v);
			testing_bundle <int>
				t0_0 {name, count_chars (d), (int) v.size()};
			report (no, name);
		}
	}

	namespace e09
	{
		int count_by_space (Document d)
		{
			int
				result {0};
			auto
				curr_iter = d.begin(),
				end_iter = d.end();
			while (curr_iter != end_iter)
			{
				if (* curr_iter == '\s')
					++result;
			}			
			return result;
		}

		void test()
		{
			string
				name {"ch20 e09"};
			int
				no = test_no;

			Document
				d {};
			string
				str	[] = {
				"Foobar is a little handy piece of software.\n",
				"I mean - it ain't an eye-candy, but works fine,\n",
				"and is highly customizable...\n",
				"Oh, and it sounds really good, which is the important part actually.\n"
			};
			for (string s: str)
			{
				Line
					l{};
				for (char c : s)
					l.push_back(c);
				d.line.push_back (l);
			}
			print (d);
		}
	}

	void main()
	{
		//e02::fct();
		//e04::fct();
		//e05::test();
		 //e07::test();
		//e08::test();
		e09::test();
	}
}