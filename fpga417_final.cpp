#include "fpga417_final.h"
#include "tap_fir.h"
#include "cordic.h"
#include <hls_stream.h>

void fpga417_fir(int input_real[25], int input_img[25], float output_mag[LENGTH], float output_phase[LENGTH])
{
#pragma HLS INTERFACE mode=m_axi port=input_real offset=slave bundle=gmem0
#pragma HLS INTERFACE mode=m_axi port=input_img offset=slave bundle=gmem1
#pragma HLS INTERFACE mode=m_axi port=output_mag offset=slave bundle=gmem2
#pragma HLS INTERFACE mode=m_axi port=output_phase offset=slave bundle=gmem3
#pragma HLS INTERFACE mode=s_axilite port=return bundle=BUS_A
#pragma HLS DATAFLOW


    hls::stream<int> img_stream;
    hls::stream<int> real_stream;

    top_fir(input_real, input_img, img_stream, real_stream);
    top_cordic_rotator(real_stream, img_stream, output_mag, output_phase);
}