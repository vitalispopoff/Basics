#include "ch20_exc.h"

namespace ch20_exc
{
	namespace e02
	{
		double * get_from_jack (int * count)
		{
			return nullptr;
		}

		vector <double> * get_from_jill()
		{
			return nullptr;
		}

		void fct()
		{
			int
				jack_count {0};
			double 
				* jack_data {get_from_jack(& jack_count)};
			vector <double> 
				* jill_data {get_from_jill()};

			double 
				h {- DBL_MAX},
				* jack_high = nullptr,
				* jill_high = nullptr;
			for (int i = 0; i < jack_count; ++i)
				if (h < jack_data [i])
				{
					jack_high = & jack_data [i];
					h = jack_data [i];
				}
			h = - DBL_MAX;
			for (int i = 0; i < jill_data -> size(); ++i)
				if (h < (* jill_data) [i])
				{
					jill_high = & (* jill_data) [i];
					h = (* jill_data) [i];

				}

			delete [] jack_data;
			delete jill_data;
		}
	}

	void main()
	{


	}
}