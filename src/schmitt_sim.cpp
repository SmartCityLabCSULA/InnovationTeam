#include <cmath>
#include <iostream>

#include "simulation/schmitt_trigger.h"
#include "hw/encoder.h"

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
    for (int i = 0; i < samples; i++)
    {
        t = double (i);
        t *= sample_rate;
        time[i] = t;
        sine_wave[i] = 0.5 * (1 + std::sin(2*M_PI*frequency*t));
        std::cout << sine_wave[i] << "," << t << std::endl;
    }

    std::cout << std::endl << std::endl;

    // Get the pulses from the sine wave using the Schmitt trigger
    int pulses[samples];
    double thresh_low = 0.4;
    double thresh_high = 0.6;

    schmitt_trigger_sim::schmitt(sine_wave, thresh_low, thresh_high, pulses, samples);
    for (int i = 0; i < samples; i++)
    {
        std::cout << time[i] << "," << pulses[i] << std::endl;
    }

    std::cout << std::endl << std::endl;


    int ticks = schmitt_trigger_sim::count_pulses(pulses, samples);

    double circumference = 2*M_PI*23.17/2;
    int pulses_per_rev = 4;
    double velocity = encoder::ticks_to_velocity(circumference, frequency,
                                                 ticks, pulses_per_rev);

    std::cout << "Velocity is " << velocity << std::endl;

    return 0;
}
