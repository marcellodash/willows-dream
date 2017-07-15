/*
 * File Name: phy_mass.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef PHY_MASS_H_
#define PHY_MASS_H_

#include <genesis.h>
#include "phy/phy.h"
#include "vec.h"

typedef struct PHY_mass {
    f32 mass;
    f32 inv_mass;
    f32 inertia;
    f32 inverse_inertia;
} PHY_mass;
const struct PHY_Mass = {
    FIX32(0), FIX32(0), FIX32(0), FIX32(0)
};

// Constructors

PHY_mass PHY_mass_init(f32 mass, f32 inertia);

#endif
