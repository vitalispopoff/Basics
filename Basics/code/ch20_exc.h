#pragma once

#include <iostream>
#include <vector>

namespace ch20_exc
{
	using namespace std;

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

	void main();

}
