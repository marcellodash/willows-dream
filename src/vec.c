/*
 * File Name: vec.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "vec.h"

// NOTE: If this function is not used, change #define MATH_BIG_TABLES to 0 and comment out
f32 VEC_dist(vec a, vec b) {
    return fix16Sqrt(fix32ToFix16(VEC_dist_sq(a, b)));
}
f32 VEC_dist_sq(vec a, vec b) {
    return fix32Add(fix32Mul(fix32Sub(a.x, b.x), fix32Sub(a.x, b.x)), fix32Mul(fix32Sub(a.y, b.y), fix32Sub(a.y, b.y)));
}

// TODO: More basic vector operations
