/*
 * File Name: helper.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include "helper.h"
#include <genesis.h>

// Bit-wise Functions

void toggle(u32 *bits, u8 bit) {
    *bits ^= 1 << bit;
}

u8 bit(u32 bits, u8 bit) {
    return (bits & (1 << bit)) >> bit;
}
