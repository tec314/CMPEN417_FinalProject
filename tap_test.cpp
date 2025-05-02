#include "tap_fir.h"
#define LENGTH 25
#define KERNEL_SIZE 25

int main(){
    //int input_real[25]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    FIR input_img[25]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    
    FIR input_real[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    //int input_img[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    FIR_OUT output_real[25]={};
    FIR_OUT output_img[25]={};

    FIR coef_real[KERNEL_SIZE]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    FIR coef_img[KERNEL_SIZE]={25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};


    top_fir(input_real,input_img,coef_real, coef_img, output_img,output_real);

    for (int i=0; i<LENGTH; i++){
        printf("output %d real part: %x img part: %x \n",i,output_real[i],output_img[i]);
    }

    return 0;

}