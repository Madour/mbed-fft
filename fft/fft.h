/**
 * @file fft.h
 * @author Modar Nasser
 * 
 * @copyright File under MIT license
 * 
 */

#ifndef FFT_H
#define FFT_H

#include <complex>

#define PI 3.14159265358979323846

// fréquences audible jusque 20kHz, on prend le double pour la fréquence d'échantillonage
const int sampling_freq = 40000;

// fft sur 2^10 échantillons
const int samples_nb = 1024;

// remplit W en calculant les twiddles factors
void initTwiddleFactors();

/* Calcul la FFT sur le tableau d'échantillon donnée.
 * On remarque un décalage (de 100 Hz en basse fréquence qui monte 
 * jusque plus de 300 Hz en haute fréquence) entre les fréquence calculée
 * par cette fonction et les fréquence réelles
 */
void FFT(std::complex<float>* data_array);

#endif
