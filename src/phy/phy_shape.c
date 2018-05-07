/*
 * File Name: phys_shape.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

// Constructors

PHY_shape PHY_particle() {
    // Init basic entity
    PHY_shape e = PHY_Shape
    e.type = PHY_SHAPE_PARTICLE;
    return e;
}

PHY_shape PHY_rectangle(f32 width, f32 height) {
    // Init basic entity and set type
    PHY_shape e = PHY_particle();
    e.type = PHY_SHAPE_RECTANGLE;

    // Set constants
    e.dimensions = VEC(width, height);

    return e;
}

PHY_shape PHY_circle(f32 radius) {
    // Init basic entity and set type
    PHY_shape e = PHY_particle();
    e.type = PHY_SHAPE_CIRCLE;

    // Set constants
    e.radius = radius;

    return e;
}

// Bounds

vec_lim PHY_bounds(PHY_shape s) {
    vec_lim lim = Vec_Lim;

    switch (s.type) {
        case PHY_SHAPE_RECTANGLE:
            lim = PHY_bounds_rect(s);
            break;
        case PHY_SHAPE_CIRCLE:
            lim = PHY_bounds_circle(s);
            break;
        case PHY_SHAPE_PARTICLE:
            lim = PHY_bounds_particle(s);
            break;
    }

    return lim;
}

vec_lim PHY_bounds_vec(vec v) {
    return VEC_LIM(v.x, v.y, v.x, v.y);
}

vec_lim PHY_bounds_particle(PHY_shape s) {
    return PHY_bounds_vec(s.pos);
}

vec_lim PHY_bounds_rectangle(PHY_shape s) {
    vec_lim lim = Vec_Lim;

    lim.min.x = (s.dimensions.x >> 1) - s.pos.x;
    lim.max.x = (s.dimensions.x >> 1) + s.pos.x;

    lim.min.y = (s.dimensions.y >> 1) - s.pos.y;
    lim.max.y = (s.dimensions.y >> 1) + s.pos.y;

    return lim;
}

vec_lim PHY_bounds_circle(PHY_shape s) {
    vec_lim lim = Vec_Lim;

    lim.min.x = s.radius - s.pos.x;
    lim.max.x = s.radius + s.pos.x;

    lim.min.y = s.radius - s.pos.y;
    lim.max.y = s.radius + s.pos.y;

    return lim;
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
            switch (b->type) {
                case PHY_SHAPE_PARTICLE:
                    return PHY_collision_rectangle_particle(a, b);
                    break;
                case PHY_SHAPE_RECTANGLE:
                    return PHY_collision_rectangle(a, b);
                    break;
                case PHY_SHAPE_CIRCLE:
                    return PHY_collision_circle_rectangle(b, a);
                    break;
            }
            break;
        case PHY_SHAPE_CIRCLE:
            switch (b->type) {
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
    if (mToInt(a.pos.x) == mToInt(b.pos.x) && mToInt(a.pos.y) == mToInt(b.pos.y)) return TRUE;

    return FALSE;
}

u8 PHY_collision_rectangle(PHY_shape a, PHY_shape b) {
    return PHY_collision_bounds(PHY_bounds_rectangle(a), PHY_bounds_rectangle(b));
}

u8 PHY_collision_rectangle_particle(PHY_shape a, PHY_shape b) {
    vec_lim ab = PHY_bounds_rectangle(a);

    u16 bx = mToInt(b.pos.x), by = mToInt(b.pos.y);

    if (mToInt(ab.min.x) > bx || mToInt(ab.max.x) < bx) return FALSE;
    if (mToInt(ab.min.y) > by || mToInt(ab.max.y) < by) return FALSE;

    return TRUE;
}

u8 PHY_collision_circle(PHY_shape a, PHY_shape b) {
    if (PHY_collision_bounds(PHY_bounds_circle(a), PHY_bounds_circle(b)) == FALSE) return FALSE;
    return fix32Add(a.radius, b.radius) < VEC_dist_sq(a.pos, b.pos);
}

u8 PHY_collision_circle_particle(PHY_shape a, PHY_shape b) {
    if (PHY_collision_bounds(PHY_bounds_circle(a), PHY_bounds_particle(b)) == FALSE) return FALSE;
    return a.radius < VEC_dist_sq(a.pos, b.pos);
}

u8 PHY_collision_circle_rectangle(PHY_shape a, PHY_shape b) {
    // Get center distance
    Vect2D_f32 d = VECT2D(abs(fix32Sub(a.pos.x - b.pos.x)), abs(fix32Sub(a.pos.y - b.pos.y)));
    // Get half size of rectangle
    Vect2D_f32 bs = VECT2D(b.dimensions.x >> 1, b.dimensions.y >> 1);

    // If entities are not within axes
    if (d.x > bs.x + a.radius) return FALSE;
    if (d.y > bs.y + a.radius) return FALSE;

    // If circle is close enough that an intersection is guaranteed
    if (d.x <= bs.x) return TRUE;
    if (d.y <= bs.y) return TRUE;

    // If circle intersects corner
    return VEC_dist_sq(d, bs) <= a.radius * a.radius;

    /* Alternate Version (not complete)
    // 1. If objects are within axes
    if (PHY_collision_bounds(PHY_bounds_circle(a), PHY_bounds_rect(b)) == FALSE) return FALSE;
    // 2. If center of circle is within rectangle
    if (PHY_collision_bounds(PHY_bounds_vec(a.pos), PHY_bounds_rect(b)) == TRUE) return TRUE;
    // 3. If the distance of the circle to the nearest point of the rectangle
    // max, min, etc
    */
}
