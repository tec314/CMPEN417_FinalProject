#include <ap_fixed.h>


typedef ap_fixed<32,17> FIXED_POINT;
typedef ap_fixed<32, 32> FIR_OUT;

void top_cordic_rotator(FIR_OUT cos, FIR_OUT sin, float *mag, float *theta);
//void top_cordic_rotator(hls::stream<int>&input_img, hls::stream<int>&input_real, float* output_res, FIXED_POINT output_img);

void cordic_rotator(FIXED_POINT cos, FIXED_POINT sin, FIXED_POINT *mag, FIXED_POINT *theta);