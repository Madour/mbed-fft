# mbed-fft
Compute FFT from microphone samples on mbed / mbed-os

### Usage

An example program using the FFT function.

```c++
#include "mbed.h"
#include "fft.h"

AnalogIn sound_sensor(A0);

Ticker ticker;

std::complex<float> samples_array[samples_nb];

int sample_count = 0;
int compute_fft = 0;

void readSample() {
    if(!compute_fft) {
        samples_array[sample_count] = std::complex<float>(sound_sensor.read());
        sample_count += 1;

        if(sample_count >= samples_nb) {
            sample_count = 0;
            compute_fft = 1;
        }
    }
}

int main() {    
    
    // needed by the FFT
    initTwiddleFactors();
    
    // interrupt, will fill samples_array with input from sound sensor
    ticker.attach(&readSample, 1.0/sampling_freq);

    while(1) {
        if(compute_fft) {
            ticker.detach();    // disable interupt
            
            // compute FFT
            FFT(samples_array);

            // retrive the first harmonic
            int H1_index = 0;

            for(int i = 1; i < samples_nb/2; ++i) {
                samples_array[i] = std::norm(samples_array[i]);
                if(samples_array[i].real() > samples_array[H1_index].real()) {
                    H1_index = i;
                }
            }

            float H1_freq = (float)H1_index * (float)sampling_freq / (float)samples_nb;
            float H1_ampl = std::abs(20*std::log10(samples_array[H1_index].real()) - 50);
            
            // print the results
            printf("Harmonic frequency : %f ; harmonic amplitude %f\n\r", H1_freq, H1_ampl);
     
            compute_fft = 0;
            
            // re enable interrupt
            ticker.attach(&readSample, 1.0/sampling_freq);
        }
        // magic line, program does not work without it
        // (I suspect it prevents compiler optimization to remove while body because it thinks the if condition will never be true)
        pc.printf("\r");
    }
}

```
