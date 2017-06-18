/*
 * File Name: vec.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "vec.h"

// General Functions

f32 clamp(f32 x, f32 minimum, f32 maximum) {
    return max(min(x, maximum), minimum);
}

// Vector Functions

vec VEC_add(vec a, vec b) {
    return VEC2D(fix32Add(a.x, b.x), fix32Add(a.y, b.y));
}
vec VEC_sub(vec a, vec b) {
    return VEC2D(fix32Sub(a.x, b.x), fix32Sub(a.y, b.y));
}
vec VEC_mul(vec a, vec b) {
    return VEC2D(fix32Mul(a.x, b.x), fix32Mul(a.y, b.y));
}
vec VEC_div(vec a, vec b) {
    return VEC2D(fix32Div(a.x, b.x), fix32Div(a.y, b.y));
}
vec VEC_scalar_mul(vec a, f32 b) {
    return VEC2D(fix32Mul(a.x, b), fix32Mul(a.y, b));
}
vec VEC_scalar_div(vec a, f32 b) {
    return VEC2D(fix32Div(a.x, b), fix32Div(a.y, b));
}
f32 VEC_dot(vec a, vec b) {
    return fix32Add(fix32Mul(a.x, b.x), fix32Mul(a.y, b.y));
}
f32 VEC_cross(vec a, vec b) {
    return fix32Sub(fix32Mul(a.x, b.x), fix32Mul(a.y, b.y));
}
f32 VEC_dist_sq(vec a, vec b) {
    return VEC_dot(a, b);
}
f32 VEC_dist(vec a, vec b) {
    return fix16Sqrt(fix32ToFix16(VEC_dist_sq(a, b)));
}
f32 VEC_len_sq(vec a) {
    return VEC_dist_sq(a, a);
}
f32 VEC_len(vec a) {
    return VEC_dist(a, a);
}
f32 VEC_unit(vec a) {
    return VEC_scalar_div(a, VEC_len(a));
}
vec VEC_left(vec a) {
    return VEC2D(a.y, fix32Mul(a.x, FIX32(-1)));
}
vec VEC_right(vec a) {
    return VEC2D(fix32Mul(a.y, FIX32(-1)), a.x);
}
vec VEC_rotate(vec a, f32 b) {
    f32 sine = sinFix32(b), cosine = cosFix32(b);
    return VEC2D(fix32Sub(fix32Mul(a.x, cosine), fix32Mul(a.y, sine)), fix32Add(fix32Mul(a.x, sine), fix32Mul(a.y, cosine)));
}
/* No atan2 :'(
vec VEC_angle(vec a) {
    return atan2(a.y, a.x);
}
*/
