#include <stdio.h>
#include <stdlib.h>

#define Signal_length 320
extern double InputSignal_f32_1kHz_15kHz[320];
extern double mean_calc (double *source_arr, int length);

int main()
{
    double sig_mean = 0;

    sig_mean = mean_calc( InputSignal_f32_1kHz_15kHz, Signal_length);
    printf("Hello signal mean : %f\n",sig_mean);

    return 0;
}

double mean_calc (double *source_arr, int length)
{
    double mean = 0.0;

    for(int i = 0 ; i < length ; i++)
    {
        mean = mean + source_arr[i];
    }

    mean = mean/length;

    return mean;
}
