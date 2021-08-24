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

		class Txt_iter
		{
			list <Line>::iterator
				ln;
			Line::iterator
				pos;
		
		public :
		
		Txt_iter (list <Line>::iterator ll, Line::iterator pp) :
				ln {ll},
				pos {pp}
			{}

			char & operator * () {return * pos;}
			
			Txt_iter & operator ++ ();
			bool operator == (const Txt_iter & other) const
				{return ln == other.ln && pos == other.pos;}
			bool operator != (const Txt_iter & other) const
				{return ! (* this == other);}
		};

		Txt_iter find_txt (Txt_iter first, Txt_iter last, const string & s);

		struct Document
		{
			list <Line> 
				line;
			Txt_iter begin() 
			{
				return 
					Txt_iter (
						line.begin(), 
						(* line.begin()).begin()
					);
			}
			Txt_iter end()
			{
				auto
					last = line.end();
				--last;
				return 
					Txt_iter (
						last, 
						(* last).end()
					);
			}
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
		
		void test();
	}

	void main();

}
