#include <stdio.h>
#include <stdlib.h>

#define Signal_length 320
#define imp_resp_length 29
#define Output_signal_length 349

extern double InputSignal_f32_1kHz_15kHz[320];
extern double Impulse_response[29];
extern double var_calc (double *source_arr, int length);
extern void convolve(double *Input_Signal, double *Filter_response, double *Output_Signal, int input_signal_len,int filter_response_len);

int main()
{
    double Convolution_Output_Signal[349];

    FILE *input_sig_pt, *imp_res_pt,*Convolution_Output_Signal_pt;

    input_sig_pt = fopen("in_sig.dat"  , "w");
    imp_res_pt   = fopen("imp_res.dat" , "w");
    Convolution_Output_Signal_pt = fopen("conv_out_sig.dat", "w");

    for(int i=0;i<Signal_length;i++){
        fprintf(input_sig_pt,"%f \n",InputSignal_f32_1kHz_15kHz[i]);
    }
    fclose(input_sig_pt);

    for(int i=0;i<imp_resp_length;i++){
        fprintf(imp_res_pt,"%f \n",Impulse_response[i]);
    }
    fclose(imp_res_pt);

    convolve(InputSignal_f32_1kHz_15kHz,Impulse_response,Convolution_Output_Signal,320,29);

    for(int i=0;i<Output_signal_length;i++){
        fprintf(Convolution_Output_Signal_pt,"%f \n",Convolution_Output_Signal[i]);
    }
    fclose(imp_res_pt);

    return 0;
}
