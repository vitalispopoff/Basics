#include "midi_vs_freq.h"

#include <cmath>
#include <iostream>

namespace midi_vs_freq
{
	using namespace std;

	double midi_to_freq (double midi, double ref)
	{
		return (ref / 32.) * (pow (2, ((midi - 9) / 12.)));
	}

	double freq_to_midi (double freq, double ref)
	{
		/*
		freq = (ref / 32) * (pow (2, ((midi - 9) / 12.)))
		32 * freq / ref = 2 ^ ((midi - 9) / 12)
		log2 (32 * freq / ref) = (midi - 9) / 12
		12 * log2 (32 * freq / erf) = midi - 9
		9 + 12 * lg2 (32 * freq / ref) = midi

		z = 32 * freq / ref

		lg2 (z) = ln (z) / ln (2)
		midi = 9 + 12 (ln (z) / ln (2))
		*/

		double 
			temp {32. * freq / ref};
		return 9. + 12. * log (temp) / log (2.);
	}

	void main ()
	{

		double
			n_1 {137.},
			f_1 {22000.},
			f_2 {10.};

		cout
			<< "\tnote " << n_1 << ":\t" 
			<< midi_vs_freq::midi_to_freq (n_1) << '\n'
			<< "\tfreq " << f_1 << ":\t"
			<< midi_vs_freq::freq_to_midi (f_1) <<'\n'
			<< "\tfreq " << f_2 << ":\t"
			<< midi_vs_freq::freq_to_midi (f_2) << '\n';

		cout
			<< "\nnatural log of 2:\t"
			<< log (2) << '\n';
	}
}