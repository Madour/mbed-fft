/**
 * @file utils.cpp
 * @author Modar Nasser
 * 
 * @copyright File under MIT license
 * 
 */

#include "utils.h"
#include <cmath>

// Pour inverser les bits d un nombre de X octets, il suffit de connaitre l'ordre inverse des bits
// sur un octet. On applique cet ordre sur le nombre en le séparant en morceaux de 1 octet.
unsigned char reversed_table[256] = { R6(0b0), R6(0b10), R6(0b01), R6(0b11) };

unsigned int reverseBits(unsigned int num) { 
    return reversed_table[(num >> 0) & 0xff] << 24 |
            reversed_table[(num >> 8) & 0xff] << 16 |
            reversed_table[(num >> 16) & 0xff] << 8 |
            reversed_table[(num >> 24) & 0xff] << 0 ;
}

float myLog2(float n) {
    return std::log(n) / std::log(2.0);
}
