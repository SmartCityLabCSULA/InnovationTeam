#include <cmath>
#include <iostream>

//#include "simulation/hw/schmitt_trigger.h"

int main(int arcg, char *argv[])
{
    double run_time = 50.0; // seconds
    double sample_rate = 0.0005; // seconds
    int samples = int (run_time / sample_rate);
    double sine_wave[samples];
    double frequency = 30;
    double time[samples];
    double t = 0.0;

    // Create the sine wave
    for (int i = 0; i < samples ; i++)
    {
        t = double (i);
        t *= sample_rate;
        time[i] = t;
        sine_wave[i] = 0.5 * (1 + std::sin(2*M_PI*frequency*t));
        std::cout << sine_wave[i] << "," << t << std::endl;
    }

    // Get the pulses from the sine wave using the Schmitt trigger
    double pulses[samples];


    // schmitt_trigger::schmitt(

    return 0;
}
