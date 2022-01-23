#include <stdio.h>
#include <stdlib.h>
#include <math.h>

////////////////Macros//////////////////////////////

////////////////Type Definitions////////////////////
//Real value signal struct
struct real_signal
{
    int     signal_length;
    double *signal_array;//First element of the signal should be equal to pointer
};
//Complex value signal struct
struct comp_signal
{
    int     signal_length;
    double *real_signal_array;//First element of the signal should be equal to pointer
    double *imag_signal_array;//First element of the signal should be equal to pointer
};
////////////////Function prototypes/////////////////
//!!!Caution!!! all signal lenght should be same for input and output signals(except convolution)
//First and second weights of signal
double	mean_calc   (struct real_signal signal);
double	var_calc    (struct real_signal signal);
//Convolution taking function
void  	convolve    (struct real_signal signal_x, struct real_signal signal_y, struct real_signal output_signal);
//integration and derivative
void  	running_sum (struct real_signal input_signal, struct real_signal output_signal);
void  	running_diff(struct real_signal input_signal, struct real_signal output_signal);
//simple fft functions
void  	dft_calc    (struct real_signal input_signal, struct comp_signal  dft_signal);
void  	idft_calc   (struct comp_signal   dft_signal, struct real_signal idft_signal);
//Complex signal absolute value calculator
void  	abs_val_calc(struct comp_signal input_signal, struct real_signal mag_signal);
//Function to write out waves
void  	real_wave_to_file( char file_name[], struct real_signal signal);
void  	comp_wave_to_file( char file_name[], struct comp_signal signal);

////////////////Function bodies/////////////////////

//Mean calculator
double mean_calc(struct real_signal signal)
{
    double mean = 0.0;

    for(int i = 0 ; i < signal.signal_length ; i++)
    {
        mean = mean + signal.signal_array[i];
    }

    mean = mean/signal.signal_length;

    return mean;
	}
//Variance calculator
double var_calc(struct real_signal signal)
{
    double mean = 0.0;
    double var  = 0.0;

    mean = mean_calc(signal);

    for(int i = 0 ; i < signal.signal_length ; i++)
    {
        var = var + pow( (signal.signal_array[i] - mean),2);
    }

    var = var/signal.signal_length;

    return var;
}
//Convolution method
void convolve(struct real_signal signal_x, struct real_signal signal_y, struct real_signal output_signal)
              {
                  for(int i = 0; i < signal_x.signal_length + signal_y.signal_length; i++)
                  {
                  output_signal.signal_array[i]=0;
                  }

                  for(int j =0; j< signal_x.signal_length; j++)
                  {
                        for(int k =0; k< signal_y.signal_length; k++)
                        {
                            output_signal.signal_array[j+k] = output_signal.signal_array[j+k] + signal_x.signal_array[j]*signal_y.signal_array[k];
                        }
                  }

              }
//Taking integral of the signal by running sum(Accumulator)
void running_sum(struct real_signal input_signal, struct real_signal output_signal)
    {
        output_signal.signal_array[0] = 0;
        for(int i = 1; i < input_signal.signal_length; i++)
        {
            output_signal.signal_array[i] = input_signal.signal_array[i] + input_signal.signal_array[i-1];
        }

    }
//Taking derivative of the signal by running difference(Differantiator)
void running_diff(struct real_signal input_signal, struct real_signal output_signal)
    {
        output_signal.signal_array[0] = 0;
        for(int i = 1; i < input_signal.signal_length; i++)
        {
            output_signal.signal_array[i] = input_signal.signal_array[i] - input_signal.signal_array[i-1];
        }
    }
//DFT of a signal for all the signal length
void dft_calc(struct real_signal input_signal, struct comp_signal  dft_signal)
{
  int n,j,k;
  double PI = 3.14159265359;

  for(j=0;j<dft_signal.signal_length;j++)
  {
      dft_signal[j] =0;
      dft_signal[j] =0;

  }

    for(k=0;k<(input_signal.signal_length);k++)
    {
        for(n=0;n<input_signal.signal_length;n++)
        {
            dft_signal.real_signal_array[k] = dft_signal.real_signal_array[k] + input_signal.signal_array[n]*cos(2*PI*k*n/input_signal.signal_length);
            dft_signal.imag_signal_array[k] = dft_signal.imag_signal_array[k] - input_signal.signal_array[n]*sin(2*PI*k*n/input_signal.signal_length);
        }
    }


}
//Inverse DFT of a signal
void idft_calc(struct comp_signal dft_signal, struct real_signal idft_signal)
{
	  double PI = 3.14159265359;
      int n,k;

      for(k=0;k<dft_signal.signal_length;k++)
      {
          dft_signal.real_signal_array[k] =  dft_signal.real_signal_array[k]/(sig_length);
          dft_signal.imag_signal_array[k] = -dft_signal.imag_signal_array[k]/(sig_length);
      }

      for(n=0;n <dft_signal.signal_length;n++)
      {
          dest_sig[n]=0;
      }

      for(k=0;k<dft_signal.signal_length;k++)
      {
          for(n=0;n<dft_signal.signal_length;n++)
          {
              idft_signal.signal_array[n] = idft_signal.signal_array[n]+ dft_signal.real_signal_array[k]*cos(2*PI*k*n/dft_signal.signal_length);
              idft_signal.signal_array[n] = idft_signal.signal_array[n]+ dft_signal.imag_signal_array[k]*sin(2*PI*k*n/dft_signal.signal_length);

          }
      }
 }
//Absolute value calculator
void abs_val_calc(struct comp_signal input_signal, struct real_signal mag_signal)
 {
     int n;

     for(n=0;n<input_signal.signal_length;n++)
     {
         mag_signal.signal_array[n] = sqrt(pow(input_signal.signal_array[n],2)+pow(input_signal.signal_array[n],2));
     }
 }

//File write out
//real signals
void real_wave_to_file( char file_name[], struct real_signal signal)
{
    FILE *wave2file_pt;

    wave2file_pt = fopen(file_name, "w");


    for(int i=0;i<signal.signal_length;i++)
    {
        fprintf(wave2file_pt,"%f \n",signal.signal_array[i]);
    }
    fclose(wave2file_pt);
}
//complex signals
void  	comp_wave_to_file( char file_name[], struct comp_signal signal);
{
    FILE *wave2file_pt;

    wave2file_pt = fopen(file_name, "w");


    for(int i=0;i<signal.signal_length;i++)
    {
        fprintf(wave2file_pt,"r : %f 	i: %f\n",signal.real_signal_array[i],signal.imag_signal_array);
    }
    fclose(wave2file_pt);
}