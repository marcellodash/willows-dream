/*
 * File Name: main.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "audio.h"
#include "scene.h"
#include "scenes.h"

int main() {
    // Setup Screen
    SYS_disableInts(); // Disable interrupt when accessing VDP
    VDP_setScreenWidth320(); // Screen Initialization
    SYS_enableInts(); // VDP process done, we can re-enable interrupts

    AUD_init(); // Initialize Audio
    JOY_init(); // Initialize Joystick

    SCN_loadScene(&SCN_title);

    while (1) {
        SCN_updateScene();
        VDP_waitVSync(); // Wait for screen refresh
    }

    SCN_cleanScene();

    return 0;
}
