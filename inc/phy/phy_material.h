/*
 * File Name: phy_material.h
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#ifndef PHY_MATERIAL_H_
#define PHY_MATERIAL_H_

typedef struct PHY_material {
    f32 density; // kg/m^3
    f32 restitution; // coefficient
    f32 friction_static; // coefficient
    f32 friction_dynamic; // coefficient
} PHY_material;
const struct PHY_Material = {
    FIX32(0), FIX32(0), FIX32(0), FIX32(0)
};
#define PHY_MATERIAL(d, r, fs, fd) PHY_material { d; r; fs; fd; }
#define PHY_MATERIAL_F32(d, r, fs, fd) PHY_material { FIX32(d); FIX32(r); FIX32(fs); FIX32(fd); }

// Material Defaults
#define PHY_MATERIAL_GLASS PHY_MATERIAL_F32(2600, 0.658, 0.95, 0.4)
#define PHY_MATERIAL_RUBBER PHY_MATERIAL_F32(1100, 0.828, 1, 0.5)
#define PHY_MATERIAL_WOOD PHY_MATERIAL_F32(530, 0.603, 0.5, 0.3)
#define PHY_MATERIAL_STEEL PHY_MATERIAL_F32(7820, 0.597, 0.55, 0.5)
#define PHY_MATERIAL_PLASTIC PHY_MATERIAL_F32(930, 0.688, 0.35, 0.3)
#define PHY_MATERIAL_STONE PHY_MATERIAL_F32(2550, 0.8, 0.3, 0.25)


// Constructors

PHY_material PHY_material_init(f32 density, f32 restitution);

#endif
