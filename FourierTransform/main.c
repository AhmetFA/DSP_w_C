#include <stdio.h>
#include <stdlib.h>

#define Signal_length 1024


extern double Sine_wave_1024s_look_up_table[1024];
extern double InputSignal_f32_1kHz_15kHz[320];


double sine_wave_dft_r[1024];
double sine_wave_dft_i[1024];
double restored_sine_wave[1024];
double Sine_wave_1024s[1024];

extern void dft_calc(double *src_sig,double *dest_sig_r, double *dest_sig_i, int sig_length);
extern void idft_calc(double *src_sig_r, double *src_sig_i, double *dest_sig, int idft_length);
extern void abs_val_calc(double *src_sig_r,double *src_sig_i,double *dest_sig_mag_arr,int sig_length);
extern void wave_to_file( char file_name[8], double *signal, int sig_length);

int main()
{
    FILE *sine_wave_pt, *sine_wave_dft_r_pt, *restored_sine_pt;
    ///////////////////////////////////////////////////////////
    for(int i=0;i<Signal_length;i++)
    {
       Sine_wave_1024s[i]=Sine_wave_1024s_look_up_table[i];
    }
    ///////////////////////////////////////////////////////////
    sine_wave_pt = fopen("sine_wave.dat"  , "w");


    for(int i=0;i<Signal_length;i++)
    {
        fprintf(sine_wave_pt,"%f \n",Sine_wave_1024s[i]);
    }
    fclose(sine_wave_pt);
///////////////////////////////////////////////////////////////////////////////////
    dft_calc(Sine_wave_1024s ,sine_wave_dft_r, sine_wave_dft_i, Signal_length);

    sine_wave_dft_r_pt = fopen("sine_wave_dft_r.dat"  , "w");


    for(int i=0;i<Signal_length;i++)
    {
        fprintf(sine_wave_dft_r_pt,"%f \n",sine_wave_dft_r[i]);
    }
    fclose(sine_wave_dft_r_pt);
/////////////////////////////////////////////////////////////////////////////////////
   idft_calc(sine_wave_dft_r, sine_wave_dft_i, restored_sine_wave, Signal_length);

    restored_sine_pt = fopen("restored_sine_wave.dat"  , "w");


    for(int i=0;i<Signal_length;i++)
    {
        fprintf(restored_sine_pt,"%f \n",restored_sine_wave[i]);
    }
    fclose(restored_sine_pt);

    wave_to_file( "sig_out.dat", restored_sine_wave, Signal_length);

    return 0;
}
