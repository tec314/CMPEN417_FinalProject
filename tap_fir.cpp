#include "tap_fir.h"

// void top_fir(FIR input_real[LENGTH], FIR input_img[LENGTH], FIR kernel_real[KERNEL_SIZE], FIR kernel_img[KERNEL_SIZE], FIR_OUT output_img[LENGTH], FIR_OUT output_real[LENGTH]){
    
//     for (int i=0; i<LENGTH; i++){
//         fir(input_real[i], &output_real[i],  kernel_real, input_img[i], &output_img[i], kernel_img); //Fir calculation
        
//     }
    
    
	
// }
void top_fir(int input_real[LENGTH], int input_img[LENGTH], hls::stream<int>&output_img, hls::stream<int>&output_real){
    // FIR kernel_real[KERNEL_SIZE];
    // FIR kernel_img[KERNEL_SIZE];

    // for(int i=0;i<KERNEL_SIZE;i++)
    // {
    //     kernel_real[i]=(FIR)input_real[i];
    //     kernel_img[i]=(FIR)input_img[i];
    // }

    FIR kernel_real[KERNEL_SIZE]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    FIR kernel_img[KERNEL_SIZE]={25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};

    for (int i=0; i<LENGTH; i++){
        int temp_output_real, temp_output_img, temp_input_real, temp_input_img;
        temp_input_real = (FIR)input_real[i];
        temp_input_img = (FIR)input_img[i];
        fir(temp_input_real, &temp_output_real,  kernel_real, temp_input_img, &temp_output_img, kernel_img); //Fir calculation
        output_real.write(temp_output_real);
        output_img.write(temp_output_img);
    }
    
    
	
}
void fir(FIR input_real, int *output_real, FIR taps_real[KERNEL_SIZE], FIR input_img, int *output_img, FIR taps_img[KERNEL_SIZE]){

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
        //#pragma HLS UNROLL factor=4
        //#pragma HLS PIPELINE II=1
        AB += delay_line_real[i]*taps_real[i];
        ab += delay_line_img[i]*taps_img[i];
        Ab += delay_line_real[i]*taps_img[i];
        aB += delay_line_img[i]*taps_real[i];
    }

    *output_real = AB-ab;
    *output_img = Ab+aB;
}