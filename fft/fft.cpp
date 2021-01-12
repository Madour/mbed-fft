/**
 * @file fft.cpp
 * @author Modar Nasser
 * 
 * @copyright File under MIT license
 * 
 */

#include "fft.h"
#include "utils.h"

// W est le tableau des twiddle factor, ce facteur représente le vecteur unité qui tourne 
// sur le cercle trigo. Il permet d'ajuster la phase des coeff sans changer leur amplitude
std::complex<float> W[FFT_SAMPLES_NB>>1];

void initTwiddleFactors() {
    // calcul des "twiddle factor" qui seront multipliés aux coeffs
    W[0] = 1;
    W[1] = std::polar<float>(1., -2. * PI / FFT_SAMPLES_NB);
    for(int i = 2; i < FFT_SAMPLES_NB>>1; ++i)
        W[i] = std::pow(W[1], i);
}


void FFT(std::complex<float>* samples_array) {
    // on ordonne le tableau d'échantillons par les indices inversés 
    // (i.e. : 000, 100, 010, 110, 001, 101, 011, 111 etc ...)
    for(int i = 0; i < FFT_SAMPLES_NB; ++i) {
        int ri = ( reverseBits(i) >> (sizeof(unsigned int)*8 - (int)std::log2(FFT_SAMPLES_NB)) );
        if(ri > i) {
            std::complex<float> t = samples_array[i];
            samples_array[i] = samples_array[ri];
            samples_array[ri] = t;
        }
    }

    int n = 1;
    int a = FFT_SAMPLES_NB >> 1;

    // début des calculs croisés de la méthode butterfly
    for(int j = 0; j < std::log2(FFT_SAMPLES_NB); ++j) {
        for(int i = 0; i < FFT_SAMPLES_NB; ++i) {
            if(!(i & n)) {
                std::complex<float> temp1 = samples_array[i];
                std::complex<float> temp2 = W[(i * a) % (FFT_SAMPLES_NB>>1)] * samples_array[i + n];
                samples_array[i] = temp1 + temp2;
                samples_array[i + n] = temp1 - temp2;
            }
        }
        n <<= 1; a >>= 1;
    }
}
