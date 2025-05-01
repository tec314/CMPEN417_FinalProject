#include "fpga417_final.h"

// void fpga417_fir(int* input_real, int* input_img, int* kernal_real, int* kernal_img, float* output_mag, float* output_real, int input_length)
// {

// #pragma HLS DATAFLOW



//     //hls::stream<int> img_stream;
//     //hls::stream<int> real_stream;

//     top_fir(input_real, input_img, kernal_real, kernal_img, img_stream, real_stream, input_length);
//     //top_cordic_rotator(img_stream, real_stream, output_real, output_img, input_length);
// }

void top_fir(FIR input_real[LENGTH], FIR input_img[LENGTH], FIR kernel_real[KERNEL_SIZE], FIR kernel_img[KERNEL_SIZE], FIR_OUT output_img[LENGTH], FIR_OUT output_real[LENGTH]){
    
    for (int i=0; i<LENGTH; i++){
        fir(input_real[i], &output_real[i],  kernel_real, input_img[i], &output_img[i], kernel_img); //Fir calculation
        
    }
    
    
	
}
void fir(FIR input_real, FIR_OUT *output_real, FIR taps_real[KERNEL_SIZE], FIR input_img, FIR_OUT *output_img, FIR taps_img[KERNEL_SIZE]){

    static FIR delay_line_real[KERNEL_SIZE] = {};
    static FIR delay_line_img[KERNEL_SIZE] = {};

    FIR_OUT AB = 0;
    FIR_OUT ab = 0;
    FIR_OUT Ab = 0;
    FIR_OUT aB = 0;

	for (int i = KERNEL_SIZE-1; i>0; i--){ //Shift the registers
        delay_line_real[i] = delay_line_real[i-1];
        delay_line_img[i] = delay_line_img[i-1];
    }
    
    delay_line_real[0] = input_real;
    delay_line_img[0] = input_img;
    
    for (int i=0; i<KERNEL_SIZE; i++){ //Calculate the output for each part of the calculation

        AB += delay_line_real[i]*taps_real[i];
        ab += delay_line_img[i]*taps_img[i];
        Ab += delay_line_real[i]*taps_img[i];
        aB += delay_line_img[i]*taps_real[i];
    }

    *output_real = AB-ab;
    *output_img = Ab+aB;
}
// void top_cordic_rotator(hls::stream<int>&input_img, hls::stream<int>&input_real, float* output_res, float* output_img, int length){
//     return;
// }
