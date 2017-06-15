/*
 * File Name: phys.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef PHYS_H_
#define PHYS_H_

#include <genesis.h>

// Maths Tut: https://github.com/Stephane-D/SGDK/wiki/Tuto-Maths
// Maths Header: https://github.com/Stephane-D/SGDK/blob/master/inc/maths.h

#define PHY_TYPE_POINT 0
#define PHY_TYPE_RECT 1
#define PHY_TYPE_CIRCLE 2

/*
typedef struct {
    u8 type;

    Vect2D_f16 pos;
    Vect2D_f16 vel;
    Vect2D_f16 acc;

    fix16 mass;
    Vect2D_f16 size;
} PHY_entity;

u8 PHY_collision(PHY_entity a, PHY_entity b);
*/

#endif
