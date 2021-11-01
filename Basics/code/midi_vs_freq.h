#pragma once

namespace midi_vs_freq
{
	double midi_to_freq (double midi, double ref = 440.);

	double freq_to_midi (double freq, double ref = 440.);

	void main ();

}