/*
 * File Name: scene.c
 * . . . .-. .   .   .-. . . . `' .-.   .-. .-. .-. .-. .  .
 * | | |  |  |   |   | | | | | `' `-.   |  )|(  |-  |-| |\/|
 * `.'.' `-' `-' `-' `-' `.'.'    `-'   `-' ' ' `-' ` ' '  `
 */

#include <genesis.h>
#include "scene.h"
#include "joy.h"

void SCN_loadScene(Scene *scene) {
    if ((SCN_active)) SCN_cleanScene();
    SCN_counter = 0;

    if ((SCN_active = scene)) {
        // Basic reset for VDP graphics functionality
        SYS_disableInts();
        VDP_resetSprites();
        if ((SCN_active->load)) SCN_active->load();
        SYS_enableInts(); // Re-enable Interrupts

        if ((SCN_active->init)) SCN_active->init();

        JOY_setEventHandler(&SCN_joyHandler);
    }
}

void SCN_joyHandler(u16 joy, u16 changed, u16 state) {
    if (!(SCN_active)) return;

    JOY_inputHandler(joy, changed, state); // General joystick input actions
    if ((SCN_active->joy)) SCN_active->joy(joy, changed, state); // Scene specific joystick input actions
}

void SCN_updateScene() {
    if (!(SCN_active)) return;

    if ((SCN_active->input)) SCN_active->input();
    if ((SCN_active->updateLogic)) SCN_active->updateLogic();
    if ((SCN_active->updateGfx)) SCN_active->updateGfx();

    SCN_counter++;
}

void SCN_cleanScene() {
    if (!(SCN_active)) return;

    JOY_setEventHandler(NULL);
    if ((SCN_active->clean)) SCN_active->clean();
    SCN_active = NULL;
}
