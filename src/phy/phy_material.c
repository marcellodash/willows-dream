/*
 * File Name: phys_material.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

// Constructors

PHY_material PHY_material_init(f32 density, f32 restitution) {
    PHY_material m = PHY_Material;
    m.density = density;
    m.restitution = restitution;
    return m;
}
