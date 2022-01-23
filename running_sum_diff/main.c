#include <stdio.h>
#include <stdlib.h>

#define Signal_length 320
#define imp_resp_length 2
#define Calc_Output_signal_length 320
#define Conv_Output_signal_length 321

extern double InputSignal_f32_1kHz_15kHz[320];


extern void convolve(double *Input_Signal, double *Filter_response, double *Output_Signal, int input_signal_len,int filter_response_len);
extern void running_sum (double *Input_Signal, double *Output_Signal, int input_signal_length);

int main()
{
double Impulse_response[2] = {-1 , 1};
double calc_out_sig[320];
double conv_out_sig[321];
    FILE *Conv_Output_Signal_pt, *Calc_Output_signal_pt;

    Conv_Output_Signal_pt = fopen("calc_out.dat" , "w");
    Calc_Output_signal_pt = fopen("conv_out.dat" , "w");

    running_sum ( InputSignal_f32_1kHz_15kHz, calc_out_sig, 320);

    for(int i=0;i<Calc_Output_signal_length;i++){
        fprintf(Calc_Output_signal_pt,"%f \n",calc_out_sig[i]);
    }
    fclose(Calc_Output_signal_pt);

    convolve(InputSignal_f32_1kHz_15kHz,Impulse_response,conv_out_sig,320,2);

    for(int i=0;i<Conv_Output_signal_length;i++){
        fprintf(Conv_Output_Signal_pt,"%f \n",conv_out_sig[i]);
    }
    fclose(Conv_Output_Signal_pt);

    return 0;
}
