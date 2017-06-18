/*
 * File Name: phys.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "vec.h"
#include "phy.h"

// Entity

PHY_entity PHY_init_entity(f32 mass, f32 restitution) {
    // Init basic entity
    PHY_entity e = PHY_Entity;

    // Set constants
    e.mass = mass;
    e.restitution = restitution;

    // Calculate constants
    if (e.mass == 0)
        e.inv_mass = 0;
    else
        e.inv_mass = fix32Div(FIX32(1), e.mass);

    return e;
}
PHY_rect PHY_init_rect(f32 mass, f32 restitution, vec size) {
    // Init basic entity and cast to struct
    PHY_rect e = *((PHY_rect*) &PHY_init_entity(mass, restitution));

    // Set constants
    e.size = size;

    return e;
}
PHY_circle PHY_init_circle(Sprite spr, f32 mass, f32 restitution, f32 radius) {
    // Init basic entity and cast to struct
    PHY_circle e = *((PHY_circle*) &PHY_init_entity(mass, restitution));

    // Set constants
    e.radius = radius;

    return e;
}

// Bounds

vec_lim PHY_bounds(PHY_entity e) {
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

vec PHY_momentum(PHY_entity e) {

}
f32 PHY_impulse(PHY_entity a, PHY_entity b) {

}
u8 PHY_resolve(PHY_entity *a, PHY_entity *b) {
    // Relative velocity
    vec rv = VEC_sub(b->vel, a->vel);

    // Relative velocity along normal direction
    vec normal = VEC_left(a->vel); // normal?
    f32 nv = VEC_dot(rv, normal);

    // Do not resolve if velocities are separating
    if (nv > 0) return FALSE;

    // Calculate restitution/elasticity
    f32 e = min(a->restitution, b->restitution);

    // Calculate impulse scalar
    f32 j = fix32Mul(fix32Mul(FIX32(-1), fix32Add(FIX32(1), e)), nv);
    j = fix32Div(j, fix32Add(a.inv_mass, b.inv_mass);

    // Apply impulse including mass ratio
    f32 mass_sum = a->mass + b->mass;
    f32 ratio = fix32Div(a->mass, mass_sum);
    vec impulse = VEC_scalar_mul(normal, j);
    a->vel = VEC_sub(a->vel, VEC_scalar_mul(impulse, fix32Mul(a.inv_mass, ratio)));
    ratio = fix32Div(b->mass, mass_sum);
    b->vel = VEC_add(b->vel, VEC_scalar_mul(impulse, fix32Mul(b.inv_mass, ratio)));

    return TRUE;
}

void VEC_positional_correction(PHY_entity *a, PHY_entity *b) {
    // f32 penetrationDepth?
    // Scale penetration depth by the total mass of the system
    f32 correctionAmount = fix32Div(max(fix32Sub(penetrationDepth, PHY_POS_CORRECTION_SLOP), FIX32(0)), fix32Add(a->inv_mass, b->inv_mass));
    // Apply correction percentage
    correctionAmount = VEC_scalar_mul(correctionAmount, PHY_POS_CORRECTION_PERC);
    // Apply along normal
    vec correction = VEC_mul(correctionAmount, n);

    a->pos = VEC_sub(a->pos, VEC_scalar_mul(correction, a->inv_mass));
    b->pos = VEC_add(b->pos, VEC_scalar_mul(correction, b->inv_mass));
}

// Manifold Generation

u8 PHY_manifold_circle_circle(PHY_manifold *m) {
    PHY_circle *a = m->a;
    PHY_circle *b = m->b;

    // Vector from a to b
    vec n = VEC_sub(b->pos, a->pos);

    f32 r = fix32Add(a->radius, b->radius);
    f32 d = VEC_len_sq(n);
    if (len > fix32Mul(r, r)) return FALSE;

    // Circles have collided, compute manifold

    // Perform sqrt for length only when colliding/necessary
    d = fix16ToFix32(fix16Sqrt(fix32ToFix16(n)));

    if (dist != 0) { // If distance between circles is not zero
        m->penetration = fix32Sub(r, d);
        m->normal = VEC_scalar_div(n, d);
    } else { // Circles are on same position
        // Choose random (but consistent) values
        m->penetration = a->radius;
        m->normal = VEC2D(1, 0);
    }

    return TRUE;
}

u8 PHY_manifold_rect_rect(PHY_manifold *m) {
    PHY_rect *a = m->a;
    PHY_rect *b = m->b;

    // Vector from a to b
    vec n = VEC_sub(b->pos, a->pos);

    vec_lim a_bounds = PHY_bounds_rect(&a);
    vec_lim b_bounds = PHY_bounds_rect(&b);

    // Calculate half extents along x axis for each object
    vec a_extent = Vec, b_extent = Vec;
    a_extent.x = fix32Sub(a_bounds.max.x, a_bounds.min.x) >> 1;
    b_extent.x = fix32Sub(b_bounds.max.x, b_bounds.min.x) >> 1;

    // Calculate overlap on x axis
    f32 x_overlap = fix32Sub(fix32Add(a_extent.x, b_extent.x), abs(n.x));

    // SAT test on x axis
    if (x_overlap <= 0) return FALSE;

    // Calculate half extents along y axis for each object
    a_extent.y = fix32Sub(a_bounds.max.y, a_bounds.min.y) >> 1;
    b_extent.y = fix32Sub(b_bounds.max.y, b_bounds.min.y) >> 1;

    f32 y_overlap = fix32Sub(fix32Add(a_extent.y, b_extent.y), abs(n.y));

    // SAT test on y axis
    if (y_overlap <= 0) return FALSE;

    // Find out which axis is axis of least penetration
    if (x_overlap > y_overlap) {
        if (n.x < 0)
            m->normal = VEC_F32(-1, 0);
        else
            m->normal = VEC_F32(1, 0);
        m->penetration = x_overlap;
    } else {
        if (n.y < 0)
            m->normal = VEC_F32(0, -1);
        else
            m->normal = VEC_F32(0, 1);
        m->penetration = y_overlap;
    }

    return TRUE;
}

u8 PHY_manifold_circle_rect(PHY_manifold *m) {
    PHY_circle *a = m->a;
    PHY_rect *b = m->b;

    // Vector from A to B
    vec n = b->pos - a->pos;

    // Closest point on A to center of B
    vec closest = n;

    // Calculate half extents along each axis
    vec_lim b_bounds = PHY_bounds_rect(&b);
    vec b_extents = VEC2D(fix32Sub(b_bounds.max.x, b_bounds.min.x) >> 1, fix32Sub(b_bounds.max.y, b_bounds.min.y) >> 1);

    // Clamp point to edgest of the rectangle
    closest.x = clamp(closest.x, fix32Mul(b_extents.x, -1), b_extents.x);
    closest.y = clamp(closest.y, fix32Mul(b_extents.y, -1), b_extents.y);

    u8 inside = FALSE;

    // Circle is inside the rectangle, so we need to clamp the circle's center to the closest edge
    if (n == closest) {
        inside = TRUE;

        // Find closest axis
        if (abs(n.x) > abs(n.y)) {
            // Clamp to closest extents
            if (closest.x > 0)
                closest.x = b_extents.x;
            else
                closest.x = -b_extents.x;
        } else { // Y axis is shorter
            // Clamp to closest extent
            if (closest.y > 0)
                closest.y = b_extents.y;
            else
                closest.y = fix32Mul(b_extents.y, FIX32(-1));
        }
    }

    vec normal = VEC_sub(n, closest);
    f32 d = VEC_len_sq(normal);
    f32 r = a->radius;

    // If the radius is shorter than distance to closest point, circle is not inside the rectangle
    if (d > fix32Mul(r, r) && inside == FALSE) return FALSE;

    // Avoided sqrt until necessary
    d = fix16ToFix32(fix16Sqrt(fix32ToFix16(d)));

    // Collision normal needs to be flipped to point outside if circle was inside the rectangle
    if (inside == TRUE) {
        m->normal = VEC_scalar_mul(n, FIX32(-1));
    } else {
        m->normal = n;
    }

    m->penetration = fix32Sub(r, d);

    return TRUE;
}

// Core Functions

u8 PHY_update(PHY_entity e) {

}
