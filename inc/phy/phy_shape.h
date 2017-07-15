/*
 * File Name: phy_shape.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef PHY_SHAPE_H_
#define PHY_SHAPE_H_

#include <genesis.h>
#include "phy/phy.h"
#include "vec.h"

#define PHY_SHAPE_NONE 0
#define PHY_SHAPE_PARTICLE 1
#define PHY_SHAPE_RECTANGLE 2
#define PHY_SHAPE_CIRCLE 3

typedef struct PHY_shape {
    u8 type;
    vec pos;

    // Specific type variables
    vec dimensions; // For rectangle
    f32 radius; // For circle
} PHY_shape;
const struct PHY_Shape = {
    PHY_SHAPE_NONE, VEC_F32(0, 0), VEC_F32(0, 0), FIX32(0)
};

// Constructors

PHY_shape PHY_particle();
PHY_shape PHY_rectangle(f32 width, f32 height);
PHY_shape PHY_circle(f32 radius);

// Bounds

vec_lim PHY_bounds(PHY_shape s);
vec_lim PHY_bounds_vec(vec v);
vec_lim PHY_bounds_particle(PHY_shape s);
vec_lim PHY_bounds_rectangle(PHY_shape s);
vec_lim PHY_bounds_circle(PHY_shape s);

// Collision

u8 PHY_collision(PHY_shape a, PHY_shape b);
u8 PHY_collision_bounds(vec_lim a, vec_lim b);
u8 PHY_collision_particle(PHY_shape a, PHY_shape b);
u8 PHY_collision_rectangle(PHY_shape a, PHY_shape b);
u8 PHY_collision_rectangle_particle(PHY_shape a, PHY_shape b);
u8 PHY_collision_circle(PHY_shape a, PHY_shape b);
u8 PHY_collision_circle_particle(PHY_shape a, PHY_shape b);
u8 PHY_collision_circle_rectangle(PHY_shape a, PHY_shape b);

#endif
