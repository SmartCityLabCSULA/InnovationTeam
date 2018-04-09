#ifndef SIMULATION_SCHMITT_TRIGGER_H

namespace schmitt_trigger
{
// Simulates a Schmitt trigger (https://en.wikipedia.org/wiki/Schmitt_trigger)
// Converts a voltage to a 1 or 0 (high or low) based on the voltage 
// thresholds.
//
// Parameters:
// @voltage (double array): the voltage reading (needs to be the same size of 
//      logic)
// @thresh_low (double): the voltage value to be considered a 0
// @thresh_high (double): the voltage value to be considered a 1
// @logic (double array): this array is the output of the Schmitt trigger 
//      (needs to be the same size as voltage)
// @length (int): length of the voltage and logic arrays
//
void schmitt(double voltage[], double thresh_low, double thresh_high, 
             int logic[], int length)
{
    bool limit = false;
    for(int i = 0; i < length; i++)
    {
        if (limit == false)
        {
            logic[i] = 0;
        }
        else 
        {
            logic[i] = 1;
        }

        if (voltage[i] <= thresh_low)
        {
            limit = false;
            logic[i] = 0;
        }
        else if (voltage[i] >= thresh_high)
        {
            limit = true;
            logic[i] = 1;
        }
    }
}

int count_pulses(int wave[], int length)
{
    int num_pulses = 0;
    int prev_pulse = wave[1];
    
    for (int i = 1; i < length; i++)
    {
        if (wave[i] != prev_pulse && wave[i] != 0)
        {
            num_pulses += 1;
        }

    }

    return num_pulses;
}
} // namespace schmitt_trigger
#endif // SIMULATION_SCHMITT_TRIGGER_H
