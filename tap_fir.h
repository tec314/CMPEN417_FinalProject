#include <ap_fixed.h>
#include <hls_stream.h>
#include "fpga417_final.h"

const int KERNEL_SIZE=25;

typedef ap_fixed<32, 32> FIR_OUT;
typedef ap_fixed<7,7> FIR;

//void top_fir(FIR input_real[LENGTH], FIR input_img[LENGTH], FIR kernel_real[KERNEL_SIZE], FIR kernel_img[KERNEL_SIZE],output_img[25], FIR_OUT output_real[25]);
void top_fir(int input_real[LENGTH], int input_img[LENGTH], hls::stream<int>&output_img, hls::stream<int>&output_real);

void fir(FIR input_real, int *output_real, FIR taps_real[KERNEL_SIZE], FIR input_img, int *output_img, FIR taps_img[KERNEL_SIZE]);