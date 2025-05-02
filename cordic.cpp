#include "cordic.h"
#include "tap_fir.h"

const int NUM_ITERATIONS=15;

void top_cordic_rotator(hls::stream<int>&cos, hls::stream<int>&sin, float mag[LENGTH], float theta[LENGTH]){
    for (int i=0; i<LENGTH; i++){
        FIXED_POINT cos_fixed, sin_fixed, mag_fixed, theta_fixed;
        int temp_cos, temp_sin;

        // cos_fixed=(FIXED_POINT)cos;
        // sin_fixed=(FIXED_POINT)sin;
        cos.read(temp_cos);
        sin.read(temp_sin);
        cos_fixed=(FIXED_POINT)temp_cos;
        sin_fixed=(FIXED_POINT)temp_sin;

        cordic_rotator(cos_fixed, sin_fixed, &mag_fixed, &theta_fixed);

        mag[i]=mag_fixed.to_float();
        theta[i]=theta_fixed.to_float(); 
    }
}

void cordic_rotator(FIXED_POINT cos, FIXED_POINT sin, FIXED_POINT *mag, FIXED_POINT *theta){
    const FIXED_POINT atan_table[NUM_ITERATIONS] = {
    0.7853981633974483,  // arctan(2^-0)
    0.4636476090008061,  // arctan(2^-1)
    0.24497866312686414,
    0.12435499454676144,
    0.06241880999595735,
    0.031239833430268277,
    0.015623728620476831,
    0.007812341060101111,
    0.0039062301319669718,
    0.0019531225164788188,
    0.0009765621895593195,
    0.0004882812111948983,
    0.00024414062014936177,
    0.00012207031189367021,
    0.00006103515617420877
};

    //Set initial vector to rotate
    FIXED_POINT current_cos = cos;
    FIXED_POINT current_sin = sin;
    FIXED_POINT theta_rotated = 0.0;

    //Radiance of 90 degrees
    FIXED_POINT ninety = 1.5708;

    //Radiance of 360 degrees
    FIXED_POINT circle = 6.28319;
    FIXED_POINT scaling_factor = 0.60735;

    //Determine and rotate based on which quadrant you're in
    if (current_cos<=0 && current_sin>0)
    {
        // 2nd quadrant
        // Rotate -90 degrees

        //Swap the sin and cos properly to indicate how it moved in the quadrants
        FIXED_POINT temp = current_cos;
        current_cos = current_sin;
        current_sin = -temp;

        //Add the ninety degree rotation to the total rotated
        theta_rotated += ninety;
    }
    else if (current_cos<0 && current_sin<=0)
    {
        // 3rd quadrant
        // Rotate +180 degrees

        current_cos = -current_cos;
        current_sin = -current_sin;
        theta_rotated += (ninety+ninety);
    }
    else if (current_cos>=0 && current_sin<0)
    {
        // 4th quadrant
        // Rotate +90 degrees

        //Swap sin and cos accordingly to swap from 4th to 1st quadrant
        FIXED_POINT temp = current_cos;
        current_cos = -current_sin;
        current_sin = temp;

        //Update the theta rotated by adding 270 degrees
        theta_rotated += (circle-ninety);
    }
    
    //Iteratively rotate to try and get vector as close to +x axis as possible
    for (int i=0; i<NUM_ITERATIONS; i++) {
        //#pragma HLS PIPELINE II=1
        FIXED_POINT shift_cos = current_cos >> i;
        FIXED_POINT shift_sin = current_sin >> i;

        if (current_sin > 0) {
            // Rotate clockwise
            FIXED_POINT temp = current_cos;
            current_cos += shift_sin;
            current_sin -= shift_cos;
            theta_rotated += atan_table[i];
        } else {
            // Rotate counterclockwise
            FIXED_POINT temp = current_cos;
            current_cos -= shift_sin;
            current_sin += shift_cos;
            theta_rotated -= atan_table[i];
        }
    }

    // Apply scaling factor (1 multiplication allowed)
    current_cos = current_cos * scaling_factor;

    // Write result back as fixed-point
    *mag = current_cos;
    *theta = theta_rotated; 
}
