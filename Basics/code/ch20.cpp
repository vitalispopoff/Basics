#include "ch20.h"



namespace ch20
{
	namespace section_1_1
	{
		/// these two implemented to avoid building errors only
		double * get_from_jack (int * count)
		{
			return (double *) nullptr;
		}
		vector <double> * get_from_jill ()
		{
			return (vector <double> *) nullptr;
		}



		void fct()
		{
		/// setup

			int
				jack_count = 0;
			double
				* jack_data = get_from_jack (& jack_count);
			vector <double>
				* jill_data = get_from_jill();

		/// process

			double 
				h = -1,
				* jack_high = nullptr;
			for (int i = 0; i < jack_count; ++i)
				if (h < jack_data [i])
				{
					jack_high = &jack_data [i];
					h = jack_data [i];
				}
			
			double
				* jill_high = nullptr;
			h = -1;
			for (int i = 0; i < jill_data -> size(); ++i)
				if (h < (* jill_data) [i])
				{
					jill_high = & (* jill_data) [i];
					h = (* jill_data) [i];
				}
			
		/// clean

			delete [] jack_data;
			delete jill_data;
		}
	}
	

	void main()
	{

	}
}