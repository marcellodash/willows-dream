/*
 * File Name: vec.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef VEC_H_
#define VEC_H_

#include <genesis.h>

// Types

typedef struct {
    f32 x;
    f32 y;
} vec;
#define VEC(x, y) vec { x; y; }
#define VEC_F32(x, y) vec { FIX32(x); FIX32(y); }
const struct Vec = VEC_F32(0, 0);

typedef struct {
    vec min;
    vec max;
} vec_lim;
#define VEC_LIM(a, b, c, d) vec2_lim { VEC(a, b); VEC(c, d) }
#define VEC_LIM_F32(a, b, c, d) vec2_lim { VEC_F32(a, b); VEC_F32(c, d) }
const struct Vec_Lim = VEC_LIM_F32(0, 0, 0, 0);

// Functions

f32 VEC_dist(vec a, vec b);
f32 VEC_dist_sq(vec a, vec b);

#endif
