/*!
 * \file gnss_signal_processing.cc
 * \brief This library gathers a few functions used by the algorithms of gnss-sdr,
 *  regardless of system used
 * \author Luis Esteve, 2012. luis(at)epsilon-formacion.com
 *
 * Detailed description of the file here if needed.
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2012  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#include "gnss_signal_processing.h"



void complex_exp_gen(std::complex<float>* _dest, double _f, double _fs, unsigned int _samps)
{
	double phase = 0;
	const double phase_step = (GPS_TWO_PI * _f) / _fs;
	for(unsigned int i = 0; i < _samps; i++)
	{
		_dest[i] = std::complex<float>(cos(phase), sin(phase));
		phase += phase_step;
	}
}


void hex_to_binary_converter(int * _dest, char _from)
{
	switch(_from)
	{
		case '0':
			*(_dest)=1;
			*(_dest+1)=1;
			*(_dest+2)=1;
			*(_dest+3)=1;
			break;
		case '1':
			*(_dest)=1;
			*(_dest+1)=1;
			*(_dest+2)=1;
			*(_dest+3)=-1;
			break;
		case '2':
			*(_dest)=1;
			*(_dest+1)=1;
			*(_dest+2)=-1;
			*(_dest+3)=1;
			break;
		case '3':
			*(_dest)=1;
			*(_dest+1)=1;
			*(_dest+2)=-1;
			*(_dest+3)=-1;
			break;
		case '4':
			*(_dest)=1;
			*(_dest+1)=-1;
			*(_dest+2)=1;
			*(_dest+3)=1;
			break;
		case '5':
			*(_dest)=1;
			*(_dest+1)=-1;
			*(_dest+2)=1;
			*(_dest+3)=-1;
			break;
		case '6':
			*(_dest)=1;
			*(_dest+1)=-1;
			*(_dest+2)=-1;
			*(_dest+3)=1;
			break;
		case '7':
			*(_dest)=1;
			*(_dest+1)=-1;
			*(_dest+2)=-1;
			*(_dest+3)=-1;
			break;
		case '8':
			*(_dest)=-1;
			*(_dest+1)=1;
			*(_dest+2)=1;
			*(_dest+3)=1;
			break;
		case '9':
			*(_dest)=-1;
			*(_dest+1)=1;
			*(_dest+2)=1;
			*(_dest+3)=-1;
			break;
		case 'A':
			*(_dest)=-1;
			*(_dest+1)=1;
			*(_dest+2)=-1;
			*(_dest+3)=1;
			break;
		case 'B':
			*(_dest)=-1;
			*(_dest+1)=1;
			*(_dest+2)=-1;
			*(_dest+3)=-1;
			break;
		case 'C':
			*(_dest)=-1;
			*(_dest+1)=-1;
			*(_dest+2)=1;
			*(_dest+3)=1;
			break;
		case 'D':
			*(_dest)=-1;
			*(_dest+1)=-1;
			*(_dest+2)=1;
			*(_dest+3)=-1;
			break;
		case 'E':
			*(_dest)=-1;
			*(_dest+1)=-1;
			*(_dest+2)=-1;
			*(_dest+3)=1;
			break;
		case 'F':
			*(_dest)=-1;
			*(_dest+1)=-1;
			*(_dest+2)=-1;
			*(_dest+3)=-1;
			break;
	}
}


void resampler(std::complex<float>* _from, std::complex<float>* _dest, float _fs_in,
		float _fs_out, unsigned int _length_in, unsigned int _length_out)
{
	unsigned int _codeValueIndex;
	//--- Find time constants --------------------------------------------------
    const float _t_in = 1/_fs_in;  // Incoming sampling  period in sec
    const float _t_out = 1/_fs_out;   // Out sampling period in sec
    for (unsigned int i=0; i<_length_out; i++)
        {
            //=== Digitizing =======================================================
            //--- compute index array to read sampled values -------------------------
            _codeValueIndex = ceil((_t_out * ((float)i + 1)) / _t_in) - 1;
            if (i == _length_out - 1)
                {
                    //--- Correct the last index (due to number rounding issues) -----------
                    _dest[i] = _from[_length_in - 1];
                }
            else
                {
                    //if repeat the chip -> upsample by nearest neighbourhood interpolation
                    _dest[i] = _from[_codeValueIndex];
                }
        }
}
