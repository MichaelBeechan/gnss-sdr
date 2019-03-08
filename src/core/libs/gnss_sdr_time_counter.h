/*!
 * \file gnss_sdr_time_counter.h
 * \brief Simple block to report the current receiver time based on the output of the tracking or telemetry blocks
 * \author Antonio Ramos 2018. antonio.ramosdet(at)gmail.com
 *
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2018  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <https://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_GNSS_SDR_TIME_COUNTER_H_
#define GNSS_SDR_GNSS_SDR_TIME_COUNTER_H_

#include <boost/shared_ptr.hpp>
#include <gnuradio/block.h>
#include <gnuradio/types.h>  // for gr_vector_const_void_star
#include <cstdint>

class gnss_sdr_time_counter;

using gnss_sdr_time_counter_sptr = boost::shared_ptr<gnss_sdr_time_counter>;

gnss_sdr_time_counter_sptr gnss_sdr_make_time_counter();

class gnss_sdr_time_counter : public gr::block
{
private:
    gnss_sdr_time_counter();
    int64_t current_T_rx_ms;  // Receiver time in ms since the beginning of the run
    uint32_t current_s;       // Receiver time in seconds, modulo 60
    bool flag_m;              // True if the receiver has been running for at least 1 minute
    uint32_t current_m;       // Receiver time in minutes, modulo 60
    bool flag_h;              // True if the receiver has been running for at least 1 hour
    uint32_t current_h;       // Receiver time in hours, modulo 24
    bool flag_days;           // True if the receiver has been running for at least 1 day
    uint32_t current_days;    // Receiver time in days since the beginning of the run
    int32_t report_interval_ms;
    friend gnss_sdr_time_counter_sptr gnss_sdr_make_time_counter();

public:
    ~gnss_sdr_time_counter();
    int general_work(int noutput_items __attribute__((unused)), gr_vector_int &ninput_items __attribute__((unused)),
        gr_vector_const_void_star &input_items __attribute__((unused)), gr_vector_void_star &output_items);
};

#endif /*GNSS_SDR_GNSS_SDR_SAMPLE_COUNTER_H_*/
