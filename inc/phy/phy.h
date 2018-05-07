/*
 * File Name: phy.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef PHY_H_
#define PHY_H_

#include <genesis.h>
#include "vec.h"

// Maths Tut: https://github.com/Stephane-D/SGDK/wiki/Tuto-Maths
// Maths Header: https://github.com/Stephane-D/SGDK/blob/master/inc/maths.h

// Defaults

#define PHY_APPROX TRUE
#define PHY_FPS (FIX32(60))
#define PHY_TIMESTEP (fix32Div(FIX32(1), PHY_FPS))
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

typedef struct PHY_entity {
    PHY_shape shape;
    PHY_mass mass;
    PHY_material material;

    vec pos;
    vec vel;
    vec force;
    f32 rotation;

    u16 layers; // layers bitmask
    // TODO: Define physics collision layers
} PHY_entity;
const struct PHY_Entity = {
    PHY_Shape, PHY_Mass, PHY_Material,
    VEC_F32(0, 0), VEC_F32(0, 0), VEC_F32(0, 0), FIX32(0),
    0
};

typedef struct PHY_pair {
    PHY_entity *a;
    PHY_entity *b;
} PHY_pair;
#define PHY_PAIR(a, b) PHY_pair { a; b; }

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

// Core Functions

u8 PHY_update(PHY_entity *e);
u8 PHY_generatePairs();

#endif
