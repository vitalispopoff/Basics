#pragma once

#include <iostream>
#include <vector>
#include <list>

namespace ch20_exc
{
	using namespace std;

	namespace text_editor
	{
		using Line = vector <char>;

		class Text_iterator
		{
			list <Line>::iterator
				ln;
			Line::iterator
				pos;		
		public :		
			Text_iterator (list <Line>::iterator ll, Line::iterator pp) :
				ln {ll},
				pos {pp}
			{}
			char & operator * () 
				{return * pos;}
			bool operator == (const Text_iterator & other) const
				{return ln == other.ln && pos == other.pos;}
			bool operator != (const Text_iterator & other) const
				{return (ln != other.ln || pos != other.pos);}
			Text_iterator & operator ++ ();

			bool ln_end()
			{
				return false;
			}
		};

		template <typename T>
			T find_txt (T first, T last, const string & s);

		struct Document
		{
			list <Line> 
				line;
			Text_iterator begin() 
				{return Text_iterator (line.begin(), line.begin() -> begin());}
			Text_iterator end()
			{
				auto
					last = line.end();
				--last;
				return Text_iterator (last, last -> end());
			}
			void erase_line (int n);
		};
		void print(Document & d);
	}

	namespace e02
	{
		double * get_from_jack (int * conut);
		vector <double> * get_from_jill();
		void fct();
	}

	namespace e04
	{
		double * get_from_jack (int * count);
		vector <double> * get_from_jill();
		template <typename Iterator>
			Iterator high (Iterator first, Iterator last);
		void fct();
	}

	namespace e05
	{
		void test();

		template <typename T>
			istream & operator >> (istream & is, vector <T> & v);
	}

	namespace e07
	{
		string find_lex_last (vector <string> & v);

		void test();
	}

	namespace e08
	{
		using namespace text_editor;

		int count_chars (const Document & d);

		void test();
	}

	namespace e09
	{
		using namespace text_editor;

		int count_by_spaces (Document d);
		int count_alphanum_words (Document d);

		void test();
	}

	void main();
}
