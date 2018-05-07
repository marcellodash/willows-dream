/*
 * File Name: phys_mass.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

// Constructors

PHY_mass PHY_mass_init(f32 mass, f32 inertia) {
    PHY_mass m = PHY_Mass;

    if (mass < 0) mass = FIX32(0);
    if (inertia < 0) inertia = FIX32(0);

    m.mass = mass;
    m.inertia = inertia;

    if (mass == 0) m.inv_mass = FIX32(0);
    else m.inv_mass = fix32Div(FIX32(1), m.mass);

    if (inertia == 0) m.inv_mass = FIX32(0);
    else m.inv_mass = fix32Div(FIX32(1), m.inertia);

    return m;
}
