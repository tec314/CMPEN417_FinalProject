#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>

#define LENGTH 25

const int KERNEL_SIZE=25;


//typedef ap_fixed<32,17> FIXED_POINT;

//void fpga417_fir(int* input_real, int* input_img, int* kernel_real, int* kernel_img, int output_mag, int output_real, int input_length);

void top_fir(int* input_real, int* input_img, int kernel_real[KERNEL_SIZE], int kernel_img[KERNEL_SIZE], int output_img[25], int output_real[25]);

void fir(int input_real, int *output_real, int taps_real[KERNEL_SIZE], int input_img, int *output_img, int taps_img[KERNEL_SIZE]);

//void top_cordic_rotator(hls::stream<int>&input_img, hls::stream<int>&input_real, float* output_res, float* output_img, int length);