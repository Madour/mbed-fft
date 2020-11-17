/**
 * @file utils.h
 * @author Modar Nasser
 * 
 * @copyright File under MIT license
 * 
 */

#ifndef UTILS_H
#define UTILS_H

// macros pour remplir automatiquement le tableau des entiers inversés
#define R2(n)   n,        n + 0b10000000,     n + 0b01000000,     n + 0b11000000
#define R4(n)   R2(n), R2(n + 0b00100000), R2(n + 0b00010000), R2(n + 0b00110000)
#define R6(n)   R4(n), R4(n + 0b00001000), R4(n + 0b00000100), R4(n + 0b00001100)


// inverse un int de 32 bits
unsigned int reverseBits(unsigned int num) ;

// calcul le log2 , utiliser cette fonction dans le cas où le compilateur ne reconnait pas std::log2
float myLog2(float n);

#endif
