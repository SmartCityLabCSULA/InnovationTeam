#ifndef HW_SCHMITT_TRIGGER_H
#define HW_SCHMITT_TRIGGER_H

namespace schmitt_trigger
{
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
#endif // HW_SCHMITT_TRIGGER_H
