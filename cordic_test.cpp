#include "cordic.h"

int main(){
    FIR_OUT cos = 5;
    FIR_OUT sin = 3;
    float test_mag, test_theta;
    top_cordic_rotator(cos, sin,&test_mag,&test_theta);
    printf("test_cos %f \n",cos);
    printf("test_sin %f \n",sin);
    printf("test angle %f \n",test_theta);
    printf("test magnitude %f \n",test_mag);

    return 0;
}
