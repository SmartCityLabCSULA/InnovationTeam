#ifndef SIMULATION_SCHMITT_TRIGGER_H

#include <cmath>

// Simulates a Schmitt trigger (https://en.wikipedia.org/wiki/Schmitt_trigger).
// Converts a voltage to a 1 or 0 (high or low) based on the voltage 
// thresholds.
//
// Parameters:
// @voltage (double): the voltage reading
// @thresh_low (double): the voltage value to be considered a 0
// @thresh_high (double): the voltage value to be considered a 1
//
// Returns:
// @logic_val (int): 0 (low), 1 (high)
//
int schmitt_trigger(double voltage, double thresh_low, double thresh_high)
{
    
}

#endif // SIMULATION_SCHMITT_TRIGGER_H
