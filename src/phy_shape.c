/*
 * File Name: phys.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "vec.h"
#include "phy/phy.h"
#include "phy/phy_shape.h"

// Constructors

PHY_shape PHY_particle() {
    PHY_shape s = PHY_Shape;
    s.type = PHY_SHAPE_PARTICLE;
    return s;
}
PHY_shape PHY_rectangle(f32 width, f32 height) {
    PHY_shape s = PHY_Shape;
    s.type = PHY_SHAPE_RECTANGLEANGLE;
    s.size = VEC_F32(width, height);
    return s;
}
PHY_shape PHY_circle(f32 radius) {
    PHY_shape s = PHY_Shape;
    s.type = PHY_SHAPE_CIRCLE;
    s.radius = radius;
    return s;
}

// Bounds

vec_lim PHY_bounds(PHY_shape s) {
    switch (s.type) {
        case PHY_SHAPE_PARTICLE:
            return PHY_bounds_particle(s);
            break;
        case PHY_SHAPE_RECTANGLE:
            return PHY_bounds_rectangle(s);
            break;
        case PHY_SHAPE_CIRCLE:
            return PHY_bounds_circle(s);
            break;
    }

    return Vec_Lim;
}
vec_lim PHY_bounds_vec(vec v) {
    return VEC_LIM(v.x, v.y, v.x, v.y);
}
vec_lim PHY_bounds_particle(PHY_shape s) {
    return PHY_bounds_vec(s.pos);
}
vec_lim PHY_bounds_rectangle(PHY_shape s) {
    vec_lim b = Vec_Lim;

    b.min.x = (s.size.x >> 1) - s.pos.x;
    b.max.x = (s.size.x >> 1) + s.pos.x;

    b.min.y = (s.size.y >> 1) - s.pos.y;
    b.max.y = (s.size.y >> 1) + s.pos.y;

    return b;
}
vec_lim PHY_bounds_circle(PHY_shape s) {
    vec_lim b = Vec_Lim;

    b.min.x = s.radius - s.pos.x;
    b.max.x = s.radius + s.pos.x;

    b.min.y = s.radius - s.pos.y;
    b.max.y = s.radius + s.pos.y;

    return b;
}

// Collision

u8 PHY_collision(PHY_shape a, PHY_shape b) {
    switch (a.type) {
        case PHY_SHAPE_PARTICLE:
            switch (b.type) {
                case PHY_SHAPE_PARTICLE:
                    return PHY_collision_particle(a, b);
                    break;
                case PHY_SHAPE_RECTANGLE:
                    return PHY_collision_rectangle_particle(b, a);
                    break;
                case PHY_SHAPE_CIRCLE:
                    return PHY_collision_circle_particle(b, a);
                    break;
            }
            break;
        case PHY_SHAPE_RECTANGLE:
            switch (b.type) {
                case PHY_SHAPE_PARTICLE:
                    return PHY_collision_rectangle_particle(a, b);
                    break;
                case PHY_SHAPE_RECTANGLE:
                    return PHY_collision_rectangle(a, b);
                    break;
                case PHY_SHAPE_CIRCLE:
                    return PHY_collision_circle_rect(b, a);
                    break;
            }
            break;
        case PHY_SHAPE_CIRCLE:
            switch (b.type) {
                case PHY_SHAPE_PARTICLE:
                    return PHY_collision_circle_particle(a, b);
                    break;
                case PHY_SHAPE_RECTANGLE:
                    return PHY_collision_circle_rectangle(a, b);
                    break;
                case PHY_SHAPE_CIRCLE:
                    return PHY_collision_circle(a, b);
                    break;
            }
            break;
    }

    return FALSE;
}
u8 PHY_collision_bounds(vec_lim a, vec_lim b) {
    if (a.max.x < b.min.x || a.min.x > b.max.x) return FALSE;
    if (a.max.y < b.min.y || a.min.y > b.max.y) return FALSE;

    return TRUE;
}
u8 PHY_collision_particle(PHY_shape a, PHY_shape b) {
    if (PHY_APPROX == TRUE) { // Pixel Approximation
        if (mToInt(a.pos.x) == mToInt(b.pos.x) && mToInt(a.pos.y) == mToInt(b.pos.y)) return TRUE;
    } else {
        if (a.pos.x == b.pos.x && a.pos.y == b.pos.y) return TRUE;
    }

    return FALSE;
}
u8 PHY_collision_rectangle(PHY_shape a, PHY_shape b) {
    return PHY_collision_bounds(PHY_bounds_rectangle(a), PHY_bounds_rectangle(b));
}
u8 PHY_collision_rectangle_particle(PHY_shape a, PHY_shape b) {
    vec_lim ab = PHY_bounds_rectangle(a);

    if (PHY_APPROX == TRUE) {
        u16 bx = mToInt(b.pos.x), by = mToInt(b.pos.y);
        if (mToInt(ab.min.x) > bx || mToInt(ab.max.x) < bx) return FALSE;
        if (mToInt(ab.min.y) > by || mToInt(ab.max.y) < by) return FALSE;
        return TRUE;
    }

    return PHY_collision_bounds(ab, PHY_bounds_particle(b));
}
u8 PHY_collision_circle(PHY_shape a, PHY_shape b) {
    if (PHY_collision_bounds(PHY_bounds_circle(a), PHY_bounds_circle(b)) == FALSE) return FALSE;
    f32 r = fix32Add(a.radius, b.radius);
    return fix32Mul(r, r) < PHY_distance_sq(a.pos, b.pos);
}
u8 PHY_collision_circle_particle(PHY_shape a, PHY_shape b) {
    if (PHY_collision_bounds(PHY_bounds_circle(a), PHY_bounds_particle(b)) == FALSE) return FALSE;
    return fix32Mul(a.radius, a.radius) < PHY_distance_sq(a.pos, b.pos);
}
u8 PHY_collision_circle_rectangle(PHY_shape a, PHY_shape b) {
    // Get center distance
    vec d = VEC_abs(VEC_sub(a, b));
    // Get half size of rectangle
    vec bs = VEC_bitr(b.size, 1);

    // If entities are not within axes
    if (d.x > fix32Add(bs.x, a.radius)) return FALSE;
    if (d.y > fix32Add(bs.y, a.radius)) return FALSE;

    // If circle is close enough that an intersection is guaranteed
    if (d.x <= bs.x) return TRUE;
    if (d.y <= bs.y) return TRUE;

    // If circle intersects corner
    return PHY_distance_sq(d, bs) <= a.radius * a.radius;
}
