#include "fpga417_final.h"
#define LENGTH 25
#define KERNEL_SIZE 25

int main()
{
    int input_real[25]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    //int input_img[25]=   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    //int input_real[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int input_img[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    float output_mag[25];
    float output_phase[25];

    int length=LENGTH;

    fpga417_fir(input_real,input_img,output_mag,output_phase);

    for (int v=0; v<LENGTH; v++)
    {
        printf("output %d  mag: %f  phase: %f \n ", v, output_mag[v], output_phase[v]);
    }
}
