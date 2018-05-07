/*
 * File Name: phys.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "vec.h"
#include "phy.h"

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

u8 PHY_update(PHY_entity *bodies) {
    u8 i;
    u8 body_count = sizeof(bodies) / sizeof(PHY_entity);
    if (body_count <= 0 || body_count == NULL) return FALSE;

    // Handle collisions
    PHY_pair* pairs = PHY_generatePairs(bodies);
    u8 pair_count = sizeof(pairs) / sizeof(PHY_pair);
    for (i = 0; i < pair_count; i++) {
        PHY_resolve(pairs[i]->a, pairs[i]->b);
        //PHY_positional_correction(pairs[i]->a, pairs[i]->b);
    }

    // Handle positions/velocities
    for (i = 0; i < body_count; i++) {
        // Symplectic Euler
        e->vel = VEC_add(e->vel, VEC_scalar_mul(e->force, fix32Mul(e->mass.inv_mass, PHY_TIMESTEP)));
        e->pos = VEC_add(e->pos, VEC_scalar_mul(e->vel, PHY_TIMESTEP));
    }

    return TRUE;
}

PHY_pair* PHY_generatePairs(PHY_entity *bodies) {

    u8 pair_count = 0;
    PHY_pair *pairs = (PHY_pair*)malloc(pair_count * sizeof(PHY_pair));

    u8 i, j, k, dupe;
    u8 body_count = sizeof(bodies) / sizeof(PHY_entity);

    for (i = 0; i < body_count; i++) {
        for (j = 0; j < body_count; j++) {
            // Skip check with self
            if (i == j) continue;

            PHY_entity *a = bodies[i];
            PHY_entity *b = bodies[j];

            // Only matching layers will be considered
            if (!(a->layers & b->layers)) continue;

            // Cull duplicates
            dupe = FALSE
            for (k = 0; k < pair_count; k++) {
                if (pairs[k]->a == a && pairs[k] == b) {
                    dupe = TRUE;
                    break;
                }
            }
            if (dupe == TRUE) continue;

            if (PHY_collision(a->shape, b->shape)) {
                pair_count++;
                pairs = (PHY_pair*)malloc(pair_count * sizeof(PHY_pair));
                pairs[pair_count - 1] = PHY_PAIR(a, b);
            }
        }
    }

    return pairs;
}
