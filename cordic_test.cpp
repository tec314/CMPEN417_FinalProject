#include "cordic.h"

int main(){
    FIR_OUT cos = 5;
    FIR_OUT sin = -3;
    float test_mag, test_theta, test_cos, test_sin;
    top_cordic_rotator(cos, sin,&test_mag,&test_theta);
    test_cos=(float)cos;
    test_sin=(float)sin;
    printf("test cos %f \n",test_cos);
    printf("test sin %f \n",test_sin);
    printf("test angle %f \n",test_theta);
    printf("test magnitude %f \n",test_mag);

    return 0;
}
