#pragma once

#include <iostream>
#include <vector>
#include <list>

namespace ch20_exc
{
	using namespace std;

	// unsolved problem with safe range loop
	namespace text_editor
	{
		using Line = vector <char>;

		class Text_iterator
		{
			list <Line>::iterator
				ln;
			Line::iterator
				pos;
		public:
			Text_iterator (list <Line>::iterator ll, Line::iterator pp) :
				ln {ll},
				pos {pp}
			{}
			char & operator * ()
			{
				return *pos;
			}

			bool operator == (const Text_iterator & other) const
			{
				return ln == other.ln && pos == other.pos;
			}																	    /// !!!! this might need redifinition

			bool operator != (const Text_iterator & other) const
			{
				return (ln != other.ln || pos != other.pos);
			}
			Text_iterator & operator ++ ();
		};

		template <typename T>
		T find_txt (T first, T last, const string & s);

		struct Document
		{
			list <Line>
				line;
			Text_iterator begin()
			{
				return Text_iterator (line.begin(), line.begin()->begin());
			}
			Text_iterator end()
			{
				auto
					last = line.end();
				--last;
				return Text_iterator (last, last->end());
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

	namespace e11
	{
		vector <double> make_vect (list <int> l);
		bool check_consistency (vector <double> v, list <int> l);
		void print_ascending (vector <double> v);
		void fct (list <int> & l);

		void test();
	}

	namespace e12
	{
		template <typename Elem>
			struct Link
		{
			Link
				* prev = nullptr,
				* succ = nullptr;
			Elem
				val = Elem {};
			Link ()
			{}
			Link (Link & p, Link & s, Elem e) :
				prev {& p},
				succ {& s},
				val {e}
			{
				p.succ = s.prev = this;							// this may cause cuts if p && q are from different lists
			}
			Link (Link & l) :
				prev {l.prev},
				succ {l.succ},
				val {l.val}
			{}
			Link (Link && l) :
				prev {l.prev},
				succ {l.succ},
				val {l.val}
			{}
			Link & operator = (const Link & r)
			{
				prev = r.prev;
				succ = r.succ;
				val = & r.val;
				return * this;
			}
			bool operator == (Link & r)							// doesn't check the connections to 'this'
			{
				if (this == & r)
					return true;
				return
					prev == r.prev			
					&& succ == r.succ
					&& val == r.val;
			}
		};

		template <typename Elem>
			class list
		{
		public:
			class iterator
			{
				Link <Elem>
					* curr;
			public :
				iterator (Link<Elem> * p) :
					curr {p}
				{}
				iterator &	operator ++ ()
				{
					curr = curr -> succ;
					return * this;
				}
				iterator &	operator -- ()
				{
					curr = curr -> prev;
					return * this;
				}
				Elem &		operator *  ()
				{return curr -> val;}
				bool		operator == (const iterator & b) const
				{return curr == b.curr;}
				bool		operator != (const iterator & b) const
				{return curr != b.curr;}
			};
		private:
			Link <Elem>
				head,
				tail;
		public:
			list () :
				head {Link <Elem> {}},
				tail {head}
			{}
			iterator	begin()
				{return iterator (& head);}
			iterator	end()
				{return iterator (& tail);}
			void /*iterator*/	insert		(iterator p, const Elem & v);
			//iterator	erase		(iterator p);
			//void		push_back	(const Elem & v);
			//void		push_front	(const Elem & v);
			//void		pop_front	();
			//void		pop_back	();

			Link <Elem> & front	()
				{return head;}
			Link <Elem> & back ()
				{return tail;}
		};

		void test();
	}

	void main();
}
