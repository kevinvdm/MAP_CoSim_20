/*
 * The MIT License
 *
 * Copyright 2017-2018 Norwegian University of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <fmi4cpp/fmi4cpp.hpp>
#include <cmath>
#include "PWMRead.hpp"
#include <unistd.h>
#include <time.h>
#include <thread>
#include <chrono>

#include <iostream>
#include <fstream>
#include <string>

using namespace fmi4cpp;

const double stop = 1800;
const double stepSize = 1E-2;

std::ofstream myfile;

int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
	return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) - ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

uint64_t get_posix_clock_time()
{
	struct timespec ts;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
		return (uint64_t) (ts.tv_sec * 10000000 + ts.tv_nsec / 1000);
	else
		return 0;
}

int main()
{
    myfile.open("output.csv", std::ofstream::out | std::ofstream::trunc);
    const std::string fmuPath = "./Controller_Seperate_Step.fmu";
    PWMRead pwmReader;
    fmi2::fmu fmu(fmuPath);
    auto cs_fmu = fmu.as_cs_fmu();
    auto md = cs_fmu->get_model_description();

    auto slave1 = cs_fmu->new_instance();

    std::vector<fmi2ValueReference> vr1;
    std::vector<fmi2ValueReference> vr2;
    std::vector<fmi2Real> ref1 = std::vector<fmi2Real>(1);
    std::vector<fmi2Real> ref2 = std::vector<fmi2Real>(1);

    std::cout << "model_identifier=" << slave1->get_model_description()->model_identifier << std::endl;

    slave1->setup_experiment();
    slave1->enter_initialization_mode();
    slave1->exit_initialization_mode();

    vr1 = {
            md->get_variable_by_name("Throttle").value_reference,
	    md->get_variable_by_name("Vdesired").value_reference
    };
    vr2 = {
            md->get_variable_by_name("Velocity").value_reference
    };


    double t = 0;
    float_t v = 0;
    struct timespec begin, end;
    uint64_t prev_time_value, time_value;
    uint64_t time_diff;
    time_value = get_posix_clock_time();
    while ((t = slave1->get_simulation_time()) <= stop) {
	if ((prev_time_value - time_value) >= 10000) 
        {
            time_value = get_posix_clock_time();
	    std::cout << "Realtimediff=" << timespecDiff(&end, &begin) << std::endl;
            slave1->step(stepSize);
            v = pwmReader.readFrequency();
	    ref2[0] = v/90 * 0.066 * M_PI;
            slave1->write_real(vr2, ref2);
            slave1->read_real(vr1, ref1);
	    if (ref1[0] == 1)
	    {
	    	pwmReader.writePWM(0.9999);
	    }
	    else if (ref1[0] == 0)
	    {
		pwmReader.writePWM(ref1[0]);
	    }
	    else 
	    {
		pwmReader.writePWM(ref1[0]);
	    }
	    if (t <= 0.05)
	    {
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		//std::cout << "i got here 0.01" << std::endl;
		myfile << t << "," << ref1[0] << "," << ref1[1] << "," << ref2[0] << "," << v << "," << millis << "\n";
            }
	    else
	    {
		//std::cout << "i got here too" << std::endl;
		myfile << t << "," << ref1[0] << "," << ref1[1] << "," << ref2[0] << "," << v << "\n";
	    }
	    std::cout << "Time=" << t << ", Throttle=" << ref1[0] << ", Vdesired="  << ref1[1]  << ", Velocity=" << ref2[0] << std::endl;
	}
	prev_time_value = get_posix_clock_time(); 
   }

    std::cout << "FMU '" << fmu.model_name() << "' terminated with success: " << (slave1->terminate() == 1 ? "true" : "false") << std::endl;

    return 0;
}
