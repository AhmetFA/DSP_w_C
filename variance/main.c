#include <stdio.h>
#include <stdlib.h>

#define Signal_length 320

extern double InputSignal_f32_1kHz_15kHz[320];
extern double var_calc (double *source_arr, int length);

int main()
{
    double var = 0;

    var = var_calc(InputSignal_f32_1kHz_15kHz,Signal_length);
    printf("Hello world!\n signal variance is : %f",var);
    return 0;
}
