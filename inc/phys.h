/*
 * File Name: phys.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef PHYS_H_
#define PHYS_H_

#include <genesis.h>
#include "vec.h"

// Maths Tut: https://github.com/Stephane-D/SGDK/wiki/Tuto-Maths
// Maths Header: https://github.com/Stephane-D/SGDK/blob/master/inc/maths.h

// Defaults

#define PHY_APPROX TRUE
#define PHY_STEP (fix32Div(FIX32(1), FIX32(60)))
#define PHY_POS_CORRECTION_PERC (FIX32(0.2)) // Usually 20% to 80%
#define PHY_POS_CORRECTION_SLOP (FIX32(0.01)) // Usually 0.01 to 0.1

// Scale Constants

#define PHY_SCALE_F32 (FIX32(1.5) / TILE_SIZE) // meters/pixels; main character is 1 tiles tall (32px) and average height of a 13 year old girl is 156 cm
#define PHY_SCALE_F16 (f32ToFix16(PHY_SCALE_F32))
#define PHY_SCALE_INT (f32ToRoundedInt(PHY_SCALE_F32))
#define PHY_SCALE PHY_SCALE_F32

// Scale Conversions

#define f32ToM(value) (f32Mul(value, PHY_SCALE_F32))
#define mToFix32(value) (f32Div(value, PHY_SCALE_F32))
#define intToM(value) (f32ToM(intToFix32(value)))
#define mToInt(value) (f32ToRoundedInt(mToFix32(value)))

// Physics Entity Types

#define PHY_TYPE_NONE 0
#define PHY_TYPE_POINT 1
#define PHY_TYPE_RECT 2
#define PHY_TYPE_CIRCLE 3

typedef struct PHY_entity {
    u8 type;
    vec pos;
    vec vel;
    vec acc;
    f32 rotation;
    f32 mass;
    f32 restitution;
    f32 inv_mass;
} PHY_entity;
const struct PHY_Entity = {
    PHY_TYPE_POINT, VEC_F32(0, 0), VEC_F32(0, 0), VEC_F32(0, 0), FIX32(0), FIX32(0), FIX32(0), FIX32(0)
};

typdef struct PHY_rect {
    struct PHY_entity;
    vec size;
} PHY_rect;
const struct PHY_Rect = {
    PHY_TYPE_RECT, VEC_F32(0, 0), VEC_F32(0, 0), VEC_F32(0, 0), FIX32(0), FIX32(0), FIX32(0), FIX32(0), VEC_F32(0, 0)
};

typedef struct PHY_circle {
    struct PHY_entity;
    f32 radius;
} PHY_circle;
const struct PHY_Circle = {
    PHY_TYPE_CIRCLE, VEC_F32(0, 0), VEC_F32(0, 0), VEC_F32(0, 0), FIX32(0), FIX32(0), FIX32(0), FIX32(0), FIX32(0)
};

PHY_entity PHY_init_entity(f32 mass, f32 restitution);
PHY_rect PHY_init_rect(f32 mass, f32 restitution, vec size);
PHY_circle PHY_init_circle(Sprite spr, f32 mass, f32 restitution, f32 radius);

// Bounds

vec_lim PHY_bounds(PHY_entity a, PHY_entity b);
vec_lim PHY_bounds_vec(vec v);
vec_lim PHY_bounds_point(PHY_entity e);
vec_lim PHY_bounds_rect(PHY_rect e);
vec_lim PHY_bounds_circle(PHY_circle e);

// Collision Detection

u8 PHY_collision(PHY_entity a, PHY_entity b);
u8 PHY_collision_bounds(vec_lim a, vec_lim b);
u8 PHY_collision_point(PHY_entity a, PHY_entity b, u8 approx);
u8 PHY_collision_rect(PHY_rect a, PHY_rect b);
u8 PHY_collision_rect_point(PHY_rect a, PHY_entity b, u8 approx);
u8 PHY_collision_circle(PHY_circle a, PHY_circle b);
u8 PHY_collision_circle_point(PHY_circle a, PHY_entity b);
u8 PHY_collision_circle_rect(PHY_circle a, PHY_rect b);

// Impulse Resolution

vec PHY_momentum(PHY_entity e);
f32 PHY_impulse(PHY_entity a, PHY_entity b);
u8 PHY_resolve(PHY_entity *a, PHY_entity *b);

// Manifold Generation

typedef struct PHY_manifold {
    PHY_entity *a;
    PHY_entity *b;
    f32 penetration;
    vec normal;
} PHY_manifold;

u8 PHY_manifold_circle_circle(PHY_manifold *m);
u8 PHY_manifold_rect_rect(PHY_manifold *m);

#endif
