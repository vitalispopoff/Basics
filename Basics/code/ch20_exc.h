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
			char & operator * () {return * pos;}			
			Text_iterator & operator ++ ();
			bool operator == (const Text_iterator & other) const
				{return ln == other.ln && pos == other.pos;}
			bool operator != (const Text_iterator & other) const
				{return ! (* this == other);}
		};

		Text_iterator find_txt (
			Text_iterator first, 
			Text_iterator last, 
			const string & s);

		struct Document
		{
			list <Line> 
				line;
			Text_iterator begin() 
			{
				return 
					Text_iterator (
						line.begin(), 
						(* line.begin()).begin()
					);
			}
			Text_iterator begin() const {return begin();}
			Text_iterator end()
			{
				auto
					last = line.end();
				--last;
				return 
					Text_iterator (
						last, 
						(* last).end()
					);
			}
			Text_iterator end() const {return end();}
			void erase_line (int n);
		};
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
		using namespace text_editor;

		int count_chars (const Document & d);
	}



	void main();

}
