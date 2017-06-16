/*
 * File Name: phys.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "vec.h"
#include "phys.h"

// Bounds

vec_lim PHY_get_bounds(PHY_entity e) {
    switch (e->type) {
        case PHY_TYPE_RECT:
            PHY_bounds_rect(e);
            break;
        case PHY_TYPE_CIRCLE:
            PHY_bounds_cirlce(e);
            break;
    }

    return Vec_Lim;
}

vec_lim PHY_bounds_vec(vec v) {
    return VEC_LIM(v.x, v.y, v.x, v.y);
}

vec_lim PHY_bounds_point(PHY_entity e) {
    return PHY_bounds_vec(e.pos);
}

// TODO: Apply rotation to rectangle bounds?
vec_lim PHY_bounds_rect(PHY_rect e) {
    vec_lim b = Vec_Lim;

    b.min.x = (e.size.x >> 1) - e.pos.x;
    b.max.x = (e.size.x >> 1) + e.pos.x;

    b.min.y = (e.size.y >> 1) - e.pos.y;
    b.max.y = (e.size.y >> 1) + e.pos.y;

    return b;
}

vec_lim PHY_bounds_circle(PHY_circle e) {
    vec_lim b = Vec_Lim;

    b.min.x = e.radius - e.pos.x;
    b.max.x = e.radius + e.pos.x;

    b.min.y = e.radius - e.pos.y;
    b.max.y = e.radius + e.pos.y;

    return b;
}

// Collision Detection

u8 PHY_collision(PHY_entity a, PHY_entity b) {
    switch (a->type) {
        case PHYS_TYPE_POINT:
            switch (b->type) {
                case PHYS_TYPE_POINT:
                    return PHY_collision_point(a, b);
                    break;
                case PHYS_TYPE_RECT:
                    return PHY_collision_rect_point(b, a);
                    break;
                case PHYS_TYPE_CIRCLE:
                    return PHY_collision_circle_point(b, a);
                    break;
            }
            break;
        case PHYS_TYPE_RECT:
            switch (b->type) {
                case PHYS_TYPE_POINT:
                    return PHY_collision_rect_point(a, b);
                    break;
                case PHYS_TYPE_RECT:
                    return PHY_collision_rect(a, b);
                    break;
                case PHYS_TYPE_CIRCLE:
                    return PHY_collision_circle_rect(b, a);
                    break;
            }
            break;
        case PHYS_TYPE_CIRCLE:
            switch (b->type) {
                case PHYS_TYPE_POINT:
                    return PHY_collision_circle_point(a, b);
                    break;
                case PHYS_TYPE_RECT:
                    return PHY_collision_circle_rect(a, b);
                    break;
                case PHYS_TYPE_CIRCLE:
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

u8 PHY_collision_point(PHY_entity a, PHY_entity b, u8 approx = PHY_APPROX) {
    if (approx == TRUE) { // Pixel Approximation
        if (mToInt(a.pos.x) == mToInt(b.pos.x) && mToInt(a.pos.y) == mToInt(b.pos.y)) return TRUE;
    } else {
        if (a.pos.x == b.pos.x && a.pos.y == b.pos.y) return TRUE;
    }

    return FALSE;
}

u8 PHY_collision_rect(PHY_rect a, PHY_rect b) {
    return PHY_collision_bounds(PHY_bounds_rect(a), PHY_bounds_rect(b));
}
u8 PHY_collision_rect_point(PHY_rect a, PHY_entity b, u8 approx = PHY_APPROX) {
    vec_lim ab = PHY_bounds_rect(a);

    if (approx == TRUE) {
        u16 bx = mToInt(b.pos.x), by = mToInt(b.pos.y);
        if (mToInt(ab.min.x) > bx || mToInt(ab.max.x) < bx) return FALSE;
        if (mToInt(ab.min.y) > by || mToInt(ab.max.y) < by) return FALSE;
        return TRUE;
    }

    return PHY_collision_bounds(PHY_bounds_rect(a), PHY_bounds_point(b));
}

u8 PHY_collision_circle(PHY_circle a, PHY_circle b) {
    if (PHY_collision_bounds(PHY_bounds_circle(a), PHY_bounds_circle(b)) == FALSE) return FALSE;
    return fix32Add(a.radius, b.radius) < PHY_distance_sq(a.pos, b.pos);
}
u8 PHY_collision_circle_point(PHY_circle a, PHY_entity b) {
    if (PHY_collision_bounds(PHY_bounds_circle(a), PHY_bounds_point(b)) == FALSE) return FALSE;
    return a.radius < PHY_distance_sq(a.pos, b.pos);
}
// TODO: Rotation applied to rectangle? This only works with axis-aligned rectangles.
u8 PHY_collision_circle_rect(PHY_circle a, PHY_rect b) {
    // Get center distance
    Vect2D_f32 d = VECT2D(abs(fix32Sub(a.pos.x - b.pos.x)), abs(fix32Sub(a.pos.y - b.pos.y)));
    // Get half size of rectangle
    Vect2D_f32 bs = VECT2D(b.size.x >> 1, b.size.y >> 1);

    // If entities are not within axes
    if (d.x > bs.x + a.radius) return FALSE;
    if (d.y > bs.y + a.radius) return FALSE;

    // If circle is close enough that an intersection is guaranteed
    if (d.x <= bs.x) return TRUE;
    if (d.y <= bs.y) return TRUE;

    // If circle intersects corner
    return PHY_distance_sq(d, bs) <= a.radius * a.radius;

    /* Alternate Version (not complete)
    // 1. If objects are within axes
    if (PHY_collision_bounds(PHY_bounds_circle(a), PHY_bounds_rect(b)) == FALSE) return FALSE;
    // 2. If center of circle is within rectangle
    if (PHY_collision_bounds(PHY_bounds_vec(a.pos), PHY_bounds_rect(b)) == TRUE) return TRUE;
    // 3. If the distance of the circle to the nearest point of the rectangle
    // max, min, etc
    */
}

// Impulse Resolution

// TODO: Impulse physics
