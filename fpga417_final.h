#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>

#define LENGTH 25

const int KERNEL_SIZE=25;

typedef ap_fixed<32,32> FIR_OUT;
typedef ap_fixed<7,7> FIR;
typedef ap_fixed<32,17> FIXED_POINT;

//void fpga417_fir(int* input_real, int* input_img, int* kernel_real, int* kernel_img, int output_mag, int output_real, int input_length);

void top_fir(FIR* input_real, FIR* input_img, FIR kernel_real[KERNEL_SIZE], FIR kernel_img[KERNEL_SIZE], FIR_OUT output_img[25], FIR_OUT output_real[25]);

void fir(FIR input_real, FIR_OUT *output_real, FIR taps_real[KERNEL_SIZE], FIR input_img, FIR_OUT *output_img, FIR taps_img[KERNEL_SIZE]);

//void top_cordic_rotator(hls::stream<int>&input_img, hls::stream<int>&input_real, float* output_res, float* output_img, int length);